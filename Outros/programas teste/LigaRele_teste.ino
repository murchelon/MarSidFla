// teste de rele


int gPinoRele_1 = 32;


void setup() {
  // put your setup code here, to run once:

  pinMode(gPinoRele_1, OUTPUT);

  digitalWrite(gPinoRele_1, LOW);
  
  //delay(2000);

  Serial.begin(9600);
  Serial.print("Ligado\n");
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(gPinoRele_1, LOW);
  delay(2000);
  //digitalWrite(gPinoRele_1, HIGH);
  //digitalWrite(gPinoRele_1, HIGH);
  Serial.print("passei aqui\n");
    

}
