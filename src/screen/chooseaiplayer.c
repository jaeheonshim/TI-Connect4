#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include "include/drawing.h"
#include "include/tic4.h"

#define SCALE 2
#define HEIGHT SCALE * 8
#define SPACING 2

static const char *humanFirst = "[1] Human plays first";
static const char *aiFirst = "[2] AI plays first";

static int humanFirstWidth;

void cai_init() {
    humanFirstWidth = gfx_GetStringWidth(humanFirst);
}

void cai_update(unsigned long delta) {
    int digitInput = getDigitInput();
    if(digitInput == 1) {
        setHumanPlayer(RED);
    } else if(digitInput == 2) {
        setHumanPlayer(YELLOW);
    }

    if(digitInput == 1 || digitInput == 2) {
        game_init();
        setScreen(&screen_game);
    }
}

void cai_draw() {
    gfx_SetTextScale(SCALE, SCALE);
    gfx_SetTextFGColor(0);
    gfx_PrintStringXY(humanFirst, (LCD_WIDTH / 2) - (humanFirstWidth / 2), (LCD_HEIGHT / 2) - (HEIGHT) - SPACING);
    gfx_PrintStringXY(aiFirst, (LCD_WIDTH / 2) - (humanFirstWidth / 2), (LCD_HEIGHT / 2) + SPACING);
}