#include "include/tic4.h"
#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <stdio.h>
#include "include/connect.h"
#include "include/drawing.h"

static char **board;
static int lastInput = -1;
static int currentPlace = 0;

static char gameMode = PVP;

int getDigitInput();

void game_init() {
    board = c_newboard();
}

void game_update(unsigned long delta) {
    int currentWinner = c_getwinner(board);
    if(kb_IsDown(kb_KeyEnter) && lastInput != kb_KeyEnter) {
        c_place(board, currentPlace);
        lastInput = kb_KeyEnter;
        currentWinner = c_getwinner(board);
        while(c_canplace(board, currentPlace) == 0 && currentWinner == 0) {
            currentPlace++;
            currentPlace %= C_WIDTH;
        }
    } else if(kb_IsDown(kb_KeyLeft) && lastInput != kb_KeyLeft) {
        do {
            currentPlace--;
            if(currentPlace < 0) currentPlace = C_WIDTH - 1;
        } while(c_canplace(board, currentPlace) == 0 && currentWinner == 0);

        lastInput = kb_KeyLeft;
    } else if(kb_IsDown(kb_KeyRight) && lastInput != kb_KeyRight) {
        do {
            currentPlace++;
            currentPlace %= C_WIDTH;
        } while(c_canplace(board, currentPlace) == 0 && currentWinner == 0);
        
        lastInput = kb_KeyRight;
    } else {
        lastInput = -1;
    }
}

void doMoveLogic() {
    switch(gameMode) {
        case PVP: {

        }
    }
}

void game_draw() {
    drawBoard(board, LCD_WIDTH / 2, LCD_HEIGHT / 2, 1);
    drawPlacer(LCD_WIDTH / 2, LCD_HEIGHT / 2, currentPlace, c_nexttoken(board), 1);
}

void setGameMode(char g) {
    gameMode = g;
}

char getGameMode() {
    return gameMode;
}