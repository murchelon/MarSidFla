

// Pino do LED Cor Fixa
#define ctPINO_LED_CORFIXA 26

// led RGB
#define ctPINO_LED_RGB_RED 35
#define ctPINO_LED_RGB_GREEN 34
#define ctPINO_LED_RGB_BLUE 33


void LED_SetLedState(String LED, bool State, String Cor)
{

	if (LED == "BUILTIN")
	{
		if (State == true)
		{
			digitalWrite(LED_BUILTIN, HIGH);    
		}
		else
		{
			digitalWrite(LED_BUILTIN, LOW); 
		}		
	}

	if (LED == "CORFIXA")
	{
		if (State == true)
		{
			digitalWrite(ctPINO_LED_CORFIXA, HIGH);  
		}
		else
		{
			digitalWrite(ctPINO_LED_CORFIXA, LOW);
		}		
	}


	if (LED == "RGB")
	{


		if (State == true)
		{

			if (Cor == "WHITE")
			{
				LED_RGB_ExecSetColor(255, 255, 255);
			}

			if (Cor == "RED")
			{
				LED_RGB_ExecSetColor(255, 0, 0);
			}

			if (Cor == "GREEN")
			{
				LED_RGB_ExecSetColor(0, 255, 0);
			}

			if (Cor == "BLUE")
			{
				LED_RGB_ExecSetColor(0, 0, 255);
			}

			if (Cor == "ORANGE")
			{
				LED_RGB_ExecSetColor(5, 215, 255);
			}

			if (Cor == "PURPLE")
			{
				LED_RGB_ExecSetColor(170, 0, 255);
			}

		}
		else
		{
			LED_RGB_ExecSetColor(0, 0, 0);
		}		
	}



}






void LED_RGB_ExecSetColor(int redValue, int greenValue, int blueValue) 
{
	analogWrite(ctPINO_LED_RGB_RED, redValue);
	analogWrite(ctPINO_LED_RGB_GREEN, greenValue);
	analogWrite(ctPINO_LED_RGB_BLUE, blueValue);

	//digitalWrite(redPin, redValue);
	//digitalWrite(greenPin, greenValue);
	//digitalWrite(bluePin, blueValue);
}




void setup() 
{

	Serial.begin(115200);  

	pinMode(ctPINO_LED_RGB_RED, OUTPUT);
	pinMode(ctPINO_LED_RGB_GREEN, OUTPUT);
	pinMode(ctPINO_LED_RGB_BLUE, OUTPUT);


    // Inicia o LED do codfixa
    pinMode(ctPINO_LED_CORFIXA, OUTPUT);


    // inicia o led interno arduino, usado para mostrar que o programa esta rodando
    pinMode(LED_BUILTIN, OUTPUT);


}




void loop() 
{


	//PWM: 3, 5, 6, 9, 10, and 11. Provide 8-bit PWM output with the analogWrite() function.
	//https://forum.arduino.cc/index.php?topic=375664.0

	Serial.println("BUILTIN");
	LED_SetLedState("BUILTIN", true, "");
	delay(1500);
	LED_SetLedState("BUILTIN", false, "");
	




	Serial.println("CORFIXA");
	LED_SetLedState("CORFIXA", true, "");
	delay(1500);
	LED_SetLedState("CORFIXA", false, "");
	



	Serial.println("RGB - Red");
	LED_SetLedState("RGB", true, "RED");
	delay(1500);
	LED_SetLedState("RGB", false, "");	


	Serial.println("RGB - Green");
	LED_SetLedState("RGB", true, "GREEN");
	delay(1500);
	LED_SetLedState("RGB", false, "");


	Serial.println("RGB - Blue");
	LED_SetLedState("RGB", true, "BLUE");
	delay(1500);
	LED_SetLedState("RGB", false, "");


	Serial.println("RGB - ORANGE");
	LED_SetLedState("RGB", true, "ORANGE");
	delay(1500);
	LED_SetLedState("RGB", false, "");


	Serial.println("RGB - PURPLE");
	LED_SetLedState("RGB", true, "PURPLE");
	delay(1500);
	LED_SetLedState("RGB", false, "");


}


