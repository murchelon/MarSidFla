



String gTela_Hardware = String("ER-TFTM070-5"); 
//String gTela_Hardware = String("TELA2"); 

uint16_t gPosTxt_X = 0;
uint16_t gPosTxt_Y = 0;
uint16_t gTxtSize = 15;


int gTamBotao_W = 180;
int gTamBotao_H = 180;

int gOffset_W = 50;
int gOffset_H = 50;

int gPosicaoAtual_X = 0;

int gTotalBotoes = 0;

//tft.getCursor(&currentX,&currentY);

// inicializa tela var principal da tela
//RA8875 tft = RA8875(RA8875_CS,RA8875_RESET);//Teensy3/arduino's



void TELA_LimpaTela()
{
  tft.fillScreen(RA8875_BLACK);  
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


// Escreve um texto na tela
void TELA_Texto(String Texto)
{

  if (gTela_Hardware == "ER-TFTM070-5")
  {
    tft.setTextColor(RA8875_WHITE);
    //use the classic print an println command
    tft.print(Texto);

    gPosTxt_X = 0;
    gPosTxt_Y = gPosTxt_Y + gTxtSize;

    tft.setCursor(gPosTxt_X, gPosTxt_Y);
  }  


}





void TELA_Render_Botao(int IndexBotao, String Texto, String Texto2, String Cor)
{
 



  int OffSet_TextoBotao_W = 19;
  int OffSet_TextoBotao_H = 20;

  int OffSet_TextoTitulo_W = 0;
  int OffSet_TextoTitulo_H = 170;

  int OffSet_TextoTitulo2_H = 20;

  //Offset_Atual_W = Offset_W * IndexBotao;

  //Offset_Atual_W = Offset_Atual_W + (TamBotao_W * IndexBotao);

  //tft.fillRect(Offset_W, Offset_H, Offset_W + TamBotao_W, Offset_H + TamBotao_H, RA8875_WHITE);

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




  if (IndexBotao == 10)
  {

    /*
    tft.setFontScale(1); 

    // Desenha o quadrado do botao
    //tft.fillRect(gOffset_W, gOffset_H, gTamBotao_W, gTamBotao_H, RA8875_WHITE);

    IndexBotao--;
    gPosicaoAtual_X = gOffset_W + (IndexBotao * gTamBotao_W) + (IndexBotao * gOffset_W);


    tft.fillRect(gPosicaoAtual_X, gOffset_H, gTamBotao_W, gTamBotao_H, RA8875_WHITE);

    // Render o numero dentro do botao
    tft.setTextColor(RA8875_BLACK);
    tft.setCursor (gOffset_W + OffSet_TextoBotao_W, gOffset_H + OffSet_TextoBotao_H);
    
    tft.print (IndexBotao);


    // Render o titulo 
    tft.setFontScale(0.4);
    tft.changeMode(TEXT);
    tft.setTextColor(RA8875_WHITE);

    tft.setCursor (gOffset_W + OffSet_TextoTitulo_W, gOffset_H + OffSet_TextoTitulo_H);    
    tft.print (Texto);


    // Render Titulo2
    if (Texto2 != "")
    {
      tft.setCursor (gOffset_W + OffSet_TextoTitulo_W, gOffset_H + OffSet_TextoTitulo_H + OffSet_TextoTitulo2_H);
      tft.print (Texto2);
    }
   

    gTotalBotoes = 1;
    */


  }
  else
  {

    //IndexBotao--;
    tft.setFontScale(1); 

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
    

    // Render o numero dentro do botao
    tft.setTextColor(RA8875_BLACK);
    tft.setCursor (gPosicaoAtual_X + OffSet_TextoBotao_W, gOffset_H + OffSet_TextoBotao_H);

    tft.print (IndexBotao);

    // Render o titulo 
    tft.setFontScale(0.4);
    tft.changeMode(TEXT);
    tft.setTextColor(RA8875_WHITE);

    tft.setCursor (gPosicaoAtual_X + OffSet_TextoBotao_W + OffSet_TextoTitulo_W, gOffset_H + OffSet_TextoBotao_H + OffSet_TextoTitulo_H);    
    tft.print (Texto);

    // Render Titulo2
    if (Texto2 != "")
    {
      tft.setCursor (gPosicaoAtual_X + OffSet_TextoBotao_W + OffSet_TextoTitulo_W, gOffset_H + OffSet_TextoBotao_H + OffSet_TextoTitulo_H + OffSet_TextoTitulo2_H); 
      tft.print (Texto2);
    }


    gTotalBotoes++;

    //tft.fillRect(Offset_W + TamBotao_W + Offset_W, Offset_H, TamBotao_W, TamBotao_H, RA8875_YELLOW);
    //tft.fillRect(Offset_W + TamBotao_W + TamBotao_W + Offset_W + Offset_W, Offset_H, TamBotao_W, TamBotao_H, RA8875_MAGENTA);

  }

  



  pinMode(7,OUTPUT);// Saida para o botao 1

  
  //tft.fillRect(Offset_W * IndexBotao + TamBotao_W + Offset_W, Offset_H, Offset_W * IndexBotao + TamBotao_W, Offset_H + TamBotao_H, RA8875_BLUE);
  //tft.fillRect(Offset_W * 2 + TamBotao_W, Offset_H, Offset_W * 2 + TamBotao_W * 2, Offset_H + TamBotao_H, RA8875_BLUE);


  /*

  if (Cor == "BRANCO")
  {
    tft.fillRect(Offset_W * IndexBotao + TamBotao_W + Offset_W, Offset_H, Offset_W * IndexBotao + TamBotao_W, Offset_H + TamBotao_H, RA8875_WHITE);
  }

  if (Cor == "AZUL")
  {
    tft.fillRect(Offset_W * IndexBotao + TamBotao_W + Offset_W, Offset_H, Offset_W * IndexBotao + TamBotao_W, Offset_H + TamBotao_H, RA8875_BLUE);
  }

  */


  //Offset_W = Offset_W + (IndexBotao * (Offset_W + TamBotao_W));

  
  //tft.changeMode(TEXT);
  //tft.setTextColor(RA8875_BLACK);
  //tft.setCursor (110, 120);
  //tft.setFontScale(6); 
  //tft.print (" 1 ");

}


void TELA_Render_Interface()
{
  if (gTela_Hardware == "ER-TFTM070-5")
  {  
    TELA_Render_Botao(1, "BRANCO", "Valor 10", "BRANCO");
    TELA_Render_Botao(2, "AZUL", "Valor 20", "AZUL");
    TELA_Render_Botao(3, "MAGENTA", "wwww", "MAGENTA");

  }

}




void TELA_VerificaTouch()
{

  uint16_t tx, ty;

  if (tft.touchDetect())
  {



    tft.touchReadPixel(&tx, &ty);

    tx = 800 - tx;
    ty = 480 - ty;



    // if (IndexBotao == 1)
    // {

    //   tft.fillRect(gOffset_W, gOffset_H, gTamBotao_W, gTamBotao_H, RA8875_WHITE);
    // }
    // else
    // {

    //   gPosicaoAtual_X = gOffset_W + IndexBotao * gTamBotao_W + IndexBotao * gOffset_W;

    //   gPosicaoAtual_X = gPosicaoAtual_X - gOffset_W - gTamBotao_W;

    //   tft.fillRect(gPosicaoAtual_X, gOffset_H, gTamBotao_W, gTamBotao_H, RA8875_WHITE);

    //   //tft.fillRect(Offset_W + TamBotao_W + Offset_W, Offset_H, TamBotao_W, TamBotao_H, RA8875_YELLOW);
    //   //tft.fillRect(Offset_W + TamBotao_W + TamBotao_W + Offset_W + Offset_W, Offset_H, TamBotao_W, TamBotao_H, RA8875_MAGENTA);

    // }


    //if (1==1)
    //if ((tx > 120 && tx < (240)))
    //if ((tx > gOffset_W && tx < (gTamBotao_W)))    
    
    //gModoOperacao = "LOGIN";tx



    if (gModoOperacao == "STANDBY")
    {


      //botao 1:
      if (tx > gOffset_W && tx < gTamBotao_W + gOffset_W)  
      {

        if (ty > gOffset_H && ty < gTamBotao_H + gOffset_H) 
        {
          TELA_Texto("BOTAO 1 APERTADO");

          Serial.print("tx = ");
          Serial.print(tx); 

          Serial.print(" | ty = ");
          Serial.println(ty); 

          //tft.changeMode(GRAPHIC);

          

          //TELA_LimpaTela();
       

          delay(1000);

          //gModoOperacao = "LOGIN";
        }

      }



      //botao 2:
      if (tx > 2 * gOffset_W + gTamBotao_W && tx < 2 * gOffset_W + 2 * gTamBotao_W )  
      {

        if (ty > gOffset_H && ty < gTamBotao_H + gOffset_H) 
        {
          TELA_Texto("BOTAO 2 APERTADO");

          Serial.print("tx = ");
          Serial.print(tx); 

          Serial.print(" | ty = ");
          Serial.println(ty); 

          //tft.changeMode(GRAPHIC);
          delay(1000);
        }

      }




      //botao 3:
      if (tx > 3 * gOffset_W + gTamBotao_W && tx < 3 * gOffset_W + 3 * gTamBotao_W )  
      {

        if (ty > gOffset_H && ty < gTamBotao_H + gOffset_H) 
        {
          TELA_Texto("BOTAO 3 APERTADO");

          Serial.print("tx = ");
          Serial.print(tx); 

          Serial.print(" | ty = ");
          Serial.println(ty); 

          //tft.changeMode(GRAPHIC);

          delay(1000);
        }

      }



    }

  }

}




void TELA_Render_Interface_OLD()
{
  if (gTela_Hardware == "ER-TFTM070-5")
  {  
    tft.fillRect(80,80,150,150,RA8875_WHITE);

    tft.changeMode(TEXT);
    tft.setTextColor(RA8875_BLACK);
    tft.setCursor (110, 120);
    tft.setFontScale(6); 
    tft.print (" 1 ");


    tft.fillRect(80+(150*1)+(80*1),80,150,150,RA8875_BLUE);

    tft.changeMode(TEXT);
    tft.setTextColor(RA8875_BLACK);
    tft.setCursor (340, 120);
    tft.setFontScale(6); 
    tft.print (" 2 ");

    tft.fillRect(80+(150*2)+(80*2),80,150,150,RA8875_MAGENTA);

    tft.changeMode(TEXT);
    tft.setTextColor(RA8875_BLACK);
    tft.setCursor (570, 120);
    tft.setFontScale(6); 
    tft.print (" 3 ");


    //  botão cancel


    tft.fillRect(720,450,50,450,RA8875_RED);

  }

}



