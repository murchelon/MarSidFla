


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

			GUI_tft.touchBegin(GUI_RA8875_INT);//enable Touch support!

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

		//GUI_tft.setFontSize(X16,true);

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




void GUI_ResetGenBtn()
{

	g_GUI_GenBtn_BtnCount = 0;
	
	for (int t = 0 ; t <= ct_GUI_MAX_BUTTONS_ONSCREEN - 1 ; t++)
	{
		g_GUI_aGenBtn[t] = F("");
	}
}


void GUI_PrintInTerm_aGenBtn()
{
	int EncontrouDados = 0;

	for (int z = 0 ; z <= ct_GUI_MAX_BUTTONS_ONSCREEN - 1 ; z++)
	{
		if (g_GUI_aGenBtn[z] != F(""))
		{
			EncontrouDados = 1;
			LogTerm( String(F("g_GUI_aGenBtn[")) + String(z) + String(F("] = ")) + g_GUI_aGenBtn[z] );
		}
	}

	if (EncontrouDados == 0)
	{
		LogTerm(F("g_GUI_aGenBtn is empty"));
	}
}



void GUI_ResetSelOptions()
{
	for (int t = 0 ; t <= ct_GUI_MAX_SELECT_OPTIONS - 1 ; t++)
	{
		g_GUI_aSelOptions[t] = F("");
	}
}


void GUI_PrintInTerm_aSelOptions()
{
	int EncontrouDados = 0;

	for (int z = 0 ; z <= ct_GUI_MAX_SELECT_OPTIONS - 1 ; z++)
	{
		if (g_GUI_aSelOptions[z] != F(""))
		{
			EncontrouDados = 1;
			LogTerm( String(F("g_GUI_aSelOptions[")) + String(z) + String(F("] = ")) + g_GUI_aSelOptions[z] );
		}
	}

	if (EncontrouDados == 0)
	{
		LogTerm(F("g_GUI_aSelOptions is empty"));
	}
}


void GUI_Define_aSelOptions(String aOptions[], int OptionsTotalCount)
{
	int EncontrouDados = 0;

	//int OptionsTotalCount = 3;

	for (int z = 0 ; z <= OptionsTotalCount; z++)
	{
		if (aOptions[z] != F(""))
		{
			EncontrouDados = 1;

			g_GUI_aSelOptions[z] = aOptions[z];

			//LogTerm( String(F("g_GUI_aSelOptions[")) + String(z) + String(F("] = ")) + g_GUI_aSelOptions[z] );
		}
	}

	if (EncontrouDados == 0)
	{
		LogTerm(F("passed array aOptions is empty"));
	}
}




