
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  GLOBAIS MAIN
//  ============
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// cor e uint16_t



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Modo de operacao atual da maquina. indica qual a funcionalidade e telas que a maquina deve exibir em qualquer dado momento
// Pode ser um dos valoes abaixo
// INICIO
// INSTALACAO
// STANDBY
// LOGIN
// OPERACAO
// ADMIN
// DEBUG
// TESTE

// VERSAO DA APLICACAO
#define VersaoAPP F("0.5")
#define NOME_LOJA_LINHA1 F("Experiencia")
#define NOME_LOJA_LINHA2 F("Cervejeira")


String gModoOperacao; 
String gModoOperacao_SubTela;

// var que define se a aplicacao esta no modo debug. isto faz com que algumas msgs de debug
// sejam exibidas na tela e/ou no terminal
#define ctMODO_DEBUG true

// tempo em ms para timeout das opcoes a serem escolhidas
#define gTimeoutOpcao 7000		

// tempo em ms para timeout de servico de torneira (operacao_servico)
#define ctTIMEOUT_TORNEIRA 7000		

// tempo em ms para timeout da tela de operacao (tela onde eh escolhido o chopp) (operacao)
#define ctTIMEOUT_TELA_OPERACAO 30000		

// tempo em ms para timeout da tela de ADMIN 
#define ctTIMEOUT_TELA_ADMIN 30000		









// Numero maximo de torneiras possiveis no sistema. Torneiras engatadas
#define ctMAX_TORNEIRAS 4 // numero real de torneiras. Ex: para 4 torneiras, colocar 4
String gaEngatados[ctMAX_TORNEIRAS];	



// BUZZER
#define BUZZER_PINO 32


// TELA
#define TELA_PINO_INT 	4
#define TELA_PINO_CS	10
#define TELA_PINO_RESET 9

// Banco de Dados
#define BANCO_MAX_CHOPPS 50  // numero maximo de chopps que podem ser cadastrados no banco de dados

// SD
#define SD_MAX_TENTATIVA_READ 	2
#define SD_DELAY_TENTATIVA_READ 1000
#define SD_PINO 				24

// RFID
#define RFID_PINO_SCK 	52
#define RFID_PINO_MOSI 	51
#define RFID_PINO_SS 	53
#define RFID_PINO_MISO 	50
#define RFID_PINO_IRQ 	2
#define RFID_PINO_RESET 3 

// RELE
#define RELE_PINO_TORNEIRA_1 45
#define RELE_PINO_TORNEIRA_2 46
#define RELE_PINO_TORNEIRA_3 47
#define RELE_PINO_TORNEIRA_4 48
#define RELE_PINO_TORNEIRA_5 0
#define RELE_PINO_TORNEIRA_6 0
#define RELE_PINO_TORNEIRA_7 0
#define RELE_PINO_TORNEIRA_8 0
#define RELE_PINO_TORNEIRA_9 0
#define RELE_PINO_TORNEIRA_10 0

// Flow Sensor
#define FLOW_PINO_SENSOR_1 36
#define FLOW_PINO_SENSOR_2 37 
#define FLOW_PINO_SENSOR_3 38 
#define FLOW_PINO_SENSOR_4 39
#define FLOW_PINO_SENSOR_5 0
#define FLOW_PINO_SENSOR_6 0
#define FLOW_PINO_SENSOR_7 0
#define FLOW_PINO_SENSOR_8 0
#define FLOW_PINO_SENSOR_9 0
#define FLOW_PINO_SENSOR_10 0

// Pino do LED Cor Fixa
#define ctPINO_LED_CORFIXA 26

// led RGB
#define ctPINO_LED_RGB_RED 35
#define ctPINO_LED_RGB_GREEN 34
#define ctPINO_LED_RGB_BLUE 33





#define ctMAX_BOTOES_GEN_TELA 10 // numero maximo de botoes genericos em tela
String gaBotoesGenTela[ctMAX_BOTOES_GEN_TELA];	



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TECLADO
// -------
//
// Vars necessarias para o teclado numerico e alfanumerico
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




