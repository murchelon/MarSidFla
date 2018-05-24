


// Functions to read a CSV text file one field at a time.
//
#include <limits.h>
#include <SPI.h>

// next line for SD.h
//#include <SD.h>

// next two lines for SdFat
#include <SdFat.h>


#define SD_CHIP_SELECT 24

bool gModoDebug = true;

//gModoDebug = true;

bool gSessao_Logado;
int gSessao_IDUser;
int gSessao_Nivel;
String gSessao_Nome;



        
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }

    if (found > index)
    {
    	return data.substring(strIndex[0], strIndex[1]);
    }
    else
    {
    	return String("");
    }

    //return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}




String SD_GetFirstRegFromFile(String FullPathFile)
{

	SdFat SD;

	File file;

	String ret = "1|";

	String buff = "";

	int ContaEnter = 0;

	int CharAtual;

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


	// Create the file.
	file = SD.open(FullPathFile, FILE_READ);
	if (!file) 
	{
		LogTerm("SD: Falha na abertura do arquivo: " + FullPathFile);

		ret = "-2|Falha na abertura do arquivo: " + FullPathFile;

		return ret;	
	}
	else
	{

		if (gModoDebug == true)
		{
			LogTerm("SD: Arquivo aberto com sucesso: " + FullPathFile);
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









// retorna:
// 0 para arquivo nao existe
// 1 para arquivo existe. retona os dados do usuario
// -1 erros outros
String BANCO_GetUserDataFromIDUser(String IDUser)
{

	String ret = "1|";

	String FullPathFile_User = "";


	FullPathFile_User = "CB/BD/Usuarios/USU_" + IDUser + ".txt";


	String retFunc = "";

	retFunc = SD_GetFirstRegFromFile(FullPathFile_User);

	if (retFunc.substring(0, 2) == "-1")
	{
		// erro de sd card
		ret = retFunc;
		return ret;
	}

	if (retFunc.substring(0, 2) == "-2")
	{
		// erro de usuario nao existe
		ret = "0|"+ retFunc.substring(3);
		return ret;
	}

	if (retFunc.substring(0, 1) == "1")
	{
		// usuaario encontrado. Retornando todos os dados do usuario (linha)
		ret = retFunc.substring(2);
		return ret;

	}

	return ret;
}



// retorna:
// 0 para arquivo nao existe
// 1 para arquivo existe. retona os dados do usuario
// -1 erros outros
String BANCO_GetIDUserFromLogin(String Login, String TipoLogin)
{

	String ret = "1|";

	String FullPathFile_Login = "";



	if (TipoLogin == "RFID")
	{

		FullPathFile_Login = "CB/BD/Logins/RFID/" + Login + ".txt";


		String retFunc = "";

		retFunc = SD_GetFirstRegFromFile(FullPathFile_Login);

		if (retFunc.substring(0, 2) == "-1")
		{
			// erro de sd card
			ret = retFunc;
			return ret;
		}

		if (retFunc.substring(0, 2) == "-2")
		{
			// erro de login nao existe
			ret = "0|"+ retFunc.substring(3);
			return ret;
		}

		if (retFunc.substring(0, 1) == "1")
		{
			// login encontrado. Retornando IDUser

			String temp_IDUser = getValue(retFunc.substring(2), ';', 0);

			ret = temp_IDUser;
			return ret;

		}


	}

	if (TipoLogin == "BIO")
	{
		
	}

	delay(100);

	return ret;
}




String CharFromAsc2(int Asc2Value)
{
    char ret;

    ret = Asc2Value;

    return String(ret);
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







void setup() 
{

	Serial.begin(115200);

    //String FullPathFile_Login;
	String Login_RFID;

    // Wait for USB Serial 
    while (!Serial) 
    {
        SysCall::yield();
    }


	//ret = SD_TestaCartao();
	//LogTerm(ret);

	Login_RFID = "79A71ED9";

	//FullPathFile_Login = "CB/BD/Logins/RFID/" + Login + ".txt";
	//FullPathFile_Login = "79A71ED9.txt";

// retorna:
// 0 para arquivo nao existe
// 1 para arquivo existe. retona os dados do usuario
// -1 erros outros


	String retIDUser = "";

	retIDUser = BANCO_GetIDUserFromLogin(Login_RFID, "RFID");


	if (retIDUser.substring(0, 2) == "-1")
	{
		// erro foda de sd
		//ret = "0|"+ retLogin.substring(3);
		//return ret;		
	}

	if (retIDUser.substring(0, 1) == "0")
	{
		// erro nao existe o LOGIN CADASTRADO
		//ret = "0|"+ retLogin.substring(3);
		//return ret;	
	}

	if (retIDUser.substring(0, 1) == "1")
	{

		

		//LogTerm("IDUser: " + retIDUser);

		String retUserData = "";

		retUserData = BANCO_GetUserDataFromIDUser(retIDUser);

		//LogTerm("retUserData: " + retUserData);

		if (retUserData.substring(0, 2) == "-1")
		{
			// erro foda de sd
			//ret = "0|"+ retUserData.substring(3);
			//return ret;		
		}

		if (retUserData.substring(0, 1) == "0")
		{
			// erro nao existe o USUARIO CADASTRADO
			//ret = "0|"+ retUserData.substring(3);
			//return ret;	
		}


		if (retUserData.substring(0, 1) == "1")
		{
			// usuario existe

			gSessao_Logado = true;

			gSessao_IDUser = retIDUser.toInt();
			gSessao_Nome = getValue(retUserData.substring(2), ';', 2);
			gSessao_Nivel = getValue(retUserData.substring(2), ';', 3).toInt();


		}

		LogTerm("gSessao_Logado: " + String(gSessao_Logado));
		LogTerm("gSessao_IDUser: " + String(gSessao_IDUser));
		LogTerm("gSessao_Nivel: " + String(gSessao_Nivel));
		LogTerm("gSessao_Nome: " + gSessao_Nome);


	}


		


	//bool gSessao_Logado;
	//int gSessao_IDUser;
	//int gSessao_Nivel;
	//String gSessao_Nome;


	//ret = SD_GetFirstRegFromFile(FullPathFile_Login);

	//LogTerm(ret);

}


// INTERNA ARDUINO: LOOP ETERNO
void loop() 
{

}

