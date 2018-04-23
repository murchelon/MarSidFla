/*
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
*/
 
#include <SPI.h>
#include <SD.h>
 
//criar um objeto File para manipular um arquivo
File myFile;
 
void setup() {
  Serial.begin(9600);
  while (!Serial);
 
  Serial.print("Inicializa o SD card...");
 
  if (!SD.begin(4)) {
    Serial.println("Nao inicializado. Veja no texto adiante sobre isso.");
    return;
  }
  Serial.println("Beleza! Seguindo...");
 
  /* A biblioteca SD tem um metodo para abrir arquivos e esse arquivo aberto
  sera armazenado no objeto myFile, descrito ao inicio desse codigo. Somente 
  um arquivo pode ser aberto por vez, portanto nao se esqueca de fecha-lo
  antes de abrir um novo ou voce tera problemas.
  */
 
  myFile = SD.open("bB.txt", FILE_WRITE);
 
  //Se o arquivo foi aberto com sucesso, escreve nele
  if (myFile) {
    Serial.print("Escrevendo para bB.txt");
    myFile.println("dobitaobyte.com.br");
 
    // Terminou de escrever, fecha-se o arquivo:
    myFile.close();
 
    Serial.println("Escrevinhado.");
 
  }
  else {
    // Se nao deu certo, comeca a dar merda desse ponto
    Serial.println("Nao foi possivel abrir o arquivo");
  }
 
  // Agora vamos abri-lo para leitura
  myFile = SD.open("bB.txt");
  if (myFile) {
    Serial.println("Conteudo de bB.txt:");
 
    // Le todo o arquivo...
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    //Finalizado, fecha-se o arquivo
    myFile.close();
  }
  else {
    // Se deu erro acima, aqui tambem dara.
    Serial.println("Nao pude abrir o arquivo.");
  }
}
 
void loop() {
  // Aqui poderia ser colocada uma rotina para leitura de sensores e entao os dados
  // poderiam ser gravados, precedendo-os pelo timestamp. Ai esta seu data logger! 
}
