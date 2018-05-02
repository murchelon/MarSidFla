
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  FUNCOES DE SUPORTE
//  ==================
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// Ativa/desativa o led de debug (led imbutido no arduino)
void Led_Light(boolean Valor) 
{
	if (Valor == true)
	{
		digitalWrite(LED_BUILTIN, HIGH);    
	}
	else
	{
		digitalWrite(LED_BUILTIN, LOW); 
	}
  
}


// Loga uma informacao no terminal
void LogTerm (String Texto)
{
	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}


// Loga uma informacao no terminal - OVERRIDE int
void LogTerm (int Texto)
{
	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}


// Loga uma informacao no terminal - OVERRIDE int
void LogTerm (unsigned long Texto)
{
	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}

// Loga uma informacao no terminal - OVERRIDE int
void LogTerm (double Texto)
{

	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}






String FormatComZerosAesq(int ValorInt)
{
	if ((ValorInt >= 0) && (ValorInt <= 9)) 
	{
		return String("00") + ValorInt;
	}

	if ((ValorInt >= 10) && (ValorInt <= 99)) 
	{
		return String("0") + ValorInt;
	}

	if ((ValorInt >= 100) && (ValorInt <= 999)) 
	{
		return String("") + ValorInt;
	}

}


    
 
        
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
