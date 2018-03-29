/*
  ChoppBot 1.0

  By Marcelo Rocha, Sidnei Conrad and Flavio Liberal

  Main program to an automated chopp dispenser with several
  features like touchscreen, biometrical recognition and RFID
  recognition. More to came....
  teste chopp 
*/



#include "BIB/Main/ChoppBot_Globais.h" 
#include "BIB/Main/ChoppBot_Suporte.h" 



#include "BIB/Tela/ChoppBot_Tela_Engine_RTP_ER-TFTM070-5.h" 
#include "BIB/Tela/ChoppBot_Tela_Main.h" 



#include "BIB/Biometrico/ChoppBot_Bio_Engine_Adafruit_Fingerprint.h" 
#include "BIB/Biometrico/ChoppBot_Bio_Main.h" 




//banco de dados:
#include <EDB.h>

//#define BOTAO1_PINO 40
//#define BOTAO2_PINO 41
//#define BOTAO3_PINO 42
//#define BOTAO4_PINO 43


// RELE ======================================================================

#define gPinoRele_1 45
#define gPinoRele_2 46
#define gPinoRele_3 47





int EstadoBotao_Rele1 = 0;

// include the SD library:
//#include <SPI.h>
//#include <SD.h>




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


  Serial.begin(9600);
  
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for native USB port only
  } 

  pinMode(LED_BUILTIN, OUTPUT);

  //pinMode(BOTAO1_PINO, INPUT);

  //pinMode(BOTAO2_PINO, INPUT);
  
  //pinMode(BOTAO3_PINO, INPUT);
  
  //pinMode(BOTAO4_PINO, INPUT);
  
  
  //define reles como output
  //pinMode(gPinoRele_1, OUTPUT);
  //pinMode(gPinoRele_2, OUTPUT);
  //pinMode(gPinoRele_3, OUTPUT);


  //define reles como desligados
  //Estado inicial dos reles - desligados
  digitalWrite(gPinoRele_1, HIGH);
  digitalWrite(gPinoRele_2, HIGH);
  digitalWrite(gPinoRele_3, HIGH);  
  
  Led_Light(false);


  TELA_IniciaTela();
  Render_Interface();


  BIOMETRICO_Inicia();
  



  // todo: inicializa hardware, fecha valvulas, etc
}




    
    
// ROTINA DE INICIO
void Exec_INICIO()
{

    //Led_Light(true);
    
    //SD_Init();

    //ShowExample_DB();

    //Init_Database();
}




// ROTINA DE INSTALACAO
void Exec_INSTALACAO()
{
  boolean Exec_Loop_PodeSair = false;

  unsigned long time_inicio;
  unsigned long time_atual;
  unsigned long time_tempo_passado;

  int SegundosPassados;
  int Last_SegundosPassados;
  
  //gModoOperacao = "INSTALACAO";

  time_inicio = millis();

  while (Exec_Loop_PodeSair == false)
  {

    time_atual = millis();
    time_tempo_passado = time_atual - time_inicio;

    SegundosPassados = floor(time_tempo_passado / 1000);
    
    if (SegundosPassados != Last_SegundosPassados)
    {
      LogTerm(SegundosPassados);
    }
    
    
    
    if (time_tempo_passado >= gTimeoutOpcao)
    {
      Exec_Loop_PodeSair = true;
    }

    Last_SegundosPassados = SegundosPassados;

    //delay(500);

  }
}





// ROTINA DE LOGIN
void Exec_LOGIN()
{
  boolean Exec_Loop_PodeSair = false;

  unsigned long time_inicio;
  unsigned long time_atual;
  unsigned long time_tempo_passado;

  int SegundosPassados;
  int Last_SegundosPassados;
  
  time_inicio = millis();

  while (Exec_Loop_PodeSair == false)
  {

    time_atual = millis();
    time_tempo_passado = time_atual - time_inicio;

    SegundosPassados = floor(time_tempo_passado / 1000);
    
    if (SegundosPassados != Last_SegundosPassados)
    {
      LogTerm(SegundosPassados);
    }
    
    
    
    if (time_tempo_passado >= gTimeoutOpcao)
    {
      Exec_Loop_PodeSair = true;
    }

    Last_SegundosPassados = SegundosPassados;
  }

  gModoOperacao = "STANDBY";

}



// ROTINA DE OPERACAO
void Exec_OPERACAO()
{
  boolean Exec_Loop_PodeSair = false;

  unsigned long time_inicio;
  unsigned long time_atual;
  unsigned long time_tempo_passado;
  
  int SegundosPassados;
  int Last_SegundosPassados;
  

  time_inicio = millis();

  while (Exec_Loop_PodeSair == false)
  {


    
    //Serial.print("Escolha o chopp 1 ou 2:");  

    time_atual = millis();
    time_tempo_passado = time_atual - time_inicio;


    SegundosPassados = floor(time_tempo_passado / 1000);
    
    if (SegundosPassados != Last_SegundosPassados)
    {
      LogTerm(SegundosPassados);
    }
    
    
    
    if (time_tempo_passado >= gTimeoutOpcao)
    {
      Exec_Loop_PodeSair = true;
    }

    Last_SegundosPassados = SegundosPassados;

  }

}



// ROTINA DE ADMIN
void Exec_ADMIN()
{
  boolean Exec_Loop_PodeSair = false;

  unsigned long time_inicio;
  unsigned long time_atual;
  unsigned long time_tempo_passado;

  int SegundosPassados;
  int Last_SegundosPassados;

  time_inicio = millis();

  while (Exec_Loop_PodeSair == false)
  {


    time_atual = millis();
    time_tempo_passado = time_atual - time_inicio;

    SegundosPassados = floor(time_tempo_passado / 1000);
    
    if (SegundosPassados != Last_SegundosPassados)
    {
      LogTerm(SegundosPassados);
    }
    
    
    
    if (time_tempo_passado >= gTimeoutOpcao)
    {
      Exec_Loop_PodeSair = true;
    }

    Last_SegundosPassados = SegundosPassados;
    
    //delay(500);
  }

}






