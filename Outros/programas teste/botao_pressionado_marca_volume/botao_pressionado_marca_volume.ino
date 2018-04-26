// botao + marca volume

// tela __________________________________________________

#include <SPI.h>
#include <RA8875.h>


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

RA8875 tft = RA8875(RA8875_CS,RA8875_RESET);

//#endif

uint16_t tx, ty;

int ajuste = 23;


// botão ________________________________________

int contador1; //Contador para saida 1
int contador2; //Contador para saida 2
int contador3; //Contador para saida 3
int contador4; //Contador para saida 4

// rele ________________________________________

int gPinoRele_1 = 45;
int gPinoRele_2 = 46;
int gPinoRele_3 = 47;

// flowmeter________________________________________

#define FLOWSENSORPIN 36
#define FLOWSENSORPIN1 37 
#define FLOWSENSORPIN2 38 

// count how many pulses!
volatile uint16_t pulses = 0;
volatile uint16_t pulses1 = 0;
volatile uint16_t pulses2 = 0;

// track the state of the pulse pin
volatile uint8_t lastflowpinstate;
volatile uint8_t lastflowpinstate1;
volatile uint8_t lastflowpinstate2;

// you can try to keep time of how long it is between pulses
volatile uint32_t lastflowratetimer = 0;
volatile uint32_t lastflowratetimer1 = 0;
volatile uint32_t lastflowratetimer2 = 0;

// and use that to calculate a flow rate
volatile float flowrate;
volatile float flowrate1;
volatile float flowrate2;

// Interrupt is called once a millisecond, looks for any pulses from the sensor!

