//Pino ligado ao push-button 1
int porta_botao1 = 40;
int gPinoRele_1 = 45;
int buttonState_1;
int var=0;       // valor instantaneo enviado pelo botão
int var2=0;     // valor guardado

//Pino ligado ao push-button 2
int porta_botao2 = 41;
int gPinoRele_2 = 46;
int buttonState_2;

//Pino ligado ao push-button 3
int porta_botao3 = 42;
int gPinoRele_3 = 47;
int buttonState_3;

//Pino ligado ao push-button 4
int porta_botao4 = 43;
int buttonState_4;

void setup()
{
  pinMode(gPinoRele_1, OUTPUT);
  pinMode(porta_botao1, INPUT);

  pinMode(gPinoRele_2, OUTPUT);
  pinMode(porta_botao2, INPUT);

  pinMode(gPinoRele_3, OUTPUT);
  pinMode(porta_botao3, INPUT);

  pinMode(porta_botao4, INPUT);

  digitalWrite(gPinoRele_1, HIGH);
  digitalWrite(gPinoRele_2, HIGH);
  digitalWrite(gPinoRele_3, HIGH);

}

void loop() 
{
  // Verifica se o estado do botao foi alterado
  buttonState_1 = digitalRead(porta_botao1);
  buttonState_2 = digitalRead(porta_botao2);
  buttonState_3 = digitalRead(porta_botao3);
  buttonState_4 = digitalRead(porta_botao4);



  
  //Se o botao 1 foi apertado
  if (buttonState_1 == HIGH) 
  {
   // Liga o rele    
    digitalWrite(gPinoRele_1, LOW);  
    delay(2000);
  } 
  else 
  {
    // Apaga o LED
    digitalWrite(gPinoRele_1
    , HIGH); 
  }


}

