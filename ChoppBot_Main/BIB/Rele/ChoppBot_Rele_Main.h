




void TELA_Render_Interface_OPERACAO_SERVICO()
{
	
	//LogTerm(gTela_Hardware);


	if (gTelaRenderizada_OPERACAO_SERVICO == false)
	{

        //LogTerm(F("== [Modo Atual: STANDBY] ==");


		if (gTela_Hardware == F("TERMINAL"))
		{  
			LogTerm(F("Encoste o cartao ou chaveiro de identificacao no leitor..."));
			//LogTerm(F("Digite algo no teclado para voltar");

		}

		if (gTela_Hardware == F("ER-TFTM070-5"))
		{  

			tft.setTextColor(RA8875_YELLOW);
			tft.setFontScale(1); 

			tft.setCursor (100, 100);
			tft.print (F("Chopp: Chopp X"));    

			tft.setCursor (100, 145);
			tft.print (String(F("Usuario: ")) + String(gSessao_Nome)); 

			tft.setCursor (100, 190);
			tft.print (F("Seu saldo atual e: ")); 
			
			tft.setCursor (100, 235);
			tft.print (F("Torneira liberada: Pode se servir !")); 
			


		    int btnVoltar_PosAtual_X = 100;
			int btnVoltar_PosAtual_Y = 360;

			tft.fillRoundRect(btnVoltar_PosAtual_X, btnVoltar_PosAtual_Y, 170, 60, 5, RA8875_BLUE);

		    tft.setTextColor(RA8875_WHITE);
		    tft.setFontScale(1); 
		    tft.setCursor (btnVoltar_PosAtual_X + (60 / 2) - 18, btnVoltar_PosAtual_Y + 11); 
		    tft.print (F("<< Voltar"));			

		}

		gTelaRenderizada_OPERACAO_SERVICO = true;


		delay(4000);



		gModoOperacao_SubTela = F("");	
		gTelaRenderizada_OPERACAO_SERVICO = false;

		TELA_LimpaTela();

		delay(500);   

	}


}



void TELA_VerificaTouch_OPERACAO_SERVICO()
{

	if (gTela_Hardware == F("ER-TFTM070-5"))
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


