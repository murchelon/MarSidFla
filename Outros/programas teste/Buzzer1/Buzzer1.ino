

// pino do buzzer
#define ctPINO_BUZZER 32


void BUZZER_TocaSom(String TipoSom)
{

	unsigned int la = 440;
	unsigned int sol = 200;
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
		tone(ctPINO_BUZZER, 1800, tempo);
		delay(tempo);
		tone(ctPINO_BUZZER, 1500, 70);
		delay(tempo);
		noTone(ctPINO_BUZZER);		
	}


	if (TipoSom == "LIGAR")
	{
		tone(ctPINO_BUZZER, 1500);		
		delay(100);
		noTone(ctPINO_BUZZER);
		delay(100);
		tone(ctPINO_BUZZER, 1500);		
		delay(100);
		noTone(ctPINO_BUZZER);


	}



}


void setup()
{

	Serial.begin(115200); 

	pinMode(ctPINO_BUZZER, OUTPUT);


}


void loop() 
{
	BUZZER_TocaSom("LIGAR");
	delay(2000);

	BUZZER_TocaSom("SUCESSO");
	delay(2000);

	BUZZER_TocaSom("ERRO");
	delay(2000);


	delay(2000);


}