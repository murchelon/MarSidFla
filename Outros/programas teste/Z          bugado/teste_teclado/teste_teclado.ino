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
uint16_t newX, newY;

int bot_size = 60;
int bot_offset = 20;
int bot_corner = 10;

int board_corner = 20;

int num = ("");
int num1 = 1;
int num2 = 2;
int num3 = 3;
int num4 = 4;
int num5 = 5;
int num6 = 6;
int num7 = 7;
int num8 = 8;
int num9 = 9;
int num0 = 0;

String valor;

void numerico(){

tft.fillRoundRect(500, 50, 260,340,board_corner,RA8875_WHITE);

  // botoes _____________________________________________________________
  
  tft.fillRoundRect(500 + bot_offset,50 + bot_offset,bot_size,bot_size,bot_corner,RA8875_BLUE);
  tft.fillRoundRect(500+(bot_offset*2)+(bot_size*1),50 + (bot_offset * 1),bot_size,bot_size,bot_corner,RA8875_BLUE); //y = 1 primeira fileira de botoes
  tft.fillRoundRect(500+(bot_offset*3)+(bot_size*2),50 + (bot_offset * 1),bot_size,bot_size,bot_corner,RA8875_BLUE); //y = 1 primeira fileira de botoes

  tft.fillRoundRect(500+(bot_offset*1)+(bot_size*0),50 + (bot_offset * 2)+(bot_size*1),bot_size,bot_size,bot_corner,RA8875_BLUE); //y =  *2 segunda fileira de botoes
  tft.fillRoundRect(500+(bot_offset*2)+(bot_size*1),50 + (bot_offset * 2)+(bot_size*1),bot_size,bot_size,bot_corner,RA8875_BLUE); //y =  *2 segunda fileira de botoes
  tft.fillRoundRect(500+(bot_offset*3)+(bot_size*2),50 + (bot_offset * 2)+(bot_size*1),bot_size,bot_size,bot_corner,RA8875_BLUE); //y =  *2 segunda fileira de botoes
  
  tft.fillRoundRect(500+(bot_offset*1)+(bot_size*0),50 + (bot_offset * 3)+(bot_size*2),bot_size,bot_size,bot_corner,RA8875_BLUE); //y =  *3 terceira fileira de botoes
  tft.fillRoundRect(500+(bot_offset*2)+(bot_size*1),50 + (bot_offset * 3)+(bot_size*2),bot_size,bot_size,bot_corner,RA8875_BLUE); //y =  *3 terceira fileira de botoes
  tft.fillRoundRect(500+(bot_offset*3)+(bot_size*2),50 + (bot_offset * 3)+(bot_size*2),bot_size,bot_size,bot_corner,RA8875_BLUE); //y =  *3 terceira fileira de botoes

  tft.fillRoundRect(500+(bot_offset*1)+(bot_size*0),50 + (bot_offset * 4)+(bot_size*3),bot_size,bot_size,bot_corner,RA8875_BLUE); //y =  *4 quarta fileira de botoes
  tft.fillRoundRect(500+(bot_offset*2)+(bot_size*1),50 + (bot_offset * 4)+(bot_size*3),bot_size,bot_size,bot_corner,RA8875_BLUE); //y =  *4 quarta fileira de botoes
  tft.fillRoundRect(500+(bot_offset*3)+(bot_size*2),50 + (bot_offset * 4)+(bot_size*3),bot_size,bot_size,bot_corner,RA8875_BLUE); //y =  *4 quarta fileira de botoes
  
 // numero botoes _____________________________________________________________

    tft.setTextColor(RA8875_WHITE);
    tft.setFontScale(2); 

  tft.setCursor((500 + bot_offset)+20,(50 + bot_offset));
  tft.print ("1");
  tft.setCursor((500+(bot_offset*2)+(bot_size*1))+20,50 + (bot_offset * 1));
  tft.print ("2");
  tft.setCursor(500+(bot_offset*3)+(bot_size*2)+20,50 + (bot_offset * 1));
  tft.print ("3");

  tft.setCursor(500+(bot_offset*1)+(bot_size*0)+20,50 + (bot_offset * 2)+(bot_size*1)); 
  tft.print ("4");
  tft.setCursor(500+(bot_offset*2)+(bot_size*1)+20,50 + (bot_offset * 2)+(bot_size*1));
  tft.print ("5"); 
  tft.setCursor(500+(bot_offset*3)+(bot_size*2)+20,50 + (bot_offset * 2)+(bot_size*1)); 
  tft.print ("6");
  
  tft.setCursor(500+(bot_offset*1)+(bot_size*0)+20,50 + (bot_offset * 3)+(bot_size*2)); 
  tft.print ("7");
  tft.setCursor(500+(bot_offset*2)+(bot_size*1)+20,50 + (bot_offset * 3)+(bot_size*2)); 
  tft.print ("8");
  tft.setCursor(500+(bot_offset*3)+(bot_size*2)+20,50 + (bot_offset * 3)+(bot_size*2)); 
  tft.print ("9");

  tft.setCursor(500+(bot_offset*1)+(bot_size*0)+20-15,50 + (bot_offset * 4)+(bot_size*3)); 
  tft.print ("OK");
  tft.setCursor(500+(bot_offset*2)+(bot_size*1)+20,50 + (bot_offset * 4)+(bot_size*3)); 
  tft.print ("0");
  tft.setCursor(500+(bot_offset*3)+(bot_size*2)+20-15,50 + (bot_offset * 4)+(bot_size*3)); 
  tft.print ("BK");

  
 // tft.setCursor(500+(bot_offset*2)+(bot_size*0) + 30,50 + (bot_offset * 4)+(bot_size*3)); 
 // tft.print ("0");
 // tft.setCursor(500+(bot_offset*4)+(bot_size*1)+20 ,50 + (bot_offset * 4)+(bot_size*3)); 
 // tft.print ("OK");

}

