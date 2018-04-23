//Programa : Teste botao
 
int gPinoRele_1 = 45;
int gPinoRele_2 = 46;
int gPinoRele_3 = 47;
 
int porta_botao1 = 40;
int porta_botao2 = 41;
int porta_botao3 = 42;
int porta_botao4 = 43;
 
void setup()
{
  //Define pinos para o rele como saida
  pinMode(gPinoRele_1, OUTPUT); 
  pinMode(gPinoRele_2, OUTPUT);
  pinMode(gPinoRele_3, OUTPUT);
}
  
void loop()
{
  digitalWrite(gPinoRele_1, LOW);  //Liga rele 1
  digitalWrite(gPinoRele_2, HIGH); //Desliga rele 2
  delay(2000);
  digitalWrite(gPinoRele_1, HIGH); //Desliga rele 1
  digitalWrite(gPinoRele_2, LOW);  //Liga rele 2
  delay(2000);
}
