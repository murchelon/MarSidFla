

#define RET_MAX_CHOPPS 50





// recupera os dadoa (linha) de um ou mais IDs de uma vez. tenho de indicar quais os ids e qual a posicao que o ID solicitado se enconta e o arquivo a ser lido
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
		MaxRegs = RET_MAX_CHOPPS;
	}

	retFunc = SD_GetAllRegsFromFile(FullPathFile, aRetData, MaxRegs);


	if ((retFunc.substring(0, 2) == F("-1")) || (retFunc.substring(0, 2) == F("-2")))
	{
		// erro de sd card
		ret = retFunc;
		return ret;
	}

	if (retFunc.substring(0, 1) == F("1"))
	{
		// dados do arquivo lidos
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


		String aChopps[RET_MAX_CHOPPS];

		retFunc = BANCO_GetDataFromIDs(F("CHOPP"), IDsChoppDesejados, aChopps);

		for (int x = 0 ; x <= RET_MAX_CHOPPS ; x++)
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

	retFunc = SD_GetFirstRegFromFile(FullPathFile_User);

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

		retFunc = SD_GetFirstRegFromFile(FullPathFile_Login);

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

