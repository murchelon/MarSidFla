


String GetCharForTecAlfa(int Index)
{

	String ret;

	ret = String(Index);

	if (Index <= 9) {ret = String(Index);}
	if (Index == 10) {ret = String(F("0"));}
	if (Index == 20) {ret = String(F("<<"));}
	if (Index == 30) {ret = String(F("ESP"));}
	if (Index == 40) {ret = String(F("OK"));}

	if (Index == 11) {ret = String(F("Q"));}
	if (Index == 12) {ret = String(F("W"));}
	if (Index == 13) {ret = String(F("E"));}
	if (Index == 14) {ret = String(F("R"));}
	if (Index == 15) {ret = String(F("T"));}
	if (Index == 16) {ret = String(F("Y"));}
	if (Index == 17) {ret = String(F("U"));}
	if (Index == 18) {ret = String(F("I"));}
	if (Index == 19) {ret = String(F("O"));}
	if (Index == 21) {ret = String(F("A"));}
	if (Index == 22) {ret = String(F("S"));}
	if (Index == 23) {ret = String(F("D"));}
	if (Index == 24) {ret = String(F("F"));}
	if (Index == 25) {ret = String(F("G"));}
	if (Index == 26) {ret = String(F("H"));}
	if (Index == 27) {ret = String(F("J"));}
	if (Index == 28) {ret = String(F("K"));}
	if (Index == 29) {ret = String(F("L"));}
	if (Index == 31) {ret = String(F("Z"));}
	if (Index == 32) {ret = String(F("X"));}
	if (Index == 33) {ret = String(F("C"));}
	if (Index == 34) {ret = String(F("V"));}
	if (Index == 35) {ret = String(F("B"));}
	if (Index == 36) {ret = String(F("N"));}
	if (Index == 37) {ret = String(F("M"));}
	if (Index == 38) {ret = String(F("P"));}
	if (Index == 39) {ret = String(F(","));}

	return ret;
}


