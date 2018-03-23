//tela + rele + biometrico

#include <SPI.h>
#include <RA8875.h>

//Arduino DUE,Arduino mega2560,Arduino UNO
#define RA8875_INT 4
#define RA8875_CS 10 
#define RA8875_RESET 9

RA8875 tft = RA8875(RA8875_CS,RA8875_RESET);

uint16_t tx, ty;

void interface(){
  tft.fillRect(10,10,40,40,RA8875_WHITE);
  tft.fillRect(10+(40*1)+(10*1),10,40,40,RA8875_BLUE);
}

// ________________________________________________

#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 13);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int gPinoRele_1 = 45;
int gPinoRele_2 = 46;
int gPinoRele_3 = 47;

// ________________________________________________


int contador1; //Contador para saida 1
int contador2; //Contador para saida 2

// ________________________________________________


void setup() 
{
  Serial.begin(9600);
  //while (!Serial) {;}
  Serial.println("RA8875 start");

  tft.begin(RA8875_800x480);//initialize library

  tft.touchBegin(RA8875_INT);//enable Touch support!
  interface();


  // ________________________________________________

 pinMode(gPinoRele_1, OUTPUT);
  pinMode(gPinoRele_2, OUTPUT);
  pinMode(gPinoRele_3, OUTPUT);

  digitalWrite(gPinoRele_1, HIGH);
  digitalWrite(gPinoRele_2, HIGH);
  digitalWrite(gPinoRele_3, HIGH);
  
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");


// ________________________________________________

// Declarando dos pinos 7 e 8 como saidas digitais
pinMode(7,OUTPUT);// Saida para o botao 1
pinMode(8,OUTPUT);// Saida para o botao 2

// Contadores para fazer as funções dos botões entre ON e OFF
contador1 = 0; //Contador para saida 1
contador2 = 0; //Contador para saida 2



// ________________________________________________

}

uint16_t choosenColor = 0;

void loop() 
{    
    tft.changeMode(TEXT);
    tft.setTextColor(RA8875_WHITE);
    tft.setCursor (300, 0);
    tft.setFontScale(2); 
    tft.print ("Chopp self service");
    tft.changeMode(GRAPHIC);
    
  if (tft.touchDetect()){//easy!
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
        tx=800-tx;ty=480-ty;
      if (ty >= 0 && ty <= 55){ //interface area
        if ((tx > 10 && tx < (10+40))){
          choosenColor = RA8875_WHITE;
          interface();
          tft.fillRect(10,10,40,40,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
                    
          Serial.println("Botao 1 apertado");
          
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (200, 200);
          tft.setFontScale(2); 
          tft.print ("Botao 1 apertado");
          
          delay(2000);

          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (200, 200);
          tft.setFontScale(2); 
          tft.print ("Botao 1 apertado");
          

        } 
        else if ((tx > 10+(40*1)+(10*1) && tx < 10+(40*2)+(10*1))){
          choosenColor = RA8875_BLUE;
          interface();
          tft.fillRect(10+(40*1)+(10*1),10,40,40,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
          
          Serial.println("Botao 2 apertado");
          
          tft.changeMode(TEXT);
          tft.setTextColor(RA8875_WHITE);
          tft.setCursor (200, 200);
          tft.setFontScale(2); 
          tft.print ("Botao 2 apertado");

                    delay(2000);

          tft.setTextColor(RA8875_BLACK);
          tft.setCursor (200, 200);
          tft.setFontScale(2); 
          tft.print ("Botao 2 apertado");

// ________________________________________________

  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  digitalWrite(gPinoRele_1, LOW);
  Serial.print("passei aqui 1\n");
  delay(5000);
  digitalWrite(gPinoRele_1, HIGH);
  Serial.print("fui 1\n");

  
  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  digitalWrite(gPinoRele_1, LOW);
  Serial.print("passei aqui 1\n");
  delay(5000);
  digitalWrite(gPinoRele_1, HIGH);
  Serial.print("fui 1\n");


  return finger.fingerID; 


// ________________________________________________
        } 
        
      }
  }
}











