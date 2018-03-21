// teste de rele


int gPinoRele_1 = 45;
int gPinoRele_2 = 46;
int gPinoRele_3 = 47;

void setup() 
{
 
  pinMode(gPinoRele_1, OUTPUT);
  pinMode(gPinoRele_2, OUTPUT);
  pinMode(gPinoRele_3, OUTPUT);

  digitalWrite(gPinoRele_1, HIGH);
  digitalWrite(gPinoRele_2, HIGH);
  digitalWrite(gPinoRele_3, HIGH);

  Serial.begin(9600);
}

void loop() 
{
  digitalWrite(gPinoRele_1, LOW);
  Serial.print("passei aqui 1\n");
  delay(5000);
  digitalWrite(gPinoRele_1, HIGH);
  Serial.print("fui 1\n");
  
  digitalWrite(gPinoRele_2, LOW);
  Serial.print("passei aqui 2 \n");
  delay(5000);
  digitalWrite(gPinoRele_2, HIGH);
  Serial.print("fui 2\n");
  
  digitalWrite(gPinoRele_3, LOW);
  Serial.print("passei aqui 3\n");
  delay(5000);
  digitalWrite(gPinoRele_3, HIGH);
  Serial.print("fui 3\n");




//  digitalWrite(gPinoRele_1, HIGH);
//  Serial.print("fui 1\n");
//  delay(5000);
  
//  digitalWrite(gPinoRele_2, HIGH);
//  Serial.print("fui 2\n");
//  delay(5000);
  
//  digitalWrite(gPinoRele_3, HIGH);
//  Serial.print("fui 3\n");
//  delay(2000);

}
