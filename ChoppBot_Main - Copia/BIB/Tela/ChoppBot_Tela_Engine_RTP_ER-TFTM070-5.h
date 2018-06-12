/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-TFTM070-5 A
Hardware SPI,4-Wire SPI Interface,5V Power Supply

Basic Text Functions
Tested and worked with:
Teensy3,Teensy3.1,Arduino UNO,Arduino YUN,Arduino Leonardo,Stellaris
Works with Arduino 1.6.0 IDE 
****************************************************/



//Arduino DUE,Arduino mega2560,Arduino UNO
#define RA8875_INT TELA_PINO_INT
#define RA8875_CS TELA_PINO_CS

#define RA8875_RESET TELA_PINO_RESET



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



//#endif



RA8875 tft = RA8875(RA8875_CS,RA8875_RESET);

//Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);

