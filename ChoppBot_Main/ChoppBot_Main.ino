/*
  ChoppBot 1.0

  By Marcelo Rocha, Sidnei Conrad and Flavio Liberal

  Main program to an automated chopp dispenser with several
  features like touchscreen, biometrical recognition and RFID
  recognition. More to came....
  teste chopp 
*/



#include "BIB/Main/ChoppBot_IncludeGeral.h" 






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




    Serial.begin(115200);       // 115200 pois o RFID precisa desta velocidade, para acompanharmos o que ele escreve no serial


    // Wait for USB Serial 
    while (!Serial) 
    {
        SysCall::yield();
    }



    InicializaVars();



    LogTerm(F("/////////////////////////////////////////////////////"));
    LogTerm(F("///                                               ///"));
    LogTerm(String(F("///  ChoppBot ")) + String(VersaoAPP) + String(F("                                 ///")));
    LogTerm(F("///  ============                                 ///"));
    LogTerm(F("///                                               ///"));
    LogTerm(F("///  by Murch & Cebola                            ///"));
    LogTerm(F("///                                               ///"));
    LogTerm(F("///  Hardware: Margarida 2                        ///"));
    LogTerm(F("///                                               ///"));
    LogTerm(F("/////////////////////////////////////////////////////"));
    LogTerm(F(""));
    LogTerm(F("MAIN: Iniciando sistema..."));


    
    LED_SetLedState(F("BUILTIN"), false, F(""));


    // da uma piscada no led interno para demonstrar inicio
    for (int x = 0 ; x <= 10 ; x++)
    {
        LED_SetLedState(F("BUILTIN"), false, F(""));
        delay(40);
        LED_SetLedState(F("BUILTIN"), true, F(""));
        delay(40);
        //LogTerm(F("ok to aqui"));
    }

    LED_SetLedState(F("BUILTIN"), false, F(""));



    // Inicia o LED do rfid
    pinMode(ctPINO_LED_CORFIXA, OUTPUT);


    // inicia o led interno arduino, usado para mostrar que o programa esta rodando
    pinMode(LED_BUILTIN, OUTPUT);

    // Inicia o BUZZER
    pinMode(BUZZER_PINO, OUTPUT);



    // Inicia os RELES e FLOWMETERS
    if (RELE_PINO_TORNEIRA_1 != 0)
    {
        pinMode(RELE_PINO_TORNEIRA_1, OUTPUT);
        digitalWrite(RELE_PINO_TORNEIRA_1, HIGH);

        digitalWrite(FLOW_PINO_SENSOR_1, HIGH);         
        pinMode(FLOW_PINO_SENSOR_1, INPUT);
    }

    if (RELE_PINO_TORNEIRA_2 != 0)
    {
        pinMode(RELE_PINO_TORNEIRA_2, OUTPUT);
        digitalWrite(RELE_PINO_TORNEIRA_2, HIGH);

        digitalWrite(FLOW_PINO_SENSOR_2, HIGH);         
        pinMode(FLOW_PINO_SENSOR_2, INPUT);
    }

    if (RELE_PINO_TORNEIRA_3 != 0)
    {
        pinMode(RELE_PINO_TORNEIRA_3, OUTPUT);
        digitalWrite(RELE_PINO_TORNEIRA_3, HIGH);

        digitalWrite(FLOW_PINO_SENSOR_3, HIGH);         
        pinMode(FLOW_PINO_SENSOR_3, INPUT);
    }

    if (RELE_PINO_TORNEIRA_4 != 0)
    {
        pinMode(RELE_PINO_TORNEIRA_4, OUTPUT);
        digitalWrite(RELE_PINO_TORNEIRA_4, HIGH);

        digitalWrite(FLOW_PINO_SENSOR_4, HIGH);         
        pinMode(FLOW_PINO_SENSOR_4, INPUT);
    }

    if (RELE_PINO_TORNEIRA_5 != 0)
    {
        pinMode(RELE_PINO_TORNEIRA_5, OUTPUT);
        digitalWrite(RELE_PINO_TORNEIRA_5, HIGH);

        digitalWrite(FLOW_PINO_SENSOR_5, HIGH);         
        pinMode(FLOW_PINO_SENSOR_5, INPUT);
    }

    if (RELE_PINO_TORNEIRA_6 != 0)
    {
        pinMode(RELE_PINO_TORNEIRA_6, OUTPUT);
        digitalWrite(RELE_PINO_TORNEIRA_6, HIGH);

        digitalWrite(FLOW_PINO_SENSOR_6, HIGH);         
        pinMode(FLOW_PINO_SENSOR_6, INPUT);
    }

    if (RELE_PINO_TORNEIRA_7 != 0)
    {
        pinMode(RELE_PINO_TORNEIRA_7, OUTPUT);
        digitalWrite(RELE_PINO_TORNEIRA_7, HIGH);

        digitalWrite(FLOW_PINO_SENSOR_7, HIGH);         
        pinMode(FLOW_PINO_SENSOR_7, INPUT);
    }

    if (RELE_PINO_TORNEIRA_8 != 0)
    {
        pinMode(RELE_PINO_TORNEIRA_8, OUTPUT);
        digitalWrite(RELE_PINO_TORNEIRA_8, HIGH);

        digitalWrite(FLOW_PINO_SENSOR_8, HIGH);         
        pinMode(FLOW_PINO_SENSOR_8, INPUT);
    }

    if (RELE_PINO_TORNEIRA_9 != 0)
    {
        pinMode(RELE_PINO_TORNEIRA_9, OUTPUT);
        digitalWrite(RELE_PINO_TORNEIRA_9, HIGH);

        digitalWrite(FLOW_PINO_SENSOR_9, HIGH);         
        pinMode(FLOW_PINO_SENSOR_9, INPUT);
    }

    if (RELE_PINO_TORNEIRA_10 != 0)
    {
        pinMode(RELE_PINO_TORNEIRA_10, OUTPUT);
        digitalWrite(RELE_PINO_TORNEIRA_10, HIGH);

        digitalWrite(FLOW_PINO_SENSOR_10, HIGH);         
        pinMode(FLOW_PINO_SENSOR_10, INPUT);
    }





    // Inicia o SD
    digitalWrite(SD_MAX_TENTATIVA_READ, HIGH);
    digitalWrite(SD_DELAY_TENTATIVA_READ, HIGH);
    digitalWrite(SD_PINO, HIGH);



    // Inicia RFID
    digitalWrite(RFID_PINO_SCK, HIGH);
    digitalWrite(RFID_PINO_MOSI, HIGH);
    digitalWrite(RFID_PINO_SS, HIGH);
    digitalWrite(RFID_PINO_MISO, HIGH);
    digitalWrite(RFID_PINO_IRQ, HIGH);
    digitalWrite(RFID_PINO_RESET, HIGH);



    delay(500);

    TELA_IniciaTela();

    TELA_Texto(String(F("Choppbot ")) + String(VersaoAPP), F("VERDE"));
    TELA_Texto(F("============"), F("VERDE"));
    TELA_Texto(F(""), F("BRANCO"));
    TELA_Texto(F("Iniciando sistema..."), F("BRANCO"));
    TELA_Texto(F(""), F("BRANCO"));




    /*
    String retFunc = F("");

    String FullPathFile_TEMP;   
    FullPathFile_TEMP = String(F("CB/BD/Chopp/EngatadosN.csv"));

    String FullPathFile_ORIGINAL;   
    FullPathFile_ORIGINAL = String(F("CB/BD/Chopp/Engatados.csv"));

    LogTerm(F("Apagando arquivo Engatados.csv ..."));
    retFunc = SD_ApagaArquivo(FullPathFile_ORIGINAL);
    delay(100);

    LogTerm(F("Copiando arquivo Engatados.csv original ..."));
    retFunc = SD_CopiaArquivo(FullPathFile_TEMP, FullPathFile_ORIGINAL);
    LogTerm(String(F("SD_CopiaArquivo = ")) + retFunc);
    delay(100);

    */





    CORE_ExecRotinaDefineChoppEngatados();
    
    BUZZER_TocaSom(F("LIGAR"));


    //BIOMETRICO_Inicia();




    // todo: inicializa hardware, fecha valvulas, etc

    LogTerm(F("MAIN: Sistema Inicializado."));



    if (ctTELA_HARDWARE == String(F("ER-TFTM070-5")))
    {
        TELA_LimpaTela();
    }




    


    /*

    String ret = F("");

    String FullPathFile_TEMP;   
    FullPathFile_TEMP = String(F("CB/BD/Usuarios/TUSU_1.csv"));

    String FullPathFile_ORIGINAL; 
    FullPathFile_ORIGINAL = String(F("CB/BD/Usuarios/USU_1.csv"));  


    
    String retFunc = F("");
    retFunc = SD_RenameArquivo(FullPathFile_TEMP, FullPathFile_ORIGINAL);


    if (retFunc.substring(0, 1) == F("0"))
    {
        // arquivo temporario antigo localizado
        LogTerm(String(F("Falha em renomear arquivo temporario de usuario para o final: ")) + retFunc);

        ret = F("0|Falha na atualizacao de saldo do usuario");
    }
    else
    {
        LogTerm(String(F("Arquivo temporario de usuario renomeado com sucesso para versao final: ")) + retFunc);

        ret = F("1|Saldo atualizado com sucesso");
    }




    while (1)
    {}
    */

     /*

    gServico_ID_TorneiraAtual = 9;
    gSessao_IDUser = 1;
    gSessao_Nome = F("murchelongo");
    gSessao_CPF = F("xxx25632071855");
    gSessao_DataCad = F("03/06/1977");
    gSessao_SaldoAtual = 999;
    gFlow_Pulses_Corrigido_Atual = 9999;



    String tmp_IDChopp = F("9");
    String tmp_Nome = F("xxxTartatuga de Pente");
    String tmp_Valor = F("55,24");
    float liters_Atual = 0.22;
    float ValorSessaoChopp = 15.12;
    float ValorSaldoAtual = 12.34;
    float VolumeAtual = 56.78;

    String retFunc = F("");
    retFunc = BANCO_AtualizaSaldoUserLogado(tmp_IDChopp,
                                            tmp_Nome,
                                            tmp_Valor,
                                            liters_Atual,
                                            ValorSessaoChopp,
                                            ValorSaldoAtual,
                                            VolumeAtual
                                            );

    if (retFunc.substring(0, 1) == F("1"))
    {
        LogTerm(F("Saldo/Sessao de usuario atualizado com sucesso !"));
    }
    else
    {
        LogTerm(String(F("Falha na atualizacao do Saldo/Sessao: ")) + retFunc);
    }


    while (1)
    {}

    */



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

    LogTerm(F("== [Modo Atual: INICIO] =="));

    
    gModoOperacao = F("STANDBY");



    //TELA_Render_MsgBox(F(""), "X");
    //TELA_Render_MsgBox("Meu nome e MARCELO wef webfwef dd d dX");
    //TELA_Render_MsgBox("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456");
    //TELA_Render_MsgBox("12345678901234567890!@#$%^&*()abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

    //TELA_Render_MsgBox("Ola! Meu nome e MARCELO ROCHA. Eu estou verificando o tamanho desta caixa de msgbox para que seja possivel escerever um texto demasiadamente grande sem problemas. Obrigado.");
    //TELA_Render_MsgBox("Super teste de Janela", "Ola! Meu nome e MARCELO ROCHA.^Eu estou verificando o tamanho desta caixa de msgbox^para que seja possivel escerever um texto demasiadamente grande sem problemas. Obrigado.^^Teste^opa");
    //TELA_Render_MsgBox("Teste de Enter", "Teste de oula linha:^Linha2");

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

    if (gTelaRenderizada_INSTALACAO == false)
    {
        LogTerm(F("== [Modo Atual: INSTALACAO] =="));
    }  

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
    if (gTelaRenderizada_LOGIN == false)
    {
        LogTerm(F("== [Modo Atual: LOGIN] =="));
    }  

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
    if (gTelaRenderizada_OPERACAO == false)
    {
        LogTerm(F("== [Modo Atual: OPERACAO] =="));
    }  

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

    if (gTelaRenderizada_ADMIN == false)
    {
        LogTerm(F("== [Modo Atual: ADMIN] =="));
    }  

    TELA_Render_Interface_ADMIN();

}






