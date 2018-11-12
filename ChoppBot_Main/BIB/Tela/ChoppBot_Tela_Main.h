






// vars usadas para posicionamento de texto generico na tela
uint16_t gPosTxt_X = 0;
uint16_t gPosTxt_Y = 0;
uint16_t gTxtSize = 15;


// valores padrao de tamanho e altura dos botoes
int gTamBotao_W = 150;
int gTamBotao_H = 150;

// valores padrao de espacamento X e Y dos botoes. A altura é iniciada como -1 pois é definida posteriormente no codigo
int gOffset_W = 40;
int gOffset_H = -1;

// var que contem a posicao atual X para desenhar os botoes
int gPosicaoAtual_X = 0;

// total de botoes desenhados em uma determinada tela
int gTotalBotoes = 0;

// vers que contem o x e y de um touch na tela
volatile uint16_t gTouch_X;
volatile uint16_t gTouch_Y;



//bool gBotao1_Apertado = false;
//bool gBotao2_Apertado = false;
//bool gBotao3_Apertado = false;


// var com a posicao Y padrao para desenhar botoes
#define POSICAO_PADRAO_BTN_Y 154






//tft.getCursor(&currentX,&currentY);


void TELA_SetFontSize(int FontSize)
{
	#ifdef ctTELA_BIB_USADA_Adafruit_RA8875

		tft.textEnlarge(FontSize);
		
	#elif ctTELA_BIB_USADA_RA8875

		tft.setFontScale(FontSize);

	#endif	
}


bool TELA_touchDetect()
{
	#ifdef ctTELA_BIB_USADA_Adafruit_RA8875

		return tft.touched();
		
	#elif ctTELA_BIB_USADA_RA8875

		return tft.touchDetect();

	#endif	
}


bool TELA_touchReadPixel(uint16_t *x, uint16_t *y)
{
	#ifdef ctTELA_BIB_USADA_Adafruit_RA8875

		return tft.touchRead(x, y);
		
	#elif ctTELA_BIB_USADA_RA8875

		tft.touchReadPixel(x, y);
		return true;		

	#endif	
}




void TELA_LimpaTela()
{
	delay(100);
	tft.fillScreen(RA8875_BLACK);
	tft.fillScreen(RA8875_BLACK);
}




 
void TELA_Texto_Centralizado(String Texto, String Cor, int Tamanho, uint16_t PosY)
{

	if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
	{

		if (Cor == F(""))
		{
			Cor = F("AMARELO");
		}


		if (Cor == F("BRANCO"))
		{
			tft.setTextColor(RA8875_WHITE);
		}

		if (Cor == F("AMARELO"))
		{
			tft.setTextColor(RA8875_YELLOW);
		}

		if (Cor == F("VERMELHO"))
		{
			tft.setTextColor(RA8875_RED);
		}

		if (Cor == F("VERDE"))
		{
			tft.setTextColor(RA8875_GREEN);
		}

		if (Cor == F("AZUL"))
		{
			tft.setTextColor(RA8875_BLUE);
		}

		if (Cor == F("MAGENTA"))
		{
			tft.setTextColor(RA8875_MAGENTA);
		}


		TELA_SetFontSize(Tamanho);

		uint16_t PosX = 0;
		int TamanhoLetra_W = 0;
		int Ajuste_W = 10;

		if (Tamanho == 0){TamanhoLetra_W = 0;}
		if (Tamanho == 1){TamanhoLetra_W = 16;}
		if (Tamanho == 2){TamanhoLetra_W = 24;}
		if (Tamanho == 3){TamanhoLetra_W = 33;}


		PosX = (800 / 2) - ((Texto.length() / 2) * TamanhoLetra_W) - Ajuste_W;
		tft.setCursor(PosX, PosY);


		tft.print(Texto);


	}
}





// Escreve um texto na tela
void TELA_Texto(String Texto, String Cor)
{

	if (ctTELA_HARDWARE == F("TERMINAL"))
	{
		LogTerm(Texto); 
	}


	if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
	{


		if (Cor == F(""))
		{
			Cor = F("AMARELO");
		}


		if (Cor == F("BRANCO"))
		{
			tft.setTextColor(RA8875_WHITE);
		}

		if (Cor == F("AMARELO"))
		{
			tft.setTextColor(RA8875_YELLOW);
		}

		if (Cor == F("VERMELHO"))
		{
			tft.setTextColor(RA8875_RED);
		}

		if (Cor == F("VERDE"))
		{
			tft.setTextColor(RA8875_GREEN);
		}

		if (Cor == F("AZUL"))
		{
			tft.setTextColor(RA8875_BLUE);
		}

		if (Cor == F("MAGENTA"))
		{
			tft.setTextColor(RA8875_MAGENTA);
		}


		TELA_SetFontSize(0);

		

		tft.setCursor(gPosTxt_X, gPosTxt_Y);

		//use the classic print an println command
		tft.print(Texto);

		gPosTxt_X = 0;
		gPosTxt_Y = gPosTxt_Y + gTxtSize;

		//tft.setCursor(gPosTxt_X, gPosTxt_Y);
		// tft.setCursor(gPosTxt_X, gPosTxt_Y);888

		if (gPosTxt_Y > 465)
		{
			TELA_LimpaTela();
			gPosTxt_Y = 0;

			// o abaixo ocorre pois quando atingimos o limite de texto que cabe na tela, 
			// limpamos a tela. Quando limpamos, a tela de debug (que no caso estava apontando para o teclado numerico)
			// nao renderizava de novo, devido ao jeito como a tela de teclado numerico eh feita. 
			// por isto, definimos de novo o teclado como nao renderizado, para que ele seja renderizado logo em seguida
			// pela rotina de desenho da tela
			if (gModoOperacao == F("DEBUG"))
			{
				//gTelaRenderizada_TecNum = false;
				gTelaRenderizada_TecAlfa = false;

			}


		}

	}  


}



