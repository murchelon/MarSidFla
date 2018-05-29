



// retorna formato: CodRetorno|descricao
// Param byref: aRetChoppsEngat contera a lista de chopps engatados, se exitirem
// 1 para a funcao rodou certo 
// -1 e -2 erros outros
String BANCO_DefineChoppEngatados(String aRetChoppsEngat[])
{

	String ret = "1";

	String retFunc = "";

	String FullPathFile_Engatados = "";

	

	//ctMAX_TORNEIRAS
	FullPathFile_Engatados = "CB/BD/Chopp/Engatados.txt";

	// inicializa var de engatados
	for (int x = 0 ; x <= ctMAX_TORNEIRAS ; x++)
	{
		aRetChoppsEngat[x] = "";
	}	


	retFunc = SD_GetAllRegsFromFile(FullPathFile_Engatados, aRetChoppsEngat, ctMAX_TORNEIRAS);

	if ((retFunc.substring(0, 2) == "-1") || (retFunc.substring(0, 2) == "-2"))
	{
		// erro de sd card
		ret = retFunc;
		return ret;
	}

	if (retFunc.substring(0, 1) == "1")
	{

		String IDsChoppDesejados = "";

		// recupera o nome e preco de cada chopp
		for (int x = 0 ; x <= ctMAX_TORNEIRAS ; x++)
		{
			if (aRetChoppsEngat[x] != "")
			{
				String temp_IDChopp = "";

				temp_IDChopp = getValue(aRetChoppsEngat[x], ';', 2);
				//LogTerm("x = "+ String(x) + " | temp_Ativo = " + temp_Ativo);

				IDsChoppDesejados += temp_IDChopp + ", ";
			}
		}	 	
		
		if (IDsChoppDesejados.substring(IDsChoppDesejados.length() - 2, 2) == ", ")
		{
			IDsChoppDesejados = IDsChoppDesejados.substring(0, IDsChoppDesejados.length() - 2);
		}

		LogTerm('IDsChoppDesejados = ' + IDsChoppDesejados);


		ret = retFunc;
		return ret;

	}

	return ret;
}


// recupera os dadoa (linha) de um ou mais IDs de uma vez. tenho de indicar quais os ids e qual a posicao que o ID solicitado se enconta
// retorna formato: CodRetorno|Descricao
// 1 retorna a linha com dados do chopp
// -2 para chopp nao existe. 
// -1 erros outros
String BANCO_GetDataFromIDs(String aIDsDesejados)
{
	String ret = "1|";

	return ret;
}



// retorna formato: CodRetorno|Descricao
// 1 retorna a linha com dados do chopp
// -2 para chopp nao existe. 
// -1 erros outros
String BANCO_GetChoppDataFromIDChopp(String IDChopp)
{

	String ret = "1|";

	String FullPathFile_Chopps = "";

	#define MAX_CHOPPS 50

	String aChopps[MAX_CHOPPS];

	String retFunc = "";

	retFunc = SD_GetAllRegsFromFile(FullPathFile_Chopps, aChopps, MAX_CHOPPS);


	if (retFunc.substring(0, 2) == "-1")
	{
		// erro de sd card
		ret = retFunc;
		return ret;
	}

	if (retFunc.substring(0, 2) == "-2")
	{
		// erro de chopp nao existe
		ret = "0|"+ retFunc.substring(3);
		return ret;
	}

	if (retFunc.substring(0, 1) == "1")
	{
		// chopp encontrado. Retornando todos os dados do chopp (linha)
		ret = retFunc;
		return ret;

	}

	return ret;
}





// retorna formato: CodRetorno|Descricao
// 1 retorna a linha com dados do usuario
// -2 para usuario nao existe. 
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

			ret = "1|" + temp_IDUser;
			return ret;

		}


	}

	if (TipoLogin == "BIO")
	{
		
	}

	delay(100);

	return ret;
}

