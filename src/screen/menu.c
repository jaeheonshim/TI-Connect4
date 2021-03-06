#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include "include/connect.h"
#include "include/tic4.h"
#include "include/drawing.h"

#define TEXT_SCALE 2
#define FONT_HEIGHT (8 * TEXT_SCALE)
#define LINE_HEIGHT 4

static char *option1 = "[1] Player v. Player";
static char *option2 = "[2] Player v. AI";

static int option1Width;

void menu_init() {
    gfx_SetTextScale(TEXT_SCALE, TEXT_SCALE);
    option1Width = gfx_GetStringWidth(option1);
}

void menu_update(unsigned long delta) {
    int digitInput = getDigitInput();
    if(digitInput == 1) {
        setGameMode(PVP);
        setScreen(&screen_game);
        game_init();
    } else if(digitInput == 2) {
        setGameMode(PVAI);
        while(getDigitInput() != -1) kb_Scan();
        setScreen(&screen_cai);
    }
}

void menu_draw() {
    gfx_SetTextScale(TEXT_SCALE, TEXT_SCALE);
    gfx_SetTextFGColor(0);

    gfx_PrintStringXY(option1, LCD_WIDTH / 2 - option1Width / 2, LCD_HEIGHT / 2 - FONT_HEIGHT - FONT_HEIGHT / 2 - LINE_HEIGHT);
    gfx_PrintStringXY(option2, LCD_WIDTH / 2 - option1Width / 2, LCD_HEIGHT / 2 - FONT_HEIGHT / 2);
}