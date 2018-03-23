// botao + marca volume

// tela __________________________________________________

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

// botão ________________________________________

int contador1; //Contador para saida 1
int contador2; //Contador para saida 2
int contador3; //Contador para saida 3

// rele ________________________________________

int gPinoRele_1 = 45;
int gPinoRele_2 = 46;
int gPinoRele_3 = 47;

// flowmeter________________________________________

#define FLOWSENSORPIN_1 36
#define FLOWSENSORPIN_2 37
#define FLOWSENSORPIN_3 38

// count how many pulses!
volatile uint16_t pulses = 0;
// track the state of the pulse pin
volatile uint8_t lastflowpinstate;
// you can try to keep time of how long it is between pulses
volatile uint32_t lastflowratetimer = 0;
// and use that to calculate a flow rate
volatile float flowrate;
// Interrupt is called once a millisecond, looks for any pulses from the sensor!
SIGNAL(TIMER0_COMPA_vect) {
  uint8_t x = digitalRead(FLOWSENSORPIN_2);
  
  if (x == lastflowpinstate) {
    lastflowratetimer++;
    return; // nothing changed!
  }
  
  if (x == HIGH) {
    //low to high transition!
    pulses++;
  }
  lastflowpinstate = x;
  flowrate = 1000.0;
  flowrate /= lastflowratetimer;  // in hertz
  lastflowratetimer = 0;
}

// void useInterrupt________________________________________

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
  }
}

// void interface________________________________________


void interface(){
  tft.fillRect(80,80,150,150,RA8875_WHITE);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (110, 120);
          tft.setFontScale(6); 
          tft.print (" 1 ");

  
  tft.fillRect(80+(150*1)+(80*1),80,150,150,RA8875_BLUE);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (330, 120);
          tft.setFontScale(6); 
          tft.print (" 2 ");

  tft.fillRect(80+(150*2)+(80*2),80,150,150,RA8875_MAGENTA);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (560, 120);
          tft.setFontScale(6); 
          tft.print (" 3 ");

  
//  botão cancel


          tft.fillRect(720,450,50,450,RA8875_RED);

}


// void setup________________________________________

void setup() 
{
  Serial.begin(9600);
  //while (!Serial) {;}
  // Serial.println("RA8875 start");

  tft.begin(RA8875_800x480);//initialize library

  tft.touchBegin(RA8875_INT);//enable Touch support!
  interface();

// setup // tela______________________________________________________________

  pinMode(RA8875_INT, INPUT);
  digitalWrite(RA8875_INT, HIGH);
  
  tft.touchEnable(true);
    
  Serial.print("Status: "); Serial.println(tft.readStatus(), HEX);
  Serial.println("Aperte o botão para uma das opçoes:");

// setup // rele ______________________________________________________________

  pinMode(gPinoRele_1, OUTPUT);
  pinMode(gPinoRele_2, OUTPUT);
  pinMode(gPinoRele_3, OUTPUT);

  digitalWrite(gPinoRele_1, HIGH);
  digitalWrite(gPinoRele_2, HIGH);
  digitalWrite(gPinoRele_3, HIGH);
  
// setup // botao ________________________________________________

// Declarando dos pinos 7,8 e 9 como saidas digitais
pinMode(7,OUTPUT);// Saida para o botao 1
pinMode(8,OUTPUT);// Saida para o botao 2
pinMode(9,OUTPUT);// Saida para o botao 3

// Contadores para fazer as funções dos botões entre ON e OFF
contador1 = 0; //Contador para saida 1
contador2 = 0; //Contador para saida 2
contador3 = 0; //Contador para saida 3

// setup // flowmeter ________________________________________________


   Serial.println("Flow sensor funcionando!");

   
   pinMode(FLOWSENSORPIN_1, INPUT);
   digitalWrite(FLOWSENSORPIN_1, HIGH);
   lastflowpinstate = digitalRead(FLOWSENSORPIN_1);
   useInterrupt(true);

   pinMode(FLOWSENSORPIN_2, INPUT);
   digitalWrite(FLOWSENSORPIN_2, HIGH);
   lastflowpinstate = digitalRead(FLOWSENSORPIN_2);
   useInterrupt(true);

   pinMode(FLOWSENSORPIN_3, INPUT);
   digitalWrite(FLOWSENSORPIN_3, HIGH);
   lastflowpinstate = digitalRead(FLOWSENSORPIN_3);
   useInterrupt(true);


// ________________________________________________
}

uint16_t choosenColor = 0;

// void loop________________________________________________

