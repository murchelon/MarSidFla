
void BUZZER_TocaSom(String TipoSom)
{

	unsigned int la = 440;
	unsigned int sol = 392;
	unsigned long tempo = 130;

	if (TipoSom == "ERRO")
	{
		tone(ctPINO_BUZZER, la);
		delay(tempo);
		noTone(ctPINO_BUZZER);
		tone(ctPINO_BUZZER, sol, tempo);
		delay(tempo);
		noTone(ctPINO_BUZZER);		
	}


	if (TipoSom == "SUCESSO")
	{
		tone(ctPINO_BUZZER, la);
		delay(tempo);
		noTone(ctPINO_BUZZER);
		tone(ctPINO_BUZZER, 1000, tempo);
		delay(tempo);
		noTone(ctPINO_BUZZER);		
	}


	if (TipoSom == "LIGAR")
	{
		tone(ctPINO_BUZZER, 500);
		delay(100);
		noTone(ctPINO_BUZZER);
		tone(ctPINO_BUZZER, 700, 100);
		delay(100);
		noTone(ctPINO_BUZZER);		
		tone(ctPINO_BUZZER, 900, 100);
		delay(100);
		noTone(ctPINO_BUZZER);	
	}


}