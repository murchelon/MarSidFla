/***************************************************
Tela 6 - Recarga
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

void interface()

{

  tft.fillRect(b_xoffset,b_yoffset,b_wide,b_high,RA8875_WHITE);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (b_xoffset + 30,b_yoffset + 40);
          tft.setFontScale(1); 
 
          tft.print (" Digital ");

  
  tft.fillRect((b_xoffset * 2) + b_wide, b_yoffset,b_wide,b_high,RA8875_BLUE);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor ((b_xoffset * 2) + b_wide + 30, b_yoffset + 40);
          tft.setFontScale(1); 

          tft.print (" Cartao ");
          

   tft.fillRect(600,400,b_wide/1.5,b_high/2 ,RA8875_GREEN);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (600 + 2, 400 + 10);
          tft.setFontScale(1); 
          tft.print (" Salvar ");
          
}

void interface2()

{

              tft.setTextColor(RA8875_WHITE);
              tft.setFontScale(1); 
              tft.setCursor (20, 200);
              tft.print ("Usuario: ");
              tft.setTextColor(RA8875_RED);
              tft.setCursor (460, 200);
              tft.print ("XXXXXXXXXXXXX");
              tft.setTextColor(RA8875_WHITE);
              tft.setCursor (20, 250);
              tft.print ("Saldo:");
              tft.setTextColor(RA8875_RED);
              tft.setCursor (460, 250);
              tft.print ("R$  ");  tft.print ("1000,00");

              tft.setTextColor(RA8875_WHITE);
              tft.setCursor (20, 300);
              tft.print ("Valor a ser adicionado:");
              tft.setTextColor(RA8875_RED);
              tft.setCursor (460, 300);
              tft.print ("R$  ");  tft.print ("520,00");

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
  tft.print ("Recarga:");

  
    tft.changeMode(GRAPHIC);

    
  if (tft.touchDetect()){
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
        tx=800-tx;ty=480-ty;

      if (ty >= b_yoffset && ty <= b_yoffset + b_high && (tx > b_xoffset && tx < b_wide + b_xoffset) ) //interface area
      
      { 

          interface();
          
          tft.fillRect(b_xoffset,b_yoffset,b_wide,b_high,RA8875_BLACK);

          tft.fillRect((b_xoffset * 2) + b_wide, b_yoffset, b_wide, b_high,RA8875_BLACK);

             delay(500);
          tft.touchDetect(false);

               interface2();

          delay(500);
          tft.touchDetect(false);

        } 
        
        else if ((ty >= b_yoffset && ty <= b_yoffset + b_high &&(tx > (b_xoffset * 2) + b_wide && (tx < +(b_xoffset * 2) + (b_wide * 2)))))  
        
        {
          
          interface();
          
          tft.fillRect((b_xoffset * 2) + b_wide, b_yoffset, b_wide, b_high,RA8875_BLACK);
           
          tft.fillRect(b_xoffset,b_yoffset,b_wide,b_high,RA8875_BLACK);

               interface2();

          delay(500);
          tft.touchDetect(false);
 
          } 

       else if ((ty >= 400 && ty <= (400 + (b_high/2)) && (tx > (600) && (tx < (600) + b_wide/1.5))))  
    {
          
          tft.fillRect(600,400,b_wide/1.5,b_high/2,RA8875_BLACK);

          delay(200);
          tft.fillScreen(RA8875_BLACK); 
          tft.fillRect(600,400,b_wide/1.5,b_high/2,RA8875_GREEN);  

                   
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (600 + 2, 400 + 10);
          tft.setFontScale(1); 
          tft.print (" Salvar ");


                    tft.setTextColor(RA8875_WHITE);
                    tft.setCursor (30, 410);
                    tft.setFontScale(1); 
                    tft.println ("Cadastro realizado com sucesso.");


          delay(500);
          tft.touchDetect(false);
          
        }
      }   
   }

