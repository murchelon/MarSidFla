//Programa : Teste Botoes acionando rele


int gPinoRele_1 = 45;
int gPinoRele_2 = 46;
int gPinoRele_3 = 47;
 
int porta_botao1 = 40;
int porta_botao2 = 41;
int porta_botao3 = 42;
int porta_botao4 = 43;
 
//Armazena o estado do rele - 0 (LOW) ou 1 (HIGH)
int estadorele1 = 1;
int estadorele2 = 1;
int estadorele3 = 1;

//Armazena o valor lido dos botoes
int leitura1 = 0;
int leitura2 = 0;
int leitura3 = 0;
int leitura4 = 0;
 
void setup()
{
  //Define pinos para o rele como saida
  pinMode(gPinoRele_1, OUTPUT);
  pinMode(gPinoRele_2, OUTPUT);
  pinMode(gPinoRele_3, OUTPUT);
  
  //Define pinos dos botoes como entrada
  pinMode(porta_botao1, INPUT); 
  pinMode(porta_botao2, INPUT);
  pinMode(porta_botao3, INPUT); 
  pinMode(porta_botao4, INPUT);
  
  //Estado inicial dos reles - desligados
  digitalWrite(gPinoRele_1, HIGH);
  digitalWrite(gPinoRele_2, HIGH);
  digitalWrite(gPinoRele_3, HIGH);
}
 
void loop()
{
  //Verifica o acionamento do botao 1
  leitura1 = digitalRead(gPinoRele_1);
  if (leitura1 != 0)
  {
    while(digitalRead(porta_botao1) != 0)
    {
      delay(100);
    }
    //Inverte o estado da porta
    estadorele1 = !estadorele1;
    //Comandos para o rele 1
    digitalWrite(gPinoRele_1, estadorele1);  
  }   
  
  //Verifica o acionamento do botao 2
  leitura2 = digitalRead(gPinoRele_2);
  if (leitura2 != 0)
  {
    while(digitalRead(porta_botao2) != 0)
    {
      delay(100);
    }
    //Inverte o estado da porta
    estadorele2 = !estadorele2;
    //Comandos para o rele 2
    digitalWrite(gPinoRele_2, estadorele2);  
  } 

  //Verifica o acionamento do botao 3
//  leitura1 = digitalRead(gPinoRele_3);
//  if (leitura3 != 0)
//  {
//    while(digitalRead(porta_botao3) != 0)
//    {
//      delay(100);
//    }
//    //Inverte o estado da porta
//    estadorele1 = !estadorele1;
//    //Comandos para o rele 3
//    digitalWrite(gPinoRele_3, estadorele3);  
//  }   

//Verifica o acionamento do botao 4
    leitura1 = digitalRead(gPinoRele_3);
    if (leitura4 != 0)
  {
    while(digitalRead(porta_botao4) != 0)
   {
      delay(100);
    }
    //Inverte o estado da porta
 //   estadorele1 = !estadorele1;
 //   estadorele2 = !estadorele2;
    estadorele3 = !estadorele3;
    
    //Comandos para o rele 1,2 e 3
//    digitalWrite(gPinoRele_1, estadorele1);
//    digitalWrite(gPinoRele_2, estadorele2);  
    digitalWrite(gPinoRele_3, estadorele3);    
  }   

}
