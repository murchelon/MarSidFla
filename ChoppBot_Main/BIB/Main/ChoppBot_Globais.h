
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  GLOBAIS MAIN
//  ============
//
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

String gModoOperacao = ""; 


const unsigned long gTimeoutOpcao = 7000;		// tempo em ms para timeout das opcoes a serem escolhidas

//const int gPin_BotaoDebug2 = 2;
//const int gPin_BotaoDebug3 = 3;
//const int gPin_BotaoDebug4 = 4;
//const int gPin_BotaoDebug5 = 5;



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TECLADO
// -------
//
// Vars necessarias para o teclado numerico 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool gTeclado_Renderizado = false;


String gTeclado_ValAtual = "";


const int ctTECLADO_TOTAL_BOTOES = 14;


// var que armazena a posicao inicial xy renderizada dos botoes e seu tamanho para poder serem usadas no touch
// var iniciada com os valores abaixo e depois modificada quando os botoes do teclado sao renderizados
String aTeclado_PosBotoes[ctTECLADO_TOTAL_BOTOES]={"X01,TAM,Y01,TAM",
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
												   "X13,TAM,Y12,TAM",
												   "X14,TAM,Y12,TAM"
												   };

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BOTOES TOUCH - BOUNCE
// ---------------------
//
// Vars necessarias para controlar o press dos botoes e nao permitir double press (bounce)
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Tempo de sensibilidade dos botoes em uma determinada tela. Para evitar o double press
const int ctBOUNCE_SENSIB_BOTAO = 50;		
	


// vars que permitem que um botao seja clicado apenas 1 vez, em vez de um monte, quado um touch ocorre
// este modelo conta os cliques disparados pelo touch ocorrido, que sempre sao muitos
// O sistema deve contar apenas o gBounce_ContaClick = 0 como o disparador do evento desejado.
// qualquer numero maior, sao os cliques extras disparados pelo botao, que o programa deve ignorar
// Depois de passado X milissegundos (ctBOUNCE_SENSIB_BOTAO) depis do touch, o programa zera a var global de cliques 
// permitindo que um novo clique ocorra
unsigned long gBounce_time_inicio;
unsigned long gBounce_time_atual;
unsigned long gBounce_time_tempo_passado;

int gBounce_SegundosPassados;
int gBounce_Last_SegundosPassados;


// var que conta o numero de cliques executaados no botao
int gBounce_ContaClick = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// abaixo daqui sao variaveis que estao ai... mas nao sei bem onde estamos usando. TODO: limpar isto e usar ou nao (fora a funcao initvars abaixo que eh correta)

//#define BOTAO1_PINO 40
//#define BOTAO2_PINO 41
//#define BOTAO3_PINO 42
//#define BOTAO4_PINO 43




// RELE ======================================================================

#define gPinoRele_1 45
#define gPinoRele_2 46
#define gPinoRele_3 47





int EstadoBotao_Rele1 = 0;

volatile uint8_t lastflowpinstate;

// include the SD library:
//#include <SPI.h>
//#include <SD.h>






// Init global vars with their operational values
void InicializaVars() 
{
	gModoOperacao = "INICIO";  
}