String gTecladoNum_ValAtual;
String gTecladoAlfa_ValAtual;


#define ctTECLADO_NUM_TOTAL_BOTOES 	14
#define ctTECLADO_ALFA_TOTAL_BOTOES 42




// var que armazena a posicao inicial xy renderizada dos botoes e seu tamanho para poder serem usadas no touch
// var iniciada com os valores abaixo e depois modificada quando os botoes do teclado sao renderizados

String aTecladoNum_PosBotoes[ctTECLADO_NUM_TOTAL_BOTOES]={"X01,TAM,Y01,TAM",
														   "X02,TAM,Y02,TAM",
														   "X03,TAM,Y03,TAM",
														   "X04,TAM,Y04,TAM",
														   "X05,TAM,Y05,TAM",
														   "X06,TAM,Y06,TAM",
														   "X07,TAM,Y07,TAM",
														   "X08,TAM,Y08,TAM",
														   "X09,TAM,Y09,TAM",
														   "X10,TAM,Y10,TAM",
														   "X11,TAM,Y11,TAM",
														   "X12,TAM,Y12,TAM",
														   "X13,TAM,Y13,TAM",
														   "X14,TAM,Y14,TAM"
														   };


String aTecladoAlfa_PosBotoes[ctTECLADO_ALFA_TOTAL_BOTOES]={"X01,TAM,Y01,TAM",
															"X02,TAM,Y02,TAM",
															"X03,TAM,Y03,TAM",
															"X04,TAM,Y04,TAM",
															"X05,TAM,Y05,TAM",
															"X06,TAM,Y06,TAM",
															"X07,TAM,Y07,TAM",
															"X08,TAM,Y08,TAM",
															"X09,TAM,Y09,TAM",
															"X10,TAM,Y10,TAM",
															"X11,TAM,Y11,TAM",
															"X12,TAM,Y12,TAM",
															"X13,TAM,Y13,TAM",
															"X14,TAM,Y14,TAM",
															"X15,TAM,Y15,TAM",
															"X16,TAM,Y16,TAM",
															"X17,TAM,Y17,TAM",
															"X18,TAM,Y18,TAM",
															"X19,TAM,Y19,TAM",
															"X20,TAM,Y20,TAM",
															"X21,TAM,Y21,TAM",
															"X22,TAM,Y22,TAM",
															"X23,TAM,Y23,TAM",
															"X24,TAM,Y24,TAM",
															"X25,TAM,Y25,TAM",
															"X26,TAM,Y26,TAM",
															"X27,TAM,Y27,TAM",
															"X28,TAM,Y28,TAM",
															"X29,TAM,Y29,TAM",
															"X30,TAM,Y30,TAM",
															"X31,TAM,Y31,TAM",
															"X32,TAM,Y32,TAM",
															"X33,TAM,Y33,TAM",
															"X34,TAM,Y34,TAM",
															"X35,TAM,Y35,TAM",
															"X36,TAM,Y36,TAM",
															"X37,TAM,Y37,TAM",
															"X38,TAM,Y38,TAM",
															"X39,TAM,Y39,TAM",
															"X40,TAM,Y40,TAM",
															"X41,TAM,Y41,TAM",
														  	"X42,TAM,Y42,TAM"
														   };

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BOTOES TOUCH - BOUNCE
// ---------------------
//
// Vars necessarias para controlar o press dos botoes e nao permitir double press (bounce)
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//  numero de clicks de sensibilidade dos botoes em uma determinada tela. Para evitar o double press
//const int ctBOUNCE_SENSIB_BOTAO = 80 //	350 foi bom	
#define ctBOUNCE_SENSIB_BOTAO 260

	