// ROTINA DE DEBUG
void Exec_DEBUG()
{
  boolean Exec_Loop_PodeSair = false;

  unsigned long time_inicio;
  unsigned long time_atual;
  unsigned long time_tempo_passado;

  int SegundosPassados;
  int Last_SegundosPassados;
  
  time_inicio = millis();

  while (Exec_Loop_PodeSair == false)
  {

    time_atual = millis();
    time_tempo_passado = time_atual - time_inicio;

    SegundosPassados = floor(time_tempo_passado / 1000);
    
    if (SegundosPassados != Last_SegundosPassados)
    {
      LogTerm(SegundosPassados);
    }
    
    
    
    if (time_tempo_passado >= gTimeoutOpcao)
    {
      Exec_Loop_PodeSair = true;
    }

    Last_SegundosPassados = SegundosPassados;


    //delay(500);

  }
}


    
    

    








// Rotina que executa o procedimento de stand by
void Exec_TESTE()
{

  boolean Exec_Loop_PodeSair = false;

  LogTerm("Exec_TESTE");

  //ShowExample_Tela();

  // TELA_IniciaTela();

  // TELA_Texto("Linha1cccc");
  // TELA_Texto("Linha2");
  // TELA_Texto("Linha3");
  // TELA_Texto("Linha4");
  // TELA_Texto("Linha5");
  // TELA_Texto("Linha6");
  // TELA_Texto("Linha7");



  while (Exec_Loop_PodeSair == false)
  {
    LogTerm("Exec_TESTE");
    delay(500);

  }
}




// ROTINA DE STANDBY
void Exec_STANDBY()
{
  //TestaInterrupts();
  LogTerm("Exec_STANDBY");
  //delay(500);

  if (tft.touchDetect())
  {
    TELA_Texto("Entrando em modo LOGIN");

    gModoOperacao = "LOGIN";
  }
}


volatile uint8_t lastflowpinstate;

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

  /*
  int buttonState1 = LOW;  
  int buttonState2 = LOW;  
  int buttonState3 = LOW;  
  int buttonState4 = LOW;  

  buttonState1 = digitalRead(BOTAO1_PINO);
  buttonState2 = digitalRead(BOTAO2_PINO);
  buttonState3 = digitalRead(BOTAO3_PINO);
  buttonState4 = digitalRead(BOTAO4_PINO);


  if (buttonState1 == HIGH) 
  {

    LogTerm("Botao apertado 1 -- pino 2 ! ");
    //LogTerm("Botao apertado 1 -- pino 2 ! -- Exec_LOGIN");

    //gModoOperacao = "LOGIN";
  
    
    ApagaConteudoSD();

    LogTerm("Modo: == StandBy ==");
    gModoOperacao = "STANDBY";
    


  }

  if (buttonState2 == HIGH) 
  {
    LogTerm("Botao apertado 2 -- pino 3 ! -- Exec_ADMIN");
    
    gModoOperacao = "ADMIN";
  }



  if (buttonState3 == HIGH) 
  {
    LogTerm("Botao apertado 3 -- pino 4! -- Exec_DEBUG");
    
    if (EstadoBotao_Rele1 == 1)
    {
      digitalWrite(gPinoRele_3, HIGH);
      EstadoBotao_Rele1 = 0;
      delay(300);
    }
    else
    {
      digitalWrite(gPinoRele_3, LOW);
      EstadoBotao_Rele1 = 1;
      delay(300);
    }
    

    //gModoOperacao = "DEBUG";
  }


  lastflowpinstate = 0;
  lastflowpinstate = digitalRead(38);
  LogTerm(lastflowpinstate);


  if (buttonState4 == HIGH) 
  {
    LogTerm("Botao apertado 4 -- pino 5! -- Exec_OPERACAO");
    
    gModoOperacao = "OPERACAO";
  }

  */

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

  delay(50);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (gModoOperacao == "INICIO")
  {
    LogTerm("Modo: INICIO");

    Exec_INICIO();

    LogTerm("Modo: == StandBy ==");
    gModoOperacao = "STANDBY";

        
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (gModoOperacao == "STANDBY")
  {
    
    Exec_STANDBY();

  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (gModoOperacao == "LOGIN")
  {
    LogTerm("Modo: LOGIN");

    Exec_LOGIN();
    
    LogTerm("Modo: == StandBy ==");
    gModoOperacao = "STANDBY";

    
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (gModoOperacao == "OPERACAO")
  {
    LogTerm("Modo: OPERACAO");
    
    //gModoOperacao = 4;  // Standby

    Exec_OPERACAO();
    
    LogTerm("Modo: == StandBy ==");
    gModoOperacao = "STANDBY";

  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (gModoOperacao == "ADMIN")
  {
    LogTerm("Modo: ADMIN");

    Exec_ADMIN();
    
    LogTerm("Modo: == StandBy ==");
    gModoOperacao = "STANDBY";
    
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (gModoOperacao == "DEBUG")
  {
    LogTerm("Modo: DEBUG");

    Exec_DEBUG();
    
    LogTerm("Modo: == StandBy ==");
    gModoOperacao = "STANDBY";
      
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
 if (gModoOperacao == "INSTALACAO")
  {
    LogTerm("Modo: INSTALACAO");

    Exec_INSTALACAO();
    
    LogTerm("Modo: == StandBy ==");
    gModoOperacao = "STANDBY";
      
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  

}

