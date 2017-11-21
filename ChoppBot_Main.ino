/*
  ChoppBot 1.0

  By Marcelo Rocha, Sidnei Conrad and Flavio Liberal

  Main program to an automated chopp dispenser with several
  features like touchscreen, biometrical recognition and RFID
  recognition. More to came.
  
*/



#include "ChoppBot_GLobais.h" 
#include "ChoppBot_Suporte.h" 


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  PROCEDURES ChoopBot
//  ===================
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Inicia a aplicacao, definido todos os parametros necessarios
void InitApp()
{

	InicializaVars();

	pinMode(gID_LefBuildint, OUTPUT);

	pinMode(gPin_BotaoDebug2, INPUT);

	pinMode(gPin_BotaoDebug3, INPUT);
	
	pinMode(gPin_BotaoDebug4, INPUT);
	
	Serial.begin(9600);
	
	Led_Light(false);
	
	// todo: inicializa hardware, fecha valvulas, etc
}





// ROTINA DE OPERACAO
void Exec_OPERACAO()
{
	boolean Exec_Loop_PodeSair = false;

	unsigned long time_inicio;
	unsigned long time_atual;
	unsigned long time_tempo_passado;
	
	gModoOperacao = "OPERACAO";

	

	time_inicio = millis();

	while (Exec_Loop_PodeSair == false)
	{


		
		//Serial.print("Escolha o chopp 1 ou 2:");	

		time_atual = millis();
		time_tempo_passado = time_atual - time_inicio;


		if (time_tempo_passado >= gTimeoutOpcao)
		{
			Exec_Loop_PodeSair = true;
			gModoOperacao = "STANDBY";
		}


		delay(500);

	}

}



// ROTINA DE ADMIN
void Exec_ADMIN()
{
	boolean Exec_Loop_PodeSair = false;

	unsigned long time_inicio;
	unsigned long time_atual;
	unsigned long time_tempo_passado;

	gModoOperacao = "ADMIN";

	time_inicio = millis();

	while (Exec_Loop_PodeSair == false)
	{


		time_atual = millis();
		time_tempo_passado = time_atual - time_inicio;

		if (time_tempo_passado >= gTimeoutOpcao)
		{
			Exec_Loop_PodeSair = true;
			gModoOperacao = "STANDBY";
		}

		delay(500);
	}

}




// ROTINA DE LOGIN
void Exec_LOGIN()
{
	boolean Exec_Loop_PodeSair = false;

	unsigned long time_inicio;
	unsigned long time_atual;
	unsigned long time_tempo_passado;

	gModoOperacao = "LOGIN";

	time_inicio = millis();

	while (Exec_Loop_PodeSair == false)
	{



		LogTerm("LOGIN");




		time_atual = millis();
		time_tempo_passado = time_atual - time_inicio;

		if (time_tempo_passado >= gTimeoutOpcao)
		{
			Exec_Loop_PodeSair = true;
			gModoOperacao = "STANDBY";
		}


		delay(500);

	}

}





// ROTINA DE DEBUG
void Exec_DEBUG()
{
	boolean Exec_Loop_PodeSair = false;

	unsigned long time_inicio;
	unsigned long time_atual;
	unsigned long time_tempo_passado;

	gModoOperacao = "DEBUG";

	time_inicio = millis();

	while (Exec_Loop_PodeSair == false)
	{



		LogTerm("DEBUG");




		time_atual = millis();
		time_tempo_passado = time_atual - time_inicio;

		if (time_tempo_passado >= gTimeoutOpcao)
		{
			Exec_Loop_PodeSair = true;
			gModoOperacao = "STANDBY";
		}

		delay(500);


	}

}





// ROTINA DE STANDBY
void Exec_STANDBY()
{
	TestaInterrupts();

	delay(500);
}






// Rotina que executa o procedimento de stand by
void Exec_TESTE()
{

	boolean Exec_Loop_PodeSair = false;

	LogTerm("Exec_STANDBY");

	//ShowExample_Tela();

	TELA_IniciaTela();

	TELA_Texto("Linha1cccc");
	TELA_Texto("Linha2");
	TELA_Texto("Linha3");
	TELA_Texto("Linha4");
	TELA_Texto("Linha5");
	TELA_Texto("Linha6");
	TELA_Texto("Linha7");



	while (Exec_Loop_PodeSair == false)
	{
		LogTerm("Exec_STANDBY");
		delay(500);

	}
}





// Procedure que testa se ocorreu algum interrupt: O sistema fica em modo StandBy ate que alguem toque na tela, ou faca alguma outra acao que gere uma interrupcao
void TestaInterrupts()
{

	//todo: testa se teve interrupt do biometrico, RFID, tela botoes, tela admin, tela screensaver, botoes fisicos



	// BIOMETRICO:


	// RFID:

	// TELA TOUCH - BOTOES:

	// TELA TOUCH - ADMIN:

	// TELA TOUCH - SCREEN SAVER:


	// ---------------
	// BOTOES FISICOS:
	// ---------------

	int buttonState2 = 0;  
	int buttonState3 = 0;  
	int buttonState4 = 0;  

	buttonState2 = digitalRead(gPin_BotaoDebug2);
	buttonState3 = digitalRead(gPin_BotaoDebug3);
	buttonState4 = digitalRead(gPin_BotaoDebug4);


	if (buttonState2 == HIGH) 
	{

		LogTerm("Botao apertado 1 -- pino 2 ! -- Exec_LOGIN");

		Exec_LOGIN();

		//Exec_OPERACAO();

	}

	if (buttonState3 == HIGH) 
	{
		LogTerm("Botao apertado 2 -- pino 3 ! -- Exec_ADMIN");
		
		Exec_ADMIN();
	}



	if (buttonState4 == HIGH) 
	{
		LogTerm("Botao apertado 3 -- pino 4! -- Exec_DEBUG");
		
		Exec_DEBUG();
	}



}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  INTERNAS ARDUINO
//  ================
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// INTERNA ARDUINO: SETUP
void setup() {
  
	InitApp();


	
}


// INTERNA ARDUINO: LOOP ETERNO
void loop() {


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (gModoOperacao == "INICIO")
	{
		LogTerm("Modo: Inicio");

		//Led_Light(true);
		
		gModoOperacao = "STANDBY";

				
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (gModoOperacao == "STANDBY")
	{
		LogTerm("Modo: StandBy");
		
		

		Exec_STANDBY();

		
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (gModoOperacao == "LOGIN")
	{
		LogTerm("Modo: LOGIN");

		Exec_LOGIN();

		
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (gModoOperacao == "OPERACAO")
	{
		LogTerm("Modo: Operacao");
		
		//gModoOperacao = 4;	// Standby

		Exec_OPERACAO();

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (gModoOperacao == "ADMIN")
	{
		LogTerm("Modo: ADMIN");

		Exec_ADMIN();
		
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (gModoOperacao == "DEBUG")
	{
		LogTerm("Modo: DEBUG");

		Exec_DEBUG();
			
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
}

