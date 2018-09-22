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



// LED MAIN
#include "../LED/ChoppBot_LED_Main.h" 



// Funcoes de suporte ChoppBot
#include "ChoppBot_Suporte.h" 


// SPI:
#include <SPI.h>

// math
#include <math.h> 


// BUZZER
#include "../Buzzer/ChoppBot_Buzzer_Main.h" 




// LEITOR SD Adafruit - Engine
#include <SdFat.h>

// LEITOR SD MAIN
#include "../SD/ChoppBot_SD_Main.h" 

// BANCO DE DADOS - EDB - Engine
//#include <EDB.h>


// LEITOR RFID PN532 (Com NFC) - Engine
#include <Wire.h>
#include <Adafruit_PN532.h>
#include "../RFID/ChoppBot_RFID_Engine_PN532.h" 

// LEITOR RFID MAIN -- inserido pelo include da tela main
//#include "../RFID/ChoppBot_RFID_Main.h" 


// TELA ER-TFTM070-5 - Engine


#ifdef ctTELA_BIB_USADA_Adafruit_RA8875

	#include "Adafruit_GFX.h"
	#include "Adafruit_RA8875.h"	
	
#elif ctTELA_BIB_USADA_RA8875

	#include <RA8875.h>

#endif


#include "../Tela/ChoppBot_Tela_Engine_RTP_ER-TFTM070-5.h" 

// BANCO DE DADOS - MAIN
#include "../BancoDados/ChoppBot_BancoDados_Main.h" 

// TELA MAIN
#include "../Tela/ChoppBot_Tela_Main.h" 

// Funcoes Core do sistema
#include "ChoppBot_FuncoesCore.h" 

// RELE MAIN
#include "../Rele/ChoppBot_Rele_Main.h" 


// LEITOR BIOMETRICO ADAFRUIT - Engine
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include "../Biometrico/ChoppBot_Bio_Engine_Adafruit_Fingerprint.h" 

// LEITOR BIOMETRICO MAIN
#include "../Biometrico/ChoppBot_Bio_Main.h" 








