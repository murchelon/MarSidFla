/***************************************************
Tela 4 - administracao
****************************************************/


#include <SPI.h>
#include <RA8875.h>

#define RA8875_INT 4
#define RA8875_CS 10 

#define RA8875_RESET 9


RA8875 tft = RA8875(RA8875_CS,RA8875_RESET);


uint16_t tx, ty;

int b_wide = 200;
int b_high = 120;
int b_xoffset = 150;
int b_yoffset = 100;

void interface(){
  tft.fillRect(b_xoffset,b_yoffset,b_wide,b_high,RA8875_WHITE);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (b_xoffset + 10,b_yoffset + 30);
          tft.setFontScale(1); 
          tft.println (" Cadastrar ");
          tft.setCursor (b_xoffset + 30,b_yoffset + 70);
          tft.print (" Usuario ");

  
  tft.fillRect((b_xoffset * 2) + b_wide, b_yoffset,b_wide,b_high,RA8875_BLUE);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor ((b_xoffset * 2) + b_wide + 10, b_yoffset + 30);
          tft.setFontScale(1); 
          tft.print (" Recaregar ");
          tft.setCursor ((b_xoffset * 2) + b_wide + 40, b_yoffset + 70);
          tft.print (" Saldo ");
          

   tft.fillRect(b_xoffset + 180,b_yoffset * 3,b_wide,b_high ,RA8875_GREEN);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (b_xoffset + 180, b_yoffset * 3 + 40);
          tft.setFontScale(1); 
          tft.print (" Manutencao ");
          
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
  tft.setCursor (90, 30);
  tft.setFontScale(2); 
  tft.print ("Administracao :");
    tft.changeMode(GRAPHIC);

    
  if (tft.touchDetect()){
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
        tx=800-tx;ty=480-ty;
        
      if (ty >= b_yoffset && ty <= b_yoffset + b_high && (tx > b_xoffset && tx < b_wide + b_xoffset) ) //interface area
      
      { 
          choosenColor = RA8875_WHITE;
          interface();
          tft.fillRect(b_xoffset,b_yoffset,b_wide,b_high,RA8875_BLACK);

          delay(200);
          tft.fillRect(b_xoffset,b_yoffset,b_wide,b_high,RA8875_WHITE);          
          
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (b_xoffset + 10,b_yoffset + 30);
          tft.setFontScale(1); 
          tft.println (" Cadastrar ");
          tft.setCursor (b_xoffset + 30,b_yoffset + 70);
          tft.print (" Usuario ");

          delay(500);
          tft.touchDetect(false);

        } 
        else if ((ty >= b_yoffset && ty <= b_yoffset + b_high &&(tx > (b_xoffset * 2) + b_wide && (tx < +(b_xoffset * 2) + (b_wide * 2)))))  
        
        {
          choosenColor = RA8875_BLUE;
          interface();
          tft.fillRect((b_xoffset * 2) + b_wide, b_yoffset, b_wide, b_high,RA8875_BLACK);

          delay(200);
          tft.fillRect((b_xoffset * 2) + b_wide, b_yoffset, b_wide,b_high, RA8875_BLUE);  

                   
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor ((b_xoffset * 2) + b_wide + 10, b_yoffset + 30);
          tft.setFontScale(1); 
          tft.print (" Recaregar ");
          tft.setCursor ((b_xoffset * 2) + b_wide + 40, b_yoffset + 70);
          tft.print (" Saldo ");

          delay(500);
          tft.touchDetect(false);
 
          } 
        
        else if ((ty >= (b_yoffset * 3) && ty <= (b_yoffset * 3) + b_high &&(tx > (b_xoffset + 180) && (tx < + (b_xoffset + 180) + (b_wide)))))  

        
        {
          choosenColor = RA8875_GREEN;
          interface();
          tft.fillRect(b_xoffset + 180,b_yoffset * 3,b_wide,b_high,RA8875_BLACK);

          delay(200);
          tft.fillRect(b_xoffset + 180,b_yoffset * 3,b_wide,b_high ,RA8875_GREEN);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (b_xoffset + 180, b_yoffset * 3 + 40);
          tft.setFontScale(1); 
          tft.print (" Manutencao ");
          

          delay(500);
          tft.touchDetect(false);
          
        }
     }
  }

