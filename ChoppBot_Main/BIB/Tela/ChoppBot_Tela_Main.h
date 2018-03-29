



String gTela_Hardware = String("ER-TFTM070-5"); 
//String gTela_Hardware = String("TELA2"); 

uint16_t gPosTxt_X = 0;
uint16_t gPosTxt_Y = 0;
uint16_t gTxtSize = 15;

//tft.getCursor(&currentX,&currentY);

// inicializa tela var principal da tela
//RA8875 tft = RA8875(RA8875_CS,RA8875_RESET);//Teensy3/arduino's


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




void Render_Botao(int IndexBotao, String Texto, String Cor)
{
 
  int TamBotao_W = 80;
  int TamBotao_H = 80;
  int Offset_W = 60;
  int Offset_H = 60;

  int Offset_Atual_W = 0;

  Offset_Atual_W = Offset_W * IndexBotao;

  Offset_Atual_W = Offset_Atual_W + (TamBotao_W * IndexBotao);

  tft.fillRect(Offset_W, Offset_H, Offset_W + TamBotao_W, Offset_H + TamBotao_H, RA8875_WHITE);

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

  
  tft.changeMode(TEXT);
  tft.setTextColor(RA8875_BLACK);
  //tft.setCursor (110, 120);
  //tft.setFontScale(6); 
  //tft.print (" 1 ");

}


void Render_Interface()
{
  if (gTela_Hardware == "ER-TFTM070-5")
  {  
    Render_Botao(1, "1", "BRANCO");
    Render_Botao(2, "2", "AZUL");
    //Render_Botao(3, "3", "MAGENTA");
  }

}




void Render_Interface2()
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
