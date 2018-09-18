
// LEITOR SD Adafruit - Engine
#include <SPI.h>
#include "SdFat.h"




// SD
#define SD_MAX_TENTATIVA_READ 	2
#define SD_DELAY_TENTATIVA_READ 1000
#define SD_PINO 				24

// Serial print stream
ArduinoOutStream cout(Serial);
//------------------------------------------------------------------------------
// store error strings in flash to save RAM
#define error(s) SD.errorHalt(F(s))


String SD_TestaCartao()
{

	uint32_t cardSize;

	SdFat SD;

	String ret = F("1|");



	uint32_t t = millis();

	// not over 50 MHz. Try a lower speed if SPI errors occur.
	if (!SD.cardBegin(SD_PINO, SPI_SIXTEENTH_SPEED))
	{
		LogTerm(F("SD: Falha na inicializacao do cartao SD"));

		ret = F("0|Falha na inicializacao do cartao SD");
		return ret;	
	}

	t = millis() - t;	

	ret += String(t) + String(F("ms|"));

	cardSize = SD.card()->cardSize();

	if (cardSize == 0) 
	{
		LogTerm(F("SD: Falha ao obter o tamanho do cartao SD"));

		ret = F("0|Falha ao obter o tamanho do cartao SD");
		return ret;	
	}


	

	//cout << F("\ninit time: ") << t << " ms" << endl;
	//cout << F("\nCard type: ");

	switch (SD.card()->type())
	{
		case SD_CARD_TYPE_SD1:
			ret += String(F("SD1"));
			break;

		case SD_CARD_TYPE_SD2:
			ret += String(F("SD2"));
			break;

		case SD_CARD_TYPE_SDHC:
			if (cardSize < 70000000) 
			{
				ret += String(F("SDHC"));
			} 
			else
			{
				ret += String(F("SDXC"));
			}
			break;

		default:
			ret += String(F("Desconhecido"));
			break;
	}


	return ret;	
}





