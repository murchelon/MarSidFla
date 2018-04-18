/***************************************************
Tela 2 - login OK
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

void interface2()

{

              tft.setTextColor(RA8875_WHITE);
              tft.setFontScale(2); 
              tft.setCursor (90, 200);
              tft.print ("Ola ");
              tft.setTextColor(RA8875_RED);
              tft.setCursor (190, 200);
              tft.print ("Murch");
              tft.setTextColor(RA8875_WHITE);
              tft.setCursor (90, 250);
              tft.print ("Seu saldo atual e :");
              tft.setTextColor(RA8875_RED);
              tft.setCursor (560, 250);
              tft.print ("R$ 860,00");


                    tft.setTextColor(RA8875_WHITE);
                    tft.setFontScale(1); 
                    tft.setCursor (90, 370);
                    tft.println ("Torneira liberada !  Pode se server !");
                    tft.setCursor (30, 410);
                    tft.setFontScale(1); 
                    tft.println ("Seu saldo ser atualizado conforme voce consome.");
                    
          
}

void login()
{

          tft.setTextColor(RA8875_MAGENTA);
          tft.setFontScale(1); 
          tft.setCursor (50, 195);
          tft.print ("Aproxime seu cartao do leitor RFID ou");
          tft.setCursor (50, 235);
          tft.print ("coloque seu dedo no leitor biometrico.");
          
              tft.setTextColor(RA8875_MAGENTA);
              tft.setFontScale(2); 
              tft.setCursor (540, 65);
              tft.print("contador");  
}


void setup() 
{

  tft.begin(RA8875_800x480);//initialize library

  tft.touchBegin(RA8875_INT);//enable Touch support!
//  interface();

      interface();

      login();

}

uint16_t choosenColor = 0;


void loop() 

{    

              
    tft.changeMode(GRAPHIC);
    
  if (tft.touchDetect()){//easy!
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
        tx=800-tx;ty=480-ty;
      if (ty >= 0 && ty <= 480){ //interface area
       
          tft.fillScreen(RA8875_BLACK);          

            delay(500);
          tft.touchDetect(false);
          
               interface();
               interface2();
       
        
      }
  }
}

