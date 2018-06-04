

void BUZZER_TocaSom(String TipoSom)
{

	unsigned int la = 440;
	unsigned int sol = 200;
	unsigned long tempo = 130;

	if (TipoSom == F("ERRO"))
	{
		tone(BUZZER_PINO, la);
		delay(tempo);
		noTone(BUZZER_PINO);
		tone(BUZZER_PINO, sol, tempo);
		delay(tempo);
		noTone(BUZZER_PINO);		
	}


	if (TipoSom == F("SUCESSO"))
	{
		tone(BUZZER_PINO, la);
		delay(tempo);
		noTone(BUZZER_PINO);
		tone(BUZZER_PINO, 1300, tempo);
		delay(tempo);
		tone(BUZZER_PINO, 1600, 70);
		delay(tempo);
		noTone(BUZZER_PINO);		
	}


	if (TipoSom == F("LIGAR"))
	{
		tone(BUZZER_PINO, 1600);		
		delay(100);
		noTone(BUZZER_PINO);
		delay(100);
		tone(BUZZER_PINO, 1600);		
		delay(100);
		noTone(BUZZER_PINO);


	}



}
