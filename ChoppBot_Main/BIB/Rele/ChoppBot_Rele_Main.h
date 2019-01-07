


#define Range_Menos 10
#define Range_Mais 10

#define ctDEBUG_FLUXO_CURVA 1



// Interrupt is called once a millisecond, looks for any Flow_Pulses_1 from the sensor!
/*

SIGNAL(TIMER0_COMPA_vect) 
{
	uint8_t x = digitalRead(FLOW_PINO_SENSOR_1);

	if (x == lastflowpinstate_1)
	{
		lastflowratetimer_1++;
		return; // nothing changed!
	}

	if (x == HIGH) 
	{
		//low to high transition!
		Flow_Pulses_1++;
	}

	lastflowpinstate_1 = x;
	flowrate_1 = 1000.0;
	flowrate_1 /= lastflowratetimer_1;  // in hertz
	lastflowratetimer_1 = 0;

	
}

*/


SIGNAL(TIMER1_COMPA_vect)
{
  
	uint8_t x1 = digitalRead(gPinoSensorFluxoAtivo);

	if (x1 == gLastflowpinstate_Atual) 
	{
		gLastflowratetimer_Atual++;
		return; // nothing changed!
	}


	if (x1 == HIGH) 
	{
		//low to high transition!
		gFlow_Pulses_Atual++;
		gFlow_Pulses_Corrigido_Atual++;
	}

	//Flow_Pulses_Corrigido_2 = Flow_Pulses_2;

	gLastflowpinstate_Atual = x1;
	gFlowrate_Atual = 1000.0;
	gFlowrate_Atual /= gLastflowratetimer_Atual;  // in hertz
	gLastflowratetimer_Atual = 0;

	//LogTerm(String(F("######## --- gFaixaVelAtual = ")) + String(gFaixaVelAtual));

	if (gFaixaVelAtual == -5)
	{
		gFlow_Pulses_Corrigido_Atual = gFlow_Pulses_Corrigido_Atual + 0.06;		
	}

	if (gFaixaVelAtual == -4)
	{
		//gFlow_Pulses_Corrigido_Atual = gFlow_Pulses_Corrigido_Atual + 1.5;		
		gFlow_Pulses_Corrigido_Atual = gFlow_Pulses_Corrigido_Atual + 0.05;		
	}

	if (gFaixaVelAtual == -3)
	{
		gFlow_Pulses_Corrigido_Atual = gFlow_Pulses_Corrigido_Atual + 0.02;	
	}

	if (gFaixaVelAtual == -2)
	{
		gFlow_Pulses_Corrigido_Atual = gFlow_Pulses_Corrigido_Atual + 0.01;		
	}

	/*
	if (gFaixaVelAtual == -1)
	{
		gFlow_Pulses_Corrigido_Atual = gFlow_Pulses_Corrigido_Atual + 0;		
	}

	if (gFaixaVelAtual == 0)		// IDEAL
	{
		gFlow_Pulses_Corrigido_Atual = gFlow_Pulses_Corrigido_Atual;		
	}

	if (gFaixaVelAtual == 1)
	{
		gFlow_Pulses_Corrigido_Atual = gFlow_Pulses_Corrigido_Atual - 0;		
	}

	if (gFaixaVelAtual == 2)
	{
		gFlow_Pulses_Corrigido_Atual = gFlow_Pulses_Corrigido_Atual - 0;		
	}

	if (gFaixaVelAtual == 3)
	{
		gFlow_Pulses_Corrigido_Atual = gFlow_Pulses_Corrigido_Atual - 0;		
	}

	if (gFaixaVelAtual == 4)
	{
		gFlow_Pulses_Corrigido_Atual = gFlow_Pulses_Corrigido_Atual - 0;		
	}

	if (gFaixaVelAtual == 5)
	{
		gFlow_Pulses_Corrigido_Atual = gFlow_Pulses_Corrigido_Atual - 0;		
	}
	*/
}


/*


SIGNAL(TIMER2_COMPA_vect) 
{
  
	uint8_t x2 = digitalRead(FLOW_PINO_SENSOR_3);

	if (x2 == lastflowpinstate_3) 
	{
		lastflowratetimer_3++;
		return; // nothing changed!
	}


	if (x2 == HIGH)
	{
		//low to high transition!
		Flow_Pulses_3++;
	}


	lastflowpinstate_3 = x2;
	flowrate_3 = 1000.0;
	flowrate_3 /= lastflowratetimer_3;  // in hertz
	lastflowratetimer_3 = 0;
}

*/

// void useInterrupt________________________________________

/*
void useInterrupt_1(boolean v) 
{
	if (v) 
	{
		// Timer0 is already used for millis() - we'll just interrupt somewhere
		// in the middle and call the "Compare A" function above
		OCR0A = 0xAF;
		TIMSK0 |= _BV(OCIE0A);
	} 
	else 
	{
		// do not call the interrupt function COMPA anymore
		TIMSK0 &= ~_BV(OCIE0A);
	}
}

*/

void useInterrupt_2(boolean c) 
{
	if (c)
	{
		// Timer0 is already used for millis() - we'll just interrupt somewhere
		// in the middle and call the "Compare A" function above
		OCR1A = 0xAF;
		TIMSK1 |= _BV(OCIE1A);
	} 
	else 
	{
		// do not call the interrupt function COMPA anymore
		TIMSK1 &= ~_BV(OCIE1A);
	}
} 


/*
void useInterrupt_3(boolean b) 
{
	if (b) 
	{
		// Timer0 is already used for millis() - we'll just interrupt somewhere
		// in the middle and call the "Compare A" function above
		OCR2A = 0xAF;
		TIMSK2 |= _BV(OCIE2A);
	} 
	else 
	{
		// do not call the interrupt function COMPA anymore
		TIMSK2 &= ~_BV(OCIE2A);
	}
} 
*/


void TELA_Render_ExibeMsgSaldoZerado()
{
	TELA_LimpaTela();

	TELA_Texto_Centralizado(F("Nao existe mais saldo para retirada de chopp"), F("AMARELO"), 1, 150);
	TELA_Texto_Centralizado(F("Por favor, carregue seu cartao no caixa"), F("AMARELO"), 1, 250);

	delay(4000);
}




