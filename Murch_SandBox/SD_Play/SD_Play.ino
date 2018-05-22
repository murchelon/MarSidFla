


// Functions to read a CSV text file one field at a time.
//
#include <limits.h>
#include <SPI.h>

// next line for SD.h
//#include <SD.h>

// next two lines for SdFat
#include <SdFat.h>


#define SD_CHIP_SELECT 24








void setup() 
{

	Serial.begin(115200);

    String FullPathFile_Login;
	String Login;

    // Wait for USB Serial 
    while (!Serial) 
    {
        SysCall::yield();
    }

	String ret = "";

	ret = SD_TestaCartao();
	LogTerm(ret);

	Login = "79A71ED9";

	FullPathFile_Login = "CB/BD/Logins/RFID/" + Login + ".txt";
	//FullPathFile_Login = "79A71ED9.txt";


	ret = SD_GetFirstRegFromFile(FullPathFile_Login);

	LogTerm(ret);

}






String SD_GetFirstRegFromFile(String FullPathFile)
{

	SdFat SD;

	File file;

	String ret = "1|";


	int ContaEnter = 0;


	uint32_t t = millis();

	// not over 50 MHz. Try a lower speed if SPI errors occur.
	if (!SD.begin(SD_CHIP_SELECT, SPI_SIXTEENTH_SPEED))
	{
		LogTerm("SD: Falha na inicializacao do cartao SD");

		ret = "-1|Falha na inicializacao do cartao SD";

		return ret;	
	}

	t = millis() - t;	

	//FullPathFile_Login = Login + ".txt";

	int CharAtual;

	// Create the file.
	file = SD.open(FullPathFile, FILE_READ);
	if (!file) 
	{
		LogTerm("SD: Falha na abertura do arquivo");

		ret = "-2|Falha na abertura do arquivo";

		return ret;	
	}
	else
	{
		Serial.println("tudo ok");

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
				Serial.write(CharAtual);
			}
			
		}		

	}

	file.close();

	return ret;
}









String SD_IniciaCartao()
{
	
}




String SD_TestaCartao()
{

	SdFat SD;


	uint32_t cardSize;

	//SdFat SD;

	String ret = "1|";



	uint32_t t = millis();

	// not over 50 MHz. Try a lower speed if SPI errors occur.
	if (!SD.cardBegin(SD_CHIP_SELECT, SPI_SIXTEENTH_SPEED))
	{
		LogTerm("SD: Falha na inicializacao do cartao SD");

		ret = "0|Falha na inicializacao do cartao SD";
		return ret;	
	}

	t = millis() - t;	

	ret += String(t) + String("ms|");

	cardSize = SD.card()->cardSize();

	if (cardSize == 0) 
	{
		LogTerm("SD: Falha ao obter o tamanho do cartao SD");

		ret = "0|Falha ao obter o tamanho do cartao SD";
		return ret;	
	}


	

	//cout << F("\ninit time: ") << t << " ms" << endl;
	//cout << F("\nCard type: ");

	switch (SD.card()->type())
	{
		case SD_CARD_TYPE_SD1:
			ret += "SD1";
			break;

		case SD_CARD_TYPE_SD2:
			ret += "SD2";
			break;

		case SD_CARD_TYPE_SDHC:
			if (cardSize < 70000000) 
			{
				ret += "SDHC";
			} 
			else
			{
				ret += "SDXC";
			}
			break;

		default:
			ret += "Desconhecido";
			break;
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






// INTERNA ARDUINO: LOOP ETERNO
void loop() 
{

}

