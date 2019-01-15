

/*

	void    	drawPixel(int16_t x, int16_t y, uint16_t color);
	void    	drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
	void    	drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
	void    	fillScreen(uint16_t color);
	void    	drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
	void    	drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
	void    	fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
	void    	drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void    	fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void    	drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void    	fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void    	drawEllipse(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis, uint16_t color);
	void    	fillEllipse(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis, uint16_t color);
	void    	drawCurve(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis, uint8_t curvePart, uint16_t color);
	void    	fillCurve(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis, uint8_t curvePart, uint16_t color);
	void 		drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
	void 		fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);


		if (Tamanho == 0){TamanhoLetra_W = 0;}
		if (Tamanho == 1){TamanhoLetra_W = 16;}
		if (Tamanho == 2){TamanhoLetra_W = 24;}
		if (Tamanho == 3){TamanhoLetra_W = 31;}


*/



void GUI_Render_Label(String Texto, uint16_t CorTexto, uint16_t CorTextoBack, int Tamanho, uint16_t PosX, uint16_t PosY, String Align)
{

	if (String(GUI_SCREEN_HARDWARE) == String(F("ER-TFTM070-5")))
	{

		int TamanhoLetra_W = 0;
		if (Tamanho == 0){TamanhoLetra_W = 7.5;}
		if (Tamanho == 1){TamanhoLetra_W = 16;}
		if (Tamanho == 2){TamanhoLetra_W = 24;}
		if (Tamanho == 3){TamanhoLetra_W = 33;}


		if (CorTexto == 0)
		{
			CorTexto = CinzaLabels;
		}

		if (CorTextoBack == -1)
		{
			GUI_tft.setTextColor(CorTexto);
		}
		else
		{
			GUI_tft.setTextColor(CorTexto, CorTextoBack);
		}
		


		if (Align == F("RIGHT"))
		{
			PosX = 800 - (Texto.length() * TamanhoLetra_W) - 10;
		}


		GUI_SetFontSize(Tamanho);

		GUI_tft.setCursor(PosX, PosY);

		GUI_tft.print(Texto);

	}
}



void GUI_Render_LineWithAllChars(int16_t PosX, int16_t PosY)
{

	if (String(GUI_SCREEN_HARDWARE) == String(F("ER-TFTM070-5")))
	{


		float LetterSize_ToWork = -1;  // font size 0

		String LineToOutput = F("");

		int FontSize = 1;



		if (FontSize == 0){LetterSize_ToWork = ct_GUI_LetterSize_W_Size_0;}
		if (FontSize == 1){LetterSize_ToWork = ct_GUI_LetterSize_W_Size_1;}
		if (FontSize == 2){LetterSize_ToWork = ct_GUI_LetterSize_W_Size_2;}
		if (FontSize == 3){LetterSize_ToWork = ct_GUI_LetterSize_W_Size_3;}

		//GUI_tft.changeMode(GRAPHIC);

		GUI_SetFontSize(FontSize);
	
		//GUI_tft.setFontSize(X32,true);

		for (int ContaLetra = 65 ; ContaLetra <= 90 ; ContaLetra++)
		{

			if (ContaLetra % 2 == 0)
			{
				GUI_tft.setTextColor(Black, White);
			}
			else
			{
				GUI_tft.setTextColor(Black, Yellow);
			}

			//LineToOutput += CharFromAsc2(ContaLetra);

			GUI_tft.setCursor(PosX + ((ContaLetra - 65) * LetterSize_ToWork), PosY);

			LineToOutput = CharFromAsc2(ContaLetra);

			GUI_tft.print(LineToOutput);
		}

	}

}