void TELA_LogTerm_XY()
{


	char TheTexto[100]; 


	/*
	if (ctTELA_HARDWARE == "ER-TFTM070-5")
	{

		

		Serial.print("X = ");
		Serial.print(gTouch_X); 

		Serial.print(" | Y = ");
		Serial.print(gTouch_Y); 


		Serial.print("  --  X > ");
		Serial.print(gOffset_W);
		Serial.print(" e X < ");
		Serial.print(gTamBotao_W + gOffset_W);

		Serial.print("    |    Y < ");
		Serial.print(gOffset_H);
		Serial.print(" e Y < ");
		Serial.println(gTamBotao_H + gOffset_H);

		//tft.changeMode(TEXT);
	}
	*/


	if (gModoOperacao == F("OPERACAO"))
	{

		/*
		// botao1:
		sprintf(TheTexto,"BOT1: X = %d | Y = %d   --   X > %d e X < %d  |  Y > %d e Y < %d  -- posY = %d", gTouch_X, gTouch_Y, gOffset_W, gTamBotao_W + gOffset_W, gOffset_H, gTamBotao_H + gOffset_H, gPosTxt_Y);  
		TELA_Texto(TheTexto, "");

		// botao2:
		sprintf(TheTexto,"BOT2: X = %d | Y = %d   --   X > %d e X < %d  |  Y > %d e Y < %d  -- posY = %d", gTouch_X, gTouch_Y, 2 * gOffset_W + gTamBotao_W, 2 * gOffset_W + 2 * gTamBotao_W , gOffset_H, gTamBotao_H + gOffset_H, gPosTxt_Y);  
		TELA_Texto(TheTexto, "");

		// botao3:
		sprintf(TheTexto,"BOT3: X = %d | Y = %d   --   X > %d e X < %d  |  Y > %d e Y < %d  -- posY = %d", gTouch_X, gTouch_Y, 3 * gOffset_W + 2 * gTamBotao_W, 3 * gOffset_W + 3 * gTamBotao_W , gOffset_H, gTamBotao_H + gOffset_H, gPosTxt_Y);  
		TELA_Texto(TheTexto, "");
		*/


		// sair:
	    int btnSair_PosAtual_X = 680;
		int btnSair_PosAtual_Y = 20;

		int btnSair_Size_W = 100;
		int btnSair_Size_H = 60;	

		sprintf(TheTexto,"SAIR: X = %d | Y = %d   --   X > %d e X < %d  |  Y > %d e Y < %d  -- gBounce_ContaClick = %d", gTouch_X, gTouch_Y, btnSair_PosAtual_X, btnSair_PosAtual_X + btnSair_Size_W, btnSair_PosAtual_Y, btnSair_PosAtual_Y + btnSair_Size_H, gBounce_ContaClick);  
		TELA_Texto(TheTexto, F(""));

		LogTerm(TheTexto);

		
	}
	else
	{
		// Apenas X Y:
		sprintf(TheTexto, "XY: X = %d | Y = %d", gTouch_X, gTouch_Y);  
		TELA_Texto(TheTexto, F(""));
		//TELA_Texto(gModoOperacao, "VERMELHO");

		LogTerm(TheTexto);
	}

	//tft.changeMode(GRAPHIC);
	

}




