#include "include/tic4.h"
#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include "include/connect.h"
#include "include/drawing.h"

static char **board;
static int lastInput = -1;
static int digitInput;

static char gameMode = PVP;

int getDigitInput();

void game_init() {
    board = c_newboard();
}

void game_update(unsigned long delta) {
    if((digitInput = getDigitInput()) != -1 && digitInput != lastInput) {
        if(digitInput >= 0 && digitInput < C_WIDTH) {
            c_place(board, digitInput);
        }
    }
    lastInput = digitInput;
}

void doMoveLogic() {
    switch(gameMode) {
        case PVP: {

        }
    }
}

void game_draw() {
    drawBoard(board, LCD_WIDTH / 2, LCD_HEIGHT / 2, 1);
    drawPlacer(LCD_WIDTH / 2, LCD_HEIGHT / 2, 0, YELLOW, 1);
}

void setGameMode(char g) {
    gameMode = g;
}

char getGameMode() {
    return gameMode;
}