void GUI_Render_ColumnWithAllChars(int16_t PosX, int16_t PosY)
{

	if (String(GUI_SCREEN_HARDWARE) == String(F("ER-TFTM070-5")))
	{

		float LetterSize_ToWork = -1;  // font size 0

		String LineToOutput = F("");

		int FontSize = 1;

		if (FontSize == 0){LetterSize_ToWork = ct_GUI_LetterSize_H_Size_0;}
		if (FontSize == 1){LetterSize_ToWork = ct_GUI_LetterSize_H_Size_1;}
		if (FontSize == 2){LetterSize_ToWork = ct_GUI_LetterSize_H_Size_2;}
		if (FontSize == 3){LetterSize_ToWork = ct_GUI_LetterSize_H_Size_3;}

		//GUI_tft.changeMode(GRAPHIC);

		GUI_SetFontSize(FontSize);
	
		//GUI_tft.setFontSize(X32,true);

		for (int ContaLetra = 65 ; ContaLetra <= 75 ; ContaLetra++)
		{

			if (ContaLetra % 2 == 0)
			{
				GUI_tft.setTextColor(Black, White);
			}
			else
			{
				GUI_tft.setTextColor(Black, Yellow);
			}

			//LineToOutput += CharFromAsc2(ContaLetra);

			GUI_tft.setCursor(PosX, PosY + ((ContaLetra - 65) * LetterSize_ToWork));

			LineToOutput = CharFromAsc2(ContaLetra);

			GUI_tft.print(LineToOutput);
		}

	}

}


void GUI_Render_Ruler_Hor(int16_t PosX, int16_t PosY)
{
	

	if (String(GUI_SCREEN_HARDWARE) == String(F("ER-TFTM070-5")))
	{

	
		for (int ContaPixel = 0 ; ContaPixel <= 500 ; ContaPixel++)
		{
			GUI_tft.drawPixel(PosX + ContaPixel, PosY, White);

			if (ContaPixel % 8 == 0)
			{
				

				GUI_tft.drawPixel(PosX + ContaPixel, PosY - 2, Yellow);
				GUI_tft.drawPixel(PosX + ContaPixel, PosY - 1, Yellow);
				GUI_tft.drawPixel(PosX + ContaPixel, PosY + 0, Yellow);
				GUI_tft.drawPixel(PosX + ContaPixel, PosY + 1, Yellow);
				GUI_tft.drawPixel(PosX + ContaPixel, PosY + 2, Yellow);

			}
		}

	}

}

void GUI_Render_Ruler_Vert(int16_t PosX, int16_t PosY)
{
	

	if (String(GUI_SCREEN_HARDWARE) == String(F("ER-TFTM070-5")))
	{

	
		for (int ContaPixel = 0 ; ContaPixel <= 500 ; ContaPixel++)
		{
			GUI_tft.drawPixel(PosX, PosY + ContaPixel, White);

			if (ContaPixel % 8 == 0)
			{
				

				GUI_tft.drawPixel(PosX - 2, PosY + ContaPixel, Yellow);
				GUI_tft.drawPixel(PosX - 1, PosY + ContaPixel, Yellow);
				GUI_tft.drawPixel(PosX + 0, PosY + ContaPixel, Yellow);
				GUI_tft.drawPixel(PosX + 1, PosY + ContaPixel, Yellow);
				GUI_tft.drawPixel(PosX + 2, PosY + ContaPixel, Yellow);

			}
		}

	}

}



