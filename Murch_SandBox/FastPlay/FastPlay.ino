
#include <SdFat.h>


const uint8_t SD_CHIP_SELECT = 24;


bool gModoDebug = true;


#define SD_MAX_TENTATIVA_READ 6
#define SD_DELAY_TENTATIVA_READ 5000



#define BANCO_RET_MAX_CHOPPS 50



// Loga uma informacao no terminal
void LogTerm (String Texto)
{
	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}


// Loga uma informacao no terminal - OVERRIDE int
void LogTerm (int Texto)
{
	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}


// Loga uma informacao no terminal - OVERRIDE int
void LogTerm (unsigned long Texto)
{
	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}

// Loga uma informacao no terminal - OVERRIDE int
void LogTerm (double Texto)
{

	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}



String CharFromAsc2(int Asc2Value)
{
    char ret;

    ret = Asc2Value;

    return String(ret);
}




// retorna formato: CodRetorno|descricao
// Param byref: LetorSD - retora o objeto passado, leitor SD
// 1 para a funcao rodou certo 
// -1 erros outros
String SD_InicializaCartaoSD(SdFat &LeitorSD)
{

	String ret = F("1|SD Inicializado");

	int ContaTentativa = 0;
	bool SucessoTentativa = false;


	// not over 50 MHz. Try a lower speed if SPI errors occur.
	if (!LeitorSD.begin(SD_CHIP_SELECT, SPI_SIXTEENTH_SPEED))
	{
		LogTerm(F("SD: Falha na inicializacao do cartao SD"));

		while ((ContaTentativa <= SD_MAX_TENTATIVA_READ) && (SucessoTentativa == false))
		{	
			LogTerm(F("SD: Realizando nova tentativa..."));
			delay(SD_DELAY_TENTATIVA_READ);

			if (LeitorSD.begin(SD_CHIP_SELECT, SPI_SIXTEENTH_SPEED))
			{
				SucessoTentativa = true;
			}

			ContaTentativa++;

		}


		ret = F("-1|Falha na inicializacao do cartao SD");

		return ret;	
	}

	return ret;
}




// retorna formato: CodRetorno|descricao
// Param byref: LetorSD - retora o objeto passado, leitor SD
// 1 para a funcao rodou certo 
// -1 erros outros
String SD_AbreArqTexto(String FullPathFile, SdFat &LeitorSD, File &objArquivo)
{

	String ret = F("1|Arquivo Aberto");

	int ContaTentativa = 0;
	bool SucessoTentativa = false;




	objArquivo = LeitorSD.open(FullPathFile, FILE_READ);

	if (!objArquivo) 
	{
		LogTerm(String(F("SD: Falha na abertura do arquivo: ")) + FullPathFile);


		while ((ContaTentativa <= SD_MAX_TENTATIVA_READ) && (SucessoTentativa == false))
		{
			LogTerm(F("SD: Realizando nova tentativa..."));
			delay(SD_DELAY_TENTATIVA_READ);

			objArquivo = LeitorSD.open(FullPathFile, FILE_READ);

			if (objArquivo) 
			{
				SucessoTentativa = true;

				return ret;	
			}


			ContaTentativa++;

		}


		ret = String(F("-1|Falha na abertura do arquivo: ")) + FullPathFile;

		return ret;	

	}

	return ret;
}

