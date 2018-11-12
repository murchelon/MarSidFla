// teste de rele


int gPinoRele_1 = 45;
int gPinoRele_2 = 46;
int gPinoRele_3 = 47;
int gPinoRele_4 = 48;

void setup() 
{
 
    pinMode(gPinoRele_1, OUTPUT);
    pinMode(gPinoRele_2, OUTPUT);
    pinMode(gPinoRele_3, OUTPUT);
    pinMode(gPinoRele_4, OUTPUT);

    digitalWrite(gPinoRele_1, HIGH);
    digitalWrite(gPinoRele_2, HIGH);
    digitalWrite(gPinoRele_3, HIGH);
    digitalWrite(gPinoRele_4, HIGH);

    Serial.begin(115200);
}

void loop() 
{
    
    digitalWrite(gPinoRele_1, LOW);
    Serial.print("LIGADO Rele 1\n");
    delay(1000);

    digitalWrite(gPinoRele_1, HIGH);
    Serial.print("Desligado Rele 1\n");
    delay(2000);
    
    digitalWrite(gPinoRele_2, LOW);
    Serial.print("LIGADO Rele 2\n");
    delay(1000);

    digitalWrite(gPinoRele_2, HIGH);
    Serial.print("Desligado Rele 2\n");
    delay(2000);
    
    digitalWrite(gPinoRele_3, LOW);
    Serial.print("LIGADO Rele 3\n");
    delay(1000);

    digitalWrite(gPinoRele_3, HIGH);
    Serial.print("Desligado Rele 3\n");
    delay(2000);
    
    digitalWrite(gPinoRele_4, LOW);
    Serial.print("LIGADO Rele 4\n");
    delay(1000);

    digitalWrite(gPinoRele_4, HIGH);
    Serial.print("Desligado Rele 4\n");
    delay(2000);

}
