

// SPI:
#include <SPI.h>

#include <RA8875.h>



// TELA: Parametros
#define TELA_PINO_INT 	4
#define TELA_PINO_CS	10
#define TELA_PINO_RESET 9



//Arduino DUE,Arduino mega2560,Arduino UNO
#define RA8875_INT TELA_PINO_INT
#define RA8875_CS TELA_PINO_CS

#define RA8875_RESET TELA_PINO_RESET


String gModoOperacao; 
String gModoOperacao_SubTela;

// var que define se a aplicacao esta no modo debug. isto faz com que algumas msgs de debug
// sejam exibidas na tela e/ou no terminal
bool gModoDebug;

// VERSAO DA APLICACAO
#define VersaoAPP F("1.0")



// Numero maximo de torneiras possiveis no sistema
#define ctMAX_TORNEIRAS 4
String gaEngatados[ctMAX_TORNEIRAS];	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TECLADO
// -------
//
// Vars necessarias para o teclado numerico e alfanumerico
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




String gTecladoNum_ValAtual;
String gTecladoAlfa_ValAtual;


#define ctTECLADO_NUM_TOTAL_BOTOES 	14
#define ctTECLADO_ALFA_TOTAL_BOTOES 42




// var que armazena a posicao inicial xy renderizada dos botoes e seu tamanho para poder serem usadas no touch
// var iniciada com os valores abaixo e depois modificada quando os botoes do teclado sao renderizados

String aTecladoNum_PosBotoes[ctTECLADO_NUM_TOTAL_BOTOES]={"X01,TAM,Y01,TAM",
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
														   "X12,TAM,Y12,TAM",
														   "X13,TAM,Y13,TAM",
														   "X14,TAM,Y14,TAM"
														   };


String aTecladoAlfa_PosBotoes[ctTECLADO_ALFA_TOTAL_BOTOES]={"X01,TAM,Y01,TAM",
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
															"X12,TAM,Y12,TAM",
															"X13,TAM,Y13,TAM",
															"X14,TAM,Y14,TAM",
															"X15,TAM,Y15,TAM",
															"X16,TAM,Y16,TAM",
															"X17,TAM,Y17,TAM",
															"X18,TAM,Y18,TAM",
															"X19,TAM,Y19,TAM",
															"X20,TAM,Y20,TAM",
															"X21,TAM,Y21,TAM",
															"X22,TAM,Y22,TAM",
															"X23,TAM,Y23,TAM",
															"X24,TAM,Y24,TAM",
															"X25,TAM,Y25,TAM",
															"X26,TAM,Y26,TAM",
															"X27,TAM,Y27,TAM",
															"X28,TAM,Y28,TAM",
															"X29,TAM,Y29,TAM",
															"X30,TAM,Y30,TAM",
															"X31,TAM,Y31,TAM",
															"X32,TAM,Y32,TAM",
															"X33,TAM,Y33,TAM",
															"X34,TAM,Y34,TAM",
															"X35,TAM,Y35,TAM",
															"X36,TAM,Y36,TAM",
															"X37,TAM,Y37,TAM",
															"X38,TAM,Y38,TAM",
															"X39,TAM,Y39,TAM",
															"X40,TAM,Y40,TAM",
															"X41,TAM,Y41,TAM",
														  	"X42,TAM,Y42,TAM"
														   };

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BOTOES TOUCH - BOUNCE
// ---------------------
//
// Vars necessarias para controlar o press dos botoes e nao permitir double press (bounce)
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//  numero de clicks de sensibilidade dos botoes em uma determinada tela. Para evitar o double press
//const int ctBOUNCE_SENSIB_BOTAO = 50;		
#define ctBOUNCE_SENSIB_BOTAO 80

	


// vars que permitem que um botao seja clicado apenas 1 vez, em vez de um monte, quado um touch ocorre
// este modelo conta os cliques disparados pelo touch ocorrido, que sempre sao muitos
// O sistema deve contar apenas o gBounce_ContaClick = 0 como o disparador do evento desejado.
// qualquer numero maior, sao os cliques extras disparados pelo botao, que o programa deve ignorar
// Depois de passado X milissegundos (ctBOUNCE_SENSIB_BOTAO) depis do touch, o programa zera a var global de cliques 
// permitindo que um novo clique ocorra
unsigned long gBounce_time_inicio;
unsigned long gBounce_time_atual;
unsigned long gBounce_time_tempo_passado;

