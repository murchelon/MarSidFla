


#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255,   0 */
#define White           0xFFFF      /* 255, 255, 255 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */
#define Pink            0xF81F

//#define CinzaShadow     		rgb565_from_triplet(205, 205, 205)       /* 205, 205, 205 */
#define CinzaShadow     		rgb565_from_triplet(99, 99, 99)       /* 205, 205, 205 */
#define CinzaFundoTitMsgBox     	rgb565_from_triplet(201, 201, 201)       /* 205, 205, 205 */





// vars usadas para posicionamento de texto generico na tela
uint16_t gPosTxt_X = 0;
uint16_t gPosTxt_Y = 0;
uint16_t gTxtSize = 15;


// valores padrao de tamanho e altura dos botoes
int gTamBotao_W = 180;
int gTamBotao_H = 180;

// valores padrao de espacamento X e Y dos botoes. A altura é iniciada como -1 pois é definida posteriormente no codigo
int gOffset_W = 65;
int gOffset_H = -1;

// var que contem a posicao atual X para desenhar os botoes
int gPosicaoAtual_X = 0;

// total de botoes desenhados em uma determinada tela
int gTotalBotoes = 0;

// vers que contem o x e y de um touch na tela
uint16_t gTouch_X, gTouch_Y;


//bool gBotao1_Apertado = false;
//bool gBotao2_Apertado = false;
//bool gBotao3_Apertado = false;


// var com a posicao Y padrao para desenhar botoes
const int POSICAO_PADRAO_BTN_Y = 140;



//tft.getCursor(&currentX,&currentY);



void TELA_LimpaTela()
{
	if (gTela_Hardware == "ER-TFTM070-5")
	{
		tft.fillScreen(RA8875_BLACK);  
	}

	if (gTela_Hardware == "TERMINAL")
	{
		LogTerm(F("TELA -> LimpaTela()")); 
	}
}



