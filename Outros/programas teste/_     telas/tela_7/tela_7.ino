/***************************************************
Tela 7 - manutenção
****************************************************/


#include <SPI.h>
#include <RA8875.h>

#define RA8875_INT 4
#define RA8875_CS 10 

#define RA8875_RESET 9


RA8875 tft = RA8875(RA8875_CS,RA8875_RESET);


uint16_t tx, ty;
int m = -40;

void interface(){
  tft.fillRect(400,120 + m,80,80,RA8875_WHITE);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (390, 130 + m);
          tft.setFontScale(6); 
          tft.print (" 1 ");

  
tft.fillRect(400+(40*1)+(80*1),120 + m,80,80,RA8875_BLUE); 
      tft.changeMode(TEXT);
      tft.setTextColor(RA8875_BLACK);
      tft.setCursor (510, 130 + m);
      tft.setFontScale(6); 
      tft.print (" 2 ");
  
tft.fillRect(400+(40*2)+(80*2),120 + m,80,80,RA8875_GREEN);
      tft.changeMode(TEXT);
      tft.setTextColor(RA8875_BLACK);
      tft.setCursor (630, 130 + m);
      tft.setFontScale(6); 
      tft.print (" 3 ");
  
                             
tft.fillRect(600,400,200/1.5,120/2 ,RA8875_MAGENTA);
      tft.changeMode(TEXT);
      tft.setTextColor(RA8875_BLACK);
      tft.setCursor (600 + 2, 400 + 10);
      tft.setFontScale(1); 
      tft.print (" Salvar ");


tft.fillRect(400+(40*0)+(80*0),0,80,60,RA8875_RED);           //botão reset 1
    tft.changeMode(TEXT);
    tft.setTextColor(RA8875_WHITE);
    tft.setCursor (420, 20);
    tft.setFontScale(.8); 
    tft.print ("Reset");
                  
tft.fillRect(400+(40*1)+(80*1),0,80,60,RA8875_RED);           //botão reset 2
  tft.changeMode(TEXT);
  tft.setTextColor(RA8875_WHITE);
  tft.setCursor (540, 20);
  tft.setFontScale(.8); 
  tft.print ("Reset");

tft.fillRect(400+(40*2)+(80*2),0,80,60,RA8875_RED);           //botão reset 3
  tft.changeMode(TEXT);
  tft.setTextColor(RA8875_WHITE);
  tft.setCursor (660, 20);
  tft.setFontScale(.8); 
  tft.print ("Reset");        


  tft.changeMode(TEXT);
  tft.setTextColor(RA8875_WHITE);
  tft.setCursor (80, 0);
  tft.setFontScale(2); 
  tft.print ("Manutencao :");


  tft.setTextColor(RA8875_WHITE);
  tft.setCursor (80, 180);
  tft.setFontScale(1); 
  tft.print ("Nome do Chopp :");

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (410, 180);
          tft.setFontScale(.9); 
          tft.print ("Chopp A");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (530, 180);
          tft.setFontScale(.9); 
          tft.print ("Chopp B");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (650, 180);
          tft.setFontScale(.9); 
          tft.print ("Chopp C");// puxa do banco de dados          
  
  tft.setTextColor(RA8875_WHITE);
  tft.setCursor (80, 220);
  tft.setFontScale(1); 
  tft.print ("Preco :");
            tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (410, 220);
          tft.setFontScale(.9); 
          tft.print ("R$ 10,00");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (530, 220);
          tft.setFontScale(.9); 
          tft.print ("R$ 20,00");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (650, 220);
          tft.setFontScale(.9); 
          tft.print ("R$ 30,00");// puxa do banco de dados          

tft.setTextColor(RA8875_WHITE);
  tft.setCursor (80, 260);
  tft.setFontScale(1); 
  tft.print ("Volume Atual :");
            tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (410, 260);
          tft.setFontScale(.9); 
          tft.print ("26l");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (530, 260);
          tft.setFontScale(.9); 
          tft.print ("17l");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (650, 260);
          tft.setFontScale(.9); 
          tft.print ("24l");// puxa do banco de dados              
tft.setTextColor(RA8875_WHITE);
  tft.setCursor (80, 300);
  tft.setFontScale(1); 
  tft.print ("Carga (volume) :");
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (410, 300);
          tft.setFontScale(.9); 
          tft.print ("30l");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (530, 300);
          tft.setFontScale(.9); 
          tft.print ("20l");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (650, 300);
          tft.setFontScale(.9); 
          tft.print ("30l");// puxa do banco de dados                

tft.setTextColor(RA8875_WHITE);
  tft.setCursor (80, 340);
  tft.setFontScale(1); 
  tft.print ("Data da carga :");    
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (410, 340);
          tft.setFontScale(.9); 
          tft.print ("01/04");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (530, 340);
          tft.setFontScale(.9); 
          tft.print ("04/04");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (650, 340);
          tft.setFontScale(.9); 
          tft.print ("06/04");// puxa do banco de dados                

  
    tft.changeMode(GRAPHIC);



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
  tft.setCursor (80, 0);
  tft.setFontScale(2); 
  tft.print ("Manutencao :");


  tft.setTextColor(RA8875_WHITE);
  tft.setCursor (80, 180);
  tft.setFontScale(1); 
  tft.print ("Nome do Chopp :");

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (410, 180);
          tft.setFontScale(.9); 
          tft.print ("Chopp A");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (530, 180);
          tft.setFontScale(.9); 
          tft.print ("Chopp B");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (650, 180);
          tft.setFontScale(.9); 
          tft.print ("Chopp C");// puxa do banco de dados          
  
  tft.setTextColor(RA8875_WHITE);
  tft.setCursor (80, 220);
  tft.setFontScale(1); 
  tft.print ("Preco :");
            tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (410, 220);
          tft.setFontScale(.9); 
          tft.print ("R$ 10,00");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (530, 220);
          tft.setFontScale(.9); 
          tft.print ("R$ 20,00");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (650, 220);
          tft.setFontScale(.9); 
          tft.print ("R$ 30,00");// puxa do banco de dados          

tft.setTextColor(RA8875_WHITE);
  tft.setCursor (80, 260);
  tft.setFontScale(1); 
  tft.print ("Volume Atual :");
            tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (410, 260);
          tft.setFontScale(.9); 
          tft.print ("26l");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (530, 260);
          tft.setFontScale(.9); 
          tft.print ("17l");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (650, 260);
          tft.setFontScale(.9); 
          tft.print ("24l");// puxa do banco de dados              
tft.setTextColor(RA8875_WHITE);
  tft.setCursor (80, 300);
  tft.setFontScale(1); 
  tft.print ("Carga (volume) :");
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (410, 300);
          tft.setFontScale(.9); 
          tft.print ("30l");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (530, 300);
          tft.setFontScale(.9); 
          tft.print ("20l");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (650, 300);
          tft.setFontScale(.9); 
          tft.print ("30l");// puxa do banco de dados                

tft.setTextColor(RA8875_WHITE);
  tft.setCursor (80, 340);
  tft.setFontScale(1); 
  tft.print ("Data da carga :");    
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (410, 340);
          tft.setFontScale(.9); 
          tft.print ("01/04");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (530, 340);
          tft.setFontScale(.9); 
          tft.print ("04/04");// puxa do banco de dados

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (650, 340);
          tft.setFontScale(.9); 
          tft.print ("06/04");// puxa do banco de dados                

  
    tft.changeMode(GRAPHIC);

    
  if (tft.touchDetect()){//easy!
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
        tx=800-tx;ty=480-ty;
      if (ty >= 80 + m && ty <= 80 + 160 + m){ //interface area
        if ((tx > 80 && tx < (80+160))){
          choosenColor = RA8875_WHITE;
          interface();
          tft.fillRect(80,80 + m,160,160,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);

          delay(200);
          tft.fillRect(80,80 + m,160,160,RA8875_WHITE);          
          
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (110, 130 + m);
          tft.setFontScale(6); 
          tft.print (" 1 ");

          delay(500);
          tft.touchDetect(false);


        } 
        else if ((tx > 80+(160*1)+(80*1) && tx < 80+(160*2)+(80*1))){
          choosenColor = RA8875_BLUE;
          interface();
          tft.fillRect(80+(160*1)+(80*1),80 + m,160,160,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);

          delay(200);
          tft.fillRect(80+(160*1)+(80*1),80 + m,160,160,RA8875_BLUE);  

                   
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (350, 130 + m);
          tft.setFontScale(6); 
          tft.print (" 2 ");

          delay(500);
          tft.touchDetect(false);
 
          } 

        else if ((tx > 80+(160*2)+(80*2) && tx < 80+(160*3)+(80*2))){
          choosenColor = RA8875_GREEN;
          interface();
          tft.fillRect(80+(160*2)+(80*2),80 + m,160,160,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);

          delay(200);
          tft.fillRect(80+(160*2)+(80*2),80 + m,160,160,RA8875_GREEN);  

                   
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (590, 130 + m);
          tft.setFontScale(6); 
          tft.print (" 3 ");

          delay(500);
          tft.touchDetect(false);
          
        }
       
        
      }
  }
}
