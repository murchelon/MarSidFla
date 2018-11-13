





void RFID_SetStatusLed(bool Valor)
{
	if (Valor == true)
	{
		//LED_SetLedState("CORFIXA", true, "");
		LED_SetLedState(F("RGB"), true, F("BLUE"));
	}
	else
	{
		//LED_SetLedState("CORFIXA", false, "");
		LED_SetLedState(F("RGB"), false, F("BLUE"));
	}
	 
}



String RFID_Exec_Leitura()
{

	String ret = F("1|");

	String idCartao = F(""); 

	String aux1 = F(""); 

	

	if (String(ctRFID_HARDWARE) == String(F("PN532")))
	{



		Adafruit_PN532 nfc(PN532_SS);


		// desabilita SD para efetuar a leitura
		pinMode(DISABLE_CHIP_SELECT, OUTPUT);
		digitalWrite(DISABLE_CHIP_SELECT, HIGH);	


		// inicia componente
		nfc.begin();

		// verifica se deu tudo certo
		uint32_t versiondata = nfc.getFirmwareVersion();

		if (! versiondata)
		{
			if (ctMODO_DEBUG == true)
			{
				LogTerm(F("RFID: Placa PN53x nao localizada"));
			} 
			

			ret = F("0|Placa PN53x nao localizada");
			return ret;
		}

		RFID_SetStatusLed(true);



		if (ctMODO_DEBUG == true)
		{
			 

			LogTerm(F("RFID: Placa PN53x localizada com sucesso"));
			//Serial.print("RFID: Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
			//Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
		} 		



		// Set the max number of retry attempts to read from a card
		// This prevents us from waiting forever for a card, which is
		// the default behaviour of the PN532.
		//nfc.setPassiveActivationRetries(0xFF); // 255 forever
		nfc.setPassiveActivationRetries(255);

		// configure board to read RFID tags
		nfc.SAMConfig();


		

		boolean success;
		uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
		uint8_t uidLength;        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

		 

		// Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
		// 'uid' will be populated with the UID, and uidLength will indicate
		// if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
		success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

		RFID_SetStatusLed(false);  

		if (success)
		{

			

			LogTerm(F("RFID: Leitura efetuada com sucesso !"));

			//Serial.print("RFID: UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
			//Serial.print("RFID: UID Value: ");

			for (uint8_t i=0; i < uidLength; i++) 
			{

				aux1 = String(uid[i], HEX);

				if (aux1.length() <= 1)
				{
					aux1 = String(F("0")) + aux1;
				}

				idCartao += aux1;

				//Serial.print(" 0x");Serial.print(uid[i], HEX); 

				//TELA_Texto("LEITOR RFID SELECIONADO VIA TELA", "MAGENTA");


			}
			
			//Serial.print("\n");

			idCartao.toUpperCase();

			ret += idCartao;

			

			LogTerm(String(F("RFID: Cartao lido: ")) + idCartao);

			//TELA_Texto("Cartao decodec: " + idCartao, "MAGENTA");




			
			//digitalWrite(RFID_PINO_SCK, HIGH);
			//digitalWrite(RFID_PINO_MOSI, HIGH);
			//digitalWrite(RFID_PINO_SS, HIGH);
			//digitalWrite(RFID_PINO_MISO, HIGH);
			//digitalWrite(RFID_PINO_IRQ, HIGH);
			//digitalWrite(RFID_PINO_RESET, HIGH);

			//delay(1000);

			//digitalWrite(SD_MAX_TENTATIVA_READ, HIGH);
			//digitalWrite(SD_DELAY_TENTATIVA_READ, HIGH);
			//digitalWrite(SD_PINO, HIGH);

			//delay(1000);


			//digitalWrite(SD_PINO, LOW);

			//delay(1000);

		}
		else
		{
			// PN532 probably timed out waiting for a card
			//Serial.println("Ocorreum um timeout da leitura do cartao");


			LogTerm(F("RFID: Timeout de leitura"));

			ret =F("0|RFID: Timeout de leitura");
				
		}	

		//delete nfc;
		nfc = NULL;	

		

	}



	return ret;	



}