void TELA_Render_MsgBox(String Titulo, String Texto)
{

	int MaxChars = 40;


	int Size_Fundo_W;
	int Size_Fundo_H;

	int TamanhoTexto;
	int TotalLinhas;
	
	int ContaLinha;

	int Size_Char_W = 16;
	int Size_Char_H = 25;

	int Inicio_X = Size_Char_W;
	//int Inicio_Y = Size_Char_H;
	int Inicio_Y = 150;

	String Texto_Ajustado = F("");

	int BarraTitulo_H;

	BarraTitulo_H = 40;

	if (Titulo == F(""))
	{
		BarraTitulo_H = 0;
	}


	if (gTelaRenderizada_MSGBOX == false)
	{


		// ajusta texto para incorporar quebra de linha


		TamanhoTexto = Texto.length();

		if (TamanhoTexto <= MaxChars)
		{
			TotalLinhas = 1;
		}
		else
		{
			if (TamanhoTexto % MaxChars == 0)
			{
				TotalLinhas = floor(TamanhoTexto / MaxChars);
			}
			else
			{
				TotalLinhas = floor(TamanhoTexto / MaxChars) + 1;
			}

			
		}
		
		/*
		for (int x=0 ; x <= TamanhoTexto ; x++)
		{
			if (Texto.substring(x, x+1) == "^")
			{
				TotalLinhas++;				
			}

			//LogTerm(F("Char: " + Texto.substring(x, 1) + " / TotalLinhas = " + TotalLinhas);

		}		
		*/
		
		Size_Fundo_W = (TamanhoTexto * Size_Char_W) + 3;
		Size_Fundo_H = (TotalLinhas * Size_Char_H) + 2;


		if (Size_Fundo_W > ((MaxChars * Size_Char_W) + 3))
		{
			Size_Fundo_W = (MaxChars * Size_Char_W) + 3;
		}


		//int Fundo_X = Inicio_X - Size_Char_W;
		int Fundo_X = 380 - Size_Fundo_W / 2;
		int Fundo_Y = Inicio_Y - Size_Char_H;
		int Fundo_W = Size_Fundo_W + 2 * Size_Char_W;
		int Fundo_H = TotalLinhas * Size_Char_H + 2 * Size_Char_H;

		//sombra
		tft.fillRoundRect(Fundo_X + 8, Fundo_Y - BarraTitulo_H + 8, Fundo_W, Fundo_H + BarraTitulo_H, 0, CinzaShadow);
		



		//fundo/frame branco
		tft.fillRoundRect(Fundo_X, Fundo_Y, Fundo_W, Fundo_H, 0, RA8875_WHITE);

		
		//titulo
		if (Titulo != F(""))
		{
			tft.fillRoundRect(Fundo_X, Fundo_Y - BarraTitulo_H, Fundo_W, BarraTitulo_H, 0, RA8875_WHITE);

			tft.fillRoundRect(Fundo_X + 2, Fundo_Y - BarraTitulo_H + 2, Fundo_W - 4, BarraTitulo_H - 2, 0, CinzaFundoTitMsgBox);

			TELA_SetFontSize(1);

			tft.setTextColor(RA8875_BLACK);
			tft.setCursor (Fundo_X + 6, Fundo_Y - BarraTitulo_H + 4);
			tft.print(Titulo);			
		}




		
		//tft.fillRoundRect(Inicio_X - Size_Char_W + 2, Inicio_Y - Size_Char_H + 2, Size_Fundo_W + 2 * Size_Char_W - 4, Size_Fundo_H + 2 * Size_Char_H - 4, 0, RA8875_BLUE);

		for (ContaLinha = 1 ; ContaLinha <= TotalLinhas ; ContaLinha++)
		{

			int Linha_X = Fundo_X + 2;
			int Linha_Y = Fundo_Y + 2;
			int Linha_W = Size_Fundo_W + 2 * Size_Char_W - 4;
			int Linha_H = Size_Fundo_H + 2 * Size_Char_H - 6;

			tft.fillRoundRect(Linha_X, Linha_Y, Linha_W, Linha_H, 0, RA8875_BLUE);
	
		}

	    //tft.fillRoundRect(Inicio_X, Inicio_Y, Size_Fundo_W, Size_Fundo_H, 20, RA8875_WHITE);
		//tft.fillRoundRect(LabelNum_PosAtual_X + 2, LabelNum_PosAtual_Y + 2, Size_LabelNum_W - 4, Size_LabelNum_H, 0, RA8875_MAGENTA);
					
		TELA_SetFontSize(1); 
		tft.setTextColor(RA8875_WHITE);
		//tft.setTextColor(RA8875_GREEN);


		//int Texto_X = Inicio_X + 1;
		int Texto_X = (380 - Size_Fundo_W / 2) + 1 + Size_Char_W;
		int Texto_Y = Inicio_Y - 4;



		String LinhaToPrint;


		for (ContaLinha = 1 ; ContaLinha <= TotalLinhas ; ContaLinha++)
		{

			//Texto_Y += (ContaLinha - 1) * Size_Char_H;
			if (ContaLinha == 1)
			{
				Texto_Y = Inicio_Y - 4;
			}
			else
			{
				Texto_Y = (Inicio_Y - 4) + (ContaLinha - 1) * Size_Char_H;
			}

			tft.setCursor (Texto_X, Texto_Y);

			int TextoString_Inicio = (ContaLinha - 1) * MaxChars;
			int TextoString_Fim = (ContaLinha) * MaxChars;

			LinhaToPrint = Texto.substring(TextoString_Inicio, TextoString_Fim);

			// remove o espaco se for a primeira linha
			if (LinhaToPrint.substring(0, 1) == F(" "))
			{
				LinhaToPrint = LinhaToPrint.substring(1);
			}

			//LinhaToPrint.replace("^", "\r\n\n");

			tft.print(LinhaToPrint);
			//tft.print(Texto.substring(0, MaxChars));

			//Texto_Y = ((ContaLinha - 1) * Size_Char_H);
	
		}		

		/*

		LogTerm(F("TamanhoTexto = " + String(TamanhoTexto));
		LogTerm(F("MaxChars = " + String(MaxChars));
		LogTerm(F("TotalLinhas = " + String(TotalLinhas));
		LogTerm(F("Size_Char_W = " + String(Size_Char_W));
		LogTerm(F("Size_Char_H = " + String(Size_Char_H));
		LogTerm(F("Size_Fundo_W = " + String(Size_Fundo_W));
		LogTerm(F("Size_Fundo_H = " + String(Size_Fundo_H));
		LogTerm(F("==================");		
		*/

	}

	gTelaRenderizada_MSGBOX = true;
				


}





//Estes includes tem de ficar neste local devido a ordem das chamadas das funcoes. Senao, da erro
#include "../Teclado/ChoppBot_Teclado_NUM.h" 
#include "../Teclado/ChoppBot_Teclado_ALFA.h" 

#include "../RFID/ChoppBot_RFID_Main.h" 



// Funcao que inicializa a tela sendo usada no momento
void TELA_IniciaTela()
{
	//LogTerm(ctTELA_HARDWARE);
	

	if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
	{

		pinMode(RA8875_INT, INPUT);
		digitalWrite(RA8875_INT, HIGH);


		tft.begin(RA8875_800x480);  

		//tft.fillScreen(RA8875_BLACK);//fill screen black
		//tft.changeMode(TEXT);
		//tft.setCursor(0,0);

			
	

		#ifdef ctTELA_BIB_USADA_Adafruit_RA8875


			
			tft.displayOn(true);
			tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
			tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
			tft.PWM1out(255);
			//tft.fillScreen(RA8875_BLACK);

			/* Switch to text mode */  
			tft.textMode();

			
		#elif ctTELA_BIB_USADA_RA8875

			tft.touchBegin(RA8875_INT);//enable Touch support!

		#endif		

		tft.touchEnable(true);
	}

}