// vars que permitem que um botao seja clicado apenas 1 vez, em vez de um monte, quado um touch ocorre
// este modelo conta os cliques disparados pelo touch ocorrido, que sempre sao muitos
// O sistema deve contar apenas o gBounce_ContaClick = 0 como o disparador do evento desejado.
// qualquer numero maior, sao os cliques extras disparados pelo botao, que o programa deve ignorar
// Depois de passado X milissegundos (ctBOUNCE_SENSIB_BOTAO) depis do touch, o programa zera a var global de cliques 
// permitindo que um novo clique ocorra
volatile unsigned long gBounce_time_inicio;
volatile unsigned long gBounce_time_atual;
volatile unsigned long gBounce_time_tempo_passado;

volatile int gBounce_SegundosPassados;
volatile int gBounce_Last_SegundosPassados;


// var que conta o numero de cliques executaados no botao
volatile int gBounce_ContaClick = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// LED INDICADOR DE PROGRAMA RODANDO COM SUCESSO
// ---------------------------------------------
//
// O  led do arduino é usado para indicar o funcionamento do programa. ele pisca em um intervalo de tempo determinado
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Tempo de alternancia da luz do led
//const int ctLED_ON_TEMPO = 2400;		// tempo em ms
#define ctLED_ON_TEMPO 2400

		

// permitindo que um novo clique ocorra
unsigned long gLedON_time_inicio;
unsigned long gLedON_time_atual;
unsigned long gLedON_time_tempo_passado;

int gLedON_SegundosPassados;
int gLedON_Last_SegundosPassados;
bool gLedON_EstadoAtual;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TELA
// ----
//
// variaveis que controlam se a tela esta desenhada, para impedir que ela fique sendo redesenhada o tempo todo e
// var que define o tipo de tela sendo usado 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// var que define a tela sendo usada
//String gTela_Hardware;		// ER-TFTM070-5 | TERMINAL definidos na rotina de iniciar vars
const String ctTELA_HARDWARE;

//#define ctTELA_HARDWARE F("ER-TFTM070-5")
//#define ctTELA_HARDWARE F("TERMINAL")


// var que define a biblioteca de tela usada
//#define ctTELA_BIB_USADA_Adafruit_RA8875 1 		// Adafruit_RA8875 | RA8875 definidos na rotina de iniciar vars
#define ctTELA_BIB_USADA_RA8875 1		// Adafruit_RA8875 | RA8875 definidos na rotina de iniciar vars


// Adafruit_RA8875 | RA8875 definidos na rotina de iniciar vars


// Vars de controle que verificam se uma determinada tela esta renderizada para nao render de novo
bool gTelaRenderizada_TecNum;
bool gTelaRenderizada_TecAlfa;
bool gTelaRenderizada_STANDBY;
bool gTelaRenderizada_LOGIN;
bool gTelaRenderizada_OPERACAO;
bool gTelaRenderizada_INSTALACAO;
bool gTelaRenderizada_ADMIN;
bool gTelaRenderizada_DEBUG;
bool gTelaRenderizada_TESTE;

bool gTelaRenderizada_LER_RFID;
bool gTelaRenderizada_OPERACAO_SERVICO;

bool gTelaRenderizada_MSGBOX;

bool gTelaRenderizada_ADMIN_NOVO_CARD;
bool gTelaRenderizada_ADMIN_USUARIOS;
bool gTelaRenderizada_ADMIN_CHOPPS;
bool gTelaRenderizada_ADMIN_ENGATADOS;
bool gTelaRenderizada_ADMIN_OUTROS;




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RFID
// ----
//
// variavel que controla qual o RFID que estamos usando
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// var que define a tela sendo usada
//#define ctRFID_HARDWARE F("MFRC522")
#define ctRFID_HARDWARE F("PN532")


// Numero de tentativas de leitura do RFID para achar um cartao 
#define ctTIMEOUT_TENTATIVA_RFID 5		


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// VARIAVEIS DE SESSAO
// -------------------
//
// variaveis qye controlam o login e pessoa logada
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool gSessao_Logado;
int gSessao_IDUser;
int gSessao_Nivel;
String gSessao_Nome;
float gSessao_SaldoAtual;
String gSessao_CPF;
String gSessao_DataCad;
String gSessao_ID_Cartao;






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// VARIAVEIS DE OPERACAO - SERVICO
// -------------------
//
// variaveis que controlam o momento de retirada de chopp
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// var que controla qual o ID da torneira sendo usada no momento
int gServico_ID_TorneiraAtual;



