




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

	if (LED == String(F("BUILTIN")))
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

	if (LED == String(F("CORFIXA")))
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


	if (LED == String(F("RGB")))
	{


		if (State == true)
		{

			if (Cor == String(F("WHITE")))
			{
				LED_RGB_ExecSetColor(255, 255, 255);
			}

			if (Cor == String(F("RED")))
			{
				LED_RGB_ExecSetColor(255, 0, 0);
			}

			if (Cor == String(F("GREEN")))
			{
				LED_RGB_ExecSetColor(0, 255, 0);
			}

			if (Cor == String(F("BLUE")))
			{
				LED_RGB_ExecSetColor(0, 0, 255);
			}

			if (Cor == String(F("ORANGE")))
			{
				LED_RGB_ExecSetColor(5, 215, 255);
			}

			if (Cor == String(F("PURPLE")))
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



// verifica se o LedON deve estar ativo ou nao . Led do arduino que indica o correto funcionamento do programa
void ExecLedON_Beat() 
{

	gLedON_time_atual = millis();

	gLedON_time_tempo_passado = gLedON_time_atual - gLedON_time_inicio;

	gLedON_SegundosPassados = floor(gLedON_time_tempo_passado / 1000);

	//LogTerm(gLedON_SegundosPassados);

	if (gLedON_Last_SegundosPassados != gLedON_SegundosPassados)
	{
		//LogTerm(gLedON_time_tempo_passado);
	}


	if (gLedON_time_tempo_passado >= ctLED_ON_TEMPO)
	{

		gLedON_time_inicio = millis();

		LED_SetLedState("BUILTIN", !gLedON_EstadoAtual, "");

		gLedON_EstadoAtual = !gLedON_EstadoAtual;

		//LogTerm(gLedON_EstadoAtual);
	}

	gLedON_Last_SegundosPassados = gLedON_SegundosPassados;
  
}