void TELA_Render_Botao(int IndexBotao, String Texto, String Texto2, String Texto3, String Texto4, String Cor)
{

	if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
	{



		switch (ctMAX_TORNEIRAS)
		{

			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;

			case 5:
				gTamBotao_W = 115;
				gTamBotao_H = 140;
				gOffset_W = 37;	
				break;

			case 6:
				gTamBotao_W = 86;
				gTamBotao_H = 140;
				gOffset_W = 50;	
				break;

			case 10:
				gTamBotao_W = 50;
				gTamBotao_H = 80;	
				gOffset_W = 25;
				break;
			
			default:

				gTamBotao_W = 80;
				gTamBotao_H = 80;	
				gOffset_W = 40;

				break;				
		}


		
		

		int OffSet_TextoBotao_W = gTamBotao_W / 2 - 11;
		int OffSet_TextoBotao_H = gTamBotao_H / 2 - 27;

		int OffSet_TextoTitulo_W = 0;
		int OffSet_TextoTitulo_H = 126;

		int OffSet_TextoTitulo2_H = 25;
		int OffSet_TextoTitulo3_H = 50;
		int OffSet_TextoTitulo4_H = 75;


		/*
		RA8875_BLACK            0x0000
		RA8875_BLUE             0x001F
		RA8875_RED              0xF800
		RA8875_GREEN            0x07E0
		RA8875_CYAN             0x07FF
		RA8875_MAGENTA          0xF81F
		RA8875_YELLOW           0xFFE0  
		RA8875_WHITE            0xFFFF
		*/



		gPosicaoAtual_X = gOffset_W + (IndexBotao * gTamBotao_W) + (IndexBotao * gOffset_W);

		gPosicaoAtual_X = gPosicaoAtual_X - gOffset_W - gTamBotao_W;

		// Desenha o quadrado do botao
		if (Cor == F("BRANCO"))
		{
			tft.fillRect(gPosicaoAtual_X, gOffset_H, gTamBotao_W, gTamBotao_H, RA8875_WHITE);
		}

		if (Cor == F("AZUL"))
		{
			tft.fillRect(gPosicaoAtual_X, gOffset_H, gTamBotao_W, gTamBotao_H, RA8875_BLUE);
		}

		if (Cor == F("MAGENTA"))
		{
			tft.fillRect(gPosicaoAtual_X, gOffset_H, gTamBotao_W, gTamBotao_H, RA8875_MAGENTA);
		}

		if (Cor == F("PRETO"))
		{
			tft.fillRect(gPosicaoAtual_X, gOffset_H, gTamBotao_W, gTamBotao_H, RA8875_BLACK);
		}


		// Render o numero dentro do botao
		TELA_SetFontSize(2);


		if ((Cor == F("PRETO")) || (Cor == F("AZUL")) )
		{
			tft.setTextColor(RA8875_WHITE);
		}		
		else
		{
			tft.setTextColor(RA8875_BLACK);
		}
		
		tft.setCursor (gPosicaoAtual_X + OffSet_TextoBotao_W, gOffset_H + OffSet_TextoBotao_H);

		tft.print (IndexBotao);

		// Render o titulo 
		TELA_SetFontSize(0);
		//tft.changeMode(TEXT);



		tft.setTextColor(RA8875_WHITE);



		

		// Render Texto
		if (Texto != F(""))
		{
			tft.setCursor (gPosicaoAtual_X + OffSet_TextoTitulo_W, gOffset_H + OffSet_TextoBotao_H + OffSet_TextoTitulo_H);    
			tft.print (Texto);
		}

		// Render Texto2
		if (Texto2 != F(""))
		{

			tft.setCursor (gPosicaoAtual_X + OffSet_TextoTitulo_W, gOffset_H + OffSet_TextoBotao_H + OffSet_TextoTitulo_H + OffSet_TextoTitulo2_H); 

			tft.print (Texto2);
			//tft.print (gPosicaoAtual_X);
			//tft.print (" a ");
			//tft.print (gPosicaoAtual_X + gTamBotao_W);

		}


		// Render Texto3
		if (Texto3 != F(""))
		{

			tft.setCursor (gPosicaoAtual_X + OffSet_TextoTitulo_W, gOffset_H + OffSet_TextoBotao_H + OffSet_TextoTitulo_H + OffSet_TextoTitulo3_H); 

			tft.print (Texto3);
			//tft.print (gPosicaoAtual_X);
			//tft.print (" a ");
			//tft.print (gPosicaoAtual_X + gTamBotao_W);

		}


		if (Texto4 != F(""))
		{
			tft.setCursor (gPosicaoAtual_X + OffSet_TextoTitulo_W, gOffset_H + OffSet_TextoBotao_H + OffSet_TextoTitulo_H + OffSet_TextoTitulo4_H); 
			tft.print (Texto4);
		}

		gTotalBotoes++;

	}

}







void TELA_Render_Interface_STANDBY()
{
	
	//LogTerm(ctTELA_HARDWARE);


	if (gTelaRenderizada_STANDBY == false)
	{

        //LogTerm(F("== [Modo Atual: STANDBY] ==");




		if (ctTELA_HARDWARE == F("TERMINAL"))
		{  
			LogTerm(String(F("ChoppBot ")) + String(VersaoAPP));

			if (NOME_LOJA_LINHA2 != F(""))
			{
				LogTerm(String(F("Licenciado para: ")) + String(NOME_LOJA_LINHA1) + String(F(" ")) + String(NOME_LOJA_LINHA2));
			}
			else
			{
				LogTerm(String(F("Licenciado para: ")) + String(NOME_LOJA_LINHA1));
			}

			LogTerm(F("Tecle algo no console para iniciar..."));
		}



		if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
		{  



			TELA_LimpaTela();

			
			// versao do choppbot
			TELA_SetFontSize(0); 
			tft.setTextColor(CinzaLabels);
			tft.setCursor (685, 10);			
			tft.print (String(F("ChoppBot ")) + String(VersaoAPP)); 



			// Titulo
			TELA_Texto_Centralizado(String(NOME_LOJA_LINHA1), F("AMARELO"), 3, 110);

			if (NOME_LOJA_LINHA2 != F(""))
			{
				TELA_Texto_Centralizado(String(NOME_LOJA_LINHA2), F("AMARELO"), 3, 180);
			}


			// texto explicativo
			tft.setTextColor(RA8875_WHITE);

  
			//tft.setCursor (195, 310);
			//TELA_SetFontSize(1); 
			TELA_Texto_Centralizado(String(F("Toque na tela para iniciar")), F("BRANCO"), 1, 330);

			//tft.print (F("Toque na tela para iniciar"));   



		}

		gTelaRenderizada_STANDBY = true;

	}


}