void TELA_VerificaTouch_OPERACAO_SERVICO()
{


	if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
	{  

		if (TELA_touchDetect())
		{

			TELA_touchReadPixel(&gTouch_X, &gTouch_Y);



			if (gModoOperacao == F("ADMIN"))
			{



				for (int ContaBotaoGen = 1 ; ContaBotaoGen <= ctMAX_BOTOES_GEN_TELA; ContaBotaoGen++)
				{
					if (gaBotoesGenTela[ContaBotaoGen - 1] != F(""))
					{
					
						//LogTerm( String(F("gaBotoesGenTela[")) + String(ContaBotaoGen - 1) + String(F("] = ")) + gaBotoesGenTela[ContaBotaoGen - 1] );

						String btnGen_TAG = 	getValue(gaBotoesGenTela[ContaBotaoGen - 1], ';', 1);
						String btnGen_PosX = 	getValue(gaBotoesGenTela[ContaBotaoGen - 1], ';', 3);
						String btnGen_PosY = 	getValue(gaBotoesGenTela[ContaBotaoGen - 1], ';', 4);
						String btnGen_W = 		getValue(gaBotoesGenTela[ContaBotaoGen - 1], ';', 5);
						String btnGen_H = 		getValue(gaBotoesGenTela[ContaBotaoGen - 1], ';', 6);



						if (gTouch_X >= btnGen_PosX.toInt() && gTouch_X <= btnGen_W.toInt() + btnGen_PosX.toInt())  
						{

							if (gTouch_Y >= btnGen_PosY.toInt() && gTouch_Y <= btnGen_H.toInt() + btnGen_PosY.toInt()) 
							{


								// Esquema de DEBounce ---- inicio

								gBounce_ContaClick++;
								

								if (gBounce_ContaClick == 1)
								{
									// Local onde deve ocorrer o evento do clique. Ocorrera apenas 1 vez --------

				
									LogTerm(String(F("BOTAO GENERICO ")) + String(ContaBotaoGen) + String(F(" APERTADO")) + String(F(" (")) + btnGen_TAG + String(F(")"))  );


									//BOTAO SAIR
									if (btnGen_TAG == F("VOLTAR"))
									{

										TELA_LimpaTela();

										//gModoOperacao = F("ADMIN");
										gModoOperacao_SubTela = F("ADMIN_SANGRIA");		

										//gTelaRenderizada_ADMIN = false;	
										gTelaRenderizada_ADMIN_SANGRIA = false;	

										// fecha a torneira
									    //digitalWrite(gPinoReleTorneiraAtiva, HIGH);
										//useInterrupt_2(false);
										//LED_SetLedState(F("RGB"), false, F(""));
										//delay(50);

										/*
										// zera as vars para cada tentativa de login
										// efetua logoff
										gSessao_Logado = false;
										gSessao_IDUser = -1;
										gSessao_Nome = F("");
										gSessao_Nivel = -1;
										gSessao_SaldoAtual = -1;

										gTelaRenderizada_ADMIN = false;	

										gModoOperacao = F("STANDBY");  
										gModoOperacao_SubTela = F("");						
									
										LogTerm(F("MAIN: Usuario clicou em SAIR"));

										*/

									}

		
									// -----------------------------------

									gBounce_time_inicio = millis();

								}


								gBounce_time_atual = millis();
								gBounce_time_tempo_passado = gBounce_time_atual - gBounce_time_inicio;

								gBounce_SegundosPassados = floor(gBounce_time_tempo_passado / 1000);

								//LogTerm(gBounce_time_tempo_passado);

								if (gBounce_SegundosPassados != gBounce_Last_SegundosPassados)
								{
									//LogTerm(time_tempo_passado);
								}



								if (gBounce_time_tempo_passado >= ctBOUNCE_SENSIB_BOTAO)
								{
									gBounce_ContaClick = 0;	
								}

								gBounce_Last_SegundosPassados = gBounce_SegundosPassados;

								// Esquema de DEBounce ---- FIM



							}

						}


					}
				}	    							 



			}




		}

	}


}





