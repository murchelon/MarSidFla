




void LED_RGB_ExecSetColor(int redValue, int greenValue, int blueValue) 
{
	analogWrite(ctPINO_LED_RGB_RED, redValue);
	analogWrite(ctPINO_LED_RGB_GREEN, greenValue);
	analogWrite(ctPINO_LED_RGB_BLUE, blueValue);

	//digitalWrite(redPin, redValue);
	//digitalWrite(greenPin, greenValue);
	//digitalWrite(bluePin, blueValue);
}




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