void TELA_Render_Interface_LOGIN()
{

	if (gTelaRenderizada_LOGIN == false)
	{

	    if (ctTELA_HARDWARE == String(F("ER-TFTM070-5")))
	    {
	        TELA_LimpaTela();
	    }

		
		//LogTerm(F("== [Modo Atual: LOGIN] ==");

		if (ctTELA_HARDWARE == F("TERMINAL"))
		{  

			LogTerm(F("Ola! Seja bem vindo!"));
			LogTerm(F("Escolha o seu metodo de identificacao e digite o numero correspondente no console:"));
			LogTerm(F("1 - LEITOR BIOMETRICO"));
			LogTerm(F("2 - LEITOR DE CARTAO"));
			//LogTerm(F("3 - ABRE TECLADO NUMERICO"));
			LogTerm(F("3 - ABRE TECLADO ALFA"));

			LogTerm(F("4 - ADMIN"));


		}


		if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
		{  


			#ifdef ctTELA_BIB_USADA_Adafruit_RA8875


				tft.textTransparent(RA8875_YELLOW);
				tft.textSetCursor (175, 30);
				TELA_SetFontSize(2);

				//char Texto1[50];
				//String(F("Ola! Seja vem vindo!")).toCharArray(Texto1, 50) ;


				tft.textTransparent(RA8875_WHITE);
				tft.textSetCursor (100, 130);
				TELA_SetFontSize(1); 

				//tft.textWrite (String(F("Escolha o seu metodo de identificacao:")));   

				gOffset_H = POSICAO_PADRAO_BTN_Y + 95;

				TELA_Render_Botao(1, F("LEITOR BIOMETRICO"), F(""), F(""), F(""), F("BRANCO"));
				TELA_Render_Botao(2, F("LEITOR DE CARTAO"), F(""), F(""), F(""), F("AZUL"));
				//TELA_Render_Botao(3, F("ABRE TECLADO NUMERICO"), F(""), F(""), F("MAGENTA"));
				TELA_Render_Botao(3, F("ABRE TECLADO ALFA"), F(""), F(""), F(""), F("MAGENTA"));

				// Area para chamar admin
				//tft.fillRect(700, 0, 100, 60, RA8875_WHITE);


			#elif ctTELA_BIB_USADA_RA8875

				tft.setTextColor(RA8875_YELLOW);
				tft.setCursor (175, 30);
				TELA_SetFontSize(2);
				tft.print (F("Ola! Seja vem vindo!"));   

				tft.setTextColor(RA8875_WHITE);
				tft.setCursor (100, 130);
				TELA_SetFontSize(1); 
				tft.print (F("Escolha o seu metodo de identificacao:"));   

				gOffset_H = POSICAO_PADRAO_BTN_Y + 95;

				TELA_Render_Botao(1, F("LEITOR BIOMETRICO"), F(""), F(""), F(""), F("BRANCO"));
				TELA_Render_Botao(2, F("LEITOR DE CARTAO"), F(""), F(""), F(""), F("AZUL"));
				//TELA_Render_Botao(3, F("ABRE TECLADO NUMERICO"), F(""), F(""), F("MAGENTA"));
				TELA_Render_Botao(3, F("ABRE TECLADO ALFA"), F(""), F(""), F(""), F("MAGENTA"));

				// Area para chamar admin
				//tft.fillRect(700, 0, 100, 60, RA8875_WHITE);


			#endif






		}

		gTelaRenderizada_LOGIN = true;

	}

}



unsigned long Timeout_Operacao_time_inicio;
unsigned long Timeout_Operacao_time_atual;
unsigned long Timeout_Operacao_time_tempo_passado;

int Timeout_Operacao_SegundosPassados;
int Timeout_Operacao_Last_SegundosPassados;


