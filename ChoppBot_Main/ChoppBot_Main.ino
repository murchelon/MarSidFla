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


  Serial.begin(115200);
  
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

  
  


  //BIOMETRICO_Inicia();
  



  // todo: inicializa hardware, fecha valvulas, etc
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  EXEC_INICIO
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    
// ROTINA DE INICIO
void Exec_INICIO()
{

    //Led_Light(true);
    
    //SD_Init();

    //ShowExample_DB();

    //Init_Database();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  EXEC_INSTALACAO
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   

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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  EXEC_LOGIN
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   


// ROTINA DE LOGIN
void Exec_LOGIN()
{

    TELA_Render_Interface_LOGIN();

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  EXEC_OPERACAO
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   


// ROTINA DE OPERACAO
void Exec_OPERACAO()
{

  TELA_Render_Interface_OPERACAO();

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  EXEC_ADMIN
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   



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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  EXEC_DEBUG
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   



// ROTINA DE DEBUG
void Exec_DEBUG()
{
  TELA_Render_Interface_TECLADO(500, 56);   // posicao x e y
}


    
    

    

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  EXEC_TESTE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   






// Rotina que executa o procedimento de TESTE
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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  EXEC_STANDBY
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   

// ROTINA DE STANDBY
void Exec_STANDBY()
{

  TELA_Render_Interface_STANDBY();

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




// Procedure que testa se ocorreu algum interrupt: O sistema fica em modo StandBy ate que alguem toque na tela, ou faca alguma outra acao que gere uma interrupcao
void TestaInterrupts()
{



  if (gModoOperacao == "INICIO")
  {

  }

  if (gModoOperacao == "INSTALACAO")
  {

  }

  if (gModoOperacao == "STANDBY")
  {
    TELA_VerificaTouch_STANDBY();
  }
  
  if (gModoOperacao == "LOGIN")
  {
    TELA_VerificaTouch_LOGIN();
  }
  
  if (gModoOperacao == "OPERACAO")
  {
    TELA_VerificaTouch_OPERACAO();
  }

  if (gModoOperacao == "ADMIN")
  {

  }

  if (gModoOperacao == "DEBUG")
  {
    TELA_VerificaTouch_DEBUG();
  }

  if (gModoOperacao == "TESTE")
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

  delay(50);

  TestaInterrupts();


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (gModoOperacao == "INICIO")
  {
    LogTerm("Modo: INICIO");

    Exec_INICIO();

    
    gModoOperacao = "STANDBY";
    LogTerm("Modo: == StandBy ==");
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
    
    //LogTerm("Modo: == StandBy ==");
    //gModoOperacao = "STANDBY";

    
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (gModoOperacao == "OPERACAO")
  {
    LogTerm("Modo: OPERACAO");
    
    //gModoOperacao = 4;  // Standby

    Exec_OPERACAO();


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
    //LogTerm("Modo: DEBUG -- teclado");

    Exec_DEBUG();
      
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

