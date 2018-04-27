//
// Demo Program
//  mbed version   Graphics Working   PrintScreen Working? "/local/file.bmp"
//  v148           Yes                No,   FILE *Image = fopen(Name_BMP, "wb"); fails
//  v142           Yes                No,   FILE *Image = fopen(Name_BMP, "wb"); fails
//  v140           Yes                No,   FILE *Image = fopen(Name_BMP, "wb"); fails
//  v138           Yes                No,   FILE *Image = fopen(Name_BMP, "wb"); fails
//  v137           Yes                Yes
//  v136           Yes                Yes
//  v128           Yes                Yes
//
#include "mbed.h"           // testing: v147 - working: v146, v145, v142, v136, v128, fails: v148
#include "RA8875.h"         // v138 - tested working
#include "MyFont18x32.h"
#include "BPG_Arial08x08.h"
#include "BPG_Arial10x10.h"
#include "BPG_Arial20x20.h"
#include "BPG_Arial31x32.h"
#include "BPG_Arial63x63.h"

// These two defines can be enabled, or commented out
#define BIG_SCREEN
#define CAP_TOUCH
#define LCD_C 16         // color - bits per pixel

#ifdef CAP_TOUCH
RA8875 lcd(p5, p6, p7, p12, NC, p9,p10,p13, "tft"); // MOSI,MISO,SCK,/ChipSelect,/reset, SDA,SCL,/IRQ, name
#else
RA8875 lcd(p5, p6, p7, p12, NC, "tft");             //MOSI, MISO, SCK, /ChipSelect, /reset, name
#endif
LocalFileSystem local("local");                     // access to calibration file for resistive touch and printscreen

#ifdef BIG_SCREEN
    #define LCD_W 800
    #define LCD_H 480
#else
    #define LCD_W 480
    #define LCD_H 272
#endif

Serial pc(USBTX, USBRX);            // And a little feedback
Timer measurement;

int main()
{
    pc.baud(460800);                            // I like a snappy terminal, so crank it up!
    pc.printf("\r\nRA8875 Soft Fonts - Build " __DATE__ " " __TIME__ "\r\n");

    measurement.start();
    lcd.init(LCD_W, LCD_H, LCD_C);
    lcd.Backlight(0.5f);

    // **************************
    //RunTestSet(lcd, pc);  // If the library was compiled for test mode...
    
    lcd.foreground(RGB(255,255,0));
    lcd.puts(0,0, "RA8875 Soft Fonts - Build " __DATE__ " " __TIME__ "\r\n");

    lcd.SelectUserFont(Dave_Smart18x32);
    lcd.puts("**** ! Soft Fonts ! **** 0123456789\r\n");
    lcd.puts("ABCDEFGHIJKLMNOPQRSTUVWXYZ\r\n");
    //lcd.puts("abcdefghijklmnopqrstuvwxyz\r\n");
    lcd.SelectUserFont();
    lcd.puts("Back to normal\r\n");
    lcd.SelectUserFont(BPG_Arial08x08);
    lcd.puts("BPG_Arial08x08 ABCDEFGHIJKLMNOPQRSTUVWXYZ\r\n");
    //lcd.puts("BPG_Arial08x08 abcdefghijklmnopqrstuvwxyz\r\n");    
    lcd.SelectUserFont(BPG_Arial10x10);
    lcd.puts("BPG_Arial10x10 ABCDEFGHIJKLMNOPQRSTUVWXYZ\r\n");
    //lcd.puts("BPG_Arial10x10 abcdefghijklmnopqrstuvwxyz\r\n");
    lcd.SelectUserFont(BPG_Arial20x20);
    lcd.puts("BPG_Arial20x20  ");
    lcd.SelectUserFont(BPG_Arial31x32);
    lcd.puts("BPG_Arial31x32\r\n");
    lcd.SelectUserFont(BPG_Arial63x63);
    lcd.puts("BPG_Arial63x63");
    pc.printf("Time trial completed in %d uSec\r\n", measurement.read_us());

    pc.printf("PrintScreen activated ...\r\n");
    RetCode_t r = lcd.PrintScreen(0,0,LCD_W,LCD_H,"/local/file.bmp");
    pc.printf("  PrintScreen returned %d\r\n", r);
    
    while(1) {
        ;       // end
    }
}