void TELA_Render_Interface_TECLADO_ALFA(int Param_Inicio_X, int Param_Inicio_Y)
{

	if (gTela_Hardware == F("TERMINAL"))
	{ 
		if (gTelaRenderizada_TecAlfa == false)
		{
			LogTerm(F("TECLADO ALFA"));
			LogTerm(String(F("Valor ATUAL da gTecladoAlfa_ValAtual: ")) + gTecladoAlfa_ValAtual);
			LogTerm(F("Digite um texto no console e tecle enter. Digite VOLTAR para voltar a tela anterior."));

			gTelaRenderizada_TecAlfa = true;	
		}		
	



	}

	if (gTela_Hardware == F("ER-TFTM070-5"))
	{  

		if (gTelaRenderizada_TecAlfa == false)
		{
		  	
		  	//LogTerm("TELA_Render_Interface_TECLADO");

		  	gTelaRenderizada_TecAlfa = true;

		    // passo os parametros originais para vars internas
		    int Inicio_X = Param_Inicio_X;
		    int Inicio_Y = Param_Inicio_Y;


		    // debug: engessando para facilitar o debug
		    //Inicio_X = 13;
		    //Inicio_Y = 198;
		 
		 	// var Inicio_X e Inicio_Y do teclado. É a var base que controla a posicao xy do teclado.
		 	// todas as outras posicoes sao relativas a estas vars para podermos mover o teclado na tela quando necessario
		 	// sao as vars que definem o inicio de todo o render dos botoes e outros objetos da tela


		    // tamanho dos botoes  
		    int Size_Botao_W = 65;
		    int Size_Botao_H = 55;

		    // tamanho do labelNum
		    int Size_LabelNum_W = 780;
		    int Size_LabelNum_H = 500;


		    // vars de controle de posicionamebto dos botoes
		    int Botoes_Offset_Inicio_H = 15;
		    int Botoes_Offset_EntreBot_H = 10;

		   	int Botoes_Offset_Inicio_W = 15;
			int Botoes_Offset_EntreBot_W = 10;

			int ContaBotao = 0;
			int ContaLinha = 0;

		    int Botao_PosAtual_X = 0;
			int Botao_PosAtual_Y = 0;

		 	// fundo
		    int Size_Fundo_W = 0;
		    int Size_Fundo_H = 0; 

		    // vars que marcam o posicionamento do texto dentro dos botoes
			int BotoesTxt_Offset_Inicio_W = 0;
			int BotoesTxt_Offset_Inicio_H = 0;

			int ContaTxtBotao = 0;


		    // vars de controle de posicionamebto do labelnum
		    int LabelNum_PosAtual_X = 0;
		    int LabelNum_PosAtual_Y = 0;

			// vars de controle de posicionamebto do botao voltar
		    int btnVoltar_PosAtual_X = 0;
			int btnVoltar_PosAtual_Y = 0;


			// vars auxiliares para armazenar as posicoes dos botoes senhdo renderizados
			String temp_pos_X= F("");
			String temp_pos_Y = F("");
			String temp_size_W = F("");
			String temp_size_H = F("");


		    // calcula o tamanho do fundo baseando-se nos botes
		    Size_Fundo_W = (10 * Size_Botao_W) + (9 * Botoes_Offset_EntreBot_W) + (2 * Botoes_Offset_Inicio_W);	
			Size_Fundo_H = (4 * Size_Botao_H) + (3 * Botoes_Offset_EntreBot_H) + (2 * Botoes_Offset_Inicio_H);	

		    // desenha o fundo do teclado
		    tft.fillRoundRect(Inicio_X, Inicio_Y, Size_Fundo_W, Size_Fundo_H, 20, RA8875_WHITE);



		    // desenha os botoes:

		    Botao_PosAtual_X = Inicio_X;
		    Botao_PosAtual_Y = Inicio_Y;


			// debug
			//gTecladoAlfa_ValAtual = "123456789012345678901234567890123";


		    for (ContaLinha = 0 ; ContaLinha <= 3 ; ContaLinha++)
		    {
			    for (ContaBotao = 0 ; ContaBotao <= 9 ; ContaBotao++)
			    {

			    	//aTecladoAlfa_PosBotoes[ContaTxtBotao] = strTemp;

			    	ContaTxtBotao++;

			    	// pos inicial
				    Botao_PosAtual_X = Inicio_X + Botoes_Offset_Inicio_W;			    
				    Botao_PosAtual_Y = Inicio_Y + Botoes_Offset_Inicio_H; 
				       	
				    // incremento para cada botao
				    Botao_PosAtual_X = Botao_PosAtual_X + (ContaBotao * Size_Botao_W) + (ContaBotao * Botoes_Offset_EntreBot_W);
				    Botao_PosAtual_Y = Botao_PosAtual_Y + (ContaLinha * Size_Botao_H) + (ContaLinha * Botoes_Offset_EntreBot_W);
				       	
				       	


					switch (ContaTxtBotao) 
					{
						case 20:
							tft.fillRoundRect(Botao_PosAtual_X, Botao_PosAtual_Y, Size_Botao_W, Size_Botao_H, 10, RA8875_GREEN);
							break;

						case 30:
							tft.fillRoundRect(Botao_PosAtual_X, Botao_PosAtual_Y, Size_Botao_W, Size_Botao_H, 10, RA8875_GREEN);
							break;

						case 40:
							tft.fillRoundRect(Botao_PosAtual_X, Botao_PosAtual_Y, Size_Botao_W, Size_Botao_H, 10, RA8875_RED);
							break;

						default:
							tft.fillRoundRect(Botao_PosAtual_X, Botao_PosAtual_Y, Size_Botao_W, Size_Botao_H, 10, RA8875_BLUE);

							break;
					}


					String temp_pos_X = FormatComZerosAesq(Botao_PosAtual_X);
					String temp_pos_Y = FormatComZerosAesq(Botao_PosAtual_Y);
					String temp_size_W = FormatComZerosAesq(Size_Botao_W);
					String temp_size_H = FormatComZerosAesq(Size_Botao_H);


					// armazena as posicoes dos botoes para uso no touch
					//aTecladoAlfa_PosBotoes[ContaTxtBotao - 1] = String("Pos: ") + ContaTxtBotao + String(" ") + temp_pos_X + String(",") + temp_size_W + String(",") + temp_pos_Y + String(",") + temp_size_H;
					aTecladoAlfa_PosBotoes[ContaTxtBotao - 1] = temp_pos_X + String(F(",")) + temp_size_W + String(F(",")) + temp_pos_Y + String(F(",")) + temp_size_H;



			    }
			}
		    




			// Desenha os numeros nos botes		
			tft.setFontScale(1); 


			ContaTxtBotao = 0;
			
			BotoesTxt_Offset_Inicio_W = (Size_Botao_W / 2) + 11;
			BotoesTxt_Offset_Inicio_H = (Size_Botao_H / 2) + 2;


		    for (ContaLinha = 0 ; ContaLinha <= 3 ; ContaLinha++)
		    {
			    for (ContaBotao = 0 ; ContaBotao <= 9 ; ContaBotao++)
			    {  	

			    	// pos inicial
				    Botao_PosAtual_X = Inicio_X + BotoesTxt_Offset_Inicio_W;			    
				    Botao_PosAtual_Y = Inicio_Y + BotoesTxt_Offset_Inicio_H; 
				       	
				    // incremento para cada botao
				    Botao_PosAtual_X = Botao_PosAtual_X + (ContaBotao * Size_Botao_W) + (ContaBotao * Botoes_Offset_EntreBot_W);
				    Botao_PosAtual_Y = Botao_PosAtual_Y + (ContaLinha * Size_Botao_H) + (ContaLinha * Botoes_Offset_EntreBot_W);
				       	

					
				    ContaTxtBotao++;

					switch (ContaTxtBotao) 
					{
						case 20:		// <<
							tft.setCursor(Botao_PosAtual_X - 15, Botao_PosAtual_Y - 4);
							tft.setTextColor(RA8875_BLACK);							
							break;

						case 30:		// ESP
							tft.setCursor(Botao_PosAtual_X - 18, Botao_PosAtual_Y - 4);
							tft.setTextColor(RA8875_BLACK);
							break;

						case 40:		// OK
							tft.setCursor(Botao_PosAtual_X - 11, Botao_PosAtual_Y - 4);
							tft.setTextColor(RA8875_WHITE);
							break;

						default:		// OUTROS BOTOES
							tft.setCursor(Botao_PosAtual_X - 4, Botao_PosAtual_Y - 4);
							tft.setTextColor(RA8875_WHITE);
					}	

					tft.print (GetCharForTecAlfa(ContaTxtBotao));

			    }
			}
		    

		    
			// Texto da tela:
		    tft.setTextColor(RA8875_WHITE);
		    tft.setFontScale(1); 
		    tft.setCursor (Inicio_X, Inicio_Y - 190); 
		    tft.print (F("Digite o texto desejado:"));			    

		 


		    // LabelNum
		    Size_LabelNum_W = 550;
		    Size_LabelNum_H = 35;

		    LabelNum_PosAtual_X = Inicio_X;
			LabelNum_PosAtual_Y = Inicio_Y - 140;


		 	if (gModoDebug == true)
		 	{
		 		// frame
		 		tft.fillRoundRect(LabelNum_PosAtual_X, LabelNum_PosAtual_Y, 550, 109, 0, RA8875_WHITE);

			 	// linha1		 	
				tft.fillRoundRect(LabelNum_PosAtual_X + 2, LabelNum_PosAtual_Y + 2, Size_LabelNum_W - 4, Size_LabelNum_H, 0, RA8875_MAGENTA);
				// linha2
				tft.fillRoundRect(LabelNum_PosAtual_X + 2, LabelNum_PosAtual_Y + 2 + 1 * Size_LabelNum_H, Size_LabelNum_W - 4, Size_LabelNum_H, 0, RA8875_GREEN);
				// linha3
				tft.fillRoundRect(LabelNum_PosAtual_X + 2, LabelNum_PosAtual_Y + 2 + 2 * Size_LabelNum_H, Size_LabelNum_W - 4, Size_LabelNum_H, 0, RA8875_BLUE);
		 	}
		 	else
		 	{
		 		// frame
		 		tft.fillRoundRect(LabelNum_PosAtual_X, LabelNum_PosAtual_Y, 550, 109, 0, RA8875_WHITE);

			 	// linha1		 	
				tft.fillRoundRect(LabelNum_PosAtual_X + 2, LabelNum_PosAtual_Y + 2, Size_LabelNum_W - 4, Size_LabelNum_H, 0, RA8875_BLUE);
				// linha2
				tft.fillRoundRect(LabelNum_PosAtual_X + 2, LabelNum_PosAtual_Y + 2 + 1 * Size_LabelNum_H, Size_LabelNum_W - 4, Size_LabelNum_H, 0, RA8875_BLUE);
				// linha3
				tft.fillRoundRect(LabelNum_PosAtual_X + 2, LabelNum_PosAtual_Y + 2 + 2 * Size_LabelNum_H, Size_LabelNum_W - 4, Size_LabelNum_H, 0, RA8875_BLUE);
		 	}


			// adiciona posicoes do labelnum para touch
			aTecladoAlfa_PosBotoes[ContaTxtBotao] = LabelNum_PosAtual_X + String(F(",")) + Size_LabelNum_W + String(F(",")) + LabelNum_PosAtual_Y + String(F(",")) + Size_LabelNum_H;
			
		


			// Botao Voltar

		    btnVoltar_PosAtual_X = Inicio_X + 597;
			btnVoltar_PosAtual_Y = Inicio_Y - 160;

			tft.fillRoundRect(btnVoltar_PosAtual_X, btnVoltar_PosAtual_Y, 170, 60, 5, RA8875_BLUE);

		    tft.setTextColor(RA8875_WHITE);
		    tft.setFontScale(1); 
		    tft.setCursor (btnVoltar_PosAtual_X + 12, btnVoltar_PosAtual_Y + 11); 
		    tft.print (F("<< Voltar"));

			// adiciona posicoes do voltar para touch
			aTecladoAlfa_PosBotoes[ContaTxtBotao + 1] = btnVoltar_PosAtual_X + String(F(",170,")) + btnVoltar_PosAtual_Y + String(F(",60"));
			//aTecladoAlfa_PosBotoes[ContaTxtBotao + 1] = String("000,000,000,000");

			


		}

	}

}


