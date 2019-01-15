

void GUI_StartScreen()
{

	if (String(GUI_SCREEN_HARDWARE) == String(F("ER-TFTM070-5")))
	{

		pinMode(GUI_RA8875_INT, INPUT);
		digitalWrite(GUI_RA8875_INT, HIGH);


		GUI_tft.begin(RA8875_800x480);  

		//tft.fillScreen(RA8875_BLACK);//fill screen black
		//tft.changeMode(TEXT);
		//tft.setCursor(0,0);

			
	

		#ifdef GUI_LIB_IN_USE_Adafruit_RA8875


			
			GUI_tft.displayOn(true);
			GUI_tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
			GUI_tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
			GUI_tft.PWM1out(255);
			//GUI_tft.fillScreen(RA8875_BLACK);

			/* Switch to text mode */  
			GUI_tft.textMode();

			
		#elif GUI_LIB_IN_USE_RA8875

			GUI_tft.touchBegin(RA8875_INT);//enable Touch support!

		#endif		

		GUI_tft.touchEnable(true);
	}

}




void GUI_SetFontSize(int FontSize)
{
	#ifdef GUI_LIB_IN_USE_Adafruit_RA8875

		GUI_tft.textEnlarge(FontSize);
		
	#elif GUI_LIB_IN_USE_RA8875

		GUI_tft.setFontScale(FontSize);

	#endif	
}


bool GUI_touchDetect()
{
	#ifdef GUI_LIB_IN_USE_Adafruit_RA8875

		return GUI_tft.touched();
		
	#elif GUI_LIB_IN_USE_RA8875

		return GUI_tft.touchDetect();

	#endif	
}


bool GUI_touchReadPixel(uint16_t *x, uint16_t *y)
{
	#ifdef GUI_LIB_IN_USE_Adafruit_RA8875

		return GUI_tft.touchRead(x, y);
		
	#elif GUI_LIB_IN_USE_RA8875

		GUI_tft.touchReadPixel(x, y);
		return true;		

	#endif	
}




void GUI_ClearScreen()
{
	delay(100);
	GUI_tft.fillScreen(RA8875_BLACK);
}



// Loga uma informacao no terminal
void GUI_LogTerm (String Texto)
{
	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}


// Loga uma informacao no terminal - OVERRIDE int
void GUI_LogTerm (int Texto)
{
	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}


// Loga uma informacao no terminal - OVERRIDE int
void GUI_LogTerm (unsigned long Texto)
{
	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}

// Loga uma informacao no terminal - OVERRIDE int
void GUI_LogTerm (double Texto)
{

	Serial.println(Texto);
	Serial.flush();
	serialEventRun();
}


String GUI_Right (String Alvo, int Qtde)
{
	return Alvo.substring(Alvo.length() - Qtde);
}


String GUI_Left (String Alvo, int Qtde)
{
	return Alvo.substring(0, Qtde);
}
