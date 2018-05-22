


String BANCO_GetUserFromLogin(String Login, String TipoLogin)
{

	String ret = "1|";

	String FullPathFile_Login = "";



	if (TipoLogin == "RFID")
	{

		FullPathFile_Login = "CB/BD/Logins/RFID/" + Login + ".txt";


		String ArqExiste = "";

		ArqExiste = SD_GetFirstRegFromFile(FullPathFile_Login);

		if (ArqExiste.substring(0, 2) == "-1")
		{
			ret = ArqExiste;
			return ret;
		}

		if (ArqExiste.substring(0, 1) == "0")
		{
			ret = ArqExiste;
			return ret;
		}

		if (ArqExiste.substring(0, 1) == "1")
		{
			//String Registro = "";
			ret = ArqExiste;
			return ret;

		}


	}

	if (TipoLogin == "BIO")
	{
		
	}

	return ret;
}


