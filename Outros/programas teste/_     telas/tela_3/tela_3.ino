/***************************************************
Tela 3 - login nao completado
****************************************************/


#include <SPI.h>
#include <RA8875.h>

#define RA8875_INT 4
#define RA8875_CS 10 

#define RA8875_RESET 9


RA8875 tft = RA8875(RA8875_CS,RA8875_RESET);


uint16_t tx, ty;

int m = 60;


void interface()

{
  
        tft.fillCircle(60,60,50,RA8875_WHITE);
 
        tft.changeMode(TEXT);
        tft.setTextColor(RA8875_BLACK);
        tft.setCursor (10, 25);
        tft.setFontScale(6); 
        tft.print (" 1 ");
                 

          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (200, 25);
          tft.setFontScale(1); 
          tft.print ("Chopp A");// puxa do banco de dados
          tft.setCursor (200, 55);
          tft.print ("R$ 10,00 / L");// puxa do banco de dados
}

void interface3()

{

              tft.setTextColor(RA8875_WHITE);
              tft.setFontScale(2); 
              tft.setCursor (90, 160);
              tft.print ("Ola ");
              tft.setTextColor(RA8875_RED);
              tft.setCursor (190, 160);
              tft.print ("Voce ainda nao esta ");
              tft.setCursor (80, 220);
              tft.print ("cadastrado no nosso sistema !");
              tft.setTextColor(RA8875_WHITE);
              tft.setCursor (70, 330);
              tft.print ("Favor se informar no caixa.");


                    tft.setTextColor(RA8875_WHITE);
                    tft.setFontScale(2); 
                    tft.setCursor (600, 430);
                    tft.println ("Obrigado");
                    
          
}




void setup() 
{

  tft.begin(RA8875_800x480);//initialize library

  tft.touchBegin(RA8875_INT);//enable Touch support!
//  interface();

      interface();

      interface3();

}

uint16_t choosenColor = 0;


void loop() 

{    

              

       
        
      
 
}

