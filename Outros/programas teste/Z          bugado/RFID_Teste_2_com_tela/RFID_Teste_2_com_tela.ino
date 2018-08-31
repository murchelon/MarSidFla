

#include <SPI.h>
#include <MFRC522.h>
#include <RA8875.h>

constexpr uint8_t RST_PIN = 30;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 53;     // Configurable, see typical pin layout above
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];

//____________________________________________________

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
              //tft.setCursor (190, 160);
              //tft.print (" ");
              //tft.setCursor (80, 220);
              tft.println ("Faca seu login,");
              tft.print (" aproximando seu cartao.");
              tft.setTextColor(RA8875_WHITE);
              tft.setCursor (70, 330);
              //tft.print ("Seu tag e:  ");
              


                    tft.setTextColor(RA8875_WHITE);
                    tft.setFontScale(2); 
                    tft.setCursor (600, 430);
                    tft.println ("Obrigado");
                    
          
}
//_______________________________________________________________________-


void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  //Serial.println(F("This code scan the MIFARE Classsic NUID."));
 //Serial.print(F("Using the following key:"));
  //printHex(key.keyByte, MFRC522::MF_KEY_SIZE);

Serial.println("Faca seu login aproximando seu cartao.");
Serial.println();

// _______________________________________________

{

  tft.begin(RA8875_800x480);//initialize library

  tft.touchBegin(RA8875_INT);//enable Touch support!


      interface();

      interface3();

}

// _______________________________________________
}
 
void loop() {

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  //Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  //Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Erro de tipo de cartao."));
    return;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    //Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
    Serial.print(F("Seu tag e:"));
  
   
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();


              tft.setCursor (70, 330);
              tft.print ("Seu saldo e de R$ 300,00 ");




  }
  else Serial.println(F("Cartao ja lido."));
        Serial.println();



  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
