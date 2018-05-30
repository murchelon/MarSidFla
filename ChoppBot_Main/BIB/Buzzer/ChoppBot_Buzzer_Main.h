

void BUZZER_TocaSom(String TipoSom)
{

	unsigned int la = 440;
	unsigned int sol = 200;
	unsigned long tempo = 130;

	if (TipoSom == F("ERRO"))
	{
		tone(ctPINO_BUZZER, la);
		delay(tempo);
		noTone(ctPINO_BUZZER);
		tone(ctPINO_BUZZER, sol, tempo);
		delay(tempo);
		noTone(ctPINO_BUZZER);		
	}


	if (TipoSom == F("SUCESSO"))
	{
		tone(ctPINO_BUZZER, la);
		delay(tempo);
		noTone(ctPINO_BUZZER);
		tone(ctPINO_BUZZER, 1300, tempo);
		delay(tempo);
		tone(ctPINO_BUZZER, 1600, 70);
		delay(tempo);
		noTone(ctPINO_BUZZER);		
	}


	if (TipoSom == F("LIGAR"))
	{
		tone(ctPINO_BUZZER, 1600);		
		delay(100);
		noTone(ctPINO_BUZZER);
		delay(100);
		tone(ctPINO_BUZZER, 1600);		
		delay(100);
		noTone(ctPINO_BUZZER);


	}



}