int gBounce_SegundosPassados;
int gBounce_Last_SegundosPassados;


// var que conta o numero de cliques executaados no botao
int gBounce_ContaClick = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// LED INDICADOR DE PROGRAMA RODANDO COM SUCESSO
// ---------------------------------------------
//
// O  led do arduino é usado para indicar o funcionamento do programa. ele pisca em um intervalo de tempo determinado
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Tempo de alternancia da luz do led
//const int ctLED_ON_TEMPO = 2400;		// tempo em ms
#define ctLED_ON_TEMPO 2400

		

// permitindo que um novo clique ocorra
unsigned long gLedON_time_inicio;
unsigned long gLedON_time_atual;
unsigned long gLedON_time_tempo_passado;

int gLedON_SegundosPassados;
int gLedON_Last_SegundosPassados;
bool gLedON_EstadoAtual;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TELA
// ----
//
// variaveis que controlam se a tela esta desenhada, para impedir que ela fique sendo redesenhada o tempo todo e
// var que define o tipo de tela sendo usado 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// var que define a tela sendo usada
String gTela_Hardware;		// ER-TFTM070-5 | TERMINAL definidos na rotina de iniciar vars

// Vars de controle que verificam se uma determinada tela esta renderizada para nao render de novo
bool gTelaRenderizada_TecNum;
bool gTelaRenderizada_TecAlfa;
bool gTelaRenderizada_STANDBY;
bool gTelaRenderizada_LOGIN;
bool gTelaRenderizada_OPERACAO;
bool gTelaRenderizada_INSTALACAO;
bool gTelaRenderizada_ADMIN;
bool gTelaRenderizada_DEBUG;
bool gTelaRenderizada_TESTE;

bool gTelaRenderizada_LER_RFID;
bool gTelaRenderizada_OPERACAO_SERVICO;

bool gTelaRenderizada_MSGBOX;




String gServico_IDChopp;



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

    
#define CinzaShadow     		rgb565_from_triplet(99, 99, 99)       
#define CinzaFundoTitMsgBox     rgb565_from_triplet(201, 201, 201)      
#define CinzaLabels			    rgb565_from_triplet(220, 220, 220)     
#define VerdeOK			    	rgb565_from_triplet(137, 255, 157)     
#define LaranjaAlerta	    	rgb565_from_triplet(255, 216, 181)     




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// VARIAVEIS DE SESSAO
// -------------------
//
// variaveis qye controlam o login e pessoa logada
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool gSessao_Logado;
int gSessao_IDUser;
int gSessao_Nivel;
String gSessao_Nome;
float gSessao_SaldoAtual;



RA8875 tft = RA8875(RA8875_CS,RA8875_RESET);





        
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

    if (found > index)
    {
    	return data.substring(strIndex[0], strIndex[1]);
    }
    else
    {
    	return String("");
    }

    //return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


String FormatNumber(float Valor, String Tipo)
{
	String ret = "";
	String temp = String(Valor);

	temp.replace(".", ",");

	if (Tipo == "MONEY")
	{
		ret = "R$ ";
	}

	ret += temp;

	return ret;
}



String Right(String Alvo, int Qtde)
{
	return Alvo.substring(Alvo.length() - Qtde);
}


String Left(String Alvo, int Qtde)
{
	return Alvo.substring(0, Qtde);
}


String ReadConsoleInput()
{

	if (Serial.available() > 0) 
	{
		return Serial.readString();
	}
	else
	{
		return String("");
	}

}



// Loga uma informacao no terminal
void LogTerm (String Texto)
{
	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}


// Loga uma informacao no terminal - OVERRIDE int
void LogTerm (int Texto)
{
	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}


// Loga uma informacao no terminal - OVERRIDE int
void LogTerm (unsigned long Texto)
{
	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}

// Loga uma informacao no terminal - OVERRIDE int
void LogTerm (double Texto)
{

	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}



