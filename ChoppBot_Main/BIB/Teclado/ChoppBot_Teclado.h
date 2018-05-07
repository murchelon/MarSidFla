





void TELA_Render_Interface_TECLADO(int Param_Inicio_X, int Param_Inicio_Y)
{

	if (gTela_Hardware == "TERMINAL")
	{ 
		if (gTelaRenderizada_TecNum == false)
		{
			LogTerm("TECLADO NUMERICO");
			LogTerm("Valor ATUAL da gTeclado_ValAtual: " + gTeclado_ValAtual);
			LogTerm("Digite um valor numerico no console e tecle enter. Digite VOLTAR para voltar a tela anterior.");

			gTelaRenderizada_TecNum = true;	
		}		
	



	}

	if (gTela_Hardware == "ER-TFTM070-5")
	{  

		if (gTelaRenderizada_TecNum == false)
		{
		  	
		  	//LogTerm("TELA_Render_Interface_TECLADO");

		  	gTelaRenderizada_TecNum = true;

		    // passo os parametros originais para vars internas
		    int Inicio_X = Param_Inicio_X;
		    int Inicio_Y = Param_Inicio_Y;


		    // debug: engessando para facilitar o debug
		    //Inicio_X = 500;
		    //Inicio_Y = 56;
		 
		 	// var Inicio_X e Inicio_Y do teclado. É a var base que controla a posicao xy do teclado.
		 	// todas as outras posicoes sao relativas a estas vars para podermos mover o teclado na tela quando necessario
		 	// sao as vars que definem o inicio de todo o render dos botoes e outros objetos da tela


		    // tamanho dos botoes  
		    int Size_Botao_W = 70;
		    int Size_Botao_H = 70;

		    // tamanho do labelNum
		    int Size_LabelNum_W = 400;
		    int Size_LabelNum_H = 100;


		    // vars de controle de posicionamebto dos botoes
		    int Botoes_Offset_Inicio_H = 20;
		    int Botoes_Offset_EntreBot_H = 15;

		   	int Botoes_Offset_Inicio_W = 20;
			int Botoes_Offset_EntreBot_W = 15;

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
			String temp_pos_X= "";
			String temp_pos_Y = "";
			String temp_size_W = "";
			String temp_size_H = "";


		    // calcula o tamanho do fundo baseando-se nos botes
		    Size_Fundo_W = (3 * Size_Botao_W) + (2 * Botoes_Offset_EntreBot_W) + (2 * Botoes_Offset_Inicio_W);	
			Size_Fundo_H = (4 * Size_Botao_H) + (3 * Botoes_Offset_EntreBot_H) + (2 * Botoes_Offset_Inicio_H);	

		    // desenha o fundo do teclado
		    tft.fillRoundRect(Inicio_X, Inicio_Y, Size_Fundo_W, Size_Fundo_H, 20, RA8875_WHITE);



		    // desenha os botoes:

		    Botao_PosAtual_X = Inicio_X;
		    Botao_PosAtual_Y = Inicio_Y;





		    for (ContaLinha = 0 ; ContaLinha <= 3 ; ContaLinha++)
		    {
			    for (ContaBotao = 0 ; ContaBotao <= 2 ; ContaBotao++)
			    {

			    	//aTeclado_PosBotoes[ContaTxtBotao] = strTemp;

			    	ContaTxtBotao++;

			    	// pos inicial
				    Botao_PosAtual_X = Inicio_X + Botoes_Offset_Inicio_W;			    
				    Botao_PosAtual_Y = Inicio_Y + Botoes_Offset_Inicio_H; 
				       	
				    // incremento para cada botao
				    Botao_PosAtual_X = Botao_PosAtual_X + (ContaBotao * Size_Botao_W) + (ContaBotao * Botoes_Offset_EntreBot_W);
				    Botao_PosAtual_Y = Botao_PosAtual_Y + (ContaLinha * Size_Botao_H) + (ContaLinha * Botoes_Offset_EntreBot_W);
				       	
				       	


					switch (ContaTxtBotao) 
					{
						case 10:
							tft.fillRoundRect(Botao_PosAtual_X, Botao_PosAtual_Y, Size_Botao_W, Size_Botao_H, 10, RA8875_GREEN);
							break;

						case 12:
							tft.fillRoundRect(Botao_PosAtual_X, Botao_PosAtual_Y, Size_Botao_W, Size_Botao_H, 10, RA8875_GREEN);
							break;

						default:
							tft.fillRoundRect(Botao_PosAtual_X, Botao_PosAtual_Y, Size_Botao_W, Size_Botao_H, 10, RA8875_BLUE);
					}


					String temp_pos_X = FormatComZerosAesq(Botao_PosAtual_X);
					String temp_pos_Y = FormatComZerosAesq(Botao_PosAtual_Y);
					String temp_size_W = FormatComZerosAesq(Size_Botao_W);
					String temp_size_H = FormatComZerosAesq(Size_Botao_H);


					// armazena as posicoes dos botoes para uso no touch
					//aTeclado_PosBotoes[ContaTxtBotao - 1] = String("Pos: ") + ContaTxtBotao + String(" ") + temp_pos_X + String(",") + temp_size_W + String(",") + temp_pos_Y + String(",") + temp_size_H;
					aTeclado_PosBotoes[ContaTxtBotao - 1] = temp_pos_X + String(",") + temp_size_W + String(",") + temp_pos_Y + String(",") + temp_size_H;



			    }
			}
		    




			// Desenha os numeros nos botes		
			tft.setFontScale(1); 


			ContaTxtBotao = 0;
			
			BotoesTxt_Offset_Inicio_W = (Size_Botao_W / 2) + 11;
			BotoesTxt_Offset_Inicio_H = (Size_Botao_H / 2) + 2;


		    for (ContaLinha = 0 ; ContaLinha <= 3 ; ContaLinha++)
		    {
			    for (ContaBotao = 0 ; ContaBotao <= 2 ; ContaBotao++)
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
						case 10:
							tft.setCursor(Botao_PosAtual_X - 9, Botao_PosAtual_Y);
							tft.setTextColor(RA8875_BLACK);
							tft.print ("<<");
							break;

						case 11:
							tft.setCursor(Botao_PosAtual_X, Botao_PosAtual_Y);
							tft.setTextColor(RA8875_WHITE);
							tft.print ("0");
							break;

						case 12:
							tft.setCursor(Botao_PosAtual_X - 6, Botao_PosAtual_Y);
							tft.setTextColor(RA8875_BLACK);
							tft.print ("OK");
							break;

						default:
							tft.setCursor(Botao_PosAtual_X, Botao_PosAtual_Y);
							tft.setTextColor(RA8875_WHITE);
							tft.print (String(ContaTxtBotao));
					}	
			    }
			}
		    
			// Texto da tela:
		    tft.setTextColor(RA8875_WHITE);
		    tft.setFontScale(2); 
		    tft.setCursor (Inicio_X - 430, Inicio_Y); 
		    tft.print ("Digite o valor:");			    


		    // LabelNum
		    Size_LabelNum_W = 370;
		    Size_LabelNum_H = 60;

		    LabelNum_PosAtual_X = Inicio_X - 430;
			LabelNum_PosAtual_Y = Inicio_Y + 75;

			tft.fillRoundRect(LabelNum_PosAtual_X, LabelNum_PosAtual_Y, Size_LabelNum_W, Size_LabelNum_H, 5, RA8875_YELLOW);

			// adiciona posicoes do labelnum para touch
			aTeclado_PosBotoes[12] = LabelNum_PosAtual_X + String(",") + Size_LabelNum_W + String(",") + LabelNum_PosAtual_Y + String(",") + Size_LabelNum_H;


			// Botao Voltar

		    btnVoltar_PosAtual_X = Inicio_X - (430 / 2) - (150 / 2) - 32;
			btnVoltar_PosAtual_Y = Inicio_Y + Size_Fundo_H - 85;

			tft.fillRoundRect(btnVoltar_PosAtual_X, btnVoltar_PosAtual_Y, 170, 60, 5, RA8875_BLUE);

		    tft.setTextColor(RA8875_WHITE);
		    tft.setFontScale(1); 
		    tft.setCursor (btnVoltar_PosAtual_X + (60 / 2) - 18, btnVoltar_PosAtual_Y + 11); 
		    tft.print ("<< Voltar");

			// adiciona posicoes do voltar para touch
			aTeclado_PosBotoes[13] = btnVoltar_PosAtual_X + String(",170,") + btnVoltar_PosAtual_Y + String(",60");

		}

	}

}


