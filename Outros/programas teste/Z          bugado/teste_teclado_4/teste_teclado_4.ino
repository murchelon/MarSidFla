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


#include <UTouch.h> 
#include <UTouchCD.h> 
#include <UTFT.h> 
#include <Print.h> 

extern uint8_t SmallFont[];            //Declares Font 
extern uint8_t BigFont[]; 

//UTFT myGLCD(SSD1289,38,39,40,41);    //(Model,RS,WR,CS,RST) 
//UTouch myTouch ( 6, 5, 4, 3, 2); 

//____________________________________________

void drawWelcome_msg(){ 

tft.fillRect (1,1,239,30, RA8875_WHITE); 
tft.fillRect (1,289,239,319, RA8875_WHITE); 
tft.fillRect (19,120,219,179, RA8875_WHITE); 
tft.setTextColor(RA8875_BLACK); 
//tft.print("TECLADO", CENTER, 10); 
//tft.print("SHANE CONCANNON - G00286539", CENTER, 299); 
//tft.print("*************************", CENTER, 120); 
//tft.print("*                       *", CENTER, 130); 
//tft.print("*    SYSTEM UNLOCKED    *", CENTER, 140); 
//tft.print("*   ENTER PIN TO LOCK   *", CENTER, 150); 
//tft.print("*                       *", CENTER, 160); 
//tft.print("*************************", CENTER, 169); 

tft.println("TECLADO"); 
tft.println("SHANE CONCANNON - G00286539"); 
tft.println("*************************"); 
tft.println("*                       *"); 
tft.println("*    SYSTEM UNLOCKED    *"); 
tft.println("*   ENTER PIN TO LOCK   *"); 
tft.println("*                       *"); 
tft.println("*************************"); 

} 


void drawButtons(){ 
 tft.fillScreen(RA8875_BLACK);
 tft.fillRect(1,1,239,30, RA8875_WHITE); 
 tft.fillRect(1,289,239,319, RA8875_WHITE); 
 tft.fillRoundRect(20,40,219,229,10, RA8875_WHITE); 
 tft.fillRoundRect(20,239,219,274,10, RA8875_WHITE); 
 
// tft.print("CAR SECURITY SYSTEM", CENTER, 10); 
// tft.print("SHANE CONCANNON - G00286539", CENTER, 299); 
 tft.println("CAR SECURITY SYSTEM"); 
 tft.println("SHANE CONCANNON - G00286539"); 
 
 tft.drawRoundRect(20,40,219,229,10, RA8875_WHITE); 
 tft.drawRoundRect(20,239,219,274,10, RA8875_YELLOW); 
// tft.print("  ___   ___  ___  ___  ", CENTER, 255); 
 tft.print("  ___   ___  ___  ___  "); 
 tft.drawLine(86,40,86,229, RA8875_RED); 
 tft.drawLine(153,40,153,229, RA8875_RED); 
 tft.drawLine(20,90,219,90, RA8875_WHITE); 
 tft.drawLine(20,140,219,140, RA8875_RED); 
 tft.drawLine(20,190,219,190, RA8875_RED); 
//tft.print("CLEAR", 35, 204); 
// tft.print("ENTER", 167, 204); 
tft.setTextColor(RA8875_BLUE);
 tft.setCursor(120, 120, true);
 tft.print("CLEAR"); 
 tft.print("ENTER"); 
// tft.setFont(BigFont); 
// tft.printNumber(0,112,202); 
// tft.printNumber(1,45,57); 
// tft.printNumber(2,112,57); 
// tft.printNumber(3,178,57); 
// tft.printNumber(4,45,107); 
// tft.printNumber(5,112,107); 
// tft.printNumber(6,178,107); 
// tft.printNumber(7,45,157); 
// tft.printNumber(8,112,157); 
// tft.printNumber(9,178,157);
 tft.println("1"); 
 tft.println("2"); 

}



//___________________________________________________________________________________________



void setup() 
{

  tft.begin(RA8875_800x480);//initialize library
  tft.touchBegin(RA8875_INT);//enable Touch support!

  Serial.begin(9600); 


 //myTouch.InitTouch(0); 
 //myTouch.setPrecision(PREC_HI); 
 //myGLCD.InitLCD(0); 
 //myGLCD.clrScr();                    //clear screen 
 //myGLCD.setFont(SmallFont); 
 //myGLCD.fillScr(VGA_BLACK);          //fill screen with black 
 //myGLCD.setColor(VGA_RED); 
 //myGLCD.setBackColor(VGA_RED); 

 tft.fillScreen(RA8875_BLACK); 

 delay(1000); 

 drawWelcome_msg(); 
 delay(5000); 
 drawButtons(); 
 Serial.println("SYSTEM STARTED");  
}


void loop() 
{   
  
      tft.changeMode(GRAPHIC);
    
  if (tft.touchDetect()){
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
      tx=800-tx;ty=480-ty;

if ((ty>=41) && (ty<=89))    //top row 
        { 
         if ((tx>=21) && (tx<=85))  //button 1 
        Serial.println("1"); 
        } 
        if ((tx>=87) && (tx<=152))  //button 2 
        { 
        Serial.println("2"); 
        } 
        if ((tx>=154) && (tx<=218))  //button 3 
        { 
        Serial.println("3"); 
      } 
} 
        
if ((ty>=91) && (ty<=139))    //middle row 
        { 
        if ((tx>=21) && (tx<=85))  //button 4 
        { 
        Serial.println("4"); 
        } 
         if ((tx>=87) && (tx<=152))  //button 5 
        { 
        Serial.println("5"); 
        } 
        if ((tx>=154) && (tx<=218))  //button 6 
        { 
        Serial.println("6"); 
        } 
} 
if ((ty>=141) && (ty<=189))    //bottom row 
        { 
        if ((tx>=21) && (tx<=85))  //button 7 
        { 
        Serial.println("7"); 
        } 
        if ((tx>=87) && (tx<=152))  //button 8 
        { 
        Serial.println("8"); 
        } 
        if ((tx>=154) && (tx<=218))  //button 9 
        { 
        Serial.println("9"); 
        } 
} 
if ((ty>=191) && (ty<=238))    //bottom row 
        { 
        if ((tx>=21) && (tx<=85))  //clear button 
        { 
        Serial.println("CLEAR"); 
        } 
        if ((tx>=87) && (tx<=152))  //button 0 
        
        { 
        Serial.println("0"); 
        } 
        if ((tx>=154) && (tx<=218))  //enter button 
        { 
        Serial.println("ENTER"); 
} 
} 
} 
