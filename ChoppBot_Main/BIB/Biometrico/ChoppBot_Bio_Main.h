
// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  //digitalWrite(gPinoRele_1, LOW);
  Serial.print("passei aqui 1\n");
  delay(5000);
  //digitalWrite(gPinoRele_1, HIGH);
  Serial.print("fui 1\n");


  
  return finger.fingerID; 
}



void BIOMETRICO_Inicia()
{



	finger.begin(57600);

	TELA_Texto("biometrico inicializado");

	if (finger.verifyPassword())
	{
		Serial.println("Found fingerprint sensor!");
	} 
	else 
	{
		Serial.println("Did not find fingerprint sensor :(");
		while (1) 
		{ 
			delay(1); 
		}
	}

	finger.getTemplateCount();
	Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
	Serial.println("Waiting for valid finger...");


	getFingerprintIDez();

}