void setup() 
{

  tft.begin(RA8875_800x480);//initialize library
  tft.touchBegin(RA8875_INT);//enable Touch support!

    tft.setTextColor(RA8875_RED);
    tft.setFontScale(2); 
    tft.setCursor (80, 20); 
    tft.print ("DIGITE O VALOR:");

    tft.fillRect(80,80,300,60, RA8875_YELLOW);

  valor = String();
  
  numerico();
  newX = 85;
}


void loop() 
{   
  
      tft.changeMode(GRAPHIC);
    
  if (tft.touchDetect()){
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
      tx=800-tx;ty=480-ty;


      if (ty >= 50 + bot_offset && ty <= 50 + (bot_offset * 1) + (bot_size * 1) && (tx > 500 + bot_offset && tx < 500 + bot_offset + bot_size) ) //interface area
           
        {
                
                tft.touchDetect(false);
                tft.fillRoundRect(500 + bot_offset,50 + bot_offset,bot_size,bot_size,bot_corner,RA8875_WHITE);
                delay(200);
      
                numerico();
       
                    tft.setTextColor(RA8875_BLACK);
                      tft.setCursor (newX, 80); 
                      tft.print ("1");
                      tft.getCursor(newX,80);
                      newX = newX + 20;
                      //num = num && num1;
                      valor = valor + 7;
                      
                      tft.setTextColor(RA8875_BLACK,RA8875_BLUE);
                      tft.setCursor (newX, 150); 
                      tft.print (valor);
                                    
        }

      if (ty >= 50 + (bot_offset * 1) && ty <= 50 + (bot_offset * 1) + (bot_size * 1) && (tx > 500+(bot_offset*2)+(bot_size*1) && tx < 500+(bot_offset*2)+(bot_size*1) + bot_size) ) //interface area
           
        {
                
                tft.touchDetect(false);
                tft.fillRoundRect(500+(bot_offset*2)+(bot_size*1),50 + (bot_offset * 1),bot_size,bot_size,bot_corner,RA8875_WHITE);
                delay(200);
                
                numerico();
                
                      tft.setTextColor(RA8875_BLACK);
                      tft.setCursor (newX, 80); 
                      tft.print ("2");
                      tft.getCursor(newX,80);
                      newX = newX + 20;
                      num = num && num2;
                                    
        }

        
              if (ty >= 50 + (bot_offset * 1) && ty <= 50 + (bot_offset * 1) + (bot_size * 1) && (tx > 500+(bot_offset*2)+(bot_size*1) + bot_size && tx < 500+(bot_offset*2)+(bot_size*2) + bot_size) ) //interface area
                  
        {
                
                tft.touchDetect(false);
                tft.fillRoundRect(500+(bot_offset*3)+(bot_size*2),50 + (bot_offset * 1),bot_size,bot_size,bot_corner,RA8875_WHITE);
                delay(200);
                
                numerico();
                
                      tft.setTextColor(RA8875_BLACK);
                      tft.setCursor (newX, 80); 
                      tft.print ("3");
                      tft.getCursor(newX,80);
                      newX = newX + 20;
                      num = num && num3;
                                    
        }
              if (ty >= 50 + (bot_offset * 2)+ (bot_size * 1) && ty <= 50 + (bot_offset * 2) + (bot_size * 2) && (tx > 500 + bot_offset && tx < 500 + bot_offset + bot_size) )
                                                                                                                
        {
                
                tft.touchDetect(false);
                tft.fillRoundRect(500+(bot_offset*1)+(bot_size*0),50 + (bot_offset * 2)+(bot_size*1),bot_size,bot_size,bot_corner,RA8875_WHITE);
                delay(200);
                
                numerico();
                
                      tft.setTextColor(RA8875_BLACK);
                      tft.setCursor (newX, 80); 
                      tft.print ("4");
                      tft.getCursor(newX,80);
                      newX = newX + 20;
                      num = num && num4;
                                    
        }

 if (ty >= 50 + (bot_offset * 2)+ (bot_size * 1) && ty <= 50 + (bot_offset * 2) + (bot_size * 2) && (tx > 500 + bot_offset *2 + bot_size && tx < 500 + bot_offset * 2 + bot_size * 2) )
                                                                                                                
        {
                
                tft.touchDetect(false);
                tft.fillRoundRect(500+(bot_offset*2)+(bot_size*1),50 + (bot_offset * 2)+(bot_size*1),bot_size,bot_size,bot_corner,RA8875_WHITE);
                delay(200);
                
                numerico();
                
                      tft.setTextColor(RA8875_BLACK);
                      tft.setCursor (newX, 80); 
                      tft.print ("5");
                      tft.getCursor(newX,80);
                      newX = newX + 20;
                      num = num && num5;
                                    
        }
 if (ty >= 50 + (bot_offset * 2)+ (bot_size * 1) && ty <= 50 + (bot_offset * 2) + (bot_size * 2) && (tx > 500 + bot_offset *3 + bot_size * 2 && tx < 500 + bot_offset * 3 + bot_size * 3) )
                                                                                                                
        {
                
                tft.touchDetect(false);
                tft.fillRoundRect(500+(bot_offset*3)+(bot_size*2),50 + (bot_offset * 2)+(bot_size*1),bot_size,bot_size,bot_corner,RA8875_WHITE);
                delay(200);
                
                numerico();
                
                      tft.setTextColor(RA8875_BLACK);
                      tft.setCursor (newX, 80); 
                      tft.print ("6");
                      tft.getCursor(newX,80);
                      newX = newX + 20;
                      num = num && num6;
                                    
        }

//____________________________________________

              if (ty >= 50 + (bot_offset * 3)+ (bot_size * 2) && ty <= 50 + (bot_offset * 3) + (bot_size * 3) && (tx > 500 + bot_offset && tx < 500 + bot_offset + bot_size) )
                                                                                                                
        {
                
                tft.touchDetect(false);
                tft.fillRoundRect(500+(bot_offset*1)+(bot_size*0),50 + (bot_offset * 3)+(bot_size*2),bot_size,bot_size,bot_corner,RA8875_WHITE);
                delay(200);
                
                numerico();
                
                      tft.setTextColor(RA8875_BLACK);
                      tft.setCursor (newX, 80); 
                      tft.print ("7");
                      tft.getCursor(newX,80);
                      newX = newX + 20;
                      num = num && num7;
                                    
        }

 if (ty >= 50 + (bot_offset * 3)+ (bot_size * 2) && ty <= 50 + (bot_offset * 3) + (bot_size * 3) && (tx > 500 + bot_offset *2 + bot_size && tx < 500 + bot_offset * 3 + bot_size * 2) )
                                                                                                                
        {
                
                tft.touchDetect(false);
                tft.fillRoundRect(500+(bot_offset*2)+(bot_size*1),50 + (bot_offset * 3)+(bot_size*2),bot_size,bot_size,bot_corner,RA8875_WHITE);
                delay(200);
                
                numerico();
                
                      tft.setTextColor(RA8875_BLACK);
                      tft.setCursor (newX, 80); 
                      tft.print ("8");
                      tft.getCursor(newX,80);
                      newX = newX + 20;
                      num = num && num8;
                                    
        }
        
 if (ty >= 50 + (bot_offset * 3)+ (bot_size * 2) && ty <= 50 + (bot_offset * 3) + (bot_size * 3) && (tx > 500 + bot_offset *3 + bot_size * 2 && tx < 500 + bot_offset * 3 + bot_size * 3) )
                                                                                                                
        {
                
                tft.touchDetect(false);
                tft.fillRoundRect(500+(bot_offset*3)+(bot_size*2),50 + (bot_offset * 3)+(bot_size*2),bot_size,bot_size,bot_corner,RA8875_WHITE);
                delay(200);
                
                numerico();
                
                      tft.setTextColor(RA8875_BLACK);
                      tft.setCursor (newX, 80); 
                      tft.print ("9");
                      tft.getCursor(newX,80);
                      newX = newX + 20;
                      num = num && num9;
                                    
        }

//____________________________________________

              if (ty >= 50 + (bot_offset * 4)+ (bot_size * 3) && ty <= 50 + (bot_offset * 4) + (bot_size * 4) && (tx > 500 + bot_offset && tx < 500 + bot_offset + bot_size) )
                                                                                                                
        {
                
                tft.touchDetect(false);
                tft.fillRoundRect(500+(bot_offset*1)+(bot_size*0),50 + (bot_offset * 4)+(bot_size*3),bot_size,bot_size,bot_corner,RA8875_WHITE);
                delay(200);
                
                numerico();
                
                      tft.setTextColor(RA8875_BLACK);
                      tft.setCursor (newX, 80); 
                      tft.print ("OK");
                      tft.getCursor(newX,80);
                      newX = newX + 20;

                      tft.setTextColor(RA8875_YELLOW);
                      tft.setCursor (85, 150); 
                      tft.print (num);

        }

 if (ty >= 50 + (bot_offset * 4)+ (bot_size * 3) && ty <= 50 + (bot_offset * 4) + (bot_size * 4) && (tx > 500 + bot_offset *2 + bot_size && tx < 500 + bot_offset * 3 + bot_size * 2) )
                                                                                                                
        {
                
                tft.touchDetect(false);
                tft.fillRoundRect(500+(bot_offset*2)+(bot_size*1),50 + (bot_offset * 4)+(bot_size*3),bot_size,bot_size,bot_corner,RA8875_WHITE);
                delay(200);
                
                numerico();
                
                      tft.setTextColor(RA8875_BLACK);
                      tft.setCursor (newX, 80); 
                      tft.print ("0");
                      tft.getCursor(newX,80);
                      newX = newX + 20;
                      num = num && num0;
                                    
        }
        
 if (ty >= 50 + (bot_offset * 4)+ (bot_size * 3) && ty <= 50 + (bot_offset * 4) + (bot_size * 4) && (tx > 500 + bot_offset *3 + bot_size * 2 && tx < 500 + bot_offset * 3 + bot_size * 3) )
                                                                                                                
        {
                
                tft.touchDetect(false);
                tft.fillRoundRect(500+(bot_offset*3)+(bot_size*2),50 + (bot_offset * 4)+(bot_size*3),bot_size,bot_size,bot_corner,RA8875_WHITE);
                delay(200);
                
                numerico();
                
                      tft.setTextColor(RA8875_BLACK);
                      tft.setCursor (newX, 80); 
                      tft.print ("BK");
                      tft.getCursor(newX,80);
                      newX = newX + 20;


                      tft.setTextColor(RA8875_YELLOW);
                      tft.setCursor (85, 180); 
                      tft.print (" nao sei fazer back space");

                               
        
        
        }
  }
}
