/// PUB_RA8875_Touch Example.
///
/// This touch screen example shows how easy it is to use the RA8875 library with
/// either the resistive touch panel, _OR_ the capacitive touch panel 
/// (using the FT5206 controller). When used with the capacitive touch
/// it tracks 5 fingers simultaneously, and only 1 for the resistive panel.
///
/// @note Copyright &copy; 2016 by Smartware Computing, all rights reserved.
///     Individuals may use this application for evaluation or non-commercial
///     purposes. Within this restriction, changes may be made to this application
///     as long as this copyright notice is retained. The user shall make
///     clear that their work is a derived work, and not the original.
///     Users of this application and sources accept this application "as is" and
///     shall hold harmless Smartware Computing, for any undesired results while
///     using this application - whether real or imagined.
///
/// @author David Smart, Smartware Computing
//
#include "mbed.h"       // Last tested: v122
#include "RA8875.h"     // Last tested: v125


// // // // // // // // // // // // // // // // // // // // // // // // 
// Configuration section
// adjust the following information for the screen size, touch panel technology,
// and port pin assignments.
// // // // // // // // // // // // // // // // // // // // // // // // 

// Define this for 800x480 panel, undefine for 480x272
#define BIG_SCREEN

// Define this for Cap touch panel, undefine for resistive
#define CAP_TOUCH

#ifdef CAP_TOUCH
RA8875 lcd(p5, p6, p7, p12, NC, p9,p10,p13, "tft"); // SPI:{MOSI,MISO,SCK,/ChipSelect,/reset}, I2C:{SDA,SCL,/IRQ}, name
#else
RA8875 lcd(p5, p6, p7, p12, NC, "tft");             // SPI:{MOSI,MISO,SCK,/ChipSelect,/reset}, name
LocalFileSystem local("local");                     // access to calibration file for resistive touch.
#endif

#define PC_BAUD 460800  // I like the serial communications to be very fast

// // // // // // // // // // // // // // // // // // // // // // // // 
// End of Configuration Section
// // // // // // // // // // // // // // // // // // // // // // // // 


Serial pc(USBTX, USBRX);    // Not required for display

#ifdef BIG_SCREEN
    #define LCD_W 800
    #define LCD_H 480
    #define LCD_C 8         // color - bits per pixel
    #define DEF_RADIUS 50   // default radius of the fingerprint
    #define BL_NORM 25      // Backlight Normal setting (0 to 255)
#else
    #define LCD_W 480
    #define LCD_H 272
    #define LCD_C 8         // color - bits per pixel
    #define DEF_RADIUS 20   // default radius of the fingerprint
    #define BL_NORM 25      // Backlight Normal setting (0 to 255)
#endif

// When drawing a "fingerprint" under the touch point - the RA8875 
// cannot draw an object partially off-screen, so this shrinks the 
// fingerprint as the touch approaches the edge of the screen.
//
int ComputeRadius(point_t p)
{
    int radius = DEF_RADIUS;
    
    if (p.x < radius)
        radius = p.x;
    else if (LCD_W - p.x < radius)
        radius = LCD_W - p.x;
    if (p.y < radius)
        radius = p.y;
    else if (LCD_H - p.y < radius)
        radius = LCD_H - p.y;
    return radius;
}

// Calibrate the resistive touch screen, and store the data on the
// local file system.
//
void CalibrateTS(void)
{
    FILE * fh;
    tpMatrix_t matrix;
    RetCode_t r;
    Timer testperiod;
 
    r = lcd.TouchPanelCalibrate("Calibrate the touch panel", &matrix);
    if (r == noerror) {
        fh = fopen("/local/tpcal.cfg", "wb");
        if (fh) {
            fwrite(&matrix, sizeof(tpMatrix_t), 1, fh);
            fclose(fh);
            printf("  tp cal written.\r\n");
            lcd.cls();
        } else {
            printf("  couldn't open tpcal file.\r\n");
        }
    } else {
        printf("error return: %d\r\n", r);
    }
    lcd.cls();
}

// Try to load a previous resistive touch screen calibration from storage. If it
// doesn't exist, activate the touch screen calibration process.
//
void InitTS(void)
{
    FILE * fh;
    tpMatrix_t matrix;

    fh = fopen("/local/tpcal.cfg", "rb");
    if (fh) {
        fread(&matrix, sizeof(tpMatrix_t), 1, fh);
        fclose(fh);
        lcd.TouchPanelSetMatrix(&matrix);
        printf("  tp cal loaded.\r\n");
    } else {
        CalibrateTS();
    }
}

// And here is where the fun begins.
int main()
{
    color_t fingerColor[5] = {Blue, Red, Green, Yellow, Magenta};
    
    pc.baud(PC_BAUD);    //I like a snappy terminal, so crank it up!
    pc.printf("\r\nRA8875 Touch Screen Example - Build " __DATE__ " " __TIME__ "\r\n");

    lcd.init(LCD_W,LCD_H,LCD_C);
    lcd.TouchPanelInit();
    lcd.Backlight_u8(BL_NORM);
    
    point_t last[5];        // space for tracking 5 touches
    #ifndef CAP_TOUCH
    InitTS();               // resistive touch calibration
    #endif
    
    // draw on one layer and erase the other for smoother transition while
    // is shows both layers.
    lcd.SetLayerMode(RA8875::BooleanOR);
    int layer = 0;
    
    while (1) {
        TouchCode_t touch;
        
        touch = lcd.TouchPanelReadable();                           // any touch to report?
        if (touch) {
            layer++;
            printf("%d: %2X: ", lcd.TouchCount(), lcd.TouchGesture());  // all printf can be removed
            
            // TouchChannels reports 1 for resistive panel and 5 for capacitive sense
            for (int i = 0; i < lcd.TouchChannels(); i++) {
                uint8_t id = lcd.TouchID(i);                        // 'id' tracks the individual touches
                TouchCode_t ev = lcd.TouchCode(i);                  // 'ev'ent indicates no_touch, touch, held, release, ...
                point_t xy = lcd.TouchCoordinates(i);               // and of course the (x,y) coordinates
                int count = lcd.TouchCount();                       // how many simultaneous touches
                printf("%2d,%d:(%4d,%4d) ", id, ev, xy.x, xy.y);
                if ((id < 5) || (i < count)) {
                    int lastRadius, newRadius;
                    
                    lastRadius = ComputeRadius(last[id]);           // To erase the last fingerprint
                    newRadius = ComputeRadius(xy);                  // Shrink near edge of screen
                    lcd.SelectDrawingLayer(layer & 1);
                    lcd.fillcircle(xy, newRadius, fingerColor[id]); // draw new fingerprint
                    lcd.SelectDrawingLayer((layer+1) & 1);
                    lcd.fillcircle(last[id], lastRadius, Black);    // erase old fingerprint
                    last[id] = xy;
                }
            }
            printf("\r\n");
        }
    }
}