

String RFID_Exec_Leitura()
{

	String ret = "1|";

	String idCartao = ""; 

	String aux1 = ""; 

	Adafruit_PN532 nfc(PN532_SS);


	// desabilita SD para efetuar a leitura
	pinMode(DISABLE_CHIP_SELECT, OUTPUT);
	digitalWrite(DISABLE_CHIP_SELECT, HIGH);	


	// inicia componente
	nfc.begin();

	// verifica se deu tudo certo
	uint32_t versiondata = nfc.getFirmwareVersion();

	if (! versiondata)
	{
		LogTerm("RFID: Placa PN53x nao localizada");

		ret = "0|Placa PN53x nao localizada";
		return ret;
	}

	LogTerm("RFID: Placa PN53x localizada com sucesso");
	Serial.print("RFID: Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
	Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);


	// Set the max number of retry attempts to read from a card
	// This prevents us from waiting forever for a card, which is
	// the default behaviour of the PN532.
	//nfc.setPassiveActivationRetries(0xFF); // 255 forever
	nfc.setPassiveActivationRetries(255);

	// configure board to read RFID tags
	nfc.SAMConfig();


	LogTerm("RFID: Aproxime o cartao da leitora RFID ...");

	boolean success;
	uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
	uint8_t uidLength;        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)


	// Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
	// 'uid' will be populated with the UID, and uidLength will indicate
	// if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
	success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

	if (success)
	{

		LogTerm("RFID: Leitura efetuada com sucesso !");

		Serial.print("RFID: UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
		Serial.print("RFID: UID Value: ");

		for (uint8_t i=0; i < uidLength; i++) 
		{

			aux1 = String(uid[i], HEX);

			if (aux1.length() <= 1)
			{
				aux1 = String("0") + aux1;
			}

			idCartao += aux1;

			Serial.print(" 0x");Serial.print(uid[i], HEX); 
		}
		
		Serial.print("\n");

		idCartao.toUpperCase();

		ret += idCartao;

		

		LogTerm("RFID: Cartao decoded: " + idCartao);

		// Wait 1 second before continuing
		delay(1000);
	}
	else
	{
		// PN532 probably timed out waiting for a card
		Serial.println("Timed out waiting for a card");

		LogTerm("RFID: Timeout de leitura");

		ret = "0|RFID: Timeout de leitura";
			
	}	

	//delete nfc;
	nfc = NULL;	

	return ret;	
}