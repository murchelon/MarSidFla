

#include <SPI.h>
#include "SdFat.h"

#include <Wire.h>
#include <Adafruit_PN532.h>


// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define USE_SDIO 0

const uint8_t SD_CHIP_SELECT = 24;
/*
 * Set DISABLE_CHIP_SELECT to disable a second SPI device.
 * For example, with the Ethernet shield, set DISABLE_CHIP_SELECT
 * to 10 to disable the Ethernet controller.
 */
const int8_t DISABLE_CHIP_SELECT = 24;

SdFat sd;









// serial output steam
ArduinoOutStream cout(Serial);




// global for card size
uint32_t cardSize;


// store error strings in flash
#define sdErrorMsg(msg) sd.errorPrint(F(msg));



// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// If using the breakout with SPI, define the pins for SPI communication.
#define PN532_SCK  (52)
#define PN532_MOSI (51)
#define PN532_SS   (53)
#define PN532_MISO (50)

// If using the breakout or shield with I2C, define just the pins connected
// to the IRQ and reset lines.  Use the values below (2, 3) for the shield!
#define PN532_IRQ   (2)
#define PN532_RESET (3)  // Not connected by default on the NFC Shield

// Uncomment just _one_ line below depending on how your breakout or shield
// is connected to the Arduino:

// Use this line for a breakout with a SPI connection:
//Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

// Use this line for a breakout with a hardware SPI connection.  Note that
// the PN532 SCK, MOSI, and MISO pins need to be connected to the Arduino's
// hardware SPI SCK, MOSI, and MISO pins.  On an Arduino Uno these are
// SCK = 13, MOSI = 11, MISO = 12.  The SS line can be any digital IO pin.
//Adafruit_PN532 nfc(PN532_SS);

// Or use this line for a breakout or shield with an I2C connection:
//Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);



// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void setup() {
    Serial.begin(115200);

    // Wait for USB Serial 
    while (!Serial) {
    SysCall::yield();
    }


    

 

}
//------------------------------------------------------------------------------


void Exec_SD()
{


    // SD CARD

    uint32_t t = millis();
    #if USE_SDIO
      if (!sd.cardBegin()) {
        sdErrorMsg("\ncardBegin failed");
        return;
      }
    #else  // USE_SDIO
      // Initialize at the highest speed supported by the board that is
      // not over 50 MHz. Try a lower speed if SPI errors occur.
      if (!sd.cardBegin(SD_CHIP_SELECT, SPI_SIXTEENTH_SPEED)) {
        sdErrorMsg("cardBegin failed");
        return;
      }
     #endif  // USE_SDIO 
      t = millis() - t;

      cardSize = sd.card()->cardSize();
      if (cardSize == 0) {
        sdErrorMsg("cardSize failed");
        return;
      }
      cout << F("\ninit time: ") << t << " ms" << endl;
      cout << F("\nCard type: ");
      switch (sd.card()->type()) {
      case SD_CARD_TYPE_SD1:
        cout << F("SD1\n");
        break;

      case SD_CARD_TYPE_SD2:
        cout << F("SD2\n");
        break;

      case SD_CARD_TYPE_SDHC:
        if (cardSize < 70000000) {
          cout << F("SDHC\n");
        } else {
          cout << F("SDXC\n");
        }
        break;

      default:
        cout << F("Unknown\n");
      }





}


void loop() {
  // Read any existing Serial data.
    do 
    {
        delay(10);
    } while (Serial.available() && Serial.read() >= 0);

    // F stores strings in flash to save RAM
    cout << F("\ntype any character to start\n");

    while (!Serial.available()) 
    {
        SysCall::yield();
    }

    cout << F("\nIniciando SD...");

    Exec_SD();

    cout << F("\nFinalizando SD...");

    cout << F("\nIniciando Exec_RFID...");

    Exec_RFID();

    cout << F("\nFinalizando Exec_RFID...");




}





void Exec_RFID() {


    /*
    // use uppercase in hex and use 0X base prefix
    cout << uppercase << showbase << endl;

    // F stores strings in flash to save RAM
    cout << F("SdFat version: ") << SD_FAT_VERSION << endl;
    */

    Adafruit_PN532 nfc(PN532_SS);

    #if !USE_SDIO  
    if (DISABLE_CHIP_SELECT < 0) {
    cout << F(
           "\nAssuming the SD is the only SPI device.\n"
           "Edit DISABLE_CHIP_SELECT to disable another device.\n");
    } else {
    cout << F("\nDisabling SPI device on pin ");
    cout << int(DISABLE_CHIP_SELECT) << endl;
    pinMode(DISABLE_CHIP_SELECT, OUTPUT);
    digitalWrite(DISABLE_CHIP_SELECT, HIGH);
    }
    cout << F("\nAssuming the SD chip select pin is: ") <<int(SD_CHIP_SELECT);
    cout << F("\nEdit SD_CHIP_SELECT to change the SD chip select pin.\n");
    #endif  // !USE_SDIO  




    nfc.begin();

    uint32_t versiondata = nfc.getFirmwareVersion();
    if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    //while (1); // halt
    return;
    }

    // Got ok data, print it out!
    Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
    Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
    Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

    // Set the max number of retry attempts to read from a card
    // This prevents us from waiting forever for a card, which is
    // the default behaviour of the PN532.
    nfc.setPassiveActivationRetries(0xFF);

    // configure board to read RFID tags
    nfc.SAMConfig();



  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
  
  if (success) {
    Serial.println("Found a card!");
    Serial.print("UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("UID Value: ");
    for (uint8_t i=0; i < uidLength; i++) 
    {
      Serial.print(" 0x");Serial.print(uid[i], HEX); 
    }
    Serial.println("");
  // Wait 1 second before continuing
  delay(1000);
  }
  else
  {
    // PN532 probably timed out waiting for a card
    Serial.println("Timed out waiting for a card");
  }
}