// retorna formato: CodRetorno|descricao
// Param byref: aRetRegs - contera todos os registros do arquivo, se existirem
// 1 para a funcao rodou certo 
// -1 erros outros
String SD_GetAllRegsFromFile(String FullPathFile, String aRetRegs[], int MaxSizeRetArray)
{



	

	String ret = F("1|");

	String buff =F("");

	int ContaEnter = 0;

	int CharAtual;


	//int ContaTentativa = 0;
	//bool SucessoTentativa = false;

	SdFat SD;
	String retSD = F("");

	retSD = SD_InicializaCartaoSD(SD);

	if (retSD.substring(0, 1) != F("1"))
	{
		return retSD;
	}



	File file;
	String retFile = F("");

	retFile = SD_AbreArqTexto(FullPathFile, SD, file);

	if (retFile.substring(0, 1) != F("1"))
	{
		return retFile;
	}
	else
	{

		LogTerm(String(F("SD: Arquivo aberto com sucesso: ")) + FullPathFile);
		

		int ContaReg = 0; 

		while (file.available()) 
		{
			//LogTerm(file.read());

			CharAtual = file.read();

			if (CharAtual == 13)
			{
				ContaEnter++;
			}
			
			if (ContaEnter >= 1)
			{

				switch (CharAtual) 
				{
					case 10:

						//tft.fillRoundRect(Botao_PosAtual_X, Botao_PosAtual_Y, Size_Botao_W, Size_Botao_H, 10, RA8875_GREEN);
						break;

					case 13:

						ContaReg++;
						break;

					default:

						if (ContaReg <= MaxSizeRetArray)
						{
							aRetRegs[ContaReg - 1] += CharFromAsc2(CharAtual);
						}
						
						break;
				}


				
			}

			//Serial.write(CharAtual);
			//Serial.println(CharAtual);

			//LogTerm(CharAtual);
			
		}		

	}

	file.close();

	return ret;


}





String SD_GetFirstRegFromFile(String FullPathFile)
{



	String ret = F("1|");

	String buff = F("");

	int ContaEnter = 0;

	int CharAtual;






	SdFat SD;
	String retSD = F("");

	retSD = SD_InicializaCartaoSD(SD);

	if (retSD.substring(0, 1) != F("1"))
	{
		return retSD;
	}



	File file;
	String retFile = F("");

	retFile = SD_AbreArqTexto(FullPathFile, SD, file);

	if (retFile.substring(0, 1) != F("1"))
	{
		return retFile;
	}
	else
	{

		if (gModoDebug == true)
		{
			LogTerm(String(F("SD: Arquivo aberto com sucesso: ")) + FullPathFile);
		}
		

		while (file.available()) 
		{
			//LogTerm(file.read());

			CharAtual = file.read();

			if (CharAtual == 13)
			{
				ContaEnter++;
			}
			
			if (ContaEnter >= 1)
			{
				if ((CharAtual != 10) && (CharAtual != 13))
				{
					ret += CharFromAsc2(CharAtual);

					//LogTerm(CharAtual);
					//Serial.write(CharAtual);
				}
				
			}

			//Serial.write(CharAtual);
			//Serial.println(CharAtual);

			//LogTerm(CharAtual);
			
		}		

	}

	file.close();

	return ret;
}








// verifica se um arquivo existe
// retorna formato: CodRetorno|Descricao
// 1 arq existe
// 0 arq nao existe
// -1 e -2 erros outros
String SD_FileExists(String FullPathFile)
{
	String ret = F("");
	



	SdFat SD;
	String retSD = F("");

	FullPathFile = F("CB/BD/Chopp/Chopps.txt");

	String FullPathDirFile = F("CB/BD/Chopp");


	retSD = SD_InicializaCartaoSD(SD);

	if (retSD.substring(0, 1) != F("1"))
	{
		ret = retSD;
		return ret;
	}

	ret = F("0|Arquivo NAO Existe");

	//SdBaseFile dir;
	//SdFat dir;

	/*
	if (!dir.open(FullPathDirFile, O_READ))
	{
		Serial.println("bad dir");
		return;
	}
	*/


	

	SD.chdir("CB/BD/Chopp");

	if (SD.exists("Chopps.txt"))
	{
		LogTerm("Chopps1 Existe");
	}
	else
	{
		LogTerm("Chopps1 nao Existe");
	}
	

	delay(1000);

	SD.chdir("/");

	if (SD.exists("i.bmp"))
	{
		LogTerm("i.bmp Existe");
	}
	else
	{
		LogTerm("i.bmp nao Existe");
	}
	

	ret = "xxx";



	return ret;
}




uint16_t rgb565_from_triplet(uint8_t red, uint8_t green, uint8_t blue)
{
  red   >>= 3;
  green >>= 2;
  blue  >>= 3;
  return (red << 11) | (green << 5) | blue;
}






