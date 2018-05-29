



#define MAX_TENTATIVA_READ 2
#define DELAY_TENTATIVA_READ 3000



// retorna formato: CodRetorno|descricao
// Param byref: LetorSD - retora o objeto passado, leitor SD
// 1 para a funcao rodou certo 
// -1 erros outros
String SD_InicializaCartaoSD(SdFat &LeitorSD)
{

	String ret = "1|SD Inicializado";

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


		ret = "-1|Falha na inicializacao do cartao SD";

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

	String ret = "1|Arquivo Aberto";

	int ContaTentativa = 0;
	bool SucessoTentativa = false;




	objArquivo = LeitorSD.open(FullPathFile, FILE_READ);

	if (!objArquivo) 
	{
		LogTerm("SD: Falha na abertura do arquivo: " + FullPathFile);


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


		ret = "-1|Falha na abertura do arquivo: " + FullPathFile;

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



	

	String ret = "1|";

	String buff = "";

	int ContaEnter = 0;

	int CharAtual;


	//int ContaTentativa = 0;
	//bool SucessoTentativa = false;

	SdFat SD;
	String retSD = "";

	retSD = SD_InicializaCartaoSD(SD);

	if (retSD.substring(0, 1) != "1")
	{
		return retSD;
	}



	File file;
	String retFile = "";

	retFile = SD_AbreArqTexto(FullPathFile, SD, file);

	if (retFile.substring(0, 1) != "1")
	{
		return retFile;
	}
	else
	{

		if (gModoDebug == true)
		{
			LogTerm("SD: Arquivo aberto com sucesso: " + FullPathFile);
		}
		

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



	String ret = "1|";

	String buff = "";

	int ContaEnter = 0;

	int CharAtual;






	SdFat SD;
	String retSD = "";

	retSD = SD_InicializaCartaoSD(SD);

	if (retSD.substring(0, 1) != "1")
	{
		return retSD;
	}



	File file;
	String retFile = "";

	retFile = SD_AbreArqTexto(FullPathFile, SD, file);

	if (retFile.substring(0, 1) != "1")
	{
		return retFile;
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
		LogTerm(F("SD: Falha na inicializacao do cartao SD"));

		ret = "0|Falha na inicializacao do cartao SD";
		return ret;	
	}

	t = millis() - t;	

	ret += String(t) + String("ms|");

	cardSize = SD.card()->cardSize();

	if (cardSize == 0) 
	{
		LogTerm(F("SD: Falha ao obter o tamanho do cartao SD"));

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


