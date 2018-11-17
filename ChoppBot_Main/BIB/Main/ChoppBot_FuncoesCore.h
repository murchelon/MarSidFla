



void CORE_PrintChoppEngatados()
{


    LogTerm(F("====  Engates  ===================="));


    // NumTorneira;DataCad;IDChopp;VolumeAtual;DataExpira;Ativa;NomeFromBanco
    for (int x = 0 ; x <= ctMAX_TORNEIRAS ; x++)
    {

        if (gaEngatados[x] != F(""))
        {


            String tmp_IDChopp = getValue(gaEngatados[x], ';', 2);
            String tmp_Nome = getValue(gaEngatados[x], ';', 7);
            String tmp_Tipo = getValue(gaEngatados[x], ';', 8);
            String tmp_Valor = getValue(gaEngatados[x], ';', 9);
            String tmp_Volume = getValue(gaEngatados[x], ';', 3);
            //tmp_DataCad = getValue(gaEngatados[x], ';', 1);
            //tmp_DataExp = getValue(gaEngatados[x], ';', 4);
            String tmp_Ativa = getValue(gaEngatados[x], ';', 5);

            //LogTerm(gaEngatados[x]);

            if (tmp_IDChopp != F(""))
            {
                LogTerm(String(F("Torneira [")) + String(x) + String(F("] -- IDChopp: ")) + tmp_IDChopp);
                LogTerm(String(F("Torneira [")) + String(x) + String(F("] -- Nome: ")) + tmp_Nome);
                LogTerm(String(F("Torneira [")) + String(x) + String(F("] -- Tipo: ")) + tmp_Tipo);
                LogTerm(String(F("Torneira [")) + String(x) + String(F("] -- Valor: ")) + tmp_Valor);
                LogTerm(String(F("Torneira [")) + String(x) + String(F("] -- Volume Atual: ")) + tmp_Volume);
                //LogTerm(F("Torneira [" + String(x) + "] -- Data de Cadastro: " + tmp_DataCad);
                //LogTerm(F("Torneira [" + String(x) + "] -- Data de Expiracao: " + tmp_DataExp);

                if (tmp_Ativa == F("1"))
                {
                    LogTerm(String(F("Torneira [")) + String(x) + String(F("] -- Ativa: SIM")));
                }
                else
                {
                    LogTerm(String(F("Torneira [")) + String(x) + String(F("] -- Ativa: NAO"))); 
                }      
                
                LogTerm(F("---------------------------"));          
            }


            
            

        }


    }    
}




// Rotina que define os chopps engatados na variavel global , a partir do arquivo engatados.txt e ainda exibe no terminal os chopps disponiveis
// deve ser chamada sempre que for desejado atualizar a variavel global com os chopps engataods, logo depois de uma sessao, com o saldo atualizado do barril
void CORE_ExecRotinaDefineChoppEngatados()
{

    String retEngatados = "";

    retEngatados = BANCO_DefineChoppEngatados(gaEngatados);  

    if (retEngatados.substring(0, 1) != "1") 
    {

        BUZZER_TocaSom(F("ERRO"));


        LogTerm(F("MAIN: Falha ao carregar arquivo com os chopps engatados"));
        LogTerm(String(F("MAIN: Erro: ")) + retEngatados.substring(3));
        LogTerm(F("MAIN: Fallha critica. O sistema sera reiniciado em 10 segundos..."));

        if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
        {       
            TELA_Texto(F("MAIN: Falha ao carregar arquivo com os chopps engatados"), F("BRANCO"));
            TELA_Texto(String(F("MAIN: Erro: ")) + retEngatados.substring(3), F("AMARELO"));
            TELA_Texto(F("MAIN: Fallha critica. O sistema sera reiniciado em 10 segundos..."), F("BRANCO"));
        }


        delay(10000);
        ResetArduino();       
    }

    

    CORE_PrintChoppEngatados();



}
