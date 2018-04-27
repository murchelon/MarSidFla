/***************************************************
teclado numerico
****************************************************/


#include <SPI.h>
#include <RA8875.h>

#define RA8875_INT 4
#define RA8875_CS 10 
#define RA8875_RESET 9

RA8875 tft = RA8875(RA8875_CS,RA8875_RESET);

uint16_t tx, ty;

const char Mobile_KB[3][13] PROGMEM = {
  {0, 13, 10, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
  {1, 12, 9, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L'},
  {3, 10, 7, 'Z', 'X', 'C', 'V', 'B', 'N', 'M'},
};

const char Mobile_NumKeys[3][13] PROGMEM = {
  {0, 13, 10, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
  {0, 13, 10, '-', '/', ':', ';', '(', ')', '$', '&', '@', '"'},
  {5, 8, 5, '.', '\,', '?', '!', '\''}
};

const char Mobile_SymKeys[3][13] PROGMEM = {
  {0, 13, 10, '[', ']', '{', '}', '#', '%', '^', '*', '+', '='},
  {4, 9, 6, '_', '\\', '|', '~', '<', '>'}, //4
  {5, 8, 5, '.', '\,', '?', '!', '\''}
};


void GetKeyPress(char * textBuffer)
{
 }


void setup() 
{

  tft.begin(RA8875_800x480);//initialize library
  tft.touchBegin(RA8875_INT);//enable Touch support!

     tft.fillScreen(RA8875_BLUE);
//  tft.setRotation(1);
  MakeKB_Button(Mobile_KB);
}

void MakeKB_Button(const char type[][13])
{
  tft.setFontScale(1);
  tft.setTextColor(0xffff, 0xf000);
  for (int y = 0; y < 3; y++)
  {
    int ShiftRight = 15 * pgm_read_byte(&(type[y][0]));

    for (int x = 3; x < 13; x++)
    {
      if (x >= pgm_read_byte(&(type[y][1]))) break;

    drawButton(15 + (65 * (x - 3)) + ShiftRight, 100 + (75 * y), 60, 70); // this will draw the button on the screen by so many pixels
      //tft.setCursor(30 + (70 * (x - 3)) + ShiftRight, 105 + (75 * y));
      tft.setCursor(15 + (65 * (x - 3)) + ShiftRight + 5,100 + (75 * y)+5);
      tft.print(char(pgm_read_byte(&(type[y][x]))));
    }
  }
  //ShiftKey
  drawButton(15, 250, 40, 70);
  tft.setCursor(20, 255);
  tft.print('^');

  //Special Characters
  drawButton(15, 325, 40, 70);
  tft.setCursor(21, 330);
  tft.print(F("SP"));

  //BackSpace
  drawButton(270, 175, 60, 70);
  tft.setCursor(276, 180);
  tft.print(F("BS"));

  //Return
  drawButton(510, 325, 60, 70);
  tft.setCursor(515, 330);
  tft.print(F("RT"));

  //Spacebar
  drawButton(60, 325, 445, 70);
  tft.setCursor(105, 330);
  tft.print(F("SPACE BAR"));
}

void drawButton(int x, int y, int w, int h)
{

  // grey
  tft.fillRoundRect(x - 3, y + 3, w, h, 3, 0x8888); //Button Shading

  // white
  tft.fillRoundRect(x, y, w, h, 3, 0xffff);// outter button color

  //red
  tft.fillRoundRect(x + 1, y + 1, w - 1 * 2, h - 1 * 2, 3, 0x0000); //inner button color
}


void loop() 
{   
  
    tft.changeMode(GRAPHIC);

     while (tft.touched())  {
      tft.touchReadPixel(&tx, &ty);
      delay(1);
      tft.print(tx); 
      tft.print(", "); 
      tft.println(ty);      
    }

    
//    if (tft.touchDetect()){
//      delay(2000);
//      tft.println("");
//      // tft.print("Touch: "); 
//      tft.touchReadPixel(&tx, &ty);  //Read the x and y value of touched area
////      tft.print(tx); 
////      tft.print(", "); 
////      tft.println(ty);
//for (int y = 0; y < 3; y++)
//  {
//    //drawButton(15 + (65 * (x - 3)) + ShiftRight, 100 + (75 * y), 60, 70); 
//    int ShiftRight = 15 ;
//     for (int x = 3; x < 13; x++)
//     {
//      
//       int xx = 15 + (65 * (x - 3)) + ShiftRight;
//       int yy = 100 + (75 * y);
//       tft.println("--------------------------");
//       tft.println("Tx: " + String(tx));
//       tft.println("xx: " + String(xx));
//       tft.println("yy: " + String(yy));
//       tft.println(constrain(tx,yy,xx));
//       tft.println("-----------");
//       if(constrain(tx,xx,yy))
//       {
//        tft.println("aaaaaaaaaaaaaaaaaaa");
//        }
//      }
//    }
//      
//  }
}
