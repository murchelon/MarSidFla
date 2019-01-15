
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  FUNCOES DE SUPORTE
//  ==================
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255,   0 */
#define White           0xFFFF      /* 255, 255, 255 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */
#define Pink            0xF81F

    
#define CinzaShadow     		rgb565_from_triplet(99, 99, 99)       
#define CinzaFundoTitMsgBox     rgb565_from_triplet(201, 201, 201)      
#define CinzaLabels			    rgb565_from_triplet(150, 150, 150)     
#define CinzaClaro			    rgb565_from_triplet(190, 190, 190)     
#define VerdeOK			    	rgb565_from_triplet(137, 255, 157)     
#define LaranjaAlerta	    	rgb565_from_triplet(255, 216, 181)     
#define AzulClaro            	rgb565_from_triplet(155, 155, 255)




void(*resetFunc) (void) = 0;  // funcao interna do arduino que reseta o arduino

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


String Right(String Alvo, int Qtde)
{
	return Alvo.substring(Alvo.length() - Qtde);
}


String Left(String Alvo, int Qtde)
{
	return Alvo.substring(0, Qtde);
}


String ReadConsoleInput()
{

	if (Serial.available() > 0) 
	{
		return Serial.readString();
	}
	else
	{
		return String("");
	}

}








String FormatComZerosAesq(int ValorInt)
{
	if ((ValorInt >= 0) && (ValorInt <= 9)) 
	{
		return String(F("00")) + ValorInt;
	}

	if ((ValorInt >= 10) && (ValorInt <= 99)) 
	{
		return String(F("0")) + ValorInt;
	}

	if ((ValorInt >= 100) && (ValorInt <= 999)) 
	{
		return String(F("")) + ValorInt;
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

    if (found > index)
    {
    	return data.substring(strIndex[0], strIndex[1]);
    }
    else
    {
    	return String("");
    }

    //return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}




String CharFromAsc2(int Asc2Value)
{
    char ret;

    ret = Asc2Value;

    return String(ret);
}

// retorna a cor em int16 a partir de rgb
uint16_t rgb565_from_triplet(uint8_t red, uint8_t green, uint8_t blue)
{
  red   >>= 3;
  green >>= 2;
  blue  >>= 3;
  return (red << 11) | (green << 5) | blue;
}


template <class SomeType>
String FormatNumber(SomeType Valor, String Tipo)
{
	String ret = F("");
	String temp = String(Valor);

	temp.replace(F("."), F(","));


	if (Tipo == F("MONEY"))
	{
		ret = F("R$ ");
	}

	if (temp.indexOf(F(",")) < 0)
	{
		ret += temp + ",00";
	}
	else
	{
		ret += temp;
	}
	

	return ret;
}


// reseta o arduino. Ok, descricao totalmente redundante.
void ResetArduino()
{
	resetFunc();
}



String Now()
{
	String retNow;

	retNow = F("03/06/2018 04:20:00");

	return retNow;
}


