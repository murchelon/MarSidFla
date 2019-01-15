

#include <RA8875.h>


// GUIduino
#include "BIB/GUI_Test_Params.h" 
#include "GUIduino/GUI_Main.h" 



// INTERNA ARDUINO: SETUP
void setup()
{  


    Serial.begin(115200);       // 115200 pois o RFID precisa desta velocidade, para acompanharmos o que ele escreve no serial





	GUI_StartScreen();

	GUI_ResetGenBtn();

	GUI_ResetSelOptions();


	String aTemp[6];

	aTemp[0] = F("Marcelo Rocha");
	aTemp[1] = F("Andre Marques Silva");
	aTemp[3] = F("Ricardo Prado");
	aTemp[4] = F("Vera Maria B. Ferraz");
	aTemp[5] = F("Paulo do Amaral Rocha");
	

	GUI_Define_aSelOptions(aTemp, 5);





	GUI_Render_GenericButton(F("TESTE"), 
								F("Super!"), 
								1, 
								White, 
								Red, 
								8, 
								White, 
								600, 
								100, 
								100, 
								100);


	GUI_Render_SelectList(20, 40, 500, 10, Blue, White, 1, White, -1);

	LogTerm(F("Resultado:"));

	GUI_PrintInTerm_aGenBtn();

	GUI_PrintInTerm_aSelOptions();




	while (1)
	{}

}


// INTERNA ARDUINO: LOOP ETERNO
void loop() 
{
 
}