void TELA_Render_ValorTec_TECLADO()
{
	if (gTela_Hardware == "ER-TFTM070-5")
	{  

		//gTeclado_ValAtual = "123456789012345";

		// posicoes do box labelnum
		//String temp_pos_X_box = getValue(aTeclado_PosBotoes[13], ',', 0);
		//String temp_size_W_box = getValue(aTeclado_PosBotoes[13], ',', 1);
		//String temp_pos_Y_box = getValue(aTeclado_PosBotoes[13], ',', 2);
		//String temp_size_H_box = getValue(aTeclado_PosBotoes[13], ',', 3);

		//tft.fillRoundRect(temp_pos_X_box.toInt() , temp_pos_Y_box.toInt(), temp_size_W_box.toInt(), temp_size_H_box.toInt(), 5, RA8875_YELLOW);



		String temp_pos_X = getValue(aTeclado_PosBotoes[12], ',', 0);
		String temp_size_W = getValue(aTeclado_PosBotoes[12], ',', 1);
		String temp_pos_Y = getValue(aTeclado_PosBotoes[12], ',', 2);
		String temp_size_H = getValue(aTeclado_PosBotoes[12], ',', 3);




	    tft.setTextColor(RA8875_BLACK, RA8875_YELLOW);
	    tft.setFontScale(2); 
	    tft.setCursor (temp_pos_X.toInt() + 3, temp_pos_Y.toInt() + 2); 
	    tft.print (gTeclado_ValAtual);	




	  	
  	}	
}