SIGNAL(TIMER0_COMPA_vect) {
  uint8_t x = digitalRead(FLOWSENSORPIN);
  
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


SIGNAL(TIMER1_COMPA_vect) {
  
  uint8_t x1 = digitalRead(FLOWSENSORPIN1);
  
  if (x1 == lastflowpinstate1) {
    lastflowratetimer1++;
    return; // nothing changed!
  }
  

  if (x1 == HIGH) {
    //low to high transition!
    pulses1++;
  }


  lastflowpinstate1 = x1;
  flowrate1 = 1000.0;
  flowrate1 /= lastflowratetimer1;  // in hertz
  lastflowratetimer1 = 0;
}

SIGNAL(TIMER2_COMPA_vect) {
  
  uint8_t x2 = digitalRead(FLOWSENSORPIN2);
  
  if (x2 == lastflowpinstate2) {
    lastflowratetimer2++;
    return; // nothing changed!
  }
  

  if (x2 == HIGH) {
    //low to high transition!
    pulses2++;
  }


  lastflowpinstate2 = x2;
  flowrate2 = 1000.0;
  flowrate2 /= lastflowratetimer2;  // in hertz
  lastflowratetimer2 = 0;
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

void useInterrupt1(boolean c) {
  if (c) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR1A = 0xAF;
    TIMSK1 |= _BV(OCIE1A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK1 &= ~_BV(OCIE1A);
  }
  } 

void useInterrupt2(boolean b) {
  if (b) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR2A = 0xAF;
    TIMSK2 |= _BV(OCIE2A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK2 &= ~_BV(OCIE2A);
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
          tft.setCursor (340, 120);
          tft.setFontScale(6); 
          tft.print (" 2 ");

  tft.fillRect(80+(150*2)+(80*2),80,150,150,RA8875_MAGENTA);

          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (570, 120);
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

// Declarando dos pinos 7,8,9 e 10 como saidas digitais
pinMode(7,OUTPUT);// Saida para o botao 1
pinMode(8,OUTPUT);// Saida para o botao 2
pinMode(9,OUTPUT);// Saida para o botao 3
pinMode(10,OUTPUT);// Saida para o botao 4

// Contadores para fazer as funções dos botões entre ON e OFF
contador1 = 0; //Contador para saida 1
contador2 = 0; //Contador para saida 2
contador3 = 0; //Contador para saida 3
contador4 = 0; //Contador para saida 4

// setup // flowmeter ________________________________________________

   Serial.begin(9600);
   Serial.println("Flow sensor funcionando!");

  delay(1000);
  
  pinMode(FLOWSENSORPIN, INPUT);
  digitalWrite(FLOWSENSORPIN, HIGH);
  lastflowpinstate = digitalRead(FLOWSENSORPIN);
  
  pinMode(FLOWSENSORPIN1, INPUT);
  digitalWrite(FLOWSENSORPIN1, HIGH);
  lastflowpinstate1 = digitalRead(FLOWSENSORPIN1);
  
  pinMode(FLOWSENSORPIN2, INPUT);
  digitalWrite(FLOWSENSORPIN2, HIGH);
  lastflowpinstate2 = digitalRead(FLOWSENSORPIN2);
  
  useInterrupt(true);
  useInterrupt1(true);
  useInterrupt2(true);

// ________________________________________________
}

uint16_t choosenColor = 0;

// void loop________________________________________________

void loop() 
{

// FLOW METER____________________________________________________

 float liters = pulses;
  liters /= 7.5;
  liters /= 60.0;

  float liters1 = pulses1;
  liters1 /= ajuste;
  liters1 /= 60.0;

  float liters2 = pulses2;
  liters2 /= 7.5;
  liters2 /= 60.0;
 
//  Serial.println(level);
  Serial.print(liters); Serial.print(" Liters"); Serial.print("        "); Serial.print(liters2); Serial.println(" Liters");
  
  delay(100);
 
  Serial.print(liters); Serial.println(" Liters");

//       tft.setTextColor(RA8875_YELLOW,RA8875_BLACK);
         tft.setTextColor(RA8875_BLACK,RA8875_WHITE);
         tft.setCursor (50, 280);
         tft.setFontScale(1); 
         tft.print (liters); tft.print ("  Liters");

//       tft.setTextColor(RA8875_YELLOW,RA8875_BLACK);
         tft.setTextColor(RA8875_BLACK,RA8875_BLUE);
         tft.setCursor (300, 280);
         tft.setFontScale(1); 
         tft.print (liters1); tft.print ("  Liters");

//       tft.setTextColor(RA8875_YELLOW,RA8875_BLACK);
         tft.setTextColor(RA8875_BLACK,RA8875_MAGENTA);
         tft.setCursor (550, 280);
         tft.setFontScale(1); 
         tft.print (liters2); tft.print ("  Liters");   
 
 delay(100);

  //_____________________________________________________________
  
  
  tft.changeMode(TEXT);
  tft.setTextColor(RA8875_WHITE);
  tft.setCursor (50, 0);
  tft.setFontScale(2); 
  tft.print ("Chopp self service");
  tft.changeMode(GRAPHIC);

//loop // botao _______________________________________________________________

  // Variaveis para criar os botões
    int Ba, Bb, Bc, Bd, Be, Bf, BotaoPressionado;
  
  
  boolean sair = false;  

//loop // ROTINA BOTAO 1 _______________________________________________________________

 
  if (tft.touchDetect())
  {//easy!
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
        tx=800-tx;ty=480-ty;
      if (ty >= 0 && ty <= 450)
      { //interface area
        if ((tx > 100 && tx < (100+200)))
        {
          choosenColor = RA8875_WHITE;
          interface();
          tft.fillRect(80,80,150,150,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);

          delay(200);
          tft.fillRect(80,80,150,150,RA8875_WHITE);          
          
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (110, 120);
          tft.setFontScale(6); 
          tft.print (" 1 ");

                    
          Serial.println("Botao 1 apertado");

          
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (200, 400);
          tft.setFontScale(2); 
          tft.print ("Botao 1 apertado");
          
          delay(400);

          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (200, 400);
          tft.setFontScale(2); 
          tft.print ("Botao 1 apertado");
          
// ______________________________________________________________

      (! digitalRead(RA8875_INT)); 
      Serial.print("Touch: "); 
      Serial.print(tx); Serial.print(", "); Serial.println(ty);

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
             
 digitalWrite(gPinoRele_3, HIGH);
 digitalWrite(gPinoRele_2, HIGH);
 digitalWrite(gPinoRele_1, LOW);
             
//              break;




         }




// rotina botao 2 ______________________   

        } 
        else if ((tx > 80+(150*1)+(80*1) && tx < 80+(150*2)+(80*1))){
          choosenColor = RA8875_BLUE;
          interface();
          tft.fillRect(80+(150*1)+(80*1),80,150,150,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);

          delay(200);
          tft.fillRect(80+(150*1)+(80*1),80,150,150,RA8875_BLUE);  

                   
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (340, 120);
          tft.setFontScale(6); 
          tft.print (" 2 ");
          
          Serial.println("Botao 2 apertado");
          
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_BLUE);
          tft.setCursor (200, 400);
          tft.setFontScale(2); 
          tft.print ("Botao 2 apertado");

            delay(400);

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

 digitalWrite(gPinoRele_3, HIGH);


        } 

// rotina botao 3 ______________________        

 else if ((tx > 80+(150*2)+(80*2) && tx < 80+(150*3)+(80*2))){
          choosenColor = RA8875_MAGENTA;
          interface();
          tft.fillRect(80+(150*2)+(80*2),80,150,150,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);

          delay(200);
          tft.fillRect(80+(150*2)+(80*2),80,150,150,RA8875_MAGENTA);  

                   
          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (570, 120);
          tft.setFontScale(6); 
          tft.print (" 3 ");
          
          Serial.println("Botao 3 apertado");
          
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_MAGENTA);
          tft.setCursor (200, 400);
          tft.setFontScale(2); 
          tft.print ("Botao 3 apertado");

            delay(400);

          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (200, 400);
          tft.setFontScale(2); 
          tft.print ("Botao 3 apertado");

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

  digitalWrite(gPinoRele_3, LOW);         

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


   //saida 4
 if(contador4==1)
 {
   digitalWrite(10,1);
 }
 if(contador4==2)
 {
   digitalWrite(10,0);
   contador4 = 0;
 }



 digitalWrite(gPinoRele_1, HIGH);
  
 digitalWrite(gPinoRele_2, HIGH);

 digitalWrite(gPinoRele_3, HIGH);

 
        }

// FIM botão cancel  ______________________________________________________________






        
      }
  }
}