void TELA_Render_ValorTec_TECLADO_ALFA()
{
	if (gTela_Hardware == F("ER-TFTM070-5"))
	{  


		int ContaLinha;

		//gTecladoAlfa_ValAtual = "123456789012345";

		// posicoes do box labelnum
		//String temp_pos_X_box = getValue(aTecladoAlfa_PosBotoes[13], ',', 0);
		//String temp_size_W_box = getValue(aTecladoAlfa_PosBotoes[13], ',', 1);
		//String temp_pos_Y_box = getValue(aTecladoAlfa_PosBotoes[13], ',', 2);
		//String temp_size_H_box = getValue(aTecladoAlfa_PosBotoes[13], ',', 3);

		//tft.fillRoundRect(temp_pos_X_box.toInt() , temp_pos_Y_box.toInt(), temp_size_W_box.toInt(), temp_size_H_box.toInt(), 5, RA8875_YELLOW);

		if (gModoDebug == true)
		{
			tft.setCursor (480, 20); 
			tft.print (String(F("Tam ValAtual = ")) + String(gTecladoAlfa_ValAtual.length()));
		}



		String temp_pos_X = getValue(aTecladoAlfa_PosBotoes[40], ',', 0);
		String temp_size_W = getValue(aTecladoAlfa_PosBotoes[40], ',', 1);
		String temp_pos_Y = getValue(aTecladoAlfa_PosBotoes[40], ',', 2);
		String temp_size_H = getValue(aTecladoAlfa_PosBotoes[40], ',', 3);


		tft.setFontScale(1); 


	 	if (gModoDebug == true)
	 	{
	 		tft.setTextColor(RA8875_BLACK, RA8875_YELLOW);
	 	}
	 	else
	 	{
	 		tft.setTextColor(RA8875_WHITE, RA8875_BLUE);
	 	}
	    

	 	// 3 linhas debug
	    //gTecladoAlfa_ValAtual = "123456789012345678901234567890123456789012345678901234567890123456789wefwefwefwefwef";


	 	if (gTecladoAlfa_ValAtual.length() <= 34)
	 	{
	 		ContaLinha = 1;
	 		tft.setCursor (temp_pos_X.toInt() + 3, temp_pos_Y.toInt() + 3 + ((ContaLinha - 1) * 35)); 
	 		tft.print (gTecladoAlfa_ValAtual);

	 	}
	 	else if ((gTecladoAlfa_ValAtual.length() > 34) && (gTecladoAlfa_ValAtual.length() <= 68))
	 	{
	 		ContaLinha = 1;
	 		tft.setCursor (temp_pos_X.toInt() + 3, temp_pos_Y.toInt() + 3 + ((ContaLinha - 1) * 35)); 
	 		tft.print (gTecladoAlfa_ValAtual.substring(0, 34));

	 		ContaLinha = 2;
	 		tft.setCursor (temp_pos_X.toInt() + 3, temp_pos_Y.toInt() + 3 + ((ContaLinha - 1) * 35)); 
	 		tft.print (gTecladoAlfa_ValAtual.substring(34, 68));


	 	}
	 	else if (gTecladoAlfa_ValAtual.length() >= 69) 
	 	{
	 		ContaLinha = 1;
	 		tft.setCursor (temp_pos_X.toInt() + 3, temp_pos_Y.toInt() + 3 + ((ContaLinha - 1) * 35)); 
	 		tft.print (gTecladoAlfa_ValAtual.substring(0, 34));

	 		ContaLinha = 2;
	 		tft.setCursor (temp_pos_X.toInt() + 3, temp_pos_Y.toInt() + 3 + ((ContaLinha - 1) * 35)); 
	 		tft.print (gTecladoAlfa_ValAtual.substring(34, 68));

	 		ContaLinha = 3;
	 		tft.setCursor (temp_pos_X.toInt() + 3, temp_pos_Y.toInt() + 3 + ((ContaLinha - 1) * 35)); 
	 		tft.print (gTecladoAlfa_ValAtual.substring(68));
	 	}

	    tft.setCursor (temp_pos_X.toInt() + 3, temp_pos_Y.toInt() + 3); 
	    
	    	




	  	
  	}	
}



