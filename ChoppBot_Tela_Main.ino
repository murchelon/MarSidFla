



String gTela_Hardware = String("ER-TFTM070-5"); 

uint16_t gPosTxt_X = 0;
uint16_t gPosTxt_Y = 0;
uint16_t gTxtSize = 15;

//tft.getCursor(&currentX,&currentY);


// teste
void TELA_IniciaTela()
{

  if (gTela_Hardware == "ER-TFTM070-5")
  {
    tft.begin(RA8875_800x480);  
    //tft.fillScreen(RA8875_BLACK);//fill screen black
    tft.changeMode(TEXT);
    tft.setCursor(0,0);
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