String CharFromAsc2(int Asc2Value)
{
    char ret;

    ret = Asc2Value;

    return String(ret);
}




uint16_t rgb565_from_triplet(uint8_t red, uint8_t green, uint8_t blue)
{
  red   >>= 3;
  green >>= 2;
  blue  >>= 3;
  return (red << 11) | (green << 5) | blue;
}










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
volatile uint16_t gTouch_X;
volatile uint16_t gTouch_Y;



//bool gBotao1_Apertado = false;
//bool gBotao2_Apertado = false;
//bool gBotao3_Apertado = false;


// var com a posicao Y padrao para desenhar botoes
#define POSICAO_PADRAO_BTN_Y 140



//tft.getCursor(&currentX,&currentY);



void TELA_LimpaTela()
{
	if (gTela_Hardware == F("ER-TFTM070-5"))
	{
		tft.fillScreen(RA8875_BLACK);  
	}

	if (gTela_Hardware == F("TERMINAL"))
	{
		LogTerm(F("TELA -> LimpaTela()")); 
	}
}



// Escreve um texto na tela
void TELA_Texto(String Texto, String Cor)
{

	if (gTela_Hardware == F("TERMINAL"))
	{
		LogTerm(Texto); 
	}


	if (gTela_Hardware == F("ER-TFTM070-5"))
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

		sprintf(TheTexto,"SAIR: X = %d | Y = %d   --   X > %d e X < %d  |  Y > %d e Y < %d  -- posY = %d", gTouch_X, gTouch_Y, btnSair_PosAtual_X, btnSair_PosAtual_X + btnSair_Size_W, btnSair_PosAtual_Y, btnSair_PosAtual_Y + btnSair_Size_H);  
		TELA_Texto(TheTexto, "");


		
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
//#include "../Teclado/ChoppBot_Teclado_NUM.h" 
//#include "../Teclado/ChoppBot_Teclado_ALFA.h" 




// Funcao que inicializa a tela sendo usada no momento
void TELA_IniciaTela()
{

	if (gTela_Hardware == F("ER-TFTM070-5"))
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





void TELA_Render_Botao(int IndexBotao, String Texto, String Texto2, String Texto3, String Cor)
{

	if (gTela_Hardware == F("ER-TFTM070-5"))
	{

		int OffSet_TextoBotao_W = gTamBotao_W / 2 - 11;
		int OffSet_TextoBotao_H = gTamBotao_H / 2 - 27;

		int OffSet_TextoTitulo_W = 0;
		int OffSet_TextoTitulo_H = 140;

		int OffSet_TextoTitulo2_H = 25;
		int OffSet_TextoTitulo3_H = 50;


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
		tft.setFontScale(2); 


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
		tft.setFontScale(0);
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


		gTotalBotoes++;

	}

}







void TELA_Render_Interface_STANDBY()
{
	
	//LogTerm(gTela_Hardware);


	if (gTelaRenderizada_STANDBY == false)
	{

        //LogTerm(F("== [Modo Atual: STANDBY] ==");


		if (gTela_Hardware == F("TERMINAL"))
		{  
			LogTerm(String(F("ChoppBot ")) + String(VersaoAPP));
			LogTerm(F("Tecle algo no console para iniciar..."));
		}

		if (gTela_Hardware == F("ER-TFTM070-5"))
		{  

			tft.setTextColor(RA8875_YELLOW);
			tft.setCursor (210, 150);
			tft.setFontScale(3); 
			tft.print (String(F("ChoppBot ")) + String(VersaoAPP));    
			//tft.print ("ChoppBot 1.0");    

			tft.setTextColor(RA8875_WHITE);
			tft.setCursor (195, 310);
			tft.setFontScale(1); 
			tft.print (F("Toque na tela para iniciar"));    

		}

		gTelaRenderizada_STANDBY = true;

	}


}



void TELA_Render_Interface_LOGIN()
{

	if (gTelaRenderizada_LOGIN == false)
	{

		//LogTerm(F("== [Modo Atual: LOGIN] ==");

		if (gTela_Hardware == F("TERMINAL"))
		{  

			LogTerm(F("Ola! Seja bem vindo!"));
			LogTerm(F("Escolha o seu metodo de identificacao e digite o numero correspondente no console:"));
			LogTerm(F("1 - LEITOR BIOMETRICO"));
			LogTerm(F("2 - LEITOR DE CARTAO"));
			//LogTerm(F("3 - ABRE TECLADO NUMERICO"));
			LogTerm(F("3 - ABRE TECLADO ALFA"));

			LogTerm(F("4 - ADMIN"));


		}


		if (gTela_Hardware == F("ER-TFTM070-5"))
		{  

			tft.setTextColor(RA8875_YELLOW);
			tft.setCursor (175, 30);
			tft.setFontScale(2); 
			tft.print (F("Ola! Seja vem vindo!"));   

			tft.setTextColor(RA8875_WHITE);
			tft.setCursor (100, 130);
			tft.setFontScale(1); 
			tft.print (F("Escolha o seu metodo de identificacao:"));   

			gOffset_H = POSICAO_PADRAO_BTN_Y + 95;

			TELA_Render_Botao(1, F("LEITOR BIOMETRICO"), F(""), F(""), F("BRANCO"));
			TELA_Render_Botao(2, F("LEITOR DE CARTAO"), F(""), F(""), F("AZUL"));
			//TELA_Render_Botao(3, F("ABRE TECLADO NUMERICO"), F(""), F("MAGENTA"));
			TELA_Render_Botao(3, F("ABRE TECLADO ALFA"), F(""), F(""), F("MAGENTA"));

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

		

		if (gTela_Hardware == F("TERMINAL"))
		{  




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
		}


		if (gTela_Hardware == F("ER-TFTM070-5"))
		{  		


			// Cabecalho logado ///////

			tft.setFontScale(1); 

			tft.setTextColor(CinzaLabels);
			tft.setCursor (10, 10);			
			tft.print (F("Nome: ")); 
			tft.setCursor (10, 45);			
			tft.print (F("Saldo: "));  

			tft.setTextColor(RA8875_WHITE);
			tft.setCursor (120, 10);			
			tft.print (gSessao_Nome); 
			tft.setCursor (120, 45);	
			tft.print (FormatNumber(gSessao_SaldoAtual, "MONEY"));  



			//////////////////////////////////////  

			tft.setTextColor(VerdeOK);
			tft.setCursor (220, 110);
			tft.setFontScale(1); 
			tft.print (F("Escolha a sua torneira:"));    



			// Botao SAIR ///////////////////////////////

		    int btnSair_PosAtual_X = 680;
			int btnSair_PosAtual_Y = 20;

			int btnSair_Size_W = 100;
			int btnSair_Size_H = 60;

			tft.fillRoundRect(btnSair_PosAtual_X, btnSair_PosAtual_Y, btnSair_Size_W, btnSair_Size_H, 8, Red);
		
		    tft.setTextColor(RA8875_WHITE);
		    tft.setFontScale(1); 
		    tft.setCursor (btnSair_PosAtual_X + (btnSair_Size_W / 2) - 35, btnSair_PosAtual_Y + 12); 
		    tft.print (F("SAIR"));	

		    //////////////////////////////////////

		    // Inicia desenho do restante da tela e botoes


			gOffset_H = POSICAO_PADRAO_BTN_Y + 49;


			TELA_Render_Botao(1, F("Imperial IPA"), F("R$ 25,00 / Litro"), F(""), F("BRANCO"));
			TELA_Render_Botao(2, F("Hoocus Pocus"), F("R$ 19,00 / Litro"), F(""), F("AZUL"));
			TELA_Render_Botao(3, F("Duchese"), F("R$ 32,00 / Litro"), F(""), F("MAGENTA"));


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


		            TELA_Render_Botao(x + 1, tmp_Nome, tmp_Tipo, String( String(F("R$ ")) + tmp_Valor + String(F(" / Litro")) ), F("AZUL"));




		        }


		    }

		}

		gTelaRenderizada_OPERACAO = true;

	}

}







void TELA_VerificaTouch_STANDBY()
{

	if (gTela_Hardware == F("TERMINAL"))
	{ 

		String retConsole;

		retConsole = ReadConsoleInput();

		if (retConsole != "") 
		{
			LogTerm(String(F("Opcao selecionada: ")) + retConsole);

			gTelaRenderizada_STANDBY = false;

			gModoOperacao = F("LOGIN");
			//gModoOperacao = "OPERACAO";
			//gModoOperacao = "DEBUG";

			TELA_LimpaTela();

			delay(500);			
		}

	}

	if (gTela_Hardware == F("ER-TFTM070-5"))
	{  

		if (tft.touchDetect())
		{

			gTelaRenderizada_STANDBY = false;

			gModoOperacao = F("LOGIN");
			//gModoOperacao = "OPERACAO";
			//gModoOperacao = "DEBUG";

			TELA_LimpaTela();

			delay(500);

		}

	}

}







void TELA_VerificaTouch_LOGIN()
{

	if (gTela_Hardware == F("TERMINAL"))
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

			TELA_LimpaTela();

			delay(500);   
		}

		if (retConsole.toInt() == 4)
		{
			gModoOperacao = F("ADMIN"); 
			gTelaRenderizada_LOGIN = false;

			//LogTerm(F("ADMIN SELECIONADO");

			TELA_LimpaTela();

			delay(500);    
		}

	}




	if (gTela_Hardware == F("ER-TFTM070-5"))
	{  

		//tft.changeMode(GRAPHIC);

		if (tft.touchDetect())
		{
			//TELA_LogTerm_XY();
			//LogTerm(F("TELA_VerificaTouch_LOGIN");

			tft.touchReadPixel(&gTouch_X, &gTouch_Y);

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

	if (gTela_Hardware == F("ER-TFTM070-5"))
	{  

		if (tft.touchDetect())
		{


			//TELA_LogTerm_XY();
			//LogTerm(F("TELA_VerificaTouch_ADMIN");

			tft.touchReadPixel(&gTouch_X, &gTouch_Y);

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

	if (gTela_Hardware == F("ER-TFTM070-5"))
	{  



		//tft.changeMode(GRAPHIC);

		if (tft.touchDetect())
		{

			tft.touchReadPixel(&gTouch_X, &gTouch_Y);

			LogTerm(String(gTouch_X) + String(" -- ") + String(gTouch_Y));

			//murch
			//gTouch_X = gTouch_X - 800;
			//gTouch_Y = gTouch_Y - 480;	

			//gTouch_X = gTouch_X * -1;
			//gTouch_Y = gTouch_Y * -1;	


			TELA_LogTerm_XY();


			//gTouch_X = 800 - gTouch_X;
			//gTouch_Y = 480 - gTouch_Y;			

			//gTouch_X = 800 - gTouch_X;
			//gTouch_Y = 480 - gTouch_Y;

			//TELA_LogTerm_XY(); 

			//botao 1:
			if (gTouch_X >= gOffset_W && gTouch_X <= gTamBotao_W + gOffset_W)  
			{

				if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
				{

					LogTerm(F("BOTAO 1 APERTADO"));
					//TELA_Texto(F("BOTAO 1 APERTADO"), F("BRANCO"));



					gServico_IDChopp = F("1");

					//gModoOperacao_SubTela = F("OPERACAO_SERVICO");


					//gTelaRenderizada_OPERACAO = false;

					//TELA_LimpaTela();

					//delay(500);   

				}

			}



			//botao 2:
			if (gTouch_X >= 2 * gOffset_W + gTamBotao_W && gTouch_X <= 2 * gOffset_W + 2 * gTamBotao_W )  
			{

				if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
				{
					LogTerm(F("BOTAO 2 APERTADO"));
					//TELA_Texto(F("BOTAO 2 APERTADO"), F("AZUL"));
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
					//TELA_Texto(F("BOTAO 3 APERTADO"), F("MAGENTA"));  
					//delay(500); 

				}

			}




			// botao sair


		    int btnSair_PosAtual_X = 680;
			int btnSair_PosAtual_Y = 20;

			int btnSair_Size_W = 100;
			int btnSair_Size_H = 60;			




			if ((gTouch_X >= btnSair_PosAtual_X) && (gTouch_X <= btnSair_PosAtual_X + btnSair_Size_W)) 
			{

				if ((gTouch_Y >= btnSair_PosAtual_Y) && (gTouch_Y <= btnSair_PosAtual_Y + btnSair_Size_H)) 
				{
					LogTerm(F("BOTAO SAIR APERTADO"));
					TELA_Texto(F("BOTAO SAIR APERTADO"), F("MAGENTA"));  
					//delay(500); 

					

				}

			}


		}

	}

}






void TELA_VerificaTouch_DEBUG()
{

	//TELA_VerificaTouch_TECLADO_NUM();
	//TELA_VerificaTouch_TECLADO_ALFA();

}










// Init global vars with their operational values
void InicializaVars() 
{




	// variaveis princiais
	gModoOperacao = F("OPERACAO");  
	gModoOperacao_SubTela = F("");
	
	gModoDebug = true;
	//gModoDebug = false;


	// Modo de output a ser usado
	gTela_Hardware = F("ER-TFTM070-5"); 		// tela LCD 7pol Touch Resistive
	//gTela_Hardware = String("TERMINAL"); 		// saidas de texto para o terminal (console)	



	// controle de render de tela
	gTelaRenderizada_TecNum = false;
	gTelaRenderizada_TecAlfa = false;
	gTelaRenderizada_STANDBY = false;	
	gTelaRenderizada_LOGIN = false;
	gTelaRenderizada_OPERACAO = false;	
	gTelaRenderizada_INSTALACAO = false;
	gTelaRenderizada_ADMIN = false;
	gTelaRenderizada_DEBUG = false;
	gTelaRenderizada_TESTE = false;
	gTelaRenderizada_LER_RFID = false;
	gTelaRenderizada_OPERACAO_SERVICO = false;
	gTelaRenderizada_MSGBOX = false;
	//teclado
	gTecladoNum_ValAtual = F("");
	gTecladoAlfa_ValAtual = F("");
				

	// Variaveis de sessao:
	gSessao_Logado = false;
	gSessao_IDUser = -1;
	gSessao_Nivel = -1;
	gSessao_Nome = "";
	gSessao_SaldoAtual = -1;				

	gServico_IDChopp = "";
	
	// inicializa var de engatados
	for (int x = 0 ; x <= ctMAX_TORNEIRAS ; x++)
	{
		gaEngatados[x] = F("");
	}	 	

}








// Procedure que testa se ocorreu algum interrupt: O sistema fica em modo StandBy ate que alguem toque na tela, ou faca alguma outra acao que gere uma interrupcao
void TestaInterrupts()
{

    if (gModoOperacao == F("OPERACAO"))
    {


        if (gModoOperacao_SubTela == F(""))
        {
            TELA_VerificaTouch_OPERACAO();
        }

        if (gModoOperacao_SubTela == F("OPERACAO_SERVICO"))
        {
            //TELA_VerificaTouch_OPERACAO_SERVICO();
        }

        
    }
}



// ROTINA DE OPERACAO
void Exec_OPERACAO()
{
    if (gTelaRenderizada_OPERACAO == false)
    {
        LogTerm(F("== [Modo Atual: OPERACAO] =="));
    }  

    TELA_Render_Interface_OPERACAO();

}



// INTERNA ARDUINO: SETUP
void setup() 
{
  
    Serial.begin(115200);       // 115200 pois o RFID precisa desta velocidade, para acompanharmos o que ele escreve no serial


    LogTerm("Iniciando");

    InicializaVars();


    TELA_IniciaTela();

    TELA_Texto(String(F("Choppbot FastPlay")) + String(VersaoAPP), F("VERDE"));

    TELA_Texto(F("======================"), F("VERDE"));

    LogTerm("Iniciado");
  
}


// INTERNA ARDUINO: LOOP ETERNO
void loop() 
{

	delay(50);

	TestaInterrupts();


    if (gModoOperacao == F("OPERACAO"))
    {

        if (gModoOperacao_SubTela == F(""))
        {
            Exec_OPERACAO();  
        }
        
       if (gModoOperacao_SubTela == F("OPERACAO_SERVICO"))
        {
            //Exec_OPERACAO_SERVICO();  
        }        

    }	
}

