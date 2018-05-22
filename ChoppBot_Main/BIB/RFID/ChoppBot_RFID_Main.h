


// led de indicacao de uso do rfid
#define ctPINO_LED_RFID 26



void RFID_SetStatusLed(bool Valor)
{
	if (Valor == true)
	{
		digitalWrite(ctPINO_LED_RFID, HIGH);
	}
	else
	{
		digitalWrite(ctPINO_LED_RFID, LOW);
	}
	 
}

String RFID_Exec_Leitura()
{

	String ret = "1|";

	String idCartao = ""; 

	String aux1 = ""; 



	if (gRFID_Hardware == "PN532")
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
			if (gModoDebug == true)
			{
				LogTerm("RFID: Placa PN53x nao localizada");
			} 
			

			ret = "0|Placa PN53x nao localizada";
			return ret;
		}


		if (gModoDebug == true)
		{
			RFID_SetStatusLed(true); 

			LogTerm("RFID: Placa PN53x localizada com sucesso");
			Serial.print("RFID: Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
			Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
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

			

			LogTerm("RFID: Leitura efetuada com sucesso !");

			Serial.print("RFID: UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
			Serial.print("RFID: UID Value: ");

			for (uint8_t i=0; i < uidLength; i++) 
			{

				aux1 = String(uid[i], HEX);

				if (aux1.length() <= 1)
				{
					aux1 = String("0") + aux1;
				}

				idCartao += aux1;

				Serial.print(" 0x");Serial.print(uid[i], HEX); 

				//TELA_Texto("LEITOR RFID SELECIONADO VIA TELA", "MAGENTA");


			}
			
			Serial.print("\n");

			idCartao.toUpperCase();

			ret += idCartao;

			

			LogTerm("RFID: Cartao decoded: " + idCartao);

			//TELA_Texto("Cartao decodec: " + idCartao, "MAGENTA");



			// Wait 1 second before continuing
			delay(1000);
		}
		else
		{
			// PN532 probably timed out waiting for a card
			//Serial.println("Ocorreum um timeout da leitura do cartao");


			LogTerm("RFID: Timeout de leitura");

			ret = "0|RFID: Timeout de leitura";
				
		}	

		//delete nfc;
		nfc = NULL;	

		

	}



	return ret;	



}




void TELA_Render_Interface_LER_RFID()
{
	
	//LogTerm(gTela_Hardware);


	if (gTelaRenderizada_LER_RFID == false)
	{

        //LogTerm("== [Modo Atual: STANDBY] ==");


		if (gTela_Hardware == "TERMINAL")
		{  
			LogTerm("Encoste o cartao ou chaveiro de identificacao no leitor...");
			//LogTerm("Digite algo no teclado para voltar");

		}

		if (gTela_Hardware == "ER-TFTM070-5")
		{  

		
			tft.setTextColor(RA8875_YELLOW);
			tft.setFontScale(2); 

			tft.setCursor (100, 100);
			tft.print ("Por favor, encoste o seu");    

			tft.setCursor (100, 145);
			tft.print ("cartao ou chaveiro de"); 

			tft.setCursor (100, 190);
			tft.print ("identificacao no leitor"); 
			
			tft.setCursor (100, 235);
			tft.print ("a sua frente ..."); 
			


		    int btnVoltar_PosAtual_X = 100;
			int btnVoltar_PosAtual_Y = 360;

			tft.fillRoundRect(btnVoltar_PosAtual_X, btnVoltar_PosAtual_Y, 170, 60, 5, RA8875_BLUE);

		    tft.setTextColor(RA8875_WHITE);
		    tft.setFontScale(1); 
		    tft.setCursor (btnVoltar_PosAtual_X + (60 / 2) - 18, btnVoltar_PosAtual_Y + 11); 
		    tft.print ("<< Voltar");			

		}

		gTelaRenderizada_LER_RFID = true;



		// REcupera o Login (numero unico existente no cartao ou chaveiro)
		String Login_RFID;

		Login_RFID = RFID_Exec_Leitura();

		LogTerm(Login_RFID);


		if (Login_RFID.substring(0,2) == "1|")
		{
			Login_RFID = Login_RFID.substring(2);

			String ret;

			
			BUZZER_TocaSom("SUCESSO");


			ret = SD_TestaCartao();

			LogTerm(ret);	


			ret = BANCO_GetUserFromLogin(Login_RFID, "RFID");

			LogTerm(ret);	



		}
		else
		{

			BUZZER_TocaSom("ERRO");

			// ocorreu um erro. imprime a msg de erro na tela
			if (gTela_Hardware == "TERMINAL")
			{  
				LogTerm("Ocorreu um erro ao realizar a leitura do cartao/chaveiro RFID:");
				LogTerm(Login_RFID.substring(2));


			}

			if (gTela_Hardware == "ER-TFTM070-5")
			{  

				TELA_LimpaTela();

				TELA_Render_MsgBox("Ocorreu um erro ao realizar a leitura do cartao/chaveiro RFID: " + Login_RFID.substring(2));

				delay(7000);

				TELA_LimpaTela();

				gTelaRenderizada_MSGBOX = false;
				gTelaRenderizada_LER_RFID = false;
				

			}
			
		}

		









		gModoOperacao_SubTela = "";	
		gTelaRenderizada_LER_RFID = false;

		TELA_LimpaTela();

		delay(500);   

	}


}



void TELA_VerificaTouch_LER_RFID()
{

	if (gTela_Hardware == "ER-TFTM070-5")
	{  



		//tft.changeMode(GRAPHIC);

		if (tft.touchDetect())
		{

			tft.touchReadPixel(&gTouch_X, &gTouch_Y);

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


