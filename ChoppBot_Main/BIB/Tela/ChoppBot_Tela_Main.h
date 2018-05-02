


// var que define a tela sendo usada
String gTela_Hardware = String("ER-TFTM070-5"); 
//String gTela_Hardware = String("TELA2"); 


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
}



// Escreve um texto na tela
void TELA_Texto(String Texto, String Cor)
{

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


      if (gModoOperacao == 'DEBUG')
      {
        gTeclado_Renderizado = false;
      }


    }

  }  


}



void TELA_LogTerm_XY()
{

  if (gTela_Hardware == "ER-TFTM070-5")
  {

    char TheTexto[100]; 

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
      TELA_Texto(gModoOperacao, "VERMELHO");
    }

    //tft.changeMode(GRAPHIC);
  }

}



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


void TELA_Render_Interface_OPERACAO()
{
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

}



void TELA_Render_Interface_LOGIN()
{
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
    TELA_Render_Botao(3, "ABRE TECLADO", "", "MAGENTA");

    // Area para chamar admin
    //tft.fillRect(700, 0, 100, 60, RA8875_WHITE);

  }

}



void TELA_Render_Interface_STANDBY()
{
  if (gTela_Hardware == "ER-TFTM070-5")
  {  

    tft.setTextColor(RA8875_YELLOW);
    tft.setCursor (195, 150);
    tft.setFontScale(3); 
    tft.print ("ChoppBot 1.0");    

    tft.setTextColor(RA8875_WHITE);
    tft.setCursor (180, 310);
    tft.setFontScale(1); 
    tft.print ("Toque na tela para iniciar");    

  }

}



//Este include tem de ficar neste local devido a ordem das chamadas das funcoes. Senao, da erro
#include "../Teclado/ChoppBot_Teclado.h" 


void TELA_VerificaTouch_STANDBY()
{

  if (gTela_Hardware == "ER-TFTM070-5")
  {  

    if (tft.touchDetect())
    {

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

  if (gTela_Hardware == "ER-TFTM070-5")
  {  

    //tft.changeMode(GRAPHIC);

    if (tft.touchDetect())
    {
      //TELA_LogTerm_XY();
      //LogTerm("TELA_VerificaTouch_LOGIN");

      tft.touchReadPixel(&gTouch_X, &gTouch_Y);

      gTouch_X = 800 - gTouch_X;
      gTouch_Y = 480 - gTouch_Y;

      //TELA_LogTerm_XY(); 

      //botao 1:
      if (gTouch_X >= gOffset_W && gTouch_X <= gTamBotao_W + gOffset_W)  
      {

        if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
        {

          LogTerm("LEITOR BIOMETRICO SELECIONADO");
          TELA_Texto("LEITOR BIOMETRICO SELECIONADO", "BRANCO");

          //TELA_Render_Botao(1, "", "", "PRETO");

        }

      }



      //botao 2:
      if (gTouch_X >= 2 * gOffset_W + gTamBotao_W && gTouch_X <= 2 * gOffset_W + 2 * gTamBotao_W )  
      {

        if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
        {
          LogTerm("LEITOR RFID SELECIONADO");
          TELA_Texto("LEITOR RFID SELECIONADO", "AZUL");
          //delay(500);
          //TELA_LogTerm_XY();        
        }

      }


      //botao 3:
      if (gTouch_X >= 3 * gOffset_W + 2 * gTamBotao_W && gTouch_X <= 3 * gOffset_W + 3 * gTamBotao_W )  
      {

        if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
        {

          gModoOperacao = "DEBUG"; 

          TELA_Texto("Abrindo TECLADO", "MAGENTA");

          TELA_LimpaTela();

          delay(500);          
        }

      }


      //botao ADMIN:
      if (gTouch_X >= 700 && gTouch_X <= 700 + 100)  
      {

        if (gTouch_Y >= 0 && gTouch_Y <= 0 + 100) 
        {

          gModoOperacao = "ADMIN"; 

          TELA_Texto("Abrindo ADMIN", "MAGENTA");

          TELA_LimpaTela();

          delay(500);          
        }

      }


        


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
      //LogTerm("TELA_VerificaTouch_ADMIN");

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

          LogTerm("BOTAO 1 APERTADO");
          TELA_Texto("BOTAO 1 APERTADO", "BRANCO");

        }

      }



      //botao 2:
      if (gTouch_X >= 2 * gOffset_W + gTamBotao_W && gTouch_X <= 2 * gOffset_W + 2 * gTamBotao_W )  
      {

        if (gTouch_Y >= gOffset_H && gTouch_Y <= gTamBotao_H + gOffset_H) 
        {
          LogTerm("BOTAO 2 APERTADO");
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
          LogTerm("BOTAO 3 APERTADO");
          TELA_Texto("BOTAO 3 APERTADO", "MAGENTA");  
          //delay(500); 
             
        }

      }





    }

  }

}






void TELA_VerificaTouch_DEBUG()
{

  if (gTela_Hardware == "ER-TFTM070-5")
  {  

    TELA_VerificaTouch_TECLADO();
  
  }

}









