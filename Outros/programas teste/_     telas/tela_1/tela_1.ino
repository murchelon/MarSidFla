/***************************************************
Tela 1 - escolha o chopp pelo botão touch
****************************************************/


#include <SPI.h>
#include <RA8875.h>

#define RA8875_INT 4
#define RA8875_CS 10 

#define RA8875_RESET 9


RA8875 tft = RA8875(RA8875_CS,RA8875_RESET);


uint16_t tx, ty;
int m = 60;

void interface(){
  tft.fillRect(80,80 + m,160,160,RA8875_WHITE);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (110, 130 + m);
          tft.setFontScale(6); 
          tft.print (" 1 ");

                   
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (110, 300 + m);
          tft.setFontScale(1); 
          tft.print ("Chopp A");// puxa do banco de dados
          tft.setCursor (80, 340 + m);
          tft.print ("R$ 10,00 / L");// puxa do banco de dados

  
  tft.fillRect(80+(160*1)+(80*1),80 + m,160,160,RA8875_BLUE);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (350, 130 + m);
          tft.setFontScale(6); 
          tft.print (" 2 ");

                             
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLUE);
          tft.setCursor (350, 300 + m);
          tft.setFontScale(1); 
          tft.print ("Chopp B");// puxa do banco de dados
          tft.setCursor (320, 340 + m);
          tft.print ("R$ 12,00 / L");// puxa do banco de dados

          

   tft.fillRect(80+(160*2)+(80*2),80 + m,160,160,RA8875_GREEN);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (590, 130 + m);
          tft.setFontScale(6); 
          tft.print (" 3 ");
  
                             
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_GREEN);
          tft.setCursor (590, 300 + m);
          tft.setFontScale(1); 
          tft.print ("Chopp c");// puxa do banco de dados
          tft.setCursor (560, 340 + m);
          tft.print ("R$ 14,00 / L");// puxa do banco de dados

          
}

void setup() 
{
  Serial.begin(9600);
  //while (!Serial) {;}
  Serial.println("RA8875 start");

  tft.begin(RA8875_800x480);//initialize library

  tft.touchBegin(RA8875_INT);//enable Touch support!
  interface();

}

uint16_t choosenColor = 0;


void loop() 

{    


  
  tft.changeMode(TEXT);
   tft.setTextColor(RA8875_WHITE);
  tft.setCursor (140, 30);
  tft.setFontScale(2); 
  tft.print ("Escolha a sua torneira :");
    tft.changeMode(GRAPHIC);
    
  if (tft.touchDetect()){//easy!
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
        tx=800-tx;ty=480-ty;
      if (ty >= 80 + m && ty <= 80 + 160 + m){ //interface area
        if ((tx > 80 && tx < (80+160))){
          choosenColor = RA8875_WHITE;
          interface();
          tft.fillRect(80,80 + m,160,160,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);

          delay(200);
          tft.fillRect(80,80 + m,160,160,RA8875_WHITE);          
          
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (110, 130 + m);
          tft.setFontScale(6); 
          tft.print (" 1 ");

          delay(500);
          tft.touchDetect(false);


        } 
        else if ((tx > 80+(160*1)+(80*1) && tx < 80+(160*2)+(80*1))){
          choosenColor = RA8875_BLUE;
          interface();
          tft.fillRect(80+(160*1)+(80*1),80 + m,160,160,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);

          delay(200);
          tft.fillRect(80+(160*1)+(80*1),80 + m,160,160,RA8875_BLUE);  

                   
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (350, 130 + m);
          tft.setFontScale(6); 
          tft.print (" 2 ");

          delay(500);
          tft.touchDetect(false);
 
          } 

        else if ((tx > 80+(160*2)+(80*2) && tx < 80+(160*3)+(80*2))){
          choosenColor = RA8875_GREEN;
          interface();
          tft.fillRect(80+(160*2)+(80*2),80 + m,160,160,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);

          delay(200);
          tft.fillRect(80+(160*2)+(80*2),80 + m,160,160,RA8875_GREEN);  

                   
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (590, 130 + m);
          tft.setFontScale(6); 
          tft.print (" 3 ");

          delay(500);
          tft.touchDetect(false);
          
        }
       
        
      }
  }
}