#define BANCO_RET_MAX_CHOPPS 50





// recupera os dados (linha) de um ou mais IDs de uma vez. tenho de indicar quais os ids e qual a posicao que o ID solicitado se enconta e o arquivo a ser lido
// retorna formato: CodRetorno|Descricao
// 1 retorna a linha com dados do chopp
// -2 para chopp nao existe. 
// -1 erros outros
String BANCO_GetDataFromIDs(String TipoDado, String IDsDesejados, String aRetData[])
{
	String ret = F("1|");
	
	String retFunc = F("");

	String FullPathFile = F("");
	int PosicaoID = -1;
	int MaxRegs = -1;

	String aTemp_Chopp[BANCO_RET_MAX_CHOPPS];



	if (TipoDado == F("CHOPP"))
	{
		FullPathFile = F("CB/BD/Chopp/Chopps.txt");
		PosicaoID = 0;
		MaxRegs = BANCO_RET_MAX_CHOPPS;
	}

	retFunc = SD_GetAllRegsFromFile(FullPathFile, aTemp_Chopp, MaxRegs);


	if ((retFunc.substring(0, 2) == F("-1")) || (retFunc.substring(0, 2) == F("-2")))
	{
		// erro de sd card
		ret = retFunc;
		return ret;
	}

	if (retFunc.substring(0, 1) == F("1"))
	{
		// dados do arquivo lidos

		for (int x=0 ; x <= BANCO_RET_MAX_CHOPPS ; x++)
		{

		}

		ret = retFunc;
		return ret;

	}


	return ret;
}





// retorna formato: CodRetorno|descricao
// Param byref: aRetChoppsEngat contera a lista de chopps engatados, se exitirem
// 1 para a funcao rodou certo 
// -1 e -2 erros outros
String BANCO_DefineChoppEngatados(String aRetChoppsEngat[])
{

	String ret = F("1");

	String retFunc = F("");

	String FullPathFile_Engatados = F("");

	String IDsChoppDesejados = F("");

	FullPathFile_Engatados = F("CB/BD/Chopp/Engatados.txt");

	// inicializa var de engatados
	for (int x = 0 ; x <= ctMAX_TORNEIRAS ; x++)
	{
		aRetChoppsEngat[x] = F("");
	}	


	retFunc = SD_GetAllRegsFromFile(FullPathFile_Engatados, aRetChoppsEngat, ctMAX_TORNEIRAS);

	if ((retFunc.substring(0, 2) == F("-1")) || (retFunc.substring(0, 2) == F("-2")))
	{
		// erro de sd card
		ret = retFunc;
		return ret;
	}

	if (retFunc.substring(0, 1) == F("1"))
	{

		

		// recupera o nome e preco de cada chopp
		for (int x = 0 ; x <= ctMAX_TORNEIRAS ; x++)
		{
			if (aRetChoppsEngat[x] != F(""))
			{
				String temp_IDChopp = F("");

				temp_IDChopp = getValue(aRetChoppsEngat[x], ';', 2);
				//LogTerm("x = "+ String(x) + " | temp_IDChopp = " + temp_IDChopp);


				IDsChoppDesejados += temp_IDChopp + String(F(","));

			}
		}	 	


		if (Right(IDsChoppDesejados, 1) == String(F(",")))
		{
			IDsChoppDesejados = Left(IDsChoppDesejados, IDsChoppDesejados.length() - 1);
		}

		LogTerm(String(F("IDsChoppDesejados = ")) + IDsChoppDesejados);


		String aChopps[BANCO_RET_MAX_CHOPPS];

		retFunc = BANCO_GetDataFromIDs(F("CHOPP"), IDsChoppDesejados, aChopps);

		for (int x = 0 ; x <= BANCO_RET_MAX_CHOPPS ; x++)
		{
			if (aChopps[x] != F(""))
			{
				LogTerm(String(F("aChopps[")) + String(x) + String(F("] = ")) + aChopps[x]);
			}
		}

		

		ret = retFunc;
		return ret;

	}

	return ret;
}





