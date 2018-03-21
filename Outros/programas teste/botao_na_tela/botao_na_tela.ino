/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-TFTM070-5 
Hardware SPI,4-Wire SPI Interface,5V Power Supply

This version use the new resistive touch screen functions, much easier!
Did you have already calibrated your screen? Better do as soon you can
Open TouchScreenCalibration example and follow instructions.
Tested and worked with:
Teensy3,Teensy3.1,Arduino UNO,Arduino YUN,Arduino Leonardo,Stellaris
Works with Arduino 1.6.0 IDE
****************************************************/


#include <SPI.h>
#include <RA8875.h>

//Arduino DUE,Arduino mega2560,Arduino UNO
#define RA8875_INT 4
#define RA8875_CS 10 

#define RA8875_RESET 9

//#if defined(NEEDS_SET_MODULE)//Energia, this case is for stellaris/tiva

//RA8875 tft = RA8875(3);//select SPI module 3
/*
for module 3 (stellaris)
SCLK:  PD_0
MOSI:  PD_3
MISO:  PD_2
SS:    PD_1
*/
//#else

RA8875 tft = RA8875(RA8875_CS,RA8875_RESET);//Teensy3/arduino's

//#endif

uint16_t tx, ty;


void interface(){
  tft.fillRect(10,10,40,40,RA8875_WHITE);
  tft.fillRect(10+(40*1)+(10*1),10,40,40,RA8875_BLUE);

  
//  tft.fillRect(10+(40*2)+(10*2),10,40,40,RA8875_RED);
//  tft.fillRect(10+(40*3)+(10*3),10,40,40,RA8875_GREEN);
//  tft.fillRect(10+(40*4)+(10*4),10,40,40,RA8875_CYAN);
//  tft.fillRect(10+(40*5)+(10*5),10,40,40,RA8875_MAGENTA);
//  tft.fillRect(10+(40*6)+(10*6),10,40,40,RA8875_YELLOW);
//  tft.drawRect(10+(40*7)+(10*7),10,40,40,RA8875_WHITE);
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
{    tft.changeMode(TEXT);
   tft.setTextColor(RA8875_WHITE);
  tft.setCursor (300, 0);
  tft.setFontScale(2); 
  tft.print ("Chopp self service");
    tft.changeMode(GRAPHIC);
    
  if (tft.touchDetect()){//easy!
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
        tx=800-tx;ty=480-ty;
      if (ty >= 0 && ty <= 55){ //interface area
        if ((tx > 10 && tx < (10+40))){
          choosenColor = RA8875_WHITE;
          interface();
          tft.fillRect(10,10,40,40,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
                    
          Serial.println("Botao 1 apertado");
          
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (200, 200);
          tft.setFontScale(2); 
          tft.print ("Botao 1 apertado");
          
          delay(2000);

          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (200, 200);
          tft.setFontScale(2); 
          tft.print ("Botao 1 apertado");
          

        } 
        else if ((tx > 10+(40*1)+(10*1) && tx < 10+(40*2)+(10*1))){
          choosenColor = RA8875_BLUE;
          interface();
          tft.fillRect(10+(40*1)+(10*1),10,40,40,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
          
          Serial.println("Botao 2 apertado");
          
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (200, 200);
          tft.setFontScale(2); 
          tft.print ("Botao 2 apertado");

                    delay(2000);

          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (200, 200);
          tft.setFontScale(2); 
          tft.print ("Botao 2 apertado");
        } 
        
      }
  }
}