void GUI_Render_GenericButton(String TAG, 
								String Text, 
								int FontSize, 
								uint16_t FontColor, 
								uint16_t FillColor, 
								int Roundness, 
								uint16_t BorderColor, 
								uint16_t PosX, 
								uint16_t PosY, 
								uint16_t W, 
								uint16_t H )
{

	if (String(GUI_SCREEN_HARDWARE) == String(F("ER-TFTM070-5")))
	{

		/*
		int TamanhoLetra_W = 0;
		if (TamanhoTextoBotao == 0){TamanhoLetra_W = 8;}

		if (TamanhoTextoBotao == 1)
		{
			if (Texto.length() >= 9)
			{
				TamanhoLetra_W = 18;
			}
			else
			{
				TamanhoLetra_W = 16;
			}
			
		}

		if (TamanhoTextoBotao == 2){TamanhoLetra_W = 24;}
		if (TamanhoTextoBotao == 3){TamanhoLetra_W = 33;}

		int TamanhoLetra_H = 0;
		if (TamanhoTextoBotao == 0){TamanhoLetra_H = 8;}
		if (TamanhoTextoBotao == 1){TamanhoLetra_H = 18;}
		*/


		g_GUI_GenBtn_BtnCount++;


		int LetterSize_ToWork_W = -1;
		int LetterSize_ToWork_H = -1;

		if (FontSize == 0){LetterSize_ToWork_W = ct_GUI_LetterSize_W_Size_0;}
		if (FontSize == 1){LetterSize_ToWork_W = ct_GUI_LetterSize_W_Size_1;}
		if (FontSize == 2){LetterSize_ToWork_W = ct_GUI_LetterSize_W_Size_2;}
		if (FontSize == 3){LetterSize_ToWork_W = ct_GUI_LetterSize_W_Size_3;}

		if (FontSize == 0){LetterSize_ToWork_H = ct_GUI_LetterSize_H_Size_0;}
		if (FontSize == 1){LetterSize_ToWork_H = ct_GUI_LetterSize_H_Size_1;}
		if (FontSize == 2){LetterSize_ToWork_H = ct_GUI_LetterSize_H_Size_2;}
		if (FontSize == 3){LetterSize_ToWork_H = ct_GUI_LetterSize_H_Size_3;}


		uint16_t Local_PosX = PosX + (W / 2) - ((Text.length() / 2) * LetterSize_ToWork_W);
		uint16_t Local_PosY = PosY + (H / 2) - LetterSize_ToWork_H / 2;


		//LogTerm(String(BorderColor));

		//border
		if (BorderColor >= 0)
		{
			GUI_tft.fillRoundRect(PosX - 1, PosY - 1, W + 2, H + 2, Roundness, BorderColor);
		}

		// background
		GUI_tft.fillRoundRect(PosX, PosY, W, H, Roundness, FillColor);	

		GUI_SetFontSize(FontSize);

		if (FontColor < 0)
		{
			FontColor = Red;
		}	

		GUI_tft.setTextColor(FontColor);


		// verifica se o texto tem 2 linhas. separador = |
		bool _TextoDuasLinhas = false;

		for (int _ContaCarac = 0 ; _ContaCarac <= Text.length() - 1 ; _ContaCarac++)
		{
			//LogTerm(String(F("Carac = ")) + String(Text.substring(_ContaCarac, _ContaCarac + 1)));

			if (String(Text.substring(_ContaCarac, _ContaCarac + 1)) == String(F("|")))
			{
				_TextoDuasLinhas = true;
			}
		}

		//_TextoDuasLinhas = true;

		if (_TextoDuasLinhas == true)
		{

			String _Linha1 = getValue(Text, '|', 0);
			String _Linha2 = getValue(Text, '|', 1);

			

			Local_PosX = PosX + (W / 2) - ((_Linha1.length() / 2) * LetterSize_ToWork_W);

			if (_Linha1.length() == 4)
			{
				Local_PosX = Local_PosX + 2;
			}

			if (_Linha1.length() == 5)
			{
				Local_PosX = Local_PosX - 2;
			}

			if (_Linha1.length() == 6)
			{
				Local_PosX = Local_PosX + 5;
			}

			if (_Linha1.length() == 7)
			{
				Local_PosX = Local_PosX - 4;
			}


		    GUI_tft.setCursor (Local_PosX, Local_PosY - 16); 
		    GUI_tft.print (_Linha1);	




		    Local_PosX = PosX + (W / 2) - ((_Linha2.length() / 2) * LetterSize_ToWork_W);

			if (_Linha2.length() == 4)
			{
				Local_PosX = Local_PosX + 2;
			}

			if (_Linha2.length() == 5)
			{
				Local_PosX = Local_PosX - 2;
			}

			if (_Linha2.length() == 6)
			{
				Local_PosX = Local_PosX + 5;
			}

			if (_Linha2.length() == 7)
			{
				Local_PosX = Local_PosX - 4;
			}

		    GUI_tft.setCursor (Local_PosX, Local_PosY + 16); 
		    GUI_tft.print (_Linha2);	

		}
		else
		{
		    GUI_tft.setCursor (Local_PosX, Local_PosY); 
		    GUI_tft.print (Text);	
		}


	    g_GUI_aGenBtn[g_GUI_GenBtn_BtnCount - 1] = String(g_GUI_GenBtn_BtnCount) 	+ String(F(";")) + 
					    							 TAG 			+ String(F(";")) + 
					    							 Text 			+ String(F(";")) + 
					    							 String(PosX) 	+ String(F(";")) + 
					    							 String(PosY) 	+ String(F(";")) + 
					    							 String(W) 		+ String(F(";")) + 
					    							 String(H);



	}


}




