

bool gTeclado_Renderizado = false;



const int TECLADO_TOTAL_BOTOES = 12;




String aTeclado_PosBotoes[TECLADO_TOTAL_BOTOES]={"X01,TAM,Y01,TAM",
												"X02,TAM,Y02,TAM",
												"X03,TAM,Y03,TAM",
												"X04,TAM,Y04,TAM",
												"X05,TAM,Y05,TAM",
												"X06,TAM,Y06,TAM",
												"X07,TAM,Y07,TAM",
												"X08,TAM,Y08,TAM",
												"X09,TAM,Y09,TAM",
												"X10,TAM,Y10,TAM",
												"X11,TAM,Y11,TAM",
												"X12,TAM,Y12,TAM"
												};




void TELA_Render_Interface_TECLADO(int Param_Inicio_X, int Param_Inicio_Y)
{
  if (gTela_Hardware == "ER-TFTM070-5")
  {  

  	if (gTeclado_Renderizado == false)
  	{
	  	
	  	//LogTerm("TELA_Render_Interface_TECLADO");

	  	gTeclado_Renderizado = true;

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



				//char strTemp[16]; 

				//strTemp = "";

				aTeclado_PosBotoes[0] = "cwcwwecwec" + Botao_PosAtual_X; 

		    	if (ContaTxtBotao <= 9)
		    	{
			    	//sprintf(strTemp, "00%d,TAM,Y01,TAM", ContaTxtBotao); 
			    	//aTeclado_PosBotoes[0] = Botao_PosAtual_X + "," + Size_Botao_W + "," + Botao_PosAtual_Y + "," + Size_Botao_H;
			    	//aTeclado_PosBotoes[0] = "cwcwwecwec"; 
		    	}

		    	if ((ContaTxtBotao >= 10) && (ContaTxtBotao <= 99))
		    	{
			    	//sprintf(strTemp, "0%d,TAM,Y01,TAM", ContaTxtBotao);
			    	//aTeclado_PosBotoes[0] = Botao_PosAtual_X + "," + Size_Botao_W + "," + Botao_PosAtual_Y + "," + Size_Botao_H;  	    		
		    	}

		    	if ((ContaTxtBotao >= 100) && (ContaTxtBotao <= 999))
		    	{
		    		//sprintf(strTemp, "%d,TAM,Y01,TAM", ContaTxtBotao); 
		    		//aTeclado_PosBotoes[0] = Botao_PosAtual_X + "," + Size_Botao_W + "," + Botao_PosAtual_Y + "," + Size_Botao_H; 
		    		//aTeclado_PosBotoes[0] = Botao_PosAtual_X + ","; 

		    	}

		    	if (ContaTxtBotao >= 1000)
		    	{
		    		//sprintf(strTemp, "999,TAM,Y01,TAM", ContaTxtBotao); 
		    		//aTeclado_PosBotoes[0] = Botao_PosAtual_X + "," + Size_Botao_W + "," + Botao_PosAtual_Y + "," + Size_Botao_H;
		    	}

				//"X12,TAM,Y12,TAM"	
		    	
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
			       	
		    	//tft.fillRoundRect(Botao_PosAtual_X, BBotao_PosAtual_Yotao_PosAtual_Y, Size_Botao_W, Size_Botao_H, 10, RA8875_BLUE);

				
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

	    btnVoltar_PosAtual_X = Inicio_X - (430 / 2) - (150 / 2) - 20;
		btnVoltar_PosAtual_Y = Inicio_Y + Size_Fundo_H - 60;

		tft.fillRoundRect(LabelNum_PosAtual_X, LabelNum_PosAtual_Y, Size_LabelNum_W, Size_LabelNum_H, 5, RA8875_YELLOW);

		// Botao Voltar
		tft.fillRoundRect(btnVoltar_PosAtual_X, btnVoltar_PosAtual_Y, 150, 60, 5, RA8875_BLUE);
	    tft.setTextColor(RA8875_WHITE);
	    tft.setFontScale(1); 
	    tft.setCursor (btnVoltar_PosAtual_X + (60 / 2) - 2, btnVoltar_PosAtual_Y + 13); 
	    tft.print ("Voltar");	
  	}



  }

}


    
 
        
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


String posX_Inicio = "";
String posX_Fim = "";
String posY_Inicio = "";
String posY_Fim = "";


void TELA_VerificaTouch_TECLADO()
{

  if (gTela_Hardware == "ER-TFTM070-5")
  {  

    if (tft.touchDetect())
    {

		

		tft.touchReadPixel(&gTouch_X, &gTouch_Y);

		gTouch_X = 800 - gTouch_X;
		gTouch_Y = 480 - gTouch_Y;

		//TELA_LogTerm_XY(); 

		for(int x = 0 ; x <= TECLADO_TOTAL_BOTOES - 1 ; x++)
		{



			//TELA_Texto(aTeclado_PosBotoes[x], "BRANCO");
			//LogTerm(aTeclado_PosBotoes[x]);

			String posX_Inicio = getValue(aTeclado_PosBotoes[x], ',', 0);
			String posX_Fim = getValue(aTeclado_PosBotoes[x], ',', 1);
			String posY_Inicio = getValue(aTeclado_PosBotoes[x], ',', 2);
			String posY_Fim = getValue(aTeclado_PosBotoes[x], ',', 3);

			//char TheTexto[100]; 
			
			//sprintf(TheTexto, "aTeclado_PosBotoes[%d] = %c", x, aTeclado_PosBotoes[x]);

			LogTerm(aTeclado_PosBotoes[x]);

		}


    }

  }

}