// recupera os dados de um usuario, usando o IDUser como parametro
// retorna formato: CodRetorno|Descricao
// 1 retorna a linha com dados do usuario
// -2 para usuario nao existe. 
// -1 erros outros
String BANCO_GetUserDataFromIDUser(String IDUser)
{

	String ret = F("1|");

	String FullPathFile_User = F("");


	FullPathFile_User = String(F("CB/BD/Usuarios/USU_")) + IDUser + String(F(".txt"));
	//FullPathFile_User = "CB/BD/Usuarios/USU_" + IDUser + ".txt";


	String retFunc = F("");

	retFunc = SD_GetFirstRegFromFile(FullPathFile_User, "CHECK");

	if (retFunc.substring(0, 2) == F("-1"))
	{
		// erro de sd card
		ret = retFunc;
		return ret;
	}

	if (retFunc.substring(0, 2) == F("-2"))
	{
		// erro de usuario nao existe
		ret = "0|"+ retFunc.substring(3);
		return ret;
	}

	if (retFunc.substring(0, 1) == F("1"))
	{
		// usuaario encontrado. Retornando todos os dados do usuario (linha)
		ret = retFunc;
		return ret;

	}

	return ret;
}


// retorna formato: CodRetorno|Descricao
// 0 para arquivo nao existe
// 1 para arquivo existe. retona os dados do usuario
// -1 erros outros
String BANCO_GetIDUserFromLogin(String Login, String TipoLogin)
{

	String ret = F("1|");

	String FullPathFile_Login = F("");



	if (TipoLogin == F("RFID"))
	{

		FullPathFile_Login = String(F("CB/BD/Logins/RFID/")) + Login + String(F(".txt"));


		String retFunc = F("");

		retFunc = SD_GetFirstRegFromFile(FullPathFile_Login, "CHECK");

		if (retFunc.substring(0, 2) == F("-1"))
		{
			// erro de sd card
			ret = retFunc;
			return ret;
		}

		if (retFunc.substring(0, 2) == F("-2"))
		{
			// erro de login nao existe
			ret = "0|"+ retFunc.substring(3);
			return ret;
		}

		if (retFunc.substring(0, 1) == F("1"))
		{
			// login encontrado. Retornando IDUser

			String temp_IDUser = getValue(retFunc.substring(2), ';', 0);

			ret = String(F("1|")) + temp_IDUser;
			return ret;

		}


	}

	if (TipoLogin == F("BIO"))
	{
		
	}

	delay(100);

	return ret;
}





// retorna formato: CodRetorno|Descricao
// 1 retorna a linha com dados do chopp
// -2 para chopp nao existe. 
// -1 erros outros
String BANCO_GetChoppDataFromIDChopp(String IDChopp)
{

	String ret = F("1|");

	String FullPathFile_Chopps = F("");

	#define MAX_CHOPPS 50

	String aChopps[MAX_CHOPPS];

	String retFunc = F("");

	retFunc = SD_GetAllRegsFromFile(FullPathFile_Chopps, aChopps, MAX_CHOPPS);


	if (retFunc.substring(0, 2) == F("-1"))
	{
		// erro de sd card
		ret = retFunc;
		return ret;
	}

	if (retFunc.substring(0, 2) == F("-2"))
	{
		// erro de chopp nao existe
		ret = String(F("0|")) + retFunc.substring(3);
		return ret;
	}

	if (retFunc.substring(0, 1) == F("1"))
	{
		// chopp encontrado. Retornando todos os dados do chopp (linha)
		ret = retFunc;
		return ret;

	}

	return ret;
}


// INTERNA ARDUINO: SETUP
void setup() 
{
  
    Serial.begin(115200);       // 115200 pois o RFID precisa desta velocidade, para acompanharmos o que ele escreve no serial



    //Serial.print(rgb565_from_triplet(205, 205, 205));


    String FullPathFile;

    FullPathFile = F("CB/BD/Chopp/Chopps.txt");

    String retFunc = "";

    retFunc = SD_FileExists(FullPathFile);

    LogTerm("retFunc = " + retFunc);
  
}


// INTERNA ARDUINO: LOOP ETERNO
void loop() 
{

}