void TELA_Render_Interface_OPERACAO_SERVICO()
{
	

	gFlow_Pulses_Corrigido_Atual = 0;
	gFlow_Pulses_Atual = 0;

    String tmp_IDChopp = F("");
    String tmp_Nome = F("");
    String tmp_Tipo = F("");
    String tmp_Valor = F("");
    float tmp_Valor_float = 0;
    String tmp_Volume = F("");
    String tmp_Ativa = F("");		
	String tmp_DataCad= F("");		
	String tmp_DataExp = F("");		

	volatile float tmp_VolumeInicialBarril = 0;
	volatile float VolumeAtual = 0;


    volatile float liters_Atual = 0;

	volatile float ValorSessaoChopp = 0;
	volatile float ValorSaldoAtual = gSessao_SaldoAtual;
	

	boolean Exec_Loop_PodeSair = false;

	unsigned long time_inicio = 0;
	unsigned long time_atual = 0;;
	unsigned long time_tempo_passado_semFluxo = 0;
	//unsigned long time_InicioSessao = 0;

	int SegundosPassados = 0;
	int Last_SegundosPassados = 0;

	unsigned long time_DuracaoSessao = 0;

	unsigned long time_TempoInicioTimeoutFluxoBaixo = 0;
	unsigned long time_TempoTotalTimeoutFluxoBaixo = 0;



	long _Local_TimeOutTorneira = 0;

    if (gModoOperacao == F("ADMIN"))
    {
    	_Local_TimeOutTorneira = ctTIMEOUT_SANGRIA;
    }
    else
    {
    	_Local_TimeOutTorneira = ctTIMEOUT_TORNEIRA;
    }




	if (gTelaRenderizada_OPERACAO_SERVICO == false)
	{


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEFINE VARIAVEIS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		unsigned long time_TempoInicioSessao = 0;

        tmp_IDChopp = getValue(gaEngatados[gServico_ID_TorneiraAtual - 1], ';', 2);
        tmp_Nome = getValue(gaEngatados[gServico_ID_TorneiraAtual - 1], ';', 7);
        tmp_Tipo = getValue(gaEngatados[gServico_ID_TorneiraAtual - 1], ';', 8);
        tmp_Valor = getValue(gaEngatados[gServico_ID_TorneiraAtual - 1], ';', 9);
        tmp_Volume = getValue(gaEngatados[gServico_ID_TorneiraAtual - 1], ';', 3);
        tmp_DataCad = getValue(gaEngatados[gServico_ID_TorneiraAtual - 1], ';', 1);
        tmp_DataExp = getValue(gaEngatados[gServico_ID_TorneiraAtual - 1], ';', 4);
        tmp_Ativa = getValue(gaEngatados[gServico_ID_TorneiraAtual - 1], ';', 5);

        tmp_Volume.replace(",", ".");
        
    	tmp_VolumeInicialBarril = tmp_Volume.toFloat();

        VolumeAtual = tmp_VolumeInicialBarril;

        volatile String Temp1 = F("");
        Temp1 = tmp_Valor;
        Temp1.replace(F(","), F("."));

        tmp_Valor_float = Temp1.toFloat();

        LogTerm(String(F("===================================================================")));

        if (gModoOperacao == F("ADMIN"))
        {
        	LogTerm(String(F("SANGRIA INICIADA")));
        }
        else
        {
        	LogTerm(String(F("SESSAO INICIADA")));
        }
                
        LogTerm(String(F("===================================================================")));
        LogTerm(String(F("Torneira: ")) + String(gServico_ID_TorneiraAtual));
        LogTerm(String(F("Chopp Selecionado: (")) + tmp_IDChopp + F(") ") + tmp_Nome);
		LogTerm(String(F("Estilo: ")) + tmp_Tipo);
		LogTerm(String(F("tmp_Valor: ")) + FormatNumber(tmp_Valor, F("MONEY")) + F(" / litro"));
		LogTerm(String(F("Volume Atual: ")) + FormatNumber(VolumeAtual, F("")) + F(" litros"));
		LogTerm(String(F("-------------------------------------------------------------------")));

		


		time_TempoInicioSessao = millis();

        if (gModoOperacao != F("ADMIN"))
        {
		    // se o saldo do usuario for zero, pode sair
		    if (ValorSaldoAtual <= 0)
		    {
		        Exec_Loop_PodeSair = true;
				LogTerm(F("O saldo do usuario foi totalmente utilizado. Finalizando sessao..."));

				TELA_Render_ExibeMsgSaldoZerado();
		    }
        }


	    if (Exec_Loop_PodeSair == false)
	    {


			switch (gServico_ID_TorneiraAtual)
			{

				case 1:

					gPinoSensorFluxoAtivo = FLOW_PINO_SENSOR_1;

					gPinoReleTorneiraAtiva = RELE_PINO_TORNEIRA_1;	

					break;

				case 2:

					gPinoSensorFluxoAtivo = FLOW_PINO_SENSOR_2;

					gPinoReleTorneiraAtiva = RELE_PINO_TORNEIRA_2;

					break;

				case 3:

					gPinoSensorFluxoAtivo = FLOW_PINO_SENSOR_3;

					gPinoReleTorneiraAtiva = RELE_PINO_TORNEIRA_3;	

					break;

				case 4:

					gPinoSensorFluxoAtivo = FLOW_PINO_SENSOR_4;

					gPinoReleTorneiraAtiva = RELE_PINO_TORNEIRA_4;	

					break;

				case 5:

					gPinoSensorFluxoAtivo = FLOW_PINO_SENSOR_5;

					gPinoReleTorneiraAtiva = RELE_PINO_TORNEIRA_5;	

					break;

				case 6:

					gPinoSensorFluxoAtivo = FLOW_PINO_SENSOR_6;

					gPinoReleTorneiraAtiva = RELE_PINO_TORNEIRA_6;	

					break;

				case 7:

					gPinoSensorFluxoAtivo = FLOW_PINO_SENSOR_7;

					gPinoReleTorneiraAtiva = RELE_PINO_TORNEIRA_7;	

					break;

				case 8:

					gPinoSensorFluxoAtivo = FLOW_PINO_SENSOR_8;

					gPinoReleTorneiraAtiva = RELE_PINO_TORNEIRA_8;	

					break;

				case 9:

					gPinoSensorFluxoAtivo = FLOW_PINO_SENSOR_9;

					gPinoReleTorneiraAtiva = RELE_PINO_TORNEIRA_9;	

					break;

				case 10:

					gPinoSensorFluxoAtivo = FLOW_PINO_SENSOR_10;

					gPinoReleTorneiraAtiva = RELE_PINO_TORNEIRA_10;	

					break;

				case -1:
					// nenhuma torneira ativa no momento
				
				
				default:
					break;				
			}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// RENDERIZA TELA DE OPERACAO SERVICO
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




			//////////////////////////////////////  
			// cebcalho logado

			if (ctTELA_HARDWARE == F("TERMINAL"))
			{  

				LogTerm(String(F("Nome: ")) + gSessao_Nome);
				LogTerm(String(F("Saldo: ")) + FormatNumber(gSessao_SaldoAtual, F("MONEY")));
				LogTerm(String(F("Tempo: ")) + String(_Local_TimeOutTorneira / 1000) + String(F(" segundos")));
				LogTerm(String(F("Torneira ")) + String(gServico_ID_TorneiraAtual) + String(F(" liberada!")));

				LogTerm(String(F("Chopp: ")) + tmp_Nome);
				LogTerm(String(F("Estilo: ")) + tmp_Tipo);
				LogTerm(String(F("Preco: ")) + FormatNumber(tmp_Valor, F("MONEY")) + String(F(" / Litro")));
				LogTerm(String(F("Restante: ")) + String(FormatNumber(tmp_Volume, F(""))) + String(F(" Litros")));
				LogTerm(F("Volume Retirado: 0,00 Litros"));
				LogTerm(String(F("Valor do Chopp sendo retirado: ")) + FormatNumber(0.0, F("MONEY")));

				LogTerm(F("Pode se servir..."));

			}



			if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
			{  

				if (gModoOperacao == F("ADMIN"))
				{

					TELA_Zera_BotaoGenericoTela();

					TELA_Render_Label(F("Administracao"), Green, -1, 2, 0, 10, F("RIGHT"));
					TELA_Render_Label(F("Outros >> Sangria"), CinzaClaro, -1, 1, 0, 60, F("RIGHT"));

					// botao voltar
				    TELA_Render_BotaoGenerico(1, F("VOLTAR"), F("VOLTAR"), 1, White, Red, 10, 15, 130, 60);


				}
				else
				{

					TELA_SetFontSize(1); 

					tft.setTextColor(CinzaLabels);
					tft.setCursor (10, 10);			
					tft.print (F("Nome: ")); 
					tft.setCursor (10, 45);			
					tft.print (F("Saldo: "));  

					tft.setTextColor(RA8875_WHITE);
					tft.setCursor (120, 10);			
					tft.print (gSessao_Nome); 
					tft.setCursor (120, 45);	
					tft.print (FormatNumber(gSessao_SaldoAtual, F("MONEY")));  

					


				}




				//////////////////////////////////////  
				// Tempo Restante


							

				TELA_SetFontSize(0); 
				tft.setTextColor(CinzaLabels);

				if (gModoOperacao == F("ADMIN"))
				{
					tft.setCursor (240, 20);
					tft.print (F("Tempo: "));
					tft.setCursor (300, 20);
					tft.print (String(_Local_TimeOutTorneira / 1000) + String(F(" segundos   "))); 						
				}
				else
				{
					tft.setCursor (620, 10);
					tft.print (F("Tempo: ")); 
					tft.setCursor (680, 10);
					tft.print (String(_Local_TimeOutTorneira / 1000) + String(F(" segundos   "))); 									
				}	

				





				//////////////////////////////////////  
				// texto torneira liberada

				TELA_SetFontSize(2); 
				tft.setTextColor(VerdeOK);

				tft.setCursor (170, 110);			
				tft.print (String(F("Torneira ")) + String(gServico_ID_TorneiraAtual) + String(F(" liberada!")));    

				if (gModoOperacao != F("ADMIN"))
				{
					tft.setCursor (220, 160);			
					tft.print (F("Pode se servir..."));  					
				}
  

				//////////////////////////////////////

				TELA_SetFontSize(1); 

				//////////////////////////////////////
				// CHOPP

				tft.setTextColor(CinzaLabels);
				tft.setCursor (180, 240);			
				tft.print (F("Chopp: ")); 

				tft.setTextColor(RA8875_WHITE);
				tft.setCursor (340, 240);			
				tft.print (tmp_Nome);


				//////////////////////////////////////
				// TIPO

				tft.setTextColor(CinzaLabels);
				tft.setCursor (180, 270);			
				tft.print (F("Estilo: ")); 

				tft.setTextColor(RA8875_WHITE);
				tft.setCursor (340, 270);			
				tft.print (tmp_Tipo);


				//////////////////////////////////////
				// PRECO

				tft.setTextColor(CinzaLabels);
				tft.setCursor (180, 300);			
				tft.print (F("Preco: ")); 

				tft.setTextColor(RA8875_WHITE);
				tft.setCursor (340, 300);			
				tft.print (FormatNumber(tmp_Valor, F("MONEY")) + String(F(" / Litro"))); 



				//////////////////////////////////////
				// RESTANTE

				tft.setTextColor(CinzaLabels);
				tft.setCursor (180, 330);			
				tft.print (F("Restante: ")); 

				tft.setTextColor(RA8875_WHITE);
				tft.setCursor (340, 330);	


				if (gModoOperacao == F("ADMIN"))
				{
					tft.print (String(F("Sangria")));
				}
				else
				{
					tft.print (String(FormatNumber(tmp_Volume, F(""))) + String(F(" Litros")));
				}
				




				//////////////////////////////////////
				// VOLUME RETIRADO

				tft.setTextColor(CinzaLabels);
				tft.setCursor (180, 390);			
				tft.print (F("Volume Retirado: ")); 

				tft.setTextColor(RA8875_YELLOW);
				tft.setCursor (450, 390);			
				tft.print ("0,00 Litros");

				//////////////////////////////////////
				// VALOR DO CHOPP SENDO RETIRADO

				//murch
				tft.setTextColor(CinzaLabels);
				tft.setCursor (180, 420);			
				tft.print (F("Valor do Chopp: ")); 

				tft.setTextColor(RA8875_YELLOW);
				tft.setCursor (450, 420);			
				tft.print (FormatNumber(0.0, F("MONEY"))); 


			}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ROTINA DE LIBERACAO DO CHOPP
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		}

		//murch
		//LogTerm(String(F("Abrindo Rele:")));
		//LogTerm(String(F("gServico_ID_TorneiraAtual = ")) + String(gServico_ID_TorneiraAtual));
		//LogTerm(String(F("gPinoSensorFluxoAtivo = ")) + String(gPinoSensorFluxoAtivo));
		//LogTerm(String(F("gPinoReleTorneiraAtiva = ")) + String(gPinoReleTorneiraAtiva));


		// libera apenas se existir saldo
		if ((ValorSaldoAtual > 0) || (gModoOperacao == F("ADMIN")))
		{
			// Liga Led Verde
			LED_SetLedState(F("RGB"), true, F("GREEN"));
			
			// Inicia o FLOW METERS
			digitalWrite(gPinoSensorFluxoAtivo, HIGH);
			gLastflowpinstate_Atual = digitalRead(gPinoSensorFluxoAtivo);

			useInterrupt_2(true);

		    // LIBERA TORNEIRA -- abre rele
			digitalWrite(gPinoReleTorneiraAtiva, LOW);


			

			delay(20);
		}
			

		// milissegundos desde que o programa comecou. sempre incrementa. em 50 dias volta a zero
		time_inicio = millis();
	




		while (Exec_Loop_PodeSair == false)
		{

			if (gModoOperacao == F("ADMIN"))
			{
				TELA_VerificaTouch_OPERACAO_SERVICO();

				if (gModoOperacao_SubTela == F("ADMIN_SANGRIA"))
				{
					// botao sair selecionado no sangria
			        Exec_Loop_PodeSair = true;
				    digitalWrite(gPinoReleTorneiraAtiva, HIGH);
					useInterrupt_2(false);		
					LED_SetLedState(F("RGB"), false, F(""));  
					LogTerm(F("Usuario clicou em SAIR da Sangria")); 					
				}
			}
			

		    time_atual = millis();
		    time_tempo_passado_semFluxo = time_atual - time_inicio;


		    SegundosPassados = floor(time_tempo_passado_semFluxo / 1000);


		    // Mostra tempo de timeout
		    if (SegundosPassados != Last_SegundosPassados)
		    {
	
				if (ctTELA_HARDWARE == F("TERMINAL"))
				{  

					LogTerm(String((_Local_TimeOutTorneira / 1000) - SegundosPassados) + String(F(" segundos   ")));

				}

				if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
				{  
				
					
					if (gModoOperacao == F("ADMIN"))
					{

						TELA_SetFontSize(0); 
						tft.setTextColor(CinzaLabels, RA8875_BLACK);
						tft.setCursor (300, 20);			
						tft.print (String((_Local_TimeOutTorneira / 1000) - SegundosPassados) + String(F(" segundos   "))); 

					}
					else
					{
						TELA_SetFontSize(0); 
						tft.setTextColor(CinzaLabels, RA8875_BLACK);
						tft.setCursor (680, 10);			
						tft.print (String((_Local_TimeOutTorneira / 1000) - SegundosPassados) + String(F(" segundos   "))); 								
					}	




	

				}

		    }


		    // se ocorrer timeout do uso, pode sair
		    if (time_tempo_passado_semFluxo >= _Local_TimeOutTorneira)
		    {
		        Exec_Loop_PodeSair = true;
			    digitalWrite(gPinoReleTorneiraAtiva, HIGH);
				useInterrupt_2(false);		
				LED_SetLedState(F("RGB"), false, F(""));  
				LogTerm(F("Timeout na torneira. Finalizando sessao..."));      
		    }


		    if (gModoOperacao != F("ADMIN"))
		    {

			    // se o saldo do usuario for zero, pode sair
			    if (ValorSaldoAtual <= 0)
			    {
			        Exec_Loop_PodeSair = true;
				    digitalWrite(gPinoReleTorneiraAtiva, HIGH);
					useInterrupt_2(false);
					LED_SetLedState(F("RGB"), false, F(""));

					LogTerm(F("O saldo do usuario foi totalmente utilizado. Finalizando sessao..."));

					delay(1500);

					TELA_Render_ExibeMsgSaldoZerado();
			    }

		    }



		    /*
		    // se o restante do chopp for zero, pode sair
		    if (VolumeAtual <= 0)
		    {
		        Exec_Loop_PodeSair = true;
			    digitalWrite(gPinoReleTorneiraAtiva, HIGH);
				useInterrupt_2(false);		
				LED_SetLedState(F("RGB"), false, F(""));        
		    }
			*/

		    Last_SegundosPassados = SegundosPassados;

		    // Inicia faixa padrao curva
			gFaixaVelAtual = -8;


		    if (Exec_Loop_PodeSair == false)
		    {

		    	time_DuracaoSessao = millis() - time_TempoInicioSessao;




			    // Se os pulsos foram maiores do que o limite baixo de ignorar, soma saida em litros
			    if (gFLOW_PulsosNosUltimosXseg >= ctLIMITE_IGNORA_PULSOS)
			   	{

					liters_Atual = gFlow_Pulses_Corrigido_Atual;
					liters_Atual /= gAjusteFluxo;
					liters_Atual /= 60.0;

				}



				if (tmp_VolumeInicialBarril - liters_Atual <= 0)
				{
					VolumeAtual = 0;
				}
				else
				{
					VolumeAtual = tmp_VolumeInicialBarril - liters_Atual;
				}


				

				tmp_Volume = String(VolumeAtual);

			


				if (gFLOW_Fluxo_Iniciado == true)
				{

					if (gFLOW_Reinicia_Contador == true)
					{

						gFLOW_time_inicio = millis();

						gFLOW_Reinicia_Contador = false;
						gFLOW_PulsosNoInicio = gFlow_Pulses_Atual;	

					}

					gFLOW_time_atual = millis();
					gFLOW_time_tempo_passado = gFLOW_time_atual - gFLOW_time_inicio;
					//SegundosPassados = floor(time_tempo_passado_semFluxo / 1000);
					gFLOW_SegundosPassados = gFLOW_time_tempo_passado / 1000;

					//LogTerm("Pulsos atuais = " + String(Flow_Pulses_3) + " | gFLOW_PulsosNosUltimosXseg = " + String(gFLOW_PulsosNosUltimosXseg));
					//LogTerm("gFLOW_PulsosNosUltimosXseg = " + String(gFLOW_PulsosNosUltimosXseg));
					//LogTerm("gFLOW_PulsosNoInicio = " + String(gFLOW_PulsosNoInicio));
					//LogTerm("gFLOW_time_atual = " + String(gFLOW_time_atual));
					//LogTerm("gFLOW_time_inicio = " + String(gFLOW_time_inicio));
					//LogTerm("gFLOW_time_tempo_passado = " + String(gFLOW_time_tempo_passado));
					//LogTerm("gFLOW_SegundosPassados = " + String(gFLOW_SegundosPassados));



					if (gFLOW_time_tempo_passado >= 300)
					{

						gFLOW_PulsosNosUltimosXseg = gFlow_Pulses_Atual - gFLOW_PulsosNoInicio;

						//LogTerm("Numero de Pulsos nos ultimos 1 segundos: = " + String(gFLOW_PulsosNosUltimosXseg));



						gFLOW_Reinicia_Contador = true;	
						

						//time_inicio = millis();
						//PulsosNoInicio = Flow_Pulses_3;
						//SegundosPassados = 0;
						//time_tempo_passado_semFluxo = 0;
					}


					delay(400);

				}



				// INICIO DA CURVA

				if (gFLOW_PulsosNosUltimosXseg >= ctLIMITE_IGNORA_PULSOS)
				{

					// nao reinicia se for em modo sangria
					if (gModoOperacao != F("ADMIN"))
					{
						time_inicio = millis();						
					}					
					
				}



				if (gFLOW_PulsosNosUltimosXseg < 10)
				{
					gAjuste_fino_baixo = 2;
				}
				else
				{
					gAjuste_fino_baixo = 1;
				}

				

				// FAIX IDEAL
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal - gAjuste_fino_baixo)) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal + gAjuste_fino_baixo)))
				{
					gFaixaVelAtual = 0;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("IDEAL                   -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal - gAjuste_fino_baixo)) + String(F(" ate ")) + (gPulse_ideal + gAjuste_fino_baixo) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}					
					
				}


				// FAIXA -1
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal - (gAjuste_fino_baixo * 2))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal - (gAjuste_fino_baixo * 1))))
				{
					gFaixaVelAtual = -1;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA -1                -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal - (gAjuste_fino_baixo * 2))) + String(F(" ate ")) + (gPulse_ideal - (gAjuste_fino_baixo * 1)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}					
					
				}


				// FAIXA +1
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal + (gAjuste_fino_baixo * 1))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal + (gAjuste_fino_baixo * 2))))
				{
					gFaixaVelAtual = 1;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA +1                -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal + (gAjuste_fino_baixo * 1))) + String(F(" ate ")) + (gPulse_ideal + (gAjuste_fino_baixo * 2)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}						
					
				}



				// FAIXA -2
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal - (gAjuste_fino_baixo * 3))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal - (gAjuste_fino_baixo * 2))))
				{
					gFaixaVelAtual = -2;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA -2                -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal - (gAjuste_fino_baixo * 3))) + String(F(" ate ")) + (gPulse_ideal - (gAjuste_fino_baixo * 2)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}	

					
				}


				// FAIX +2
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal + (gAjuste_fino_baixo * 2))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal + (gAjuste_fino_baixo * 3))))
				{
					gFaixaVelAtual = 2;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA +2                -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal + (gAjuste_fino_baixo * 2))) + String(F(" ate ")) + (gPulse_ideal + (gAjuste_fino_baixo * 3)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}						
					
				}


				// FAIXA -3
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal - (gAjuste_fino_baixo * 4))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal - (gAjuste_fino_baixo * 3))))
				{
					gFaixaVelAtual = -3;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA -3                -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal - (gAjuste_fino_baixo * 4))) + String(F(" ate ")) + (gPulse_ideal - (gAjuste_fino_baixo * 3)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}	

					
				}

				// FAIXA +3
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal + (gAjuste_fino_baixo * 3))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal + (gAjuste_fino_baixo * 4))))
				{
					gFaixaVelAtual = 3;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA +3        	        -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal + (gAjuste_fino_baixo * 3))) + String(F(" ate ")) + (gPulse_ideal + (gAjuste_fino_baixo * 4)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}						
					
				}


				// FAIXA -4
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal - (gAjuste_fino_baixo * 5))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal - (gAjuste_fino_baixo * 4))))
				{
					gFaixaVelAtual = -4;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA -4                -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal - (gAjuste_fino_baixo * 5))) + String(F(" ate ")) + (gPulse_ideal - (gAjuste_fino_baixo * 4)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}	


				}

				// FAIXA +4
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal + (gAjuste_fino_baixo * 4))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal + (gAjuste_fino_baixo * 5))))
				{
					gFaixaVelAtual = 4;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA +3                 -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal + (gAjuste_fino_baixo * 4))) + String(F(" ate ")) + (gPulse_ideal + (gAjuste_fino_baixo * 5)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}					
					
				}


				// FAIXA -5
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal - (gAjuste_fino_baixo * 6))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal - (gAjuste_fino_baixo * 5))))
				{
					gFaixaVelAtual = -5;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA -5                -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal - (gAjuste_fino_baixo * 6))) + String(F(" ate ")) + (gPulse_ideal - (gAjuste_fino_baixo * 5)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}	

					 
				}

				// FAIXA +5
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal + (gAjuste_fino_baixo * 5))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal + (gAjuste_fino_baixo * 6))))
				{
					gFaixaVelAtual = 5;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA +5                 -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal + (gAjuste_fino_baixo * 5))) + String(F(" ate ")) + (gPulse_ideal + (gAjuste_fino_baixo * 6)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}						
					
				}

				// FAIXA -6
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal - (gAjuste_fino_baixo * 7))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal - (gAjuste_fino_baixo * 6))))
				{
					gFaixaVelAtual = -6;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA -6                -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal - (gAjuste_fino_baixo * 7))) + String(F(" ate ")) + (gPulse_ideal - (gAjuste_fino_baixo * 6)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}					
					
				}


				// FAIXA +6
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal + (gAjuste_fino_baixo * 6))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal + (gAjuste_fino_baixo * 7))))
				{
					gFaixaVelAtual = 6;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA +6                -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal + (gAjuste_fino_baixo * 6))) + String(F(" ate ")) + (gPulse_ideal + (gAjuste_fino_baixo * 7)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}
				}

				// FAIXA -7
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal - (gAjuste_fino_baixo * 8))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal - (gAjuste_fino_baixo * 7))))
				{
					gFaixaVelAtual = -7;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA -7                -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal - (gAjuste_fino_baixo * 8))) + String(F(" ate ")) + (gPulse_ideal - (gAjuste_fino_baixo * 7)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}						
					
				}

				// FAIXA +7
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal + (gAjuste_fino_baixo * 7))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal + (gAjuste_fino_baixo * 8))))
				{
					gFaixaVelAtual = 7;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA +7                -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal + (gAjuste_fino_baixo * 7))) + String(F(" ate ")) + (gPulse_ideal + (gAjuste_fino_baixo * 8)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}
				}



				// FAIXA -8 --  ESTANQUE - MENOR QUE ZERO - PUSOS NEGATIVOS OU IGUAL A ZERO
				if (gFLOW_PulsosNosUltimosXseg <= 0)
				{
					gFaixaVelAtual = -8;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA -8  EXTREMA ZERO  -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal - (gAjuste_fino_baixo * 9))) + String(F(" ate ")) + (gPulse_ideal - (gAjuste_fino_baixo * 8)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}							
					
				}
				else
				{
					// FAIXA -8 --  ATUAL EXTREMA BAIXA -- ATUAL BAIXA
					if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal - (gAjuste_fino_baixo * 9))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal - (gAjuste_fino_baixo * 8))))
					{
						gFaixaVelAtual = -8;

						if (ctDEBUG_FLUXO_CURVA == 1)
						{
							LogTerm(String(F("FAIXA -8  EXTREMA BAIXA -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal - (gAjuste_fino_baixo * 9))) + String(F(" ate ")) + (gPulse_ideal - (gAjuste_fino_baixo * 8)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
						}						
						
					}					
				}


				// FAIXA +8 - EXTREMA ALTA
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal + (gAjuste_fino_baixo * 7))))
				{
					gFaixaVelAtual = 8;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA +8  EXTREMA ALTA  -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal + (gAjuste_fino_baixo * 7))) + String(F(" ate inf")) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) + String(F(" | time_TempoTotalTimeoutFluxoBaixo = ")) + String(time_TempoTotalTimeoutFluxoBaixo) + String(F(" | time_DuracaoSessao = ")) + String(time_DuracaoSessao) );
					}
				}

				/*
				// No hardware, torneira e parametros atuais, nunca chegamos noa faixa abaixo de 8 pois com os valores atuais
				// quando nao passa nada, fica zero pulsos e se enquadra na faixa 8 que vai de zero a 2
				// logo, comentei o abaixo e deixei a extrema baixa como a -8

				// FAIXA -9
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal - (gAjuste_fino_baixo * 10))) && (gFLOW_PulsosNosUltimosXseg < (gPulse_ideal - (gAjuste_fino_baixo * 9))))
				{
					gFaixaVelAtual = -9;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA -9 -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal - (gAjuste_fino_baixo * 10))) + String(F(" ate ")) + (gPulse_ideal - (gAjuste_fino_baixo * 9)) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) );
					}						
					
				}


				// FAIXA -10 -- EXTREMA BAIXA DEPRECIADA NAS CONDICOES ATUAIS
				if ((gFLOW_PulsosNosUltimosXseg >= (gPulse_ideal - (gAjuste_fino_baixo * 11))) )
				{
					gFaixaVelAtual = -10;

					if (ctDEBUG_FLUXO_CURVA == 1)
					{
						LogTerm(String(F("FAIXA -10 -- EXTREMA BAIXA -- gFLOW_PulsosNosUltimosXseg: ")) + String(gFLOW_PulsosNosUltimosXseg) + String(F(" | de ")) + String((gPulse_ideal - (gAjuste_fino_baixo * 11))) + String(F(" ate inf")) + String(F(" | gFlow_Pulses_Atual: ")) + String(gFlow_Pulses_Atual) + String(F(" | gFlow_Pulses_Corrigido_Atual = ")) + String(gFlow_Pulses_Corrigido_Atual) + String(F(" | time_tempo_passado_semFluxo = ")) + String(time_tempo_passado_semFluxo) );
					}						
					
				}

				*/




				//LogTerm("gFLOW_PulsosNosUltimosXseg = " + String(gFLOW_PulsosNosUltimosXseg));

				/*
				if ((gFaixaVelAtual <= -3) && (time_DuracaoSessao >= _Local_TimeOutTorneira))
				{
					time_TempoInicioTimeoutFluxoBaixo = millis();
				}
				*/




				if (time_DuracaoSessao >= _Local_TimeOutTorneira)
				{
					if (gFaixaVelAtual >= -5)
					{
						time_TempoInicioTimeoutFluxoBaixo = millis();
					}
				}
				else
				{
					time_TempoInicioTimeoutFluxoBaixo = millis();
				}

				 
				time_TempoTotalTimeoutFluxoBaixo = millis() - time_TempoInicioTimeoutFluxoBaixo;


			    if (gModoOperacao != F("ADMIN"))
			    {

				    // Se esta tirando chopp devagar, entao fecha torneira --  timeout fluxo baixo
				    if (time_TempoTotalTimeoutFluxoBaixo >= 5000)
				    {
				        Exec_Loop_PodeSair = true;
					    digitalWrite(gPinoReleTorneiraAtiva, HIGH);
						useInterrupt_2(false);		
						LED_SetLedState(F("RGB"), false, F(""));  
						LogTerm(F("Chopp muito devagar. Finalizando sessao..."));      
				    }	

			    }

	


				// RENDER DOS VALORES ATUALIZADOS EM TELA


				if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
				{  
					TELA_SetFontSize(1);
				}

				

				//////////////////////////////////////
				// VOLUME RETIRADO

				//LogTerm("liters_1 = ");
				//LogTerm(liters_1);

			   	if (gFLOW_PulsosNosUltimosXseg >= ctLIMITE_IGNORA_PULSOS)
			   	{				

					if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
					{  
					
						
						tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);
						tft.setCursor (450, 390);			
						tft.print (String(FormatNumber(liters_Atual, F(""))) + String(F(" Litros     ")));

					}

					//////////////////////////////////////
					// VALOR DO CHOPP SENDO RETIRADO

					
					if (tmp_Valor_float * liters_Atual >= gSessao_SaldoAtual)
					{
						ValorSessaoChopp = gSessao_SaldoAtual;
					}
					else
					{
						ValorSessaoChopp = tmp_Valor_float * liters_Atual;
					}

					
					if (ctDEBUG_FLUXO_CURVA == 0)
					{
						LogTerm(String(F("Valor do Chopp = ")) + FormatNumber(ValorSessaoChopp, F("MONEY")));
					}					

					

					if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
					{  
					
						tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);
						tft.setCursor (450, 420);			
						tft.print (FormatNumber(ValorSessaoChopp, F("MONEY")) + String(F("     "))); 

					}


					//////////////////////////////////////  
					// cebcalho logado -- SALDO ATUAL

					
					if (gSessao_SaldoAtual - ValorSessaoChopp <= 0)
					{
						ValorSaldoAtual = 0;
					}
					else
					{
						ValorSaldoAtual = gSessao_SaldoAtual - ValorSessaoChopp;
					}
					

					if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
					{  

					    if (gModoOperacao != F("ADMIN"))
					    {
		    
							tft.setTextColor(RA8875_WHITE, RA8875_BLACK);
							tft.setCursor (120, 45);	
							tft.print (FormatNumber(ValorSaldoAtual, F("MONEY")) + String(F("     "))); 
					    }

 

					}


					//////////////////////////////////////
					// RESTANTE

					if (String(ctTELA_HARDWARE) == String(F("ER-TFTM070-5")))
					{  

					    if (gModoOperacao != F("ADMIN"))
					    {
							tft.setTextColor(RA8875_WHITE, RA8875_BLACK);
							tft.setCursor (340, 330);			
							tft.print (FormatNumber(VolumeAtual, F("")) + String(F(" Litros")) + String(F("     ")));
					    }



					}




				}


			}


		}

		time_inicio = millis();
	
		//aqui

	    // FECHA TORNEIRA -- FINALIZA SESSAO
	    digitalWrite(gPinoReleTorneiraAtiva, HIGH);
		useInterrupt_2(false);
		LED_SetLedState(F("RGB"), false, F(""));
		delay(50);



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EXTRATO DA SESSAO - TERMINAL
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	    if (gModoOperacao == F("ADMIN"))
	    {
	    	LogTerm(String(F("-- Sangria - EXTRATO ------------------------------------------------")));
		    LogTerm(String(F("Torneira (gServico_ID_TorneiraAtual) = ")) + String(gServico_ID_TorneiraAtual));
		    LogTerm(String(F("IDChopp (tmp_IDChopp) = ")) + tmp_IDChopp);
		    LogTerm(String(F("Nome Chopp (tmp_Nome) = ")) + tmp_Nome);
		    LogTerm(String(F("Preco Chopp (tmp_Valor) = ")) + tmp_Valor);
		    LogTerm(String(F("Pulsos (gFlow_Pulses_Corrigido_Atual) = ")) + String(gFlow_Pulses_Corrigido_Atual));
			
			LogTerm(String(F("ValorSessaoChopp = ")) + String(ValorSessaoChopp));
			LogTerm(String(F("Saldo Atual (ValorSaldoAtual) = ")) + String(ValorSaldoAtual));		
			LogTerm(String(F("Consumido (liters_Atual) = ")) + String(liters_Atual));
		}
	    else
	    {
	    	LogTerm(String(F("-- Sessao - EXTRATO ------------------------------------------------")));
		    LogTerm(String(F("Torneira (gServico_ID_TorneiraAtual) = ")) + String(gServico_ID_TorneiraAtual));
		    LogTerm(String(F("IDChopp (tmp_IDChopp) = ")) + tmp_IDChopp);
		    LogTerm(String(F("Nome Chopp (tmp_Nome) = ")) + tmp_Nome);
		    LogTerm(String(F("Preco Chopp (tmp_Valor) = ")) + tmp_Valor);
		    LogTerm(String(F("IDUser = ")) + String(gSessao_IDUser));
			LogTerm(String(F("gSessao_Nome = ")) + gSessao_Nome);
			LogTerm(String(F("gSessao_CPF = ")) + gSessao_CPF);
			LogTerm(String(F("gSessao_DataCad = ")) + gSessao_DataCad);
			LogTerm(String(F("Saldo Original (gSessao_SaldoAtual) = ")) + String(gSessao_SaldoAtual));
			LogTerm(String(F("Pulsos (gFlow_Pulses_Corrigido_Atual) = ")) + String(gFlow_Pulses_Corrigido_Atual));
			
			LogTerm(String(F("ValorSessaoChopp = ")) + String(ValorSessaoChopp));
			LogTerm(String(F("Saldo Atual (ValorSaldoAtual) = ")) + String(ValorSaldoAtual));		
			LogTerm(String(F("Chopp Barril Inicial (tmp_VolumeInicialBarril) = ")) + String(tmp_VolumeInicialBarril));
			LogTerm(String(F("Consumido (liters_Atual) = ")) + String(liters_Atual));
			LogTerm(String(F("Chopp Restante string (tmp_Volume) = ")) + tmp_Volume);
			LogTerm(String(F("Chopp Restante float (VolumeAtual) = ")) + String(VolumeAtual));	    	
	    }

	    
	    


		LogTerm(String(F("===================================================================")));


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EXTRATO DA SESSAO - TELA
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		

		// Exibe tela te extrato, se em TELA
	    if (ctTELA_HARDWARE == String(F("ER-TFTM070-5")))
	    {

	    	int ExibeExtratoEmTela = 0;


	    	if (ExibeExtratoEmTela == 1)
	    	{



	            TELA_LimpaTela();

	            int PosInicial_X = 175;
	            int PosInicial_Y = 130;

	            int TamanhoLinha = 38;
	            int Pos_X_Coluna = 170;

	            int Fator_X = 0;
	            int Fator_Y = 0;

	            int ContaLinha = 0;


	            String outLabel = F("");
	            String outValor = F("");



	            //////////////////////////////////////  
	            // Extrato da sessao

	            TELA_SetFontSize(2); 

	            tft.setTextColor(VerdeOK);

	            tft.setCursor (200, 30);           
	            tft.print (F("Extrato da Sessao"));    

	            ////////////////////////////////////// 

	            TELA_SetFontSize(1); 

	            ////////////////////////////////////// 

	            for (ContaLinha = 1 ; ContaLinha <= 8 ; ContaLinha++)
	            {


	                switch (ContaLinha) 
	                {
	                    case 1:
	                        outLabel = F("Nome:");
	                        outValor = gSessao_Nome;
	                        break;

	                    case 2:
	                        outLabel = F("Saldo:");
	                        outValor = FormatNumber(ValorSaldoAtual, F("MONEY"));
	                        break;

	                    case 4:
	                        outLabel = F("Torneira:");
	                        outValor = String(gServico_ID_TorneiraAtual);
	                        break;

	                    case 5:
	                        outLabel = F("Chopp:");
	                        outValor = tmp_Nome;
	                        break;

	                    case 6:
	                        outLabel = F("Estilo:");
	                        outValor = tmp_Tipo;
	                        break;

	                    case 8:
	                        outLabel = F("Total:");
	                        outValor = FormatNumber(ValorSessaoChopp, F("MONEY"));
	                        break;

	                    default:
	                        outLabel = F("");
	                        outValor = F("");
	                        break;
	                }



	                // Label
	                Fator_X = PosInicial_X;
	                Fator_Y = PosInicial_Y + ((ContaLinha - 1) * TamanhoLinha);  

	                tft.setTextColor(CinzaLabels);
	                tft.setCursor (Fator_X, Fator_Y);         
	                tft.print (outLabel);


	                // Valor 
	                Fator_X = PosInicial_X + Pos_X_Coluna;
	                Fator_Y = PosInicial_Y + ((ContaLinha - 1) * TamanhoLinha);

	                if (ContaLinha == 8)
	                {
	                    tft.setTextColor(RA8875_YELLOW);
	                }
	                else
	                {
	                    tft.setTextColor(RA8875_WHITE);
	                }
	                
	                tft.setCursor (Fator_X, Fator_Y);         
	                tft.print (outValor);

	            }



	    	}



	    }


	    if (gModoOperacao != F("ADMIN"))
	    {

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// SALVA DADOS DO USUARIO
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		    

		    String retFunc = F("");

		    // atualiza dados apenas se realmente foi retirado algum chopp
	 		if (ValorSessaoChopp > 0)
	 		{
				retFunc = F("");
				retFunc = BANCO_AtualizaSaldoUserLogado(ValorSaldoAtual);


				if (retFunc.substring(0, 1) == F("1"))
				{
				    LogTerm(F("Saldo/Sessao de usuario atualizado com sucesso !"));
				}
				else
				{
				    LogTerm(String(F("Falha na atualizacao do Saldo/Sessao: ")) + retFunc);
				} 			
	 		}
	 		else
	 		{
	 			LogTerm(F("Nao foi retirado chopp. Nenhuma atualizacao de Usuario sera feita"));
	 		}




			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// SALVA DADOS DE ENGATADOS
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		    // atualiza dados apenas se realmente foi retirado algum chopp
	 		if (ValorSessaoChopp > 0)
	 		{
				retFunc = F("");
				retFunc = BANCO_AtualizaSaldoEngatadosSessao(VolumeAtual);



				if (retFunc.substring(0, 1) == F("1"))
				{
				    LogTerm(F("Saldo do Chopp atualizado com sucesso !"));
				}
				else
				{
				    LogTerm(String(F("Falha na atualizacao do Saldo do Chopp: ")) + retFunc);
				}			
	 		}
	 		else
	 		{
	 			LogTerm(F("Nao foi retirado chopp. Nenhuma atualizacao de Engatados sera feita"));
	 		}


			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// RECARREGA VARIAVEL COM CHOPPS ENGATADOS E ZERA DEMAIS VARIAVEIS
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		    // atualiza dados apenas se realmente foi retirado algum chopp
	 		if (ValorSessaoChopp > 0)
	 		{
			
				// atualiza a variavel de chopps engatados
				CORE_ExecRotinaDefineChoppEngatados();	

	 		}
	 		else
	 		{
	 			// apenas exibe a lista de chopps atual
	 			CORE_PrintChoppEngatados();
	 		}

	 	}
		




		volatile unsigned long gBounce_time_inicio = 0;
		volatile unsigned long gBounce_time_atual = 0;
		volatile unsigned long gBounce_time_tempo_passado = 0;

		volatile int gBounce_SegundosPassados = 0;
		volatile int gBounce_Last_SegundosPassados = 0;


		// var que conta o numero de cliques executaados no botao
		volatile int gBounce_ContaClick = 0;	    


		gServico_ID_TorneiraAtual = -1;	


	    tmp_IDChopp = F("");
	    tmp_Nome = F("");
	    tmp_Tipo = F("");
	    tmp_Valor = F("");
	    tmp_Volume = F("");
	    tmp_Ativa = F("");		
		tmp_DataCad= F("");		
		tmp_DataExp = F("");		
		
		
		gFlow_Pulses_Corrigido_Atual = 0;
		gFlow_Pulses_Atual = 0;
		liters_Atual = 0;


		ValorSessaoChopp = 0;
		ValorSaldoAtual = 0;
		VolumeAtual = 0;

		gPinoSensorFluxoAtivo = -1;	
		gPinoReleTorneiraAtiva = -1;


	    if (gModoOperacao == F("ADMIN"))
	    {
			
			gTelaRenderizada_OPERACAO_SERVICO = false;
  			gTelaRenderizada_ADMIN_SANGRIA = false;
  
			gModoOperacao_SubTela = F("ADMIN_SANGRIA");	
	    }
	    else
	    {
			// zera as vars para cada tentativa de login
			// efetua logoff
			gSessao_Logado = false;
			gSessao_IDUser = -1;
			gSessao_Nome = F("");
			gSessao_Nivel = -1;
			gSessao_SaldoAtual = -1;
			gSessao_CPF = F("");
			gSessao_DataCad = F("");
			
			gTelaRenderizada_OPERACAO_SERVICO = false;
			gTelaRenderizada_OPERACAO = false;	

			gModoOperacao = F("STANDBY");  
			gModoOperacao_SubTela = F("");	
	    }



		//gBounce_time_inicio = millis();
		//gBounce_ContaClick = 2;
		


	    if (ctTELA_HARDWARE == String(F("ER-TFTM070-5")))
	    {
	        TELA_LimpaTela();
	    }




	}
	

}