void TELA_VerificaTouch_TECLADO_ALFA()
{

	if (gTela_Hardware == F("TERMINAL"))
	{  

		String retConsole;

		retConsole = ReadConsoleInput();

		if (retConsole != F(""))
		{
			
			LogTerm(String(F("Valor digitado: ")) + retConsole);
				

			gTecladoAlfa_ValAtual = retConsole;			
				
			LogTerm(String(F("Valor NOVO da gTecladoAlfa_ValAtual: ")) + gTecladoAlfa_ValAtual);	

			gTelaRenderizada_TecAlfa = false;


			gModoOperacao = F("LOGIN");				

		}


		if ((retConsole == F("VOLTAR")) || (retConsole == F("voltar")))
		{
			LogTerm(F("VOLTAR"));

			gTelaRenderizada_TecAlfa = false;
			//gTecladoAlfa_ValAtual = "";


			gModoOperacao = F("LOGIN");			
		}

	}




	//LogTerm("gTecladoAlfa_ValAtual.length() = " + String(gTecladoAlfa_ValAtual.length()));

	if (gTela_Hardware == F("ER-TFTM070-5"))
	{  

		if (tft.touchDetect())
		{

			tft.touchReadPixel(&gTouch_X, &gTouch_Y);

			gTouch_X = 800 - gTouch_X;
			gTouch_Y = 480 - gTouch_Y;
			



			//TELA_LogTerm_XY(); 

			for(int x = 0 ; x <= ctTECLADO_ALFA_TOTAL_BOTOES - 1 ; x++)
			{
				String temp_pos_X = getValue(aTecladoAlfa_PosBotoes[x], ',', 0);
				String temp_size_W = getValue(aTecladoAlfa_PosBotoes[x], ',', 1);
				String temp_pos_Y = getValue(aTecladoAlfa_PosBotoes[x], ',', 2);
				String temp_size_H= getValue(aTecladoAlfa_PosBotoes[x], ',', 3);



				if (temp_size_H != F("TAM"))
				{


					if ((gTouch_X >= temp_pos_X.toInt()) && (gTouch_X <= temp_pos_X.toInt() + temp_size_W.toInt()))  
					{

						if ((gTouch_Y >= temp_pos_Y.toInt()) && (gTouch_Y <= temp_pos_Y.toInt() + temp_size_H.toInt())) 
						{



							// Esquema de DEBounce ---- inicio

							gBounce_ContaClick++;

							


							if (gBounce_ContaClick == 1)
							{
								// Local onde deve ocorrer o evento do clique. Ocorrera apenas 1 vez --------

								//debug:
								//TELA_Texto(String(x + 1), "BRANCO");
								//LogTerm(x + 1);
								//----

								//TELA_Texto(String(x), "BRANCO");

								//String TesteBug = "";


								switch (x) 
								{
									case 19:			// tecla << backspace:

										if (gTecladoAlfa_ValAtual.length() >= 0)
										{
											gTecladoAlfa_ValAtual = gTecladoAlfa_ValAtual.substring(0, gTecladoAlfa_ValAtual.length() - 1);


											String temp_pos_X_limpa = getValue(aTecladoAlfa_PosBotoes[40], ',', 0);
											String temp_size_W_limpa = getValue(aTecladoAlfa_PosBotoes[40], ',', 1);
											String temp_pos_Y_limpa = getValue(aTecladoAlfa_PosBotoes[40], ',', 2);
											String temp_size_H_limpa = getValue(aTecladoAlfa_PosBotoes[40], ',', 3);




										 	if (gModoDebug == true)
										 	{
										 		tft.setTextColor(RA8875_BLACK, RA8875_YELLOW);
										 	}
										 	else
										 	{
										 		tft.setTextColor(RA8875_WHITE, RA8875_BLUE);
										 	}



										 	int ContaLinha;

									 		ContaLinha = 1;
									 		tft.setCursor (temp_pos_X_limpa.toInt() + 3, temp_pos_Y_limpa.toInt() + 3 + ((ContaLinha - 1) * 35)); 
									 		tft.print (F("                                  "));

									 		ContaLinha = 2;
									 		tft.setCursor (temp_pos_X_limpa.toInt() + 3, temp_pos_Y_limpa.toInt() + 3 + ((ContaLinha - 1) * 35)); 
									 		tft.print (F("                                  "));

									 		ContaLinha = 3;
									 		tft.setCursor (temp_pos_X_limpa.toInt() + 3, temp_pos_Y_limpa.toInt() + 3 + ((ContaLinha - 1) * 35)); 
									 		tft.print (F("                                  "));

										    tft.setCursor (temp_pos_X_limpa.toInt() + 3, temp_pos_Y_limpa.toInt() + 3); 
					

										}

										break;


									case 29:		// tecla espaco:

										if (gTecladoAlfa_ValAtual.length() <= 101)
										{
											gTecladoAlfa_ValAtual = gTecladoAlfa_ValAtual + String(F(" "));
										}

										break;


									case 39:		// tecla OK:

									    //tft.setTextColor(RA8875_RED);
									    //tft.setFontScale(2); 
									    //tft.setCursor (70, 210); 
									    //tft.print ("Obrigado !");	

										TELA_LimpaTela();

										tft.setCursor (0,0); 
										for(int k = 0 ; k <= ctTECLADO_ALFA_TOTAL_BOTOES - 1 ; k++)
										{
											TELA_Texto(String(F("aTecladoAlfa_PosBotoes[")) + String(k) + String(F("] = ")) + aTecladoAlfa_PosBotoes[k], F("BRANCO"));
										}

										delay(6000);
										break;


									case 40:		// labelnum - local onde exibe o texto:

										break;

									case 41: 		// botao voltar:  41


										
										/*
										TesteBug = "PORRA !!!!   Tocou em X=" + String(gTouch_X) + " e Y=" + String(gTouch_Y) + 
												" -- testou:   X >> " + String(gTouch_X) + " >= " + String(temp_pos_X.toInt()) + " e " + String(gTouch_X) + " <= " + String(temp_pos_X.toInt() + temp_size_W.toInt()) +
												" -- Y >> " + String(gTouch_Y) + " >= " + String(temp_pos_Y.toInt()) + " e " + String(gTouch_Y) + " <= " + String(temp_pos_Y.toInt() + temp_size_H.toInt());
										*/
										//LogTerm(TesteBug);
										//TELA_Texto(TesteBug, "VERDE");

										TELA_LimpaTela();

										gTelaRenderizada_TecAlfa = false;
										gTecladoAlfa_ValAtual = F("");

	

										gModoOperacao = F("LOGIN");
										//gModoOperacao = "INICIO";
										//gModoOperacao = "LOGIN";
										//gModoOperacao = "OPERACAO";
										//gModoOperacao = "DEBUG";

										
										delay(700);

										break;


									case 90:		// botao voltar:  41

										
										TELA_LimpaTela();

										gTelaRenderizada_TecAlfa = false;
										gTecladoAlfa_ValAtual = F("");

	

										gModoOperacao = F("LOGIN");
										//gModoOperacao = "INICIO";
										//gModoOperacao = "LOGIN";
										//gModoOperacao = "OPERACAO";
										//gModoOperacao = "DEBUG";

										
										delay(700);

										break;

										
									default:

										if (gTecladoAlfa_ValAtual.length() <= 101)
										{
											gTecladoAlfa_ValAtual = gTecladoAlfa_ValAtual + GetCharForTecAlfa(x + 1);
										}

										break;
								}





								
								TELA_Render_ValorTec_TECLADO_ALFA();

								// -----------------------------------

								gBounce_time_inicio = millis();
							}


							gBounce_time_atual = millis();
							gBounce_time_tempo_passado = gBounce_time_atual - gBounce_time_inicio;

							gBounce_SegundosPassados = floor(gBounce_time_tempo_passado / 1000);

							//LogTerm(gBounce_time_tempo_passado);

							if (gBounce_SegundosPassados != gBounce_Last_SegundosPassados)
							{
								//LogTerm(time_tempo_passado);
							}



							if (gBounce_time_tempo_passado >= ctBOUNCE_SENSIB_BOTAO)
							{

								gBounce_ContaClick = 0;		

							}

							gBounce_Last_SegundosPassados = gBounce_SegundosPassados;

							// Esquema de DEBounce ---- FIM




						}

					}

				}	

					
				
			}




		}

	}

}


void TELA_RenderTecUnificado_ALFA()
{
	TELA_Render_Interface_TECLADO_ALFA(13, 198);   // posicao x e y
	TELA_Render_ValorTec_TECLADO_ALFA();	
}


