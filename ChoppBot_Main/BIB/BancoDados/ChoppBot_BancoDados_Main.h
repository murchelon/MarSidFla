







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
// 1 para saldo atualizado com sucesso 
// -1 erros outros
String BANCO_AtualizaSaldoUserLogado()
{

	String ret = F("1|");



	// cria novo arquivo de usuario no formato TUSU_IDUser.txt

	// grava os dados no arquivo temporario

	// apaga o arquivo antigo original

	// renomeia o arquivo temporario para oficial
	


	String FullPathFile_TEMP;	
	FullPathFile_TEMP = String(F("CB/BD/Usuarios/TUSU_")) + gSessao_IDUser + String(F(".txt"));

	String FullPathFile_ORIGINAL;	
	FullPathFile_ORIGINAL = String(F("CB/BD/Usuarios/USU_")) + gSessao_IDUser + String(F(".txt"));
	

	// apaga o arquivo antigo original
	String retFunc = F("");
	retFunc = SD_ApagaArquivo(FullPathFile_ORIGINAL);


	if (retFunc.substring(0, 2) == F("-1"))
	{
		// erro de sd card
		ret = retFunc;
		return ret;
	}


	if (retFunc.substring(0, 1) == F("1"))
	{


		// cria novo arquivo de usuario no formato TUSU_IDUser.txt e grava os dados do logado no arquivo temporario
		String retFunc2 = F("");
		//retFunc2 = SD_CreateNewUserFile(FullPathFile_TEMP, gSessao_IDUser, gSessao_CPF, gSessao_DataCad, gSessao_Nome, gSessao_Nivel, ValorSaldoAtual);


		if (retFunc2.substring(0, 2) == F("-1"))
		{
			// erro de sd card
			ret = retFunc2;
			return ret;
		}


		if (retFunc2.substring(0, 1) == F("1"))
		{
			// sucesso
			ret = retFunc2;
			return ret;
		}


	}


	return ret;



}



