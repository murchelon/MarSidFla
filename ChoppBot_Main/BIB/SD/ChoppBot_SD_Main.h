




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








String SD_TestaCartao()
{

	uint32_t cardSize;

	SdFat SD;

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


