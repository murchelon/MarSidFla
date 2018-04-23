int porta_botao1 = 40;
int gPinoRele_1 = 45;
int var=0;       // valor instantaneo enviado pelo botão
int var2=0;     // valor guardado
int estado=0;  // guarda o valor 0 ou 1 (HIGH ou LOW)
void setup()
{
  pinMode(gPinoRele_1, OUTPUT);
  pinMode(porta_botao1, INPUT);
}
void loop()
{
  var=digitalRead(porta_botao1); // ler o valor enviado pelo botão: "HIGH" ou "LOW"
  if ((var == HIGH) && (var2 == LOW)) {
    estado = 1 - estado;
    delay(200); // de-bouncing
  }
  var2=var;
  if (estado == 1) {
    digitalWrite(porta_botao1, HIGH); // liga o rele
  } else {
    digitalWrite(porta_botao1, LOW);  // desliga o rele
  }
  delay(2000);
}