void TELA_Render_Interface_LER_RFID()
{
	
	//LogTerm(ctTELA_HARDWARE);


	if (gTelaRenderizada_LER_RFID == false)
	{

        //LogTerm(F("== [Modo Atual: STANDBY] ==");


		if (ctTELA_HARDWARE == F("TERMINAL"))
		{  
			LogTerm(F("Encoste o cartao ou chaveiro de identificacao no leitor..."));
			//LogTerm(F("Digite algo no teclado para voltar");

		}

		if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
		{  

		
			tft.setTextColor(RA8875_YELLOW);
			TELA_SetFontSize(2); 

			tft.setCursor (115, 100);
			tft.print (F("Por favor, encoste o seu"));    

			tft.setCursor (115, 145);
			tft.print (F("cartao ou chaveiro de")); 

			tft.setCursor (115, 190);
			tft.print (F("identificacao no leitor")); 
			
			tft.setCursor (115, 235);
			tft.print (F("a sua frente ...")); 
			

			tft.setTextColor(LaranjaAlerta);
			TELA_SetFontSize(1); 
			tft.setCursor (160, 350);
			tft.print (F("[Aguardando leitura do cartao]")); 


			/*
		    int btnVoltar_PosAtual_X = 100;
			int btnVoltar_PosAtual_Y = 360;

			tft.fillRoundRect(btnVoltar_PosAtual_X, btnVoltar_PosAtual_Y, 170, 60, 5, RA8875_BLUE);

		
		    tft.setTextColor(RA8875_WHITE);
		    TELA_SetFontSize(1); 
		    tft.setCursor (btnVoltar_PosAtual_X + (60 / 2) - 18, btnVoltar_PosAtual_Y + 11); 
		    tft.print (F("<< Voltar"));	
		    */		

		}

		gTelaRenderizada_LER_RFID = true;



		// REcupera o Login (numero unico existente no cartao ou chaveiro)
		String Login_RFID;

		Login_RFID = RFID_Exec_Leitura();

		//LogTerm(Login_RFID);


		if (Login_RFID.substring(0,2) == F("1|"))
		{
			Login_RFID = Login_RFID.substring(2);

			

			String ret;

			//ret = SD_TestaCartao();

			//LogTerm(ret);	

			// zera as vars para cada tentativa de login
			gSessao_Logado = false;
			gSessao_IDUser = -1;
			gSessao_Nome = F("");
			gSessao_Nivel = -1;
			gSessao_SaldoAtual = -1;
			gSessao_CPF = F("");
			gSessao_DataCad = F("");

			String retIDUser = "";

			retIDUser = BANCO_GetIDUserFromLogin(Login_RFID, F("RFID"));


			if (ctMODO_DEBUG == true)
			{
				//LogTerm(F("BANCO_GetIDUserFromLogin(" + Login_RFID + ") = " + retIDUser);
			}
			


			if (retIDUser.substring(0, 2) == F("-1"))
			{
				// erro foda de sd

				BUZZER_TocaSom(F("ERRO"));

				LED_SetLedState(F("RGB"), true, F("RED"));

				// ocorreu um erro. imprime a msg de erro na tela
				if (ctTELA_HARDWARE == F("TERMINAL"))
				{  
					LogTerm(F("Ocorreu um erro ao efetuar a leitura do cartao SD: Login"));
				}

				if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
				{  

					TELA_LimpaTela();

					

					if (ctMODO_DEBUG == false)
					{
						TELA_Render_MsgBox(F("Erro no Leitor SD"), F("Ocorreu um erro ao efetuar a leitura do cartao SD: Login"));
					}
					else
					{
						TELA_Render_MsgBox(F("Erro no Leitor SD"), String(F("Ocorreu um erro ao efetuar a leitura do cartao SD: Login:  ")) + retIDUser);
					}

					delay(6000);

					TELA_LimpaTela();

					gTelaRenderizada_MSGBOX = false;
					gTelaRenderizada_LER_RFID = false;
					
				}

				gModoOperacao = F("STANDBY");
				gModoOperacao_SubTela = F("");	
				

			}

			if (retIDUser.substring(0, 1) == F("0"))
			{
				// erro nao existe o LOGIN CADASTRADO

				BUZZER_TocaSom(F("ERRO"));

				LED_SetLedState(F("RGB"), true, F("RED"));

				// ocorreu um erro. imprime a msg de erro na tela
				if (ctTELA_HARDWARE == F("TERMINAL"))
				{  
					LogTerm(F("O cartao utilizado nao esta cadastrado. Por favor procure o caixa para maiores informacoes."));


				}

				if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
				{  

					TELA_LimpaTela();

					

					if (ctMODO_DEBUG == false)
					{
						TELA_Render_MsgBox(F("Cartao nao cadastrado"), F("O cartao utilizado nao esta cadastrado. Por favor procure o caixa para maiores  informacoes."));
					}
					else
					{
						TELA_Render_MsgBox(F("Cartao nao cadastrado"), String(F("O cartao utilizado nao esta cadastrado. Por favor procure o caixa para maiores  informacoes: ")) + retIDUser);
					}

					delay(6000);

					TELA_LimpaTela();

					gTelaRenderizada_MSGBOX = false;
					gTelaRenderizada_LER_RFID = false;
					
				}


				gModoOperacao = F("STANDBY");
				gModoOperacao_SubTela = F("");	

			}

			if (retIDUser.substring(0, 1) == F("1"))
			{
	

				//LogTerm(String(F("IDUser: ")) + retIDUser);

				String temp_IDUser = getValue(retIDUser.substring(2), ';', 0);

				String retUserData = F("");

				retUserData = BANCO_GetUserDataFromIDUser(temp_IDUser);

				//LogTerm(String(F("retUserData: ")) + retUserData);

				if (ctMODO_DEBUG == true)
				{
					//LogTerm(F("BANCO_GetUserDataFromIDUser(" + retIDUser.substring(2) + ") = " + retUserData);
				}

				//LogTerm(F("retUserData: " + retUserData);

				if (retUserData.substring(0, 2) == F("-1"))
				{
					// erro foda de sd

					BUZZER_TocaSom(F("ERRO"));

					LED_SetLedState(F("RGB"), true, F("RED"));

					// ocorreu um erro. imprime a msg de erro na tela
					if (ctTELA_HARDWARE == F("TERMINAL"))
					{  
						LogTerm(F("Ocorreu um erro ao efetuar a leitura do cartao SD: Usuario"));

					}

					if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
					{  

						TELA_LimpaTela();

						

						if (ctMODO_DEBUG == false)
						{
							TELA_Render_MsgBox(F("Erro no Leitor SD"), F("Ocorreu um erro ao efetuar a leitura do cartao SD: Usuario"));
						}
						else
						{
							TELA_Render_MsgBox(F("Erro no Leitor SD"), String(F("Ocorreu um erro ao efetuar a leitura do cartao SD: Usuario:  ")) + retUserData);
						}

						delay(6000);

						TELA_LimpaTela();

						gTelaRenderizada_MSGBOX = false;
						gTelaRenderizada_LER_RFID = false;
						
					}


					gModoOperacao = F("STANDBY");
					gModoOperacao_SubTela = F("");	

				}

				if (retUserData.substring(0, 1) == F("0"))
				{


					// erro nao existe o USUARIO CADASTRADO

					BUZZER_TocaSom(F("ERRO"));

					LED_SetLedState(F("RGB"), true, F("RED"));

					// ocorreu um erro. imprime a msg de erro na tela
					if (ctTELA_HARDWARE == F("TERMINAL"))
					{  
						LogTerm(F("Usuario nao localizado. Este cartao esta associado a um usuario que nao foi localizado no sistema. Por favor procure o caixa para maiores informacoes"));

					}

					if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
					{  

						TELA_LimpaTela();

						

						if (ctMODO_DEBUG == false)
						{
							TELA_Render_MsgBox(F("Usuario nao localizado"), F("Este cartao esta associado a um usuario que nao foi localizado no sistema. Por  favor procure o caixa para maiores informacoes"));
						}
						else
						{
							TELA_Render_MsgBox(F("Usuario nao localizado"), String(F("Este cartao esta associado a um usuario que nao foi localizado no sistema. Por  favor procure o caixa para maiores informacoes: ")) + retUserData);
						}

						delay(6000);

						TELA_LimpaTela();

						gTelaRenderizada_MSGBOX = false;
						gTelaRenderizada_LER_RFID = false;
						
					}

					gModoOperacao = F("STANDBY");
					gModoOperacao_SubTela = F("");	

				}




				if (retUserData.substring(0, 1) == "1")
				{
					// usuario existe

					LED_SetLedState(F("RGB"), true, F("GREEN"));

					BUZZER_TocaSom(F("SUCESSO"));

					


					gSessao_Logado = true;

					gSessao_IDUser = retIDUser.substring(2).toInt();
					gSessao_Nome = getValue(retUserData.substring(2), ';', 3);
					gSessao_Nivel = getValue(retUserData.substring(2), ';', 4).toInt();
					gSessao_SaldoAtual = getValue(retUserData.substring(2), ';', 5).toFloat();
					gSessao_CPF = getValue(retUserData.substring(2), ';', 1);
					gSessao_DataCad = getValue(retUserData.substring(2), ';', 2);



					LogTerm(F("MAIN: Usuario LOGADO"));
					//LogTerm("gSessao_IDUser: " + String(gSessao_IDUser));
					LogTerm(String(F("MAIN: Nome: ")) + gSessao_Nome);	
					LogTerm(String(F("MAIN: Nivel: ")) + String(gSessao_Nivel));
					LogTerm(String(F("MAIN: Saldo: ")) + String(gSessao_SaldoAtual));
						



					if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
					{  

						TELA_LimpaTela();
						
						if (ctMODO_DEBUG == true)
						{
							//TELA_Render_MsgBox(F("Usuario Identificado"), String(F("Ola ! Seja bem vindo ")) + gSessao_Nome + String(F(" ! -- gSessao_Logado = ")) + String(gSessao_Logado) + String(F(" | gSessao_IDUser = ")) + String(gSessao_IDUser) + String(F(" | gSessao_Nivel = ")) + String(gSessao_Nivel) + String(F(" | gSessao_SaldoAtual = ")) + String(gSessao_SaldoAtual)  );
							//delay(5000);
							//TELA_LimpaTela();
						}

						gTelaRenderizada_MSGBOX = false;
						gTelaRenderizada_LER_RFID = false;

					}

					// murch cebola
					//gModoOperacao = F("OPERACAO");
					gModoOperacao = F("OPERACAO");
					gModoOperacao_SubTela = F("OPERACAO_SERVICO");

					delay(100);

				}


			}


	

		}
		else
		{

			BUZZER_TocaSom(F("ERRO"));

			LED_SetLedState(F("RGB"), true, F("RED"));

			// ocorreu um erro. imprime a msg de erro na tela
			if (ctTELA_HARDWARE == F("TERMINAL"))
			{  
				LogTerm(F("Ocorreu um erro ao realizar a leitura do cartao/chaveiro RFID:"));
				LogTerm(Login_RFID.substring(2));


			}

			if (ctTELA_HARDWARE == String(F("ER-TFTM070-5")))
			{  

				TELA_LimpaTela();

				TELA_Render_MsgBox(F("Erro no Leitor SD"), String(F("Ocorreu um erro ao realizar a leitura do cartao/chaveiro RFID: ")) + Login_RFID.substring(2));

				delay(7000);

				TELA_LimpaTela();

				gTelaRenderizada_MSGBOX = false;
				gTelaRenderizada_LER_RFID = false;
				

			}
			
		}

		




		LED_SetLedState(F("RGB"), false, "");




		
		gTelaRenderizada_LER_RFID = false;

	    if (ctTELA_HARDWARE == String(F("ER-TFTM070-5")))
	    {
	        TELA_LimpaTela();
	    }


		//delay(500);   

	}


}



void TELA_VerificaTouch_LER_RFID()
{

	if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
	{  



		//tft.changeMode(GRAPHIC);

		if (TELA_touchDetect())
		{

			TELA_touchReadPixel(&gTouch_X, &gTouch_Y);

			gTouch_X = 800 - gTouch_X;
			gTouch_Y = 480 - gTouch_Y;

			//TELA_LogTerm_XY(); 

			//botao 1:
			if (gTouch_X >= 100 && gTouch_X <= 100 + 170)  
			{

				if (gTouch_Y >= 250 && gTouch_Y <= 250 + 60) 
				{

					// DO VOLTAR DA TELA LER RFID

				}

			}




		}

	}

}