void TELA_Render_Interface_OPERACAO()
{

	//LogTerm(F("== [Modo Atual: OPERACAO] ==");



	// Mostra tempo de timeout da tela de operacao -----------------------

	if (gTelaRenderizada_OPERACAO == false)
	{
		// Inicia a contagem do tempo
		Timeout_Operacao_time_inicio = millis();
	}
	else
	{
		if ((ctTIMEOUT_TELA_OPERACAO / 1000) - Timeout_Operacao_SegundosPassados <= 0)
		{
			Timeout_Operacao_time_inicio = millis();

			gTelaRenderizada_OPERACAO = false;

		}
	}


	// Renderiza os segundos
	if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
	{  		

	    Timeout_Operacao_time_atual = millis();
	    Timeout_Operacao_time_tempo_passado = Timeout_Operacao_time_atual - Timeout_Operacao_time_inicio;

	    Timeout_Operacao_SegundosPassados = floor(Timeout_Operacao_time_tempo_passado / 1000);


	    if (Timeout_Operacao_SegundosPassados != Timeout_Operacao_Last_SegundosPassados)
	    {	

				TELA_SetFontSize(0); 
				tft.setTextColor(CinzaLabels, RA8875_BLACK);
				tft.setCursor (620, 10);			
				tft.print (F("Tempo: ")); 

				tft.setCursor (680, 10);
				tft.print (String((ctTIMEOUT_TELA_OPERACAO / 1000) - Timeout_Operacao_SegundosPassados) + String(F(" segundos   "))); 

		} 
	}

	//LogTerm(String(F("(ctTIMEOUT_TELA_OPERACAO / 1000) - SegundosPassados = ")) + String((ctTIMEOUT_TELA_OPERACAO / 1000) - Timeout_Operacao_SegundosPassados));



	// sai se o tempo limite ocorrer
	if ((ctTIMEOUT_TELA_OPERACAO / 1000) - Timeout_Operacao_SegundosPassados <= 0)
	{


		// zera as vars para cada tentativa de login
		// efetua logoff
		gSessao_Logado = false;
		gSessao_IDUser = -1;
		gSessao_Nome = F("");
		gSessao_Nivel = -1;
		gSessao_SaldoAtual = -1;

		gTelaRenderizada_OPERACAO = false;	

		gModoOperacao = F("STANDBY");  
		gModoOperacao_SubTela = F("");						



		LogTerm(F("MAIN: Timeout de tela Operacao"));

		delay(1000);
		
	}

	// ====================================================================


	if (gTelaRenderizada_OPERACAO == false)
	{

		

		if (ctTELA_HARDWARE == F("TERMINAL"))
		{  


			LogTerm(F("Selecione o chopp desejado e digite o numero correspondente no console:"));

		    // NumTorneira;DataCad;IDChopp;VolumeAtual;DataExpira;Ativa;NomeFromBanco;Tipo;Valor
		    for (int x = 0 ; x <= ctMAX_TORNEIRAS ; x++)
		    {

		        if (gaEngatados[x] != F(""))
		        {


		            String tmp_IDChopp = getValue(gaEngatados[x], ';', 2);
		            String tmp_Nome = getValue(gaEngatados[x], ';', 7);
		            String tmp_Tipo = getValue(gaEngatados[x], ';', 8);
		            String tmp_Valor = getValue(gaEngatados[x], ';', 9);
		            String tmp_Volume = getValue(gaEngatados[x], ';', 3);
		            //tmp_DataCad = getValue(gaEngatados[x], ';', 1);
		            //tmp_DataExp = getValue(gaEngatados[x], ';', 4);
		            String tmp_Ativa = getValue(gaEngatados[x], ';', 5);


		            LogTerm(  
		            		String(x + 1) + 
		            		String(F(" - ")) + 
		            		tmp_Nome + 
		            		String(F(" | R$ ")) + 
							tmp_Valor + 
							String(F(" / Litro ")) 
		                   );



		        }


		    }	

		    LogTerm(F("99 - Sair"));		
		}


		if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
		{  		


			
			/*

			// Cabecalho logado ///////

			TELA_SetFontSize(1);

			tft.setTextColor(CinzaLabels);
			tft.setCursor (10, 10);			
			tft.print (F("Nome: ")); 
			tft.setCursor (10, 45);			
			tft.print (F("Saldo: "));  

			tft.setTextColor(RA8875_WHITE);
			tft.setCursor (120, 10);			
			tft.print (gSessao_Nome); 
			tft.setCursor (120, 45);	

			tft.print (FormatNumber(gSessao_SaldoAtual, F("MONEY")));  

			*/


			//////////////////////////////////////  

			TELA_Texto_Centralizado(F("Escolha a sua torneira:"), F("VERDE"), 2, 90);



		
			// Botao SAIR ///////////////////////////////

		    int btnSair_PosAtual_X = 10;
			int btnSair_PosAtual_Y = 15;

			int btnSair_Size_W = 100;
			int btnSair_Size_H = 60;

			tft.fillRoundRect(btnSair_PosAtual_X, btnSair_PosAtual_Y, btnSair_Size_W, btnSair_Size_H, 8, Red);
		
			TELA_SetFontSize(1);
		    tft.setTextColor(RA8875_WHITE);
		    tft.setCursor (btnSair_PosAtual_X + (btnSair_Size_W / 2) - 35, btnSair_PosAtual_Y + 12); 
		    tft.print (F("SAIR"));	

		    //////////////////////////////////////



		    // Inicia desenho do restante da tela e botoes


			gOffset_H = POSICAO_PADRAO_BTN_Y + 49;




		    // NumTorneira;DataCad;IDChopp;VolumeAtual;DataExpira;Ativa;NomeFromBanco;Tipo;Valor
		    for (int x = 0 ; x <= ctMAX_TORNEIRAS ; x++)
		    {

		        if (gaEngatados[x] != "")
		        {


		            String tmp_IDChopp = getValue(gaEngatados[x], ';', 2);
		            String tmp_Nome = getValue(gaEngatados[x], ';', 7);
		            String tmp_Tipo = getValue(gaEngatados[x], ';', 8);
		            String tmp_Valor = getValue(gaEngatados[x], ';', 9);
		            String tmp_Volume = getValue(gaEngatados[x], ';', 3);
		            //tmp_DataCad = getValue(gaEngatados[x], ';', 1);
		            //tmp_DataExp = getValue(gaEngatados[x], ';', 4);
		            String tmp_Ativa = getValue(gaEngatados[x], ';', 5);


		            //TELA_Render_Botao(x + 1, tmp_Nome, tmp_Tipo, String( String(F("R$ ")) + tmp_Valor + String(F(" / Litro")) ), F("AZUL"));

		            TELA_Render_Botao(x + 1, tmp_Nome, tmp_Tipo, String( FormatNumber(tmp_Valor, F("MONEY")) + String(F(" / Litro")) ), String(FormatNumber(tmp_Volume, F("")) + String(F(" litros")) ), F("AZUL"));




		        }


		    }

		}

		gTelaRenderizada_OPERACAO = true;

	}





    




}







