#include "mbed.h"           // v122
#include "RA8875.h"         // v127
#include "Keypad.h"         // v4

// These two defines can be enabled, or commented out
#define BIG_SCREEN
#define CAP_TOUCH
#define LCD_C 16         // color - bits per pixel

#ifdef CAP_TOUCH
RA8875 lcd(p5, p6, p7, p12, NC, p9,p10,p13, "tft"); // MOSI,MISO,SCK,/ChipSelect,/reset, SDA,SCL,/IRQ, name
#else
RA8875 lcd(p5, p6, p7, p12, NC, "tft");             //MOSI, MISO, SCK, /ChipSelect, /reset, name
LocalFileSystem local("local");                     // access to calibration file for resistive touch.
#endif

#ifdef BIG_SCREEN
    #define LCD_W 800
    #define LCD_H 480
#else
    #define LCD_W 480
    #define LCD_H 272
#endif

Serial pc(USBTX, USBRX);            // And a little feedback
Keypad kp(lcd);

// Define a keyboard layout as a calculator-like keypad
// 789 /(
// 456 *)
// 123 -
// 00. +=
const char numberkeys[] = {
    5,'\x01', 10,'7',10,'8',10,'9', 5,'\x01', 10,'/',10,'(', 0,0,
    5,'\x01', 10,'4',10,'5',10,'6', 5,'\x01', 10,'*',10,')', 0,0,
    5,'\x01', 10,'1',10,'2',10,'3', 5,'\x01', 10,'-',10,KYBD_SYM_BS, 0,0,
    5,'\x01', 20,'0',       10,'.', 5,'\x01', 10,'+',10,'=', 0,0,
    0,0
};

// Define the implementation of that keyboard
const Keypad::keyboard_t altkeyboard = {
    100,        // x=100; left edge
    0,          // y=0; computed from bottom up
    240,        // width=240
    0,          // height=0; bottom of screen justified
    4,          // rows
    6,          // columns
    numberkeys, // pointer to the keypad
    numberkeys
};



void CalibrateTS(void)
{
    FILE * fh;
    tpMatrix_t matrix;
    RetCode_t r;

    r = lcd.TouchPanelCalibrate("Calibrate the touch panel", &matrix);
    if (r == noerror) {
        fh = fopen("/local/tpcal.cfg", "wb");
        if (fh) {
            fwrite(&matrix, sizeof(tpMatrix_t), 1, fh);
            fclose(fh);
        } else {
            lcd.printf("Cannot save calibration in /local/tpcal.cfg\r\n");
            wait_ms(1000);
        }
    } else {
        lcd.printf("TouchPanelCalibrate returned error code %d\r\n", r);
        wait_ms(2000);
    }
}


void InitTS(void)
{
    FILE * fh;
    tpMatrix_t matrix;

    fh = fopen("/local/tpcal.cfg", "rb");
    if (fh) {
        fread(&matrix, sizeof(tpMatrix_t), 1, fh);
        fclose(fh);
        lcd.TouchPanelSetMatrix(&matrix);
        pc.printf("Touch Panel calibration set\r\n");
    } else {
        CalibrateTS();
    }
}


void UsernameAndPasswordTest(void) {
    char name1[20];
    char name2[20];
    
    kp.SetKeyboard();
    kp.SetKeyboardFont(0, 2);  // big characters
    lcd.puts(0,20, "Enter username and password\r\n");
    if (kp.GetString(name1, sizeof(name1), "Username:")) {
        //lcd.printf("username: %s\r\n", name1);
        if (kp.GetString(name2, sizeof(name2), "Password:", '*')) {
            //lcd.printf("password: %s\r\n", name2);
            kp.Erase();
            lcd.foreground(BrightRed);
            lcd.background(Black);
            lcd.cls();
            lcd.SetTextFontSize(2);
            lcd.SetTextCursor(0,30);
            lcd.printf("username: %s\r\npassword: %s\r\n", name1, name2);
            lcd.SetTextFontSize();
        }
    } else {
        //kp.Erase();
        pc.printf("<esc>\r\n");
    }
}


void CalculatorKeypadTest(void) {
    char name1[20];
    
    kp.SetKeyboard(&altkeyboard, '=', 0);
    kp.SetKeyboardFont(0, 4);
    if (kp.GetString(name1, sizeof(name1), "Calc:")) {
        lcd.foreground(BrightRed);
        lcd.background(Black);
        lcd.cls();
        lcd.SetTextCursor(0,40);
        lcd.printf("Calculator: %s\r\n", name1);
    }
}

void FloatingSmallQWERTYTest(loc_t x, loc_t y, dim_t w, dim_t h) {
    Keypad::keyboard_t tiny;
    char name1[10];
    
    // copy definition and then resize it
    kp.SetKeyboard();   // select the internal keyboard
    memcpy(&tiny, kp.GetKeyboard(), sizeof(Keypad::keyboard_t));
    tiny.x = x; tiny.y = y;
    tiny.width = w; tiny.height=h;
    
    // now select this tiny keyboard
    kp.SetKeyboard(&tiny);
    kp.SetKeyboardFont(0, 1);
    if (kp.GetString(name1, sizeof(name1), "Cprs:")) {
        lcd.foreground(BrightRed);
        lcd.background(Black);
        lcd.cls();
        lcd.SetTextCursor(0,40);
        lcd.printf("Compressed: %s\r\n", name1);
    }
}




int main()
{
    int testNum = 0;    // starting test

    pc.baud(460800);                            // I like a snappy terminal, so crank it up!
    pc.printf("\r\nDev Keypad - Build " __DATE__ " " __TIME__ "\r\n");

    lcd.init(LCD_W, LCD_H, LCD_C);
    lcd.Backlight(0.5f);
    
    #ifndef CAP_TOUCH
    InitTS();
    #endif
    while(1) {
        lcd.foreground(Yellow);
        lcd.background(Black);
        lcd.cls();
        lcd.puts(0,0, "Dev Keypad - Build " __DATE__ " " __TIME__ "\r\n");
        switch (testNum) {
            default:
            case 0:
                testNum = 0;    // capture the overflow and start over...
                UsernameAndPasswordTest();
                break;
            case 1:
                CalculatorKeypadTest();
                break;
            case 2:
                FloatingSmallQWERTYTest(50,0, 200,0);      // horizontally in by 50, width 200, extend to bottom of screen
                break;
            case 3:
                FloatingSmallQWERTYTest(75, 100, 220, 6 * (lcd.fontheight()+4));   // floating with the top at x=75, y=100
                break;
        }
        testNum++;
        wait(5);
    }
}