void loop() 
{

// FLOW METER____________________________________________________

// Serial.print("Freq: "); Serial.println(flowrate);
// Serial.print("Pulses: "); Serial.println(pulses, DEC);



  
  // if a sensor use the following calculation
  // Sensor Frequency (Hz) = 7.5 * Q (Liters/min)
  // Liters = Q * time elapsed (seconds) / 60 (seconds/minute)
  // Liters = (Frequency (Pulses/second) / 7.5) * time elapsed (seconds) / 60
  // Liters = Pulses / (7.5 * 60)
  float liters = pulses;
  liters /= 7.5;
  liters /= 60.0;

 
//  Serial.print(liters); Serial.println(" Liters");

          tft.setTextColor(RA8875_YELLOW,RA8875_BLACK);
          tft.setCursor (50, 350);
          tft.setFontScale(2); 
          tft.print (liters); tft.print ("  Liters");
 
  delay(100);

  //_____________________________________________________________
  
  
  tft.changeMode(TEXT);
  tft.setTextColor(RA8875_WHITE);
  tft.setCursor (300, 0);
  tft.setFontScale(2); 
  tft.print ("Chopp self service");
  tft.changeMode(GRAPHIC);

//loop // botao _______________________________________________________________

  // Variaveis para criar os botões
    int Ba, Bb, Bc, Bd, Be, Bf, BotaoPressionado;
  
  
  boolean sair = false;  

//loop // tela _______________________________________________________________

   
  if (tft.touchDetect()){//easy!
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
        tx=800-tx;ty=480-ty;
      if (ty >= 0 && ty <= 550){ //interface area
        if ((tx > 100 && tx < (100+200))){
          choosenColor = RA8875_WHITE;
          interface();
          tft.fillRect(100,100,200,200,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);

          delay(200);
          tft.fillRect(100,100,200,200,RA8875_WHITE);          
          
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (150, 150);
          tft.setFontScale(6); 
          tft.print (" 1 ");

                    
          Serial.println("Botao 1 apertado");

          
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (200, 400);
          tft.setFontScale(2); 
          tft.print ("Botao 1 apertado");
          
          delay(1000);

          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (200, 400);
          tft.setFontScale(2); 
          tft.print ("Botao 1 apertado");
          
// ______________________________________________________________

      (! digitalRead(RA8875_INT)); 
//      Serial.print("Touch: "); 
//      Serial.print(tx); Serial.print(", "); Serial.println(ty);

// loop // aciona botao______________________________________________________________

 //saida 1
 if(contador1==1)
 {
   digitalWrite(7,1);
 }
 if(contador1==2)
 {
   digitalWrite(7,0);
   contador1 = 0;
 }


// ______________________________________________________________


         if (BotaoPressionado == Ba)
         {
          contador1++;
          
           if(contador1==1)
          {
  //        Serial.println("Saida 1 Ligado");
          }
           if(contador1==2)
          {
  //        Serial.println("Saida 1 Desligada");
          }
             
 digitalWrite(gPinoRele_2, HIGH);
 digitalWrite(gPinoRele_1, LOW);
             
//              break;

         }




// ______________________________________________________________

        } 
        else if ((tx > 100+(200*1)+(100*1) && tx < 100+(200*2)+(100*1))){
          choosenColor = RA8875_BLUE;
          interface();
          tft.fillRect(100+(200*1)+(100*1),100,200,200,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);

          delay(200);
          tft.fillRect(100+(200*1)+(100*1),100,200,200,RA8875_BLUE);  

                   
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (450, 150);
          tft.setFontScale(6); 
          tft.print (" 2 ");
          
          Serial.println("Botao 2 apertado");
          
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLUE);
          tft.setCursor (200, 400);
          tft.setFontScale(2); 
          tft.print ("Botao 2 apertado");

            delay(1000);

          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (200, 400);
          tft.setFontScale(2); 
          tft.print ("Botao 2 apertado");

// ______________________________________________________________

      (! digitalRead(RA8875_INT)); 
      Serial.print("Touch: "); 
      Serial.print(tx); Serial.print(", "); Serial.println(ty);

// ______________________________________________________________


   //saida 2
 if(contador2==1)
 {
   digitalWrite(8,1);
 }
 if(contador2==2)
 {
   digitalWrite(8,0);
   contador2 = 0;
 }



 digitalWrite(gPinoRele_1, HIGH);
  
 digitalWrite(gPinoRele_2, LOW);

          


          
        } 


// botão cancel  ______________________________________________________________


        else if ((tx > 750  && tx < 800 )){
          choosenColor = RA8875_RED;
          interface();
          tft.fillRect(720,450,50,450,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);

          delay(200);
          tft.fillRect(720,450,50,450,RA8875_RED);  

        
          Serial.println("CANCELADO");
          
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_RED);
          tft.setCursor (200, 400);
          tft.setFontScale(2); 
          tft.print ("CANCELADO");

            delay(1000);

          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (200, 400);
          tft.setFontScale(2); 
          tft.print ("CANCELADO");

// ______________________________________________________________

      (! digitalRead(RA8875_INT)); 
      Serial.print("Touch: "); 
      Serial.print(tx); Serial.print(", "); Serial.println(ty);

// ______________________________________________________________


   //saida 3
 if(contador3==1)
 {
   digitalWrite(9,1);
 }
 if(contador3==2)
 {
   digitalWrite(9,0);
   contador3 = 0;
 }


 digitalWrite(gPinoRele_1, HIGH);
  
 digitalWrite(gPinoRele_2, HIGH);
        }

// FIM botão cancel  ______________________________________________________________






        
      }
  }
}