// retorna formato: CodRetorno|descricao
// Param byref: LetorSD - SD_CHIP_SELECT	SD_CHIP_SELECTretora o objeto passado, leitor SD
// 1 para a funcao rodou certo 
// -1 erros outros
String SD_InicializaCartaoSD(SdFat &LeitorSD)
{

	String ret = F("1|SD Inicializado");

	int ContaTentativa = 0;
	bool SucessoTentativa = false;


	// not over 50 MHz. Try a lower speed if SPI errors occur.
	if (!LeitorSD.begin(SD_PINO, SPI_SIXTEENTH_SPEED))
	{
		LogTerm(F("SD: Falha na inicializacao do cartao SD"));

		while ((ContaTentativa <= SD_MAX_TENTATIVA_READ) && (SucessoTentativa == false))
		{	
			LogTerm(F("SD: Realizando nova tentativa..."));

			// desliga sd
			pinMode(SD_PINO, OUTPUT);
			digitalWrite(SD_PINO, HIGH);	
			delay(SD_DELAY_TENTATIVA_READ);

			// religa sd
			pinMode(SD_PINO, INPUT);
			digitalWrite(SD_PINO, LOW);	
			delay(SD_DELAY_TENTATIVA_READ);



			if (LeitorSD.begin(SD_PINO, SPI_SIXTEENTH_SPEED))
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
// RetryOrCheckExists = RETRY ou CHECK . Se for RETRY, significa que esta sendo tentado abrir um arquivo conhecido e caso
//	ocorra algum erro, o sistema deve tentar de novo. Se for CHECK, o sistema nao sabe se existe o arquivo e deseja justamente
//  verificar se ele existe. Para tanto, tenta abri-lo e se ocorrer o erro, informa o caller que o arquivo nao existe
// 1 para a funcao rodou certo 
// -1 erros outros
// -2 para arquivo nao existe
String SD_AbreArqTexto(String FullPathFile, SdFat &LeitorSD, File &objArquivo, String RetryOrCheck)
{

	String ret = F("1|Arquivo Aberto");

	int ContaTentativa = 0;
	bool SucessoTentativa = false;




	objArquivo = LeitorSD.open(FullPathFile, FILE_READ);

	if (!objArquivo) 
	{

		if (RetryOrCheck == "RETRY")
		{
			LogTerm(String(F("SD: Falha na abertura do arquivo: ")) + FullPathFile);


			while ((ContaTentativa <= SD_MAX_TENTATIVA_READ) && (SucessoTentativa == false))
			{
				LogTerm(F("SD: Realizando nova tentativa..."));

				// desliga sd
				pinMode(SD_PINO, OUTPUT);
				digitalWrite(SD_PINO, HIGH);	
				delay(SD_DELAY_TENTATIVA_READ);

				// religa sd
				pinMode(SD_PINO, INPUT);
				digitalWrite(SD_PINO, LOW);	
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



		if (RetryOrCheck == "CHECK")
		{
			LogTerm(String(F("SD: Arquivo nao localizado: ")) + FullPathFile);

			ret = String(F("-2|Arquivo nao localizado: ")) + FullPathFile;

			return ret;	
		}



	}

	return ret;
}





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





String SD_ApagaArquivo(String FullPathFile)
{

	String ret = F("");

	File Arquivo_Temp;


	SdFat SD;
	String retSD = F("");

	retSD = SD_InicializaCartaoSD(SD);

	if (retSD.substring(0, 1) != F("1"))
	{
		return retSD;
	}


	Arquivo_Temp = SD.open(FullPathFile, O_WRITE);

	if (Arquivo_Temp.remove())
	{
		ret = F("1|Arquivo apagado com sucesso");
	}
	else
	{
		ret = String(F("0|Nao foi possivel apagar o arquivo: ")) + FullPathFile;
	}

	return ret;
}





String SD_RenameArquivo(String FullPathFile_Original, String FullPathFile_Destino)
{

	String ret = F("");

	SdFat SD;
	String retSD = F("");

	retSD = SD_InicializaCartaoSD(SD);

	if (retSD.substring(0, 1) != F("1"))
	{
		return retSD;
	}


	char __FullPathFile_Original[FullPathFile_Original.length() + 1];
	FullPathFile_Original.toCharArray(__FullPathFile_Original, sizeof(__FullPathFile_Original));

	char __FullPathFile_Destino[FullPathFile_Destino.length() + 1];
	FullPathFile_Destino.toCharArray(__FullPathFile_Destino, sizeof(__FullPathFile_Destino));


	SdFile Arquivo_Temp(__FullPathFile_Original, O_WRITE);

	if (!Arquivo_Temp.isOpen()) 
	{
		ret = String(F("0|Nao foi possivel localizar o arquivo: ")) + FullPathFile_Original;
	}
	else
	{
		if (Arquivo_Temp.rename(SD.vwd(), __FullPathFile_Destino)) 
		{
			ret = F("1|Arquivo renomeado com sucesso");
		}
		else
		{
			ret = String(F("0|Nao foi possivel renomear o arquivo: ")) + FullPathFile_Original + String(F(" para ")) + FullPathFile_Destino;
		}
	}

	return ret;
}





void TesteDelete(String FullPathFile)
{

	SdFat sd;
	File myFile;

	// Initialize SdFat or print a detailed error message and halt
	// Use half speed like the native library.
	// change to SPI_FULL_SPEED for more performance.
	if (!sd.begin(SD_PINO, SPI_HALF_SPEED)) sd.initErrorHalt();


	myFile = sd.open(FullPathFile, O_WRITE);

	if (!myFile.remove())
	{
		Serial.println("remove ok!");
	}
	else
	{
		Serial.println("Error file.remove");
	}


	/*
	// re-open the file for reading:
	if (!myFile.open(FullPathFile, 1)) 
	{
		sd.errorHalt("opening test.txt for read failed");
	}
	*/

	/*
	Serial.println("test.txt:");

	// read from the file until there's nothing else in it:
	int data;
	while ((data = myFile.read()) >= 0) Serial.write(data);

	// close the file:
	//if (!myFile.close()) Serial.println("Error file.close");
	if (!myFile.remove()) Serial.println("Error file.remove");

	*/
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  PROCEDURES ChoopBot
//  ===================
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Inicia a aplicacao, definido todos os parametros necessarios
void InitApp()
{

    Serial.begin(115200);       // 115200 pois o RFID precisa desta velocidade, para acompanharmos o que ele escreve no serial


    // Wait for USB Serial 
    while (!Serial) 
    {
        SysCall::yield();
    }


    

    digitalWrite(SD_MAX_TENTATIVA_READ, HIGH);
    digitalWrite(SD_DELAY_TENTATIVA_READ, HIGH);
    digitalWrite(SD_PINO, HIGH);



   	LogTerm("teste");

   	String ret = F("");

    ret = SD_TestaCartao();

    LogTerm(ret);


    String gSessao_IDUser = F("");
    String retFunc = F("");
    String FullPathFile_ORIGINAL = F("");
	String FullPathFile_DESTINO = F("");


    /*
    gSessao_IDUser = F("1");
    retFunc = F("");
    FullPathFile_ORIGINAL = String(F("CB/BD/Usuarios/USU_")) + gSessao_IDUser + String(F(".txt"));
	retFunc = SD_ApagaArquivo(FullPathFile_ORIGINAL);
	LogTerm(retFunc);

    gSessao_IDUser = F("2");
    retFunc = F("");
    FullPathFile_ORIGINAL = String(F("CB/BD/Usuarios/USU_")) + gSessao_IDUser + String(F(".txt"));
	retFunc = SD_ApagaArquivo(FullPathFile_ORIGINAL);
	LogTerm(retFunc);


	*/

    gSessao_IDUser = F("7");
    retFunc = F("");
    FullPathFile_ORIGINAL = String(F("CB/BD/Usuarios/USU_")) + gSessao_IDUser + String(F(".txt"));
	FullPathFile_DESTINO = String(F("CB/BD/Usuarios/USU_")) + gSessao_IDUser + String(F("_X.txt"));
	retFunc = SD_RenameArquivo(FullPathFile_ORIGINAL, FullPathFile_DESTINO);
	LogTerm(retFunc);


    gSessao_IDUser = F("7");
    retFunc = F("");
    FullPathFile_ORIGINAL = String(F("CB/BD/Usuarios/USU_")) + gSessao_IDUser + String(F("_X.txt"));
	FullPathFile_DESTINO = String(F("CB/BD/Usuarios/USU_")) + gSessao_IDUser + String(F("_Y.txt"));
	retFunc = SD_RenameArquivo(FullPathFile_ORIGINAL, FullPathFile_DESTINO);
	LogTerm(retFunc);



    gSessao_IDUser = F("7");
    retFunc = F("");
    FullPathFile_ORIGINAL = String(F("CB/BD/Usuarios/USU_")) + gSessao_IDUser + String(F("_Y.txt"));
	FullPathFile_DESTINO = String(F("CB/BD/Usuarios/USU_")) + gSessao_IDUser + String(F("_Z.txt"));
	retFunc = SD_RenameArquivo(FullPathFile_ORIGINAL, FullPathFile_DESTINO);
	LogTerm(retFunc);


    gSessao_IDUser = F("7");
    retFunc = F("");
    FullPathFile_ORIGINAL = String(F("CB/BD/Usuarios/USU_")) + gSessao_IDUser + String(F("_Z.txt"));
	FullPathFile_DESTINO = String(F("CB/BD/Usuarios/USU_")) + gSessao_IDUser + String(F(".txt"));
	retFunc = SD_RenameArquivo(FullPathFile_ORIGINAL, FullPathFile_DESTINO);
	LogTerm(retFunc);





	//String FullPathFile_TEMP;	
	//FullPathFile_TEMP = String(F("CB/BD/Usuarios/TUSU_")) + gSessao_IDUser + String(F(".txt"));

	

	


	//TesteDelete(FullPathFile_ORIGINAL);

	//LogTerm(retFunc);

}



// INTERNA ARDUINO: SETUP
void setup()
{  
    InitApp();  
}


// INTERNA ARDUINO: LOOP ETERNO
void loop() 
{

    
}