// Escreve um texto na tela
void TELA_Texto(String Texto, String Cor)
{

	if (gTela_Hardware == "TERMINAL")
	{
		LogTerm(Texto); 
	}


	if (gTela_Hardware == "ER-TFTM070-5")
	{


		if (Cor == "")
		{
			Cor = "AMARELO";
		}


		if (Cor == "BRANCO")
		{
			tft.setTextColor(RA8875_WHITE);
		}

		if (Cor == "AMARELO")
		{
			tft.setTextColor(RA8875_YELLOW);
		}

		if (Cor == "VERMELHO")
		{
			tft.setTextColor(RA8875_RED);
		}

		if (Cor == "VERDE")
		{
			tft.setTextColor(RA8875_GREEN);
		}

		if (Cor == "AZUL")
		{
			tft.setTextColor(RA8875_BLUE);
		}

		if (Cor == "MAGENTA")
		{
			tft.setTextColor(RA8875_MAGENTA);
		}

		tft.setFontScale(0);

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
			if (gModoOperacao == 'DEBUG')
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
	if (gTela_Hardware == "ER-TFTM070-5")
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


	if (gModoOperacao == "OPERACAO")
	{

		// botao1:
		sprintf(TheTexto,"BOT1: X = %d | Y = %d   --   X > %d e X < %d  |  Y > %d e Y < %d  -- posY = %d", gTouch_X, gTouch_Y, gOffset_W, gTamBotao_W + gOffset_W, gOffset_H, gTamBotao_H + gOffset_H, gPosTxt_Y);  
		TELA_Texto(TheTexto, "");

		// botao2:
		sprintf(TheTexto,"BOT2: X = %d | Y = %d   --   X > %d e X < %d  |  Y > %d e Y < %d  -- posY = %d", gTouch_X, gTouch_Y, 2 * gOffset_W + gTamBotao_W, 2 * gOffset_W + 2 * gTamBotao_W , gOffset_H, gTamBotao_H + gOffset_H, gPosTxt_Y);  
		TELA_Texto(TheTexto, "");

		// botao3:
		sprintf(TheTexto,"BOT3: X = %d | Y = %d   --   X > %d e X < %d  |  Y > %d e Y < %d  -- posY = %d", gTouch_X, gTouch_Y, 3 * gOffset_W + 2 * gTamBotao_W, 3 * gOffset_W + 3 * gTamBotao_W , gOffset_H, gTamBotao_H + gOffset_H, gPosTxt_Y);  
		TELA_Texto(TheTexto, "");

	}
	else
	{
		// Apenas X Y:
		sprintf(TheTexto,"XY: X = %d | Y = %d", gTouch_X, gTouch_Y);  
		TELA_Texto(TheTexto, "");
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

	String Texto_Ajustado = "";

	int BarraTitulo_H;

	BarraTitulo_H = 40;

	if (Titulo == "")
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
		if (Titulo != "")
		{
			tft.fillRoundRect(Fundo_X, Fundo_Y - BarraTitulo_H, Fundo_W, BarraTitulo_H, 0, RA8875_WHITE);

			tft.fillRoundRect(Fundo_X + 2, Fundo_Y - BarraTitulo_H + 2, Fundo_W - 4, BarraTitulo_H - 2, 0, CinzaFundoTitMsgBox);

			tft.setFontScale(1); 
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
					
		tft.setFontScale(1); 
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
			if (LinhaToPrint.substring(0, 1) == " ")
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

	if (gTela_Hardware == "ER-TFTM070-5")
	{

		pinMode(RA8875_INT, INPUT);
		digitalWrite(RA8875_INT, HIGH);


		tft.begin(RA8875_800x480);  

		//tft.fillScreen(RA8875_BLACK);//fill screen black
		//tft.changeMode(TEXT);
		//tft.setCursor(0,0);

		tft.touchBegin(RA8875_INT);//enable Touch support!

		tft.touchEnable(true);
	}

}





void TELA_Render_Botao(int IndexBotao, String Texto, String Texto2, String Cor)
{

	if (gTela_Hardware == "ER-TFTM070-5")
	{

		int OffSet_TextoBotao_W = gTamBotao_W / 2 - 11;
		int OffSet_TextoBotao_H = gTamBotao_H / 2 - 27;

		int OffSet_TextoTitulo_W = 0;
		int OffSet_TextoTitulo_H = 140;

		int OffSet_TextoTitulo2_H = 25;


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
		if (Cor == "BRANCO")
		{
			tft.fillRect(gPosicaoAtual_X, gOffset_H, gTamBotao_W, gTamBotao_H, RA8875_WHITE);
		}

		if (Cor == "AZUL")
		{
			tft.fillRect(gPosicaoAtual_X, gOffset_H, gTamBotao_W, gTamBotao_H, RA8875_BLUE);
		}

		if (Cor == "MAGENTA")
		{
			tft.fillRect(gPosicaoAtual_X, gOffset_H, gTamBotao_W, gTamBotao_H, RA8875_MAGENTA);
		}

		if (Cor == "PRETO")
		{
			tft.fillRect(gPosicaoAtual_X, gOffset_H, gTamBotao_W, gTamBotao_H, RA8875_BLACK);
		}


		// Render o numero dentro do botao
		tft.setFontScale(2); 
		tft.setTextColor(RA8875_BLACK);
		tft.setCursor (gPosicaoAtual_X + OffSet_TextoBotao_W, gOffset_H + OffSet_TextoBotao_H);

		tft.print (IndexBotao);

		// Render o titulo 
		tft.setFontScale(0);
		//tft.changeMode(TEXT);
		tft.setTextColor(RA8875_WHITE);

		// Render Titulo
		if (Texto != "")
		{
			tft.setCursor (gPosicaoAtual_X + OffSet_TextoTitulo_W, gOffset_H + OffSet_TextoBotao_H + OffSet_TextoTitulo_H);    
			tft.print (Texto);
		}

		// Render Titulo2
		if (Texto2 != "")
		{

			tft.setCursor (gPosicaoAtual_X + OffSet_TextoTitulo_W, gOffset_H + OffSet_TextoBotao_H + OffSet_TextoTitulo_H + OffSet_TextoTitulo2_H); 

			tft.print (Texto2);
			//tft.print (gPosicaoAtual_X);
			//tft.print (" a ");
			//tft.print (gPosicaoAtual_X + gTamBotao_W);

		}


		gTotalBotoes++;

	}

}







void TELA_Render_Interface_STANDBY()
{
	
	//LogTerm(gTela_Hardware);


	if (gTelaRenderizada_STANDBY == false)
	{

        //LogTerm(F("== [Modo Atual: STANDBY] ==");


		if (gTela_Hardware == "TERMINAL")
		{  
			LogTerm("ChoppBot " + String(VersaoAPP));
			LogTerm("Tecle algo no console para iniciar...");
		}

		if (gTela_Hardware == "ER-TFTM070-5")
		{  

			tft.setTextColor(RA8875_YELLOW);
			tft.setCursor (210, 150);
			tft.setFontScale(3); 
			tft.print ("ChoppBot " + String(VersaoAPP));    
			//tft.print ("ChoppBot 1.0");    

			tft.setTextColor(RA8875_WHITE);
			tft.setCursor (195, 310);
			tft.setFontScale(1); 
			tft.print ("Toque na tela para iniciar");    

		}

		gTelaRenderizada_STANDBY = true;

	}


}



void TELA_Render_Interface_LOGIN()
{

	if (gTelaRenderizada_LOGIN == false)
	{

		//LogTerm(F("== [Modo Atual: LOGIN] ==");

		if (gTela_Hardware == "TERMINAL")
		{  

			LogTerm(F("Ola! Seja bem vindo!"));
			LogTerm(F("Escolha o seu metodo de identificacao e digite o numero correspondente no console:"));
			LogTerm(F("1 - LEITOR BIOMETRICO"));
			LogTerm(F("2 - LEITOR DE CARTAO"));
			//LogTerm(F("3 - ABRE TECLADO NUMERICO"));
			LogTerm(F("3 - ABRE TECLADO ALFA"));

			LogTerm(F("4 - ADMIN"));


		}


		if (gTela_Hardware == "ER-TFTM070-5")
		{  

			tft.setTextColor(RA8875_YELLOW);
			tft.setCursor (175, 30);
			tft.setFontScale(2); 
			tft.print ("Ola! Seja vem vindo!");   

			tft.setTextColor(RA8875_WHITE);
			tft.setCursor (100, 130);
			tft.setFontScale(1); 
			tft.print ("Escolha o seu metodo de identificacao:");   

			gOffset_H = POSICAO_PADRAO_BTN_Y + 95;

			TELA_Render_Botao(1, "LEITOR BIOMETRICO", "", "BRANCO");
			TELA_Render_Botao(2, "LEITOR DE CARTAO", "", "AZUL");
			//TELA_Render_Botao(3, "ABRE TECLADO NUMERICO", "", "MAGENTA");
			TELA_Render_Botao(3, "ABRE TECLADO ALFA", "", "MAGENTA");

			// Area para chamar admin
			//tft.fillRect(700, 0, 100, 60, RA8875_WHITE);

		}

		gTelaRenderizada_LOGIN = true;

	}

}





void TELA_Render_Interface_OPERACAO()
{

	//LogTerm(F("== [Modo Atual: OPERACAO] ==");

	if (gTelaRenderizada_OPERACAO == false)
	{

		if (gTela_Hardware == "TERMINAL")
		{  
			LogTerm(F("1 - Imperial IPA - R$ 25,00 / Litro"));
			LogTerm(F("2 - Hoocus Pocus - R$ 19,00"));
			LogTerm(F("3 - Duchese - R$ 32,00 / Litro"));
		}


		if (gTela_Hardware == "ER-TFTM070-5")
		{  		

			tft.setTextColor(RA8875_WHITE);
			tft.setCursor (125, 30);
			tft.setFontScale(2); 
			tft.print ("Escolha a sua torneira:");    


			gOffset_H = POSICAO_PADRAO_BTN_Y;

			TELA_Render_Botao(1, "Imperial IPA", "R$ 25,00 / Litro", "BRANCO");
			TELA_Render_Botao(2, "Hoocus Pocus", "R$ 19,00 / Litro", "AZUL");
			TELA_Render_Botao(3, "Duchese", "R$ 32,00 / Litro", "MAGENTA");
		}

		gTelaRenderizada_OPERACAO = true;

	}

}







void TELA_VerificaTouch_STANDBY()
{

	if (gTela_Hardware == "TERMINAL")
	{ 

		String retConsole;

		retConsole = ReadConsoleInput();

		if (retConsole != "") 
		{
			LogTerm("Opcao selecionada: " + retConsole);

			gTelaRenderizada_STANDBY = false;

			gModoOperacao = "LOGIN";
			//gModoOperacao = "OPERACAO";
			//gModoOperacao = "DEBUG";

			TELA_LimpaTela();

			delay(500);			
		}

	}

	if (gTela_Hardware == "ER-TFTM070-5")
	{  

		if (tft.touchDetect())
		{

			gTelaRenderizada_STANDBY = false;

			gModoOperacao = "LOGIN";
			//gModoOperacao = "OPERACAO";
			//gModoOperacao = "DEBUG";

			TELA_LimpaTela();

			delay(500);

		}

	}

}







void TELA_VerificaTouch_LOGIN()
{

	if (gTela_Hardware == "TERMINAL")
	{ 

		String retConsole;

		retConsole = ReadConsoleInput();

		if (retConsole != "") 
		{
			LogTerm("Opcao selecionada: " + retConsole);	
		}


		if (retConsole.toInt() == 1)
		{
			//LogTerm(F("LEITOR BIOMETRICO SELECIONADO");
		}

		if (retConsole.toInt() == 2)
		{
			//LogTerm(F("LEITOR RFID SELECIONADO VIA TERMINAL");


			gModoOperacao_SubTela = "LER_RFID";


			gTelaRenderizada_LOGIN = false;



			
		}

		if (retConsole.toInt() == 3)
		{
			gModoOperacao = "DEBUG";
			gTelaRenderizada_LOGIN = false;

			//LogTerm(F("TECLADO NUM SELECIONADO");
			//LogTerm(F("TECLADO ALFA SELECIONADO");

			TELA_LimpaTela();

			delay(500);   
		}

		if (retConsole.toInt() == 4)
		{
			gModoOperacao = "ADMIN"; 
			gTelaRenderizada_LOGIN = false;

			//LogTerm(F("ADMIN SELECIONADO");

			TELA_LimpaTela();

			delay(500);    
		}

	}




	if (gTela_Hardware == "ER-TFTM070-5")
	{  

		//tft.changeMode(GRAPHIC);

		if (tft.touchDetect())
		{
			//TELA_LogTerm_XY();
			//LogTerm(F("TELA_VerificaTouch_LOGIN");

			tft.touchReadPixel(&gTouch_X, &gTouch_Y);

			gTouch_X = 800 - gTouch_X;
			gTouch_Y = 480 - gTouch_Y;

			//TELA_LogTerm_XY(); 

			//botao 1:
			if (gTouch_X >= gOffset_W && gTouch_X <= gTamBotao_W + gOffset_W)  
			{

				if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
				{

					LogTerm(F("LEITOR BIOMETRICO SELECIONADO"));
					TELA_Texto("LEITOR BIOMETRICO SELECIONADO", "BRANCO");

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

					gModoOperacao_SubTela = "LER_RFID";


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
					gModoOperacao = "DEBUG"; 

					//TELA_Texto("TECLADO NUM SELECIONADO", "MAGENTA");
					TELA_Texto("TECLADO ALFA SELECIONADO", "MAGENTA");

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

	if (gTela_Hardware == "ER-TFTM070-5")
	{  

		if (tft.touchDetect())
		{


			//TELA_LogTerm_XY();
			//LogTerm(F("TELA_VerificaTouch_ADMIN");

			tft.touchReadPixel(&gTouch_X, &gTouch_Y);

			gTouch_X = 800 - gTouch_X;
			gTouch_Y = 480 - gTouch_Y;



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
			if (gTouch_X >= gOffset_W && gTouch_X <= gTamBotao_W + gOffset_W)  
			{

				if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
				{

					LogTerm(F("BOTAO 1 APERTADO"));
					TELA_Texto("BOTAO 1 APERTADO", "BRANCO");

				}

			}



			//botao 2:
			if (gTouch_X >= 2 * gOffset_W + gTamBotao_W && gTouch_X <= 2 * gOffset_W + 2 * gTamBotao_W )  
			{

				if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
				{
					LogTerm(F("BOTAO 2 APERTADO"));
					TELA_Texto("BOTAO 2 APERTADO", "AZUL");
					//delay(500);
					//TELA_LogTerm_XY();        
				}

			}



			//botao 3:
			if (gTouch_X >= 3 * gOffset_W + 2 * gTamBotao_W && gTouch_X <= 3 * gOffset_W + 3 * gTamBotao_W )  
			{

				if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
				{
					LogTerm(F("BOTAO 3 APERTADO"));
					TELA_Texto("BOTAO 3 APERTADO", "MAGENTA");  
					//delay(500); 

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










