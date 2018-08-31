
#include <SdFat.h>


const uint8_t SD_CHIP_SELECT = 24;


bool gModoDebug = true;


#define MAX_TENTATIVA_READ 6
#define DELAY_TENTATIVA_READ 5000




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

		while ((ContaTentativa <= MAX_TENTATIVA_READ) && (SucessoTentativa == false))
		{	
			LogTerm(F("SD: Realizando nova tentativa..."));
			delay(DELAY_TENTATIVA_READ);

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


		while ((ContaTentativa <= MAX_TENTATIVA_READ) && (SucessoTentativa == false))
		{
			LogTerm(F("SD: Realizando nova tentativa..."));
			delay(DELAY_TENTATIVA_READ);

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

