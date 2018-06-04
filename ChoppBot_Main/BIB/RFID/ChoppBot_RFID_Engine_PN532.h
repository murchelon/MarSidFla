/*
Adafruit PN532 NFC/RFID breakout boards
https://www.adafruit.com/products/364
*/

/*
 * Set DISABLE_CHIP_SELECT to disable a second SPI device.
 * For example, with the Ethernet shield, set DISABLE_CHIP_SELECT
 * to 10 to disable the Ethernet controller.
 */


#define DISABLE_CHIP_SELECT SD_PINO


// If using the breakout with SPI, define the pins for SPI communication.
#define PN532_SCK  RFID_PINO_SCK
#define PN532_MOSI RFID_PINO_MOSI
#define PN532_SS   RFID_PINO_SS
#define PN532_MISO RFID_PINO_MISO

// If using the breakout or shield with I2C, define just the pins connected
// to the IRQ and reset lines.  Use the values below (2, 3) for the shield!
#define PN532_IRQ   RFID_PINO_IRQ
#define PN532_RESET RFID_PINO_RESET  // Not connected by default on the NFC Shield

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

