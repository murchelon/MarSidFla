/*
  ChoppBot 1.0

  By Marcelo Rocha, Sidnei Conrad and Flavio Liberal

  Main program to an automated chopp dispenser with several
  features like touchscreen, biometrical recognition and RFID
  recognition. More to came.
  
*/


	// 1 = INICIO
	// 2 = OPERACAO
	// 3 = ADMIN
	// 4 = STANDBY
	// 5 = DEBUG



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

	pinMode(gPin_BotaoDebug1, INPUT);

	pinMode(gPin_BotaoDebug2, INPUT);
	
	Serial.begin(9600);
	
	Led_Light(false);
	
	// todo: inicializa hardware, fecha valvulas, etc
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

	int buttonState1 = 0;  
	int buttonState2 = 0;  

	buttonState1 = digitalRead(gPin_BotaoDebug1);
	buttonState2 = digitalRead(gPin_BotaoDebug2);


	if (buttonState1 == HIGH) 
	{

		LogTerm("Botao apertado 1 ! -- Exec_OPERACAO");

		Exec_OPERACAO();
	}

	if (buttonState2 == HIGH) 
	{
		LogTerm("Botao apertado 2 ! -- Exec_ADMIN");
		
		Exec_ADMIN();
	}



}




// ROTINA DE OPERACAO
void Exec_OPERACAO()
{
	boolean Exec_Loop_PodeSair = false;

	unsigned long time_inicio;
	unsigned long time_atual;
	unsigned long time_tempo_passado;
	
	gModoOperacao = 2; 	// OPERACAO

	

	time_inicio = millis();

	while (Exec_Loop_PodeSair == false)
	{


		
		Serial.print("Escolha o chopp 1 ou 2:");	

		time_atual = millis();
		time_tempo_passado = time_atual - time_inicio;


		if (time_tempo_passado >= gTimeoutOpcao)
		{
			Exec_Loop_PodeSair = true;
			gModoOperacao = 4; 	// Standby
		}




	}

}



// ROTINA DE ADMIN
void Exec_ADMIN()
{
	boolean Exec_Loop_PodeSair = false;

	unsigned long time_inicio;
	unsigned long time_atual;
	unsigned long time_tempo_passado;

	gModoOperacao = 3; 	// ADMIN

	time_inicio = millis();

	while (Exec_Loop_PodeSair == false)
	{


		time_atual = millis();
		time_tempo_passado = time_atual - time_inicio;

		if (time_tempo_passado >= gTimeoutOpcao)
		{
			Exec_Loop_PodeSair = true;
			gModoOperacao = 4; 	// Standby
		}


	}

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


	switch (gModoOperacao) {

		case 1:
			// INICIO
			
			LogTerm("Modo: Inicio");

			//Led_Light(true);
			
			gModoOperacao = 4; 	// Standby

			delay(500);
			break;

		case 2:
			// OPERACAO
			
			LogTerm("Modo: Operacao");
			
			//gModoOperacao = 4;	// Standby
			
			//delay(500);
			break;

		case 3:
			// ADMIN

			LogTerm("Modo: ADMIN");

			//delay(500);
			break;
			
		case 4:
			// STANDBY
			
			LogTerm("Modo: StandBy");
			
			TestaInterrupts();

			//Exec_STANDBY();

			//delay(200);
			break;
			
		case 5:
			// DEBUG
			
			////LogTerm("Modo: DEBUG");
			
			gContaPasso_Debug = gContaPasso_Debug + 1;

			if (gContaPasso_Debug == 2)
			{
				gContaPasso_Debug = 0;
				gModoOperacao = 4;	// Standby
			}
			
			delay(500);
			break;


	}  
}


	// 1 = INICIO
	// 2 = OPERACAO
	// 3 = ADMIN
	// 4 = STANDBY
	// 5 = DEBUG