void TELA_VerificaTouch_TECLADO()
{

	if (gTela_Hardware == "TERMINAL")
	{  

		String retConsole;

		retConsole = ReadConsoleInput();

		if (retConsole != "") 
		{
			
			LogTerm("Valor digitado: " + retConsole);
				

			gTeclado_ValAtual = retConsole;			
				
			LogTerm("Valor NOVO da gTeclado_ValAtual: " + gTeclado_ValAtual);	

			gTelaRenderizada_TecNum = false;


			gModoOperacao = "LOGIN";				

		}


		if ((retConsole == "VOLTAR") || (retConsole == "voltar"))
		{
			LogTerm("VOLTAR");

			gTelaRenderizada_TecNum = false;
			//gTeclado_ValAtual = "";


			gModoOperacao = "LOGIN";			
		}

	}







	if (gTela_Hardware == "ER-TFTM070-5")
	{  

		if (tft.touchDetect())
		{

			tft.touchReadPixel(&gTouch_X, &gTouch_Y);

			gTouch_X = 800 - gTouch_X;
			gTouch_Y = 480 - gTouch_Y;
			



			//TELA_LogTerm_XY(); 

			for(int x = 0 ; x <= ctTECLADO_TOTAL_BOTOES - 1 ; x++)
			{
				String temp_pos_X = getValue(aTeclado_PosBotoes[x], ',', 0);
				String temp_size_W = getValue(aTeclado_PosBotoes[x], ',', 1);
				String temp_pos_Y = getValue(aTeclado_PosBotoes[x], ',', 2);
				String temp_size_H= getValue(aTeclado_PosBotoes[x], ',', 3);



				if (temp_size_H != "TAM")
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
								LogTerm(x + 1);
								//----


								switch (x) 
								{
									case 9:			// tecla << backspace:

										if (gTeclado_ValAtual.length() >= 0)
										{
											gTeclado_ValAtual = gTeclado_ValAtual.substring(0, gTeclado_ValAtual.length() - 1);


											String temp_pos_X_limpa = getValue(aTeclado_PosBotoes[12], ',', 0);
											String temp_size_W_limpa = getValue(aTeclado_PosBotoes[12], ',', 1);
											String temp_pos_Y_limpa = getValue(aTeclado_PosBotoes[12], ',', 2);
											String temp_size_H_limpa = getValue(aTeclado_PosBotoes[12], ',', 3);


										    tft.setTextColor(RA8875_BLACK, RA8875_YELLOW);
										    tft.setFontScale(2); 
										    tft.setCursor (temp_pos_X_limpa.toInt() + 3, temp_pos_Y_limpa.toInt() + 2); 

										    tft.print ("               ");

										    tft.setCursor (temp_pos_X_limpa.toInt() + 3, temp_pos_Y_limpa.toInt() + 2);
											

										}

										break;


									case 10:		// tecla 0 (zero)

										if (gTeclado_ValAtual.length() <= 14)
										{
											gTeclado_ValAtual = gTeclado_ValAtual + String("0");
										}

										break;


									case 11:		// tecla OK:

									    tft.setTextColor(RA8875_RED);
									    tft.setFontScale(2); 
									    tft.setCursor (70, 210); 
									    tft.print ("Obrigado !");	


										break;


									case 12:		// labelnum - local onde exibe os numeros:

										break;


									case 13:		// botao voltar:

										TELA_LimpaTela();

										gTelaRenderizada_TecNum = false;
										gTeclado_ValAtual = "";

	

										gModoOperacao = "LOGIN";
										//gModoOperacao = "INICIO";
										//gModoOperacao = "LOGIN";
										//gModoOperacao = "OPERACAO";
										//gModoOperacao = "DEBUG";

										
										delay(700);

										break;

									default:

										if (gTeclado_ValAtual.length() <= 14)
										{
											gTeclado_ValAtual = gTeclado_ValAtual + String(x + 1);
										}

								}





								
								TELA_Render_ValorTec_TECLADO();

								// -----------------------------------

								gBounce_time_inicio = millis();
							}


							gBounce_time_atual = millis();
							gBounce_time_tempo_passado = gBounce_time_atual - gBounce_time_inicio;

							gBounce_SegundosPassados = floor(gBounce_time_tempo_passado / 1000);

							LogTerm(gBounce_time_tempo_passado);

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


void TELA_RenderTecUnificado_NUM()
{

	TELA_Render_Interface_TECLADO(500, 56);   // posicao x e y
	TELA_Render_ValorTec_TECLADO();	
}

