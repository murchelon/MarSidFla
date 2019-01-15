


// Width of the chars in the screen
#define ct_GUI_LetterSize_W_Size_0 8  // font size 0
#define ct_GUI_LetterSize_W_Size_1 16  // font size 1
#define ct_GUI_LetterSize_W_Size_2 24  // font size 2
#define ct_GUI_LetterSize_W_Size_3 32  // font size 3

// Heigth of the chars in the screen
#define ct_GUI_LetterSize_H_Size_0 16  // font size 0
#define ct_GUI_LetterSize_H_Size_1 32  // font size 1
#define ct_GUI_LetterSize_H_Size_2 48  // font size 2
#define ct_GUI_LetterSize_H_Size_3 64  // font size 3

// Max buttons allowed in one screen at the same time
#define ct_GUI_MAX_BUTTONS_ONSCREEN 10

// Mas number of itens/options a select can have
#define ct_GUI_MAX_SELECT_OPTIONS 30

// incremental number that keeps track of the count of buttons in a screen. Index
int g_GUI_GenBtn_BtnCount = 0;

// var that hold the coordinates, tag and other info of all buttons in screen
String g_GUI_aGenBtn[ct_GUI_MAX_BUTTONS_ONSCREEN];

// var that hold the coordinates, tag and other info of all options in a select rendered
String g_GUI_aSelOptions[ct_GUI_MAX_SELECT_OPTIONS];