void TELA_VerificaTouch_STANDBY()
{

	if (ctTELA_HARDWARE == F("TERMINAL"))
	{ 

		String retConsole;

		retConsole = ReadConsoleInput();

		if (retConsole != F(""))
		{
			LogTerm(String(F("Opcao selecionada: ")) + retConsole);

			gTelaRenderizada_STANDBY = false;

			//gModoOperacao = F("LOGIN");
			gModoOperacao = "OPERACAO";
			//gModoOperacao = "DEBUG";


     
			delay(500);		
		}

	}

	if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
	{  

		if (TELA_touchDetect())
		{


			// Esquema de DEBounce ---- inicio

			gBounce_ContaClick++;

			TELA_touchReadPixel(&gTouch_X, &gTouch_Y);

			//LogTerm(String(F("TELA_VerificaTouch_STANDBY - gBounce_ContaClick = ")) + String(gBounce_ContaClick) + String(F(" / gBounce_time_tempo_passado = ")) + String(gBounce_time_tempo_passado) + String(F(" / gBounce_SegundosPassados = ")) + String(gBounce_SegundosPassados));


			//if ((gBounce_ContaClick == 1) && (gBounce_time_tempo_passado <= ctBOUNCE_SENSIB_BOTAO))
			if (gBounce_ContaClick == 1)
			{
				// Local onde deve ocorrer o evento do clique. Ocorrera apenas 1 vez --------


				

				gTelaRenderizada_STANDBY = false;

				//gModoOperacao = F("LOGIN");
				gModoOperacao = F("OPERACAO");

			    TELA_LimpaTela();

				delay(500);  

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







void TELA_VerificaTouch_LOGIN()
{

	if (ctTELA_HARDWARE == F("TERMINAL"))
	{ 

		String retConsole;

		retConsole = ReadConsoleInput();

		if (retConsole != F(""))
		{
			LogTerm(String(F("Opcao selecionada: ")) + retConsole);	
		}


		if (retConsole.toInt() == 1)
		{
			//LogTerm(F("LEITOR BIOMETRICO SELECIONADO");
		}

		if (retConsole.toInt() == 2)
		{
			//LogTerm(F("LEITOR RFID SELECIONADO VIA TERMINAL");


			gModoOperacao_SubTela = F("LER_RFID");


			gTelaRenderizada_LOGIN = false;



			
		}

		if (retConsole.toInt() == 3)
		{
			gModoOperacao = F("DEBUG");
			gTelaRenderizada_LOGIN = false;

			//LogTerm(F("TECLADO NUM SELECIONADO");
			//LogTerm(F("TECLADO ALFA SELECIONADO");


			delay(500);   
		}

		if (retConsole.toInt() == 4)
		{
			gModoOperacao = F("ADMIN"); 
			gTelaRenderizada_LOGIN = false;

			//LogTerm(F("ADMIN SELECIONADO");

			delay(500);    
		}

	}




	if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
	{  

		//tft.changeMode(GRAPHIC);

		if (TELA_touchDetect())
		{


			TELA_touchReadPixel(&gTouch_X, &gTouch_Y);

			//LogTerm(F("TELA_VerificaTouch_LOGIN"));
			//TELA_LogTerm_XY();
			

			// murch
			//gTouch_X = 800 - gTouch_X;
			//gTouch_Y = 480 - gTouch_Y;

			//TELA_LogTerm_XY(); 

			//botao 1:
			if (gTouch_X >= gOffset_W && gTouch_X <= gTamBotao_W + gOffset_W)  
			{

				if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
				{

					LogTerm(F("LEITOR BIOMETRICO SELECIONADO"));
					TELA_Texto(F("LEITOR BIOMETRICO SELECIONADO"), F("BRANCO"));

					//TELA_Render_Botao(1, "", "", "PRETO");

				}

			}



			//botao 2:
			if (gTouch_X >= 2 * gOffset_W + gTamBotao_W && gTouch_X <= 2 * gOffset_W + 2 * gTamBotao_W )  
			{

				if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
				{

					//TELA_Texto("LEITOR RFID SELECIONADO VIA TELA", "AZUL");


					//LogTerm(F("LEITOR RFID SELECIONADO VIA TELA"));

					//LogTerm(F("Aproxime o cartao da leitora RFID ...");

					gModoOperacao_SubTela = F("LER_RFID");


					gTelaRenderizada_LOGIN = false;

					TELA_LimpaTela();

					delay(500);   





				}

			}


			//botao 3:
			if (gTouch_X >= 3 * gOffset_W + 2 * gTamBotao_W && gTouch_X <= 3 * gOffset_W + 3 * gTamBotao_W )  
			{

				if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
				{
					
					gTelaRenderizada_LOGIN = false;
					gModoOperacao = F("DEBUG"); 

					//TELA_Texto(F("TECLADO NUM SELECIONADO"), F("MAGENTA"));
					TELA_Texto(F("TECLADO ALFA SELECIONADO"), F("MAGENTA"));

					TELA_LimpaTela();

					delay(500);          
				}

			}

			/*

			//botao ADMIN:
			if (gTouch_X >= 700 && gTouch_X <= 700 + 100)  
			{

				if (gTouch_Y >= 0 && gTouch_Y <= 0 + 100) 
				{


					gTelaRenderizada_LOGIN = false;
					gModoOperacao = "ADMIN"; 

					TELA_Texto("ADMIN SELECIONADO", "MAGENTA");

					TELA_LimpaTela();

					delay(500);          
				}

			}

			*/


		}

	}


}









void TELA_VerificaTouch_ADMIN()
{

	if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
	{  

		if (TELA_touchDetect())
		{


			//TELA_LogTerm_XY();
			//LogTerm(F("TELA_VerificaTouch_ADMIN");

			TELA_touchReadPixel(&gTouch_X, &gTouch_Y);

			//murch
			//gTouch_X = 800 - gTouch_X;
			//gTouch_Y = 480 - gTouch_Y;



			//botao 1:
			if (gTouch_X >= gOffset_W && gTouch_X <= gTamBotao_W + gOffset_W)  
			{

				if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
				{




				}

			}

		}

	}

}










void TELA_VerificaTouch_OPERACAO()
{


	if (ctTELA_HARDWARE == F("TERMINAL"))
	{ 

		String retConsole;

		retConsole = ReadConsoleInput();

		if (retConsole != F(""))
		{
			LogTerm(String(F("Opcao selecionada: ")) + retConsole);	
		}


	


		if (retConsole.toInt() == 99)
		{

			// zera as vars para cada tentativa de login
			// efetua logoff
			gSessao_Logado = false;
			gSessao_IDUser = -1;
			gSessao_Nome = F("");
			gSessao_Nivel = -1;
			gSessao_SaldoAtual = -1;

			gTelaRenderizada_OPERACAO = false;	

			gModoOperacao = F("STANDBY");  
			gModoOperacao_SubTela = F("");						
			
			LogTerm(F("MAIN: Usuario clicou em SAIR")); 
		}
		else
		{
			LogTerm(String(F("TORNEIRA ")) + retConsole + String(F(" SELECIONADA")));

			gServico_ID_TorneiraAtual = retConsole.toInt();

			//gModoOperacao_SubTela = F("OPERACAO_SERVICO");


			gModoOperacao = F("LOGIN");
			gModoOperacao_SubTela = F("LER_RFID");			

			gTelaRenderizada_OPERACAO = false;

			delay(500);  				
		}



	}



	if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
	{  

		//LogTerm("gBounce_ContaClick = " + String(gBounce_ContaClick));

		//tft.changeMode(GRAPHIC);

		if (TELA_touchDetect())
		{

			TELA_touchReadPixel(&gTouch_X, &gTouch_Y);

			

			//LogTerm(String(gTouch_X) + String(" -- ") + String(gTouch_Y));

			//TELA_LogTerm_XY();	


			// botao sair


		    int btnSair_PosAtual_X = 10;
			int btnSair_PosAtual_Y = 15;

			int btnSair_Size_W = 100;
			int btnSair_Size_H = 60;			


			// BOTAO SAIR
			if ((gTouch_X >= btnSair_PosAtual_X) && (gTouch_X <= btnSair_PosAtual_X + btnSair_Size_W)) 
			{

				if ((gTouch_Y >= btnSair_PosAtual_Y) && (gTouch_Y <= btnSair_PosAtual_Y + btnSair_Size_H)) 
				{


					//LogTerm(String(F("a - gBounce_ContaClick = ")) + String(gBounce_ContaClick) + String(F(" / gBounce_time_tempo_passado = ")) + String(gBounce_time_tempo_passado) + String(F(" / gBounce_SegundosPassados = ")) + String(gBounce_SegundosPassados));

					// Esquema de DEBounce ---- inicio

					gBounce_ContaClick++;
					

					if (gBounce_ContaClick == 1)
					{
						// Local onde deve ocorrer o evento do clique. Ocorrera apenas 1 vez --------
						
						//LogTerm(String(F("1 - gBounce_ContaClick = ")) + String(gBounce_ContaClick) + String(F(" / gBounce_time_tempo_passado = ")) + String(gBounce_time_tempo_passado) + String(F(" / gBounce_SegundosPassados = ")) + String(gBounce_SegundosPassados));


						TELA_LimpaTela();

						// zera as vars para cada tentativa de login
						// efetua logoff
						gSessao_Logado = false;
						gSessao_IDUser = -1;
						gSessao_Nome = F("");
						gSessao_Nivel = -1;
						gSessao_SaldoAtual = -1;

						gTelaRenderizada_OPERACAO = false;	

						gModoOperacao = F("STANDBY");  
						gModoOperacao_SubTela = F("");						
						
					


						LogTerm(F("MAIN: Usuario clicou em SAIR"));
						//TELA_Texto(F("BOTAO SAIR APERTADO"), F("MAGENTA"));  
						//delay(500); 								

						//LogTerm(F("TELA_VerificaTouch_OPERACAO"));
						//TELA_LogTerm_XY();
							
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
					//LogTerm(String(F("B - gBounce_ContaClick = ")) + String(gBounce_ContaClick) + String(F(" / gBounce_time_tempo_passado = ")) + String(gBounce_time_tempo_passado) + String(F(" / gBounce_SegundosPassados = ")) + String(gBounce_SegundosPassados));


				}

			}
			else
			{



				//botao 1:
				if (gTouch_X >= gOffset_W && gTouch_X <= gTamBotao_W + gOffset_W)  
				{

					if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
					{




						// Esquema de DEBounce ---- inicio

						gBounce_ContaClick++;
						

						if (gBounce_ContaClick == 1)
						{
							// Local onde deve ocorrer o evento do clique. Ocorrera apenas 1 vez --------

							LogTerm(F("BOTAO 1 APERTADO"));
							//TELA_Texto(F("BOTAO 2 APERTADO"), F("AZUL"));
							//delay(500);
							//TELA_LogTerm_XY();    

							gServico_ID_TorneiraAtual = 1;

							//gModoOperacao_SubTela = F("OPERACAO_SERVICO");


							gModoOperacao = F("LOGIN");
							gModoOperacao_SubTela = F("LER_RFID");

							gTelaRenderizada_OPERACAO = false;

							TELA_LimpaTela();

							delay(500);  	
								
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
				else
				{
					// outros botoes

					for (int ContaBotao = 2 ; ContaBotao <= 10 ; ContaBotao++)
					{


					
						if (gTouch_X >= ContaBotao * gOffset_W + (ContaBotao - 1) * gTamBotao_W && gTouch_X <= ContaBotao * gOffset_W + ContaBotao * gTamBotao_W )  
						{

							if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
							{

								

								// Esquema de DEBounce ---- inicio

								gBounce_ContaClick++;
								

								if (gBounce_ContaClick == 1)
								{
									// Local onde deve ocorrer o evento do clique. Ocorrera apenas 1 vez --------

									LogTerm(String(F("TORNEIRA ")) + String(ContaBotao) + String(F(" SELECIONADA")));
									//TELA_Texto(F("BOTAO 2 APERTADO"), F("AZUL"));
									//delay(500);
									//TELA_LogTerm_XY();    

									gServico_ID_TorneiraAtual = ContaBotao;

									//gModoOperacao_SubTela = F("OPERACAO_SERVICO");

									gModoOperacao = F("LOGIN");
									gModoOperacao_SubTela = F("LER_RFID");

									gTelaRenderizada_OPERACAO = false;

									TELA_LimpaTela();

									delay(500);  	
										
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

}






void TELA_VerificaTouch_DEBUG()
{

	//TELA_VerificaTouch_TECLADO_NUM();
	TELA_VerificaTouch_TECLADO_ALFA();

}







