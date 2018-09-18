







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



	if (TipoDado == F("CHOPP"))
	{
		FullPathFile = F("CB/BD/Chopp/Chopps.txt");
		PosicaoID = 0;
		MaxRegs = BANCO_MAX_CHOPPS;
	}



	String aTempRet[MaxRegs];

	for (int x=0 ; x <= MaxRegs ; x++)
	{
		aTempRet[x] = F("");
	}	

	retFunc = SD_GetAllRegsFromFile(FullPathFile, aTempRet, MaxRegs);


	if ((retFunc.substring(0, 2) == F("-1")) || (retFunc.substring(0, 2) == F("-2")))
	{
		// erro de sd card
		ret = retFunc;
		return ret;
	}

	int IndexArrayRet = 0;

	if (retFunc.substring(0, 1) == F("1"))
	{
		// dados do arquivo lidos

		for (int x=0 ; x <= MaxRegs - 1; x++)
		{
			String temp_ID = getValue(aTempRet[x], ';', PosicaoID);

			//LogTerm("temp_ID = " + temp_ID);


			for (int IndexSelItem = 0 ; IndexSelItem <= 30 ; IndexSelItem++)
			{
				String temp_SelItem = getValue(IDsDesejados, ',', IndexSelItem);

				if (temp_SelItem != "")
				{
					if (temp_ID == temp_SelItem)
					{

						//LogTerm("estou dentro = " + temp_ID);

						aRetData[IndexArrayRet] = aTempRet[x];

						IndexArrayRet++;
					}
				}

			}


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

		//LogTerm(String(F("IDsChoppDesejados = ")) + IDsChoppDesejados);


		String aChopps[BANCO_MAX_CHOPPS];

		// inicializa var de chopps
		for (int x = 0 ; x <= BANCO_MAX_CHOPPS ; x++)
		{
			aChopps[x] = F("");
		}	 		

		retFunc = BANCO_GetDataFromIDs(F("CHOPP"), IDsChoppDesejados, aChopps);

		/*
		for (int x = 0 ; x <= BANCO_MAX_CHOPPS - 1 ; x++)
		{
			if (aChopps[x] != F(""))
			{
				LogTerm(String(F("aChopps[")) + String(x) + String(F("] = ")) + aChopps[x]);
			}
		}
		*/

		// define o nome e valor no array de engatados
		for (int x = 0 ; x <= ctMAX_TORNEIRAS ; x++)
		{
			if (aRetChoppsEngat[x] != F(""))
			{
				String temp_IDChopp = F("");

				temp_IDChopp = getValue(aRetChoppsEngat[x], ';', 2);
				//LogTerm("x = "+ String(x) + " | temp_IDChopp = " + temp_IDChopp);


				for (int k = 0 ; k <= BANCO_MAX_CHOPPS - 1 ; k++)
				{
					if (aChopps[k] != F(""))
					{

						String temp_IDChoppTabela = getValue(aChopps[k], ';', 0);

						if (temp_IDChopp == temp_IDChoppTabela)
						{
							aRetChoppsEngat[x] = getValue(aRetChoppsEngat[x], ';', 0) + String(";") + 
												 getValue(aRetChoppsEngat[x], ';', 1) + String(";") + 
												 getValue(aRetChoppsEngat[x], ';', 2) + String(";") + 
												 getValue(aRetChoppsEngat[x], ';', 3) + String(";") + 
												 getValue(aRetChoppsEngat[x], ';', 4) + String(";") + 
												 getValue(aRetChoppsEngat[x], ';', 5) + String(";") + 
												 getValue(aRetChoppsEngat[x], ';', 5) + String(";") + 
												 getValue(aChopps[k], ';', 1) + String(";") + 
												 getValue(aChopps[k], ';', 2) + String(";") + 
												 getValue(aChopps[k], ';', 3);
						}



					}
				}



			}
		}	




		for (int x = 0 ; x <= ctMAX_TORNEIRAS ; x++)
		{
			if (aRetChoppsEngat[x] != F(""))
			{
				//LogTerm(String(F("aRetChoppsEngat[")) + String(x) + String(F("] = ")) + aRetChoppsEngat[x]);
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








// retorna formato: CodRetorno|Descricao
// 1 para arquivo criado com sucesso 
// 0 erros outros
String BANCO_CriaArquivoUsuario(String FullPathFile,
								int IDUser,
								String CPF,
								String DataCad,
								String Nome,
								int Nivel,
								float SaldoAtual
								)
{

	String ret = F("");

	String Linha = F("");

	SdFat SD;
	String retSD = F("");

	retSD = SD_InicializaCartaoSD(SD);

	if (retSD.substring(0, 1) != F("1"))
	{
		return retSD;
	}



	char __FullPathFile[FullPathFile.length() + 1];
	FullPathFile.toCharArray(__FullPathFile, sizeof(__FullPathFile));

	SdFile Arquivo_Temp(__FullPathFile, O_WRITE | O_CREAT);

	if (!Arquivo_Temp.isOpen()) 
	{
		ret = String(F("0|Nao foi possivel criar o arquivo: ")) + FullPathFile;
	}
	else
	{

		//IDUser;CPF;DataCad;Nome;Nivel;SaldoAtual

		Linha = String(
						String(IDUser) + F(";") +
						CPF + F(";") +
						DataCad + F(";") + 
						Nome + F(";") +
						String(Nivel) + F(";") +
						String(SaldoAtual) 
						);


		Arquivo_Temp.println("IDUser;CPF;DataCad;Nome;Nivel;SaldoAtual");
		Arquivo_Temp.println(Linha);

		Arquivo_Temp.close();

		ret = String(F("1|Arquivo criado com sucesso: ")) + FullPathFile;

	}
	
	
	return ret;

}


// retorna formato: CodRetorno|Descricao
// 1 para saldo atualizado com sucesso 
// -1 erros outros
String BANCO_AtualizaSaldoUserLogado(String IDChopp,
									 String NomeChopp,
									 String ValorChopp,
									 float litersConsumido,
									 float ValorSessaoChopp,
									 float ValorSaldoAtual,
									 float VolumeAtual
									 )
{


	// Algoritmo:
	// cria novo arquivo de usuario no formato TUSU_IDUser.txt
	// grava os dados no arquivo temporario
	// apaga o arquivo antigo original
	// renomeia o arquivo temporario para oficial


	String ret = F("");

	String FullPathFile_TEMP;	
	FullPathFile_TEMP = String(F("CB/BD/Usuarios/TUSU_")) + gSessao_IDUser + String(F(".txt"));

	String FullPathFile_ORIGINAL;	
	FullPathFile_ORIGINAL = String(F("CB/BD/Usuarios/USU_")) + gSessao_IDUser + String(F(".txt"));
	

	// apaga o arquivo temporario antigo se existir
    String retFunc = F("");

	retFunc = SD_ApagaArquivo(FullPathFile_TEMP);

	if (retFunc.substring(0, 1) == F("1"))
	{
		// arquivo temporario antigo localizado
		LogTerm(String(F("Arquivo Temporario de Usuario antigo localizado e apagado: ")) + retFunc);
	}
	
	// cria o novo arquivo temporario com os dados da sessao
	retFunc = F("");
	retFunc = BANCO_CriaArquivoUsuario(FullPathFile_TEMP,
										gSessao_IDUser,
										gSessao_CPF,
										gSessao_DataCad,
										gSessao_Nome,
										gSessao_Nivel,
										ValorSaldoAtual
										);


	LogTerm(String(F("Retorno da criacao de arquivo temporario: ")) + retFunc);

	retFunc = F("");
	retFunc = SD_RenameArquivo(FullPathFile_TEMP, FullPathFile_ORIGINAL);

	if (retFunc.substring(0, 1) == F("0"))
	{
		// arquivo temporario antigo localizado
		LogTerm(String(F("Falha em renomear arquivo temporario de usuario para o final: ")) + retFunc);

		ret = F("0|Falha na atualizacao de saldo do usuario");
	}
	else
	{
		LogTerm(String(F("Arquivo temporario de usuario renomeado com sucesso para versao final: ")) + retFunc);

		ret = F("1|Saldo atualizado com sucesso");
	}

	/*
    LogTerm(String(F("banco dados ---------------------------------------")));
    LogTerm(String(F("Torneira (gServico_ID_TorneiraAtual) = ")) + String(gServico_ID_TorneiraAtual));
    LogTerm(String(F("IDChopp (IDChopp) = ")) + IDChopp);
    LogTerm(String(F("Nome Chopp (NomeChopp) = ")) + NomeChopp);
    LogTerm(String(F("Preco Chopp (ValorChopp) = ")) + ValorChopp);
    LogTerm(String(F("IDUser = ")) + String(gSessao_IDUser));
	LogTerm(String(F("gSessao_Nome = ")) + gSessao_Nome);
	LogTerm(String(F("gSessao_CPF = ")) + gSessao_CPF);
	LogTerm(String(F("gSessao_DataCad = ")) + gSessao_DataCad);
	LogTerm(String(F("Saldo Original (gSessao_SaldoAtual) = ")) + String(gSessao_SaldoAtual));
	LogTerm(String(F("Consumido (litersConsumido) = ")) + String(litersConsumido));
	LogTerm(String(F("ValorSessaoChopp = ")) + String(ValorSessaoChopp));
	LogTerm(String(F("Saldo Atual (ValorSaldoAtual) = ")) + String(ValorSaldoAtual));		
	LogTerm(String(F("Chopp Restante (VolumeAtual) = ")) + String(VolumeAtual));
	LogTerm(String(F("---------------------------------------")));
	*/

	return ret;


}