// ROTINA DE ADMIN
void Exec_ADMIN_VERY_OLD()
{

    
    boolean Exec_Loop_PodeSair = false;

    unsigned long time_inicio;
    unsigned long time_atual;
    unsigned long time_tempo_passado;

    int SegundosPassados;
    int Last_SegundosPassados;

    if (gTelaRenderizada_ADMIN == false)
    {
        LogTerm(F("== [Modo Atual: ADMIN] =="));
    }  

    gTelaRenderizada_ADMIN = true;


    time_inicio = millis();

    TELA_Texto(String(F("MODO ADMIN: Saindo em ")) + String(gTimeoutOpcao / 1000) + String(F(" segundos...")), F("BRANCO"));

    while (Exec_Loop_PodeSair == false)
    {


        time_atual = millis();
        time_tempo_passado = time_atual - time_inicio;

        SegundosPassados = floor(time_tempo_passado / 1000);



        if (SegundosPassados != Last_SegundosPassados)
        {
            //LogTerm(SegundosPassados);
            TELA_Texto(String(SegundosPassados), F("AMARELO"));
        }



        if (time_tempo_passado >= gTimeoutOpcao)
        {
            Exec_Loop_PodeSair = true;
        }

        Last_SegundosPassados = SegundosPassados;

        //delay(500);
    }


    if (ctTELA_HARDWARE == String(F("ER-TFTM070-5")))
    {
        TELA_LimpaTela();
    }

    
    gTelaRenderizada_ADMIN = false;
    gModoOperacao = F("STANDBY");


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
    if (gTelaRenderizada_DEBUG == false)
    {
        LogTerm(F("== [Modo Atual: DEBUG] =="));
    }  

    gTelaRenderizada_DEBUG = true;

    //TELA_RenderTecUnificado_NUM();
    TELA_RenderTecUnificado_ALFA();

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

    if (gTelaRenderizada_TESTE == false)
    {
        LogTerm(F("== [Modo Atual: TESTE] =="));
    }  

    boolean Exec_Loop_PodeSair = false;

    LogTerm(F("Exec_TESTE"));

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
        LogTerm(F("Exec_TESTE"));
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
    if (gTelaRenderizada_STANDBY == false)
    {
        LogTerm(F("== [Modo Atual: STANDBY] =="));
    }    
    

    TELA_Render_Interface_STANDBY();

    

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  ROTINAS SECUNDARIAS (Rotinas como tela para edicao de dados, ler rfid, etc)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   


void Exec_LER_RFID()
{
    if (gTelaRenderizada_LER_RFID == false)
    {
        LogTerm(F("== [Modo Atual: LOGIN -- SubTela: LER_RFID] =="));
        TELA_Render_Interface_LER_RFID();
    }  

    

}


void Exec_OPERACAO_SERVICO()
{
    

    if (gTelaRenderizada_OPERACAO_SERVICO == false)
    {
        LogTerm(F("== [Modo Atual: OPERACAO -- SubTela: OPERACAO_SERVICO] =="));
        TELA_Render_Interface_OPERACAO_SERVICO();
    }  

    

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




// Procedure que testa se ocorreu algum interrupt: O sistema fica em modo StandBy ate que alguem toque na tela, ou faca alguma outra acao que gere uma interrupcao
void TestaInterrupts()
{



    if (gModoOperacao == F("INICIO"))
    {

    }

    if (gModoOperacao == F("INSTALACAO"))
    {

    }

    if (gModoOperacao == F("STANDBY"))
    {
        
        TELA_VerificaTouch_STANDBY();
        
    }

    if (gModoOperacao == F("LOGIN"))
    {

        if (gModoOperacao_SubTela == F(""))
        {
            TELA_VerificaTouch_LOGIN();
        }

        if (gModoOperacao_SubTela == F("LER_RFID"))
        {
            TELA_VerificaTouch_LER_RFID();
        }

        
    }

    if (gModoOperacao == F("OPERACAO"))
    {



        if (gModoOperacao_SubTela == F(""))
        {
            TELA_VerificaTouch_OPERACAO();
        }

        if (gModoOperacao_SubTela == F("OPERACAO_SERVICO"))
        {
            TELA_VerificaTouch_OPERACAO_SERVICO();
        }

        
    }

    if (gModoOperacao == F("ADMIN"))
    {


        if (gModoOperacao_SubTela == F(""))
        {
            TELA_VerificaTouch_ADMIN();
        }

        if (gModoOperacao_SubTela == F("ADMIN_1"))
        {
            TELA_VerificaTouch_ADMIN();
        }

    }

    if (gModoOperacao == F("DEBUG"))
    {
        TELA_VerificaTouch_DEBUG();
    }

    if (gModoOperacao == F("TESTE"))
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
void setup()
{  
    InitApp();  
}


// INTERNA ARDUINO: LOOP ETERNO
void loop() 
{

    
    //Led_Light(false);

    delay(50);

    //debug:
    //delay(1000);

    ExecLedON_Beat();

    //Led_Light(true);
    //LogTerm(F("estou no loop");




    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (gModoOperacao == F("INICIO"))
    {
        Exec_INICIO();       
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (gModoOperacao == F("STANDBY"))
    {
        Exec_STANDBY();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (gModoOperacao == F("LOGIN"))
    {

        if (gModoOperacao_SubTela == F(""))
        {
            Exec_LOGIN();  
        }
        
       if (gModoOperacao_SubTela == F("LER_RFID"))
        {
            Exec_LER_RFID();  
        }        

    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (gModoOperacao == F("OPERACAO"))
    {

        if (gModoOperacao_SubTela == F(""))
        {
            Exec_OPERACAO();  
        }
        
       if (gModoOperacao_SubTela == F("OPERACAO_SERVICO"))
        {
            Exec_OPERACAO_SERVICO();  
        }        

    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (gModoOperacao == F("ADMIN"))
    {

        if (gModoOperacao_SubTela == F(""))
        {
            Exec_ADMIN();  
        }
        
       if (gModoOperacao_SubTela == F("ADMIN_1"))
        {
            Exec_ADMIN();  
        }   

    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (gModoOperacao == F("DEBUG"))
    {
        Exec_DEBUG();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    if (gModoOperacao == F("INSTALACAO"))
    {
        LogTerm(F("Modo: INSTALACAO"));

        Exec_INSTALACAO();

        LogTerm(F("Modo: == StandBy =="));
        gModoOperacao = F("STANDBY");

    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TestaInterrupts();

}

