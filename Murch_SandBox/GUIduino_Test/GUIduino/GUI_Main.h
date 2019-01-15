


// define the screen hardware used
#define GUI_SCREEN_HARDWARE F("ER-TFTM070-5")

// define the library used
//#define GUI_LIB_IN_USE_Adafruit_RA8875 1 		// Adafruit_RA8875 
#define GUI_LIB_IN_USE_RA8875 1		// RA8875 




//Arduino DUE,Arduino mega2560,Arduino UNO
#define GUI_RA8875_INT TELA_PINO_INT
#define GUI_RA8875_CS TELA_PINO_CS

#define GUI_RA8875_RESET TELA_PINO_RESET




#ifdef GUI_LIB_IN_USE_Adafruit_RA8875

	//#include "Adafruit_GFX.h"
	//#include "Adafruit_RA8875.h"	

	//#include "../Tela/Adafruit_RA8875/Adafruit_GFX.h"
	//#include "../Tela/Adafruit_RA8875/Adafruit_RA8875.h"
	
#elif GUI_LIB_IN_USE_RA8875

	#include <RA8875.h>
	//#include "../Tela/RA8875/RA8875.h"

#endif


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



//#endif


#ifdef GUI_LIB_IN_USE_Adafruit_RA8875

	Adafruit_RA8875 GUI_tft = Adafruit_RA8875(GUI_RA8875_CS, GUI_RA8875_RESET);	
	
#elif GUI_LIB_IN_USE_RA8875

	RA8875 GUI_tft = RA8875(GUI_RA8875_CS, GUI_RA8875_RESET);

#endif


#include "GUI_Globals.h" 

#include "GUI_Support.h" 
	
#include "GUI_Core.h" 

#include "GUI_Controls.h" 





