void GUI_Render_SelectList(int16_t PosX, 
							int16_t PosY, 
							int16_t SizeW, 
							int16_t Lines, 
							uint16_t FillColor, 
							uint16_t BorderColor, 
							int FontSize, 
							uint16_t TextColor, 
							uint16_t TextBackColor)
{

	if (String(GUI_SCREEN_HARDWARE) == String(F("ER-TFTM070-5")))
	{

		//GUI_Render_Ruler_Hor(0, 100);
		//GUI_Render_Ruler_Vert(100, 50);

		//GUI_Render_LineWithAllChars(0, 105);
		//GUI_Render_ColumnWithAllChars(120, 50);

		
		int _CharSizeW = -1;
		int _CharSizeH = -1;


		if (FontSize == 0){_CharSizeW = ct_GUI_LetterSize_W_Size_0;}
		if (FontSize == 1){_CharSizeW = ct_GUI_LetterSize_W_Size_1;}
		if (FontSize == 2){_CharSizeW = ct_GUI_LetterSize_W_Size_2;}
		if (FontSize == 3){_CharSizeW = ct_GUI_LetterSize_W_Size_3;}

		if (FontSize == 0){_CharSizeH = ct_GUI_LetterSize_H_Size_0;}
		if (FontSize == 1){_CharSizeH = ct_GUI_LetterSize_H_Size_1;}
		if (FontSize == 2){_CharSizeH = ct_GUI_LetterSize_H_Size_2;}
		if (FontSize == 3){_CharSizeH = ct_GUI_LetterSize_H_Size_3;}


		// Calculate the heigth of the background
		int16_t Calc_H = Lines * _CharSizeH;

		// Border
		GUI_tft.fillRect(PosX - 1, PosY - 1, SizeW + 2, Calc_H + 2, BorderColor);
		
		// Background
		GUI_tft.fillRect(PosX, PosY, SizeW, Calc_H, FillColor);
		

		// Render Scroll Bar

		int _SizeBtnSroll_W_UP = 3 * _CharSizeW;
		int _SizeBtnSroll_H_UP = 3 * _CharSizeW;

		int _SizeBtnSroll_W_DOWN = 50;
		int _SizeBtnSroll_H_DOWN = 50;


		GUI_Render_GenericButton(F("SCROLL_UP"), 
									F("/\\"), 
									1, 
									White, 
									AzulClaro, 
									0, 
									White, 
									PosX + SizeW - _SizeBtnSroll_W_UP, 
									PosY, 
									_SizeBtnSroll_W_UP, 
									_SizeBtnSroll_H_UP);



		GUI_Render_GenericButton(F("SCROLL_DOWN"), 
									F("\\/"), 
									1, 
									White, 
									AzulClaro, 
									0, 
									White, 
									PosX + SizeW - _SizeBtnSroll_W_UP, 
									PosY + Calc_H - _SizeBtnSroll_H_UP, 
									_SizeBtnSroll_W_UP, 
									_SizeBtnSroll_H_UP);

		// borda barra rolagem
		GUI_tft.fillRect(PosX + SizeW - _SizeBtnSroll_W_UP - 1, PosY + _SizeBtnSroll_H_UP + 2, _SizeBtnSroll_W_UP + 2, Calc_H - (2 * _SizeBtnSroll_H_UP) - 3, BorderColor);

		// BARRA ROLAGEM
		GUI_tft.fillRect(PosX + SizeW - _SizeBtnSroll_W_UP, PosY + _SizeBtnSroll_H_UP + 3, _SizeBtnSroll_W_UP, Calc_H - (2 * _SizeBtnSroll_H_UP) - 5, CinzaClaro);
		

		// Lista conteudo

		GUI_SetFontSize(FontSize);

		GUI_tft.setTextColor(TextColor);

		GUI_tft.setCursor (PosX, PosY); 
		GUI_tft.print (F("Teste de texto"));

		GUI_tft.setCursor (PosX, PosY + 1 * _CharSizeH); 
		GUI_tft.print (F("Teste de texto"));

		GUI_tft.setCursor (PosX, PosY + 2 * _CharSizeH); 
		GUI_tft.print (F("Teste de texto"));

		GUI_tft.setCursor (PosX, PosY + 3 * _CharSizeH); 
		GUI_tft.print (F("Teste de texto"));


	}
}







