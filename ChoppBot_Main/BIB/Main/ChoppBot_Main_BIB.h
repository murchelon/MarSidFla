//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// INCLUDE
// =========
//
// Local unificado para includes de bibs
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// GLOBAIS
#include "ChoppBot_Globais.h" 


// Funcoes de suporte ChoppBot
#include "ChoppBot_Suporte.h" 


// SPI:
#include <SPI.h>


// LEITOR RFID PN532 -- Murch
#include <Wire.h>
#include <Adafruit_PN532.h>
#include "../RFID/ChoppBot_RFID_Engine_PN532.h" 

// RFID MAIN
#include "../RFID/ChoppBot_RFID_Main.h" 



// TELA ER-TFTM070-5
#include <RA8875.h>
#include "../Tela/ChoppBot_Tela_Engine_RTP_ER-TFTM070-5.h" 

// TELA MAIN
#include "../Tela/ChoppBot_Tela_Main.h" 


// BIOMETRICO:
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include "../Biometrico/ChoppBot_Bio_Engine_Adafruit_Fingerprint.h" 
#include "../Biometrico/ChoppBot_Bio_Main.h" 


// LEITOR SD
#include "SdFat.h"





// BANCO DE DADOS EDB
//#include <EDB.h>


