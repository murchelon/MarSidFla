#include <UTFT.h>
#include <ITDB02_Touch.h>


extern uint8_t BigFont[];
extern uint8_t SmallFont[];

// constantes do menu

const int MENU_PRINCIPAL = 1000;
const int ACT_BOTAO1 = 1001;
const int ACT_BOTAO2 = 1002;
const int ACT_BOTAO3 = 1003;
const int ACT_BOTAO4 = 1004;



// Aqui deve-se saber qual o CI de controle da sua tela, no meu caso o SSD1289
UTFT myGLCD(ITDB32S,38,39,40,41);
ITDB02_Touch myTouch(42,43,44,45,46);


// Constantes de Menu \ Ações
int x, y;
int coordTouchButton[6][5];
int qtdButtons = 0;


void printButton(String titulo, int id, int x1, int y1, int x2, int y2){
    myGLCD.setColor(0, 0, 255);
    myGLCD.fillRoundRect (x1, y1, x2, y2);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (x1, y1, x2, y2);
    myGLCD.setBackColor(0, 0, 255);
    myGLCD.print(titulo, x1+10, centered(y1,y2));
    coordTouchButton[qtdButtons][0] = x1;
    coordTouchButton[qtdButtons][1] = y1;
    coordTouchButton[qtdButtons][2] = x2;
    coordTouchButton[qtdButtons][3] = y2;
    coordTouchButton[qtdButtons][4] = id;
    qtdButtons++;
}



void printMenuPrincipal(){
  myTouch.InitTouch(orientation);
  myGLCD.clrScr();
  printButton("BOTAO 1", ACT_BOTAO1, 10, 30, 150, 80);
  printButton("BOTAO 2", ACT_BOTAO2, 160, 30, 300, 80);
  printButton("BOTAO 3", ACT_BOTAO3, 10, 90, 150, 140);
  printButton("BOTAO 4", ACT_BOTAO4, 160, 90, 300, 140);
//  Se precisar de mais botões
//  printButton("", 10, 150, 150, 200);
//  printButton("", 160, 150, 300, 200);
  printTitle("Titulo Controle X");
  printStatus("Status ok!");
}


void printStatus(String texto){
    myGLCD.setBackColor(0, 0, 200);
    myGLCD.print("                                        ", LEFT, 224);
    myGLCD.setColor(0, 255, 0);
    myGLCD.print(texto, LEFT, 224);
}

void printTitle(String texto){
    myGLCD.setBackColor(0, 0, 102);
    myGLCD.print("                                                            ", LEFT, LEFT);
    myGLCD.setColor(0, 255, 0);
    myGLCD.print(texto, LEFT, LEFT);
}

void executeTouchCmd(int id){

  switch (id)
  {
    case MENU_PRINCIPAL:
      printMenuPrincipal();
      menu_action = id;
      break;

    case BOTAO_1:
      //executaAcao1();
      menu_action = id;
      break;


    default:
      Serial1.println(id);
      break;
  }
 }

// Draw a red frame while a button is touched
void waitForIt(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}


int getButton(int x, int y){
        for(int i=0;i<qtdButtons;i++){
            if ((y>=coordTouchButton[i][1]) && (y<=coordTouchButton[i][3])){
                if ((x>=coordTouchButton[i][0]) && (x<=coordTouchButton[i][2])){
                    tone(PIN_BUZZ, NOTE_C4, 8);
                    waitForIt(coordTouchButton[i][0], coordTouchButton[i][1], coordTouchButton[i][2],          coordTouchButton[i][3]);
                    return coordTouchButton[i][4];
                }
            }
        }
}

void getTouch(){
        if (myTouch.dataAvailable()){
            myTouch.read();
            x=myTouch.getX();
            y=map(myTouch.getY(), 0, 240, 240, 0);
//            y=myTouch.getY();
            Serial.print("x:");
            Serial.println(x);
            Serial.print("y:");
            Serial.println(y);
            executeTouchCmd(getButton(x,y));
        }
}

void setup()
{
  // Initial setup
  myGLCD.InitLCD(orientation);
  myGLCD.clrScr();

  myTouch.InitTouch(orientation);
  myTouch.setPrecision(PREC_HI);

  myGLCD.setFont(SmallFont);
  myGLCD.setBackColor(0, 0, 255);

  printMenuPrincipal();
}

void loop(){
  getTouch();
}
