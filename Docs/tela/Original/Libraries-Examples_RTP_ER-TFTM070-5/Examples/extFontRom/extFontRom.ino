/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-TFTM070-5 
Hardware SPI,4-Wire SPI Interface,5V Power Supply

An example of how use an external ROM chip with RA8875, this time
the ER3303_1 (same as GT23L24T3Y or GT30H24T3Y), an unified chinese
font rom. 
In short:

1) use setExternalFontRom to set ROM and it's correct encoding
2) use setFont(EXT) to use the external font
3) to switch back to internal font ROM, use setFont(INT)

Library can handle the following Font ROM:
ER3300-1,ER3301-1,ER3303-1,ER3304-1
Each font ROM has it's encoding so follow font rom datasheet!

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

void setup() 
{
  Serial.begin(9600);
  //while (!Serial) {;}
  Serial.println("RA8875 start");
  tft.begin(RA8875_800x480);

  tft.changeMode(TEXT);
  tft.setTextColor(RA8875_WHITE);
  //now set the external rom font ER3303_1 an unified chinese font chip,
  //it contains also some ASCII char and use GB12345 encoding. 
  //It's important to read your font chip datasheet or you will 
  //get from nothing ti garbage on screen!
  tft.setExternalFontRom(ER3303_1,GB12345);
  //switch to external rom
  tft.setFont(EXT);
  //now write some chinese....
  //note that when using ext font chip the size will be X24
  //since most of font maps are 24x24.
  tft.print("ÉîÛÚÐñÈÕ¶«·½¿Æ¼¼ÓÐÏÞ¹«Ë¾"); //
  //the X16 sixe of ROM ER3303_1 can also use ASCII...
  tft.setFontSize(X16);//switch to X16
  tft.setTextColor(RA8875_RED);
  tft.setCursor(0,50);
  tft.println("ABCD 1234567890"); //I will use println this time!
  //switch to internal rom 
  tft.setFont(INT);
  tft.setTextColor(RA8875_GREEN);
  tft.println("www.buydisplay.com"); 
  //not bad neh? you can use different encodings without use
  //any MCU memory, just add an hardware font chip and istruct library.
  tft.setFont(EXT);
  //you can switching back on the fly to EXT
  tft.print("ÉîÛÚÐñÈÕ¶«·½¿Æ¼¼ÓÐÏÞ¹«Ë¾");
  //voilà
}

void loop() 
{
}