//float gAjusteFluxo = 23; original do sensor
float gAjusteFluxo = 19; // teste x com 2 bar (oficiaL) . numero ajustado para mangueira 3/8
// float gAjusteFluxo = 7.5; // testes margarida murch com ar, na casa do murch




int gAjuste_fino_baixo = 1;
int gPulse_ideal = 18;
int gAjuste_fino_alto = 1;


// Pino do sensor ativo no momento
int gPinoSensorFluxoAtivo = -1;


// Pino da torneira ativa no momento
int gPinoReleTorneiraAtiva = -1;

bool gFLOW_Reinicia_Contador = true;
bool gFLOW_Fluxo_Iniciado = true;


float gFLOW_time_inicio;
float gFLOW_time_atual;
float gFLOW_time_tempo_passado;


int gFLOW_PulsosNosUltimosXseg = 0;
int gFLOW_PulsosNoInicio = 0;


float gFLOW_SegundosPassados;


#define ctLIMITE_IGNORA_PULSOS 3


volatile uint16_t gFlow_Pulses_Atual = 0;
volatile float gFlow_Pulses_Corrigido_Atual = 0;
volatile uint8_t gLastflowpinstate_Atual;
volatile uint32_t gLastflowratetimer_Atual = 0;
volatile float gFlowrate_Atual;
volatile float gFaixaVelAtual = 99;








//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





// Init global vars with their operational values
void InicializaVars() 
{




	// variaveis princiais
	gModoOperacao = F("INICIO");  
	gModoOperacao_SubTela = F("");


	//ctTELA_HARDWARE = F("TERMINAL");
	ctTELA_HARDWARE = F("ER-TFTM070-5");


	// led de indicao de funcionamento
	gLedON_time_inicio = millis();
	gLedON_EstadoAtual = false;


	// controle de render de tela
	gTelaRenderizada_TecNum = false;
	gTelaRenderizada_TecAlfa = false;
	gTelaRenderizada_STANDBY = false;	
	gTelaRenderizada_LOGIN = false;
	gTelaRenderizada_OPERACAO = false;	
	gTelaRenderizada_INSTALACAO = false;
	gTelaRenderizada_ADMIN = false;
	gTelaRenderizada_DEBUG = false;
	gTelaRenderizada_TESTE = false;
	gTelaRenderizada_LER_RFID = false;
	gTelaRenderizada_OPERACAO_SERVICO = false;
	gTelaRenderizada_MSGBOX = false;

	gTelaRenderizada_ADMIN_NOVO_CARD = false;
	gTelaRenderizada_ADMIN_USUARIOS = false;
	gTelaRenderizada_ADMIN_CHOPPS = false;
	gTelaRenderizada_ADMIN_ENGATADOS = false;
	gTelaRenderizada_ADMIN_OUTROS = false;





	//teclado
	gTecladoNum_ValAtual = F("");
	gTecladoAlfa_ValAtual = F("");
				

	// Variaveis de sessao:
	gSessao_Logado = false;
	gSessao_IDUser = -1;
	gSessao_Nivel = -1;
	gSessao_Nome = F("");
	gSessao_SaldoAtual = -1;				
	gSessao_CPF = F("");
	gSessao_DataCad = F("");
	gSessao_ID_Cartao = F("");
	
	gServico_ID_TorneiraAtual = -1;
	
	// inicializa var de engatados
	for (int x = 0 ; x <= ctMAX_TORNEIRAS ; x++)
	{
		gaEngatados[x] = F("");
	}	 	

	// incia a var dos botoes genericos de tela
	for (int x = 0 ; x <= ctMAX_BOTOES_GEN_TELA ; x++)
	{
		gaBotoesGenTela[x] = F("");
	}

}
