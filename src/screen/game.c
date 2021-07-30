#include "include/tic4.h"
#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <stdio.h>
#include "include/connect.h"
#include "include/connectai.h"
#include "include/drawing.h"

static Board board;
static int lastInput = -1;
static int lastPlace = -1;
static int currentPlace = 0;

static char gameMode = PVP;
char game_winner = 0;

int getDigitInput();
void handleUserInput();
void doMoveLogic();
int getMoveDepth(Board board);

void game_init() {
    game_winner = 0;
    lastInput = -1;
    currentPlace = 0;
    lastPlace = -1;
    if(board != NULL) c_freeboard(board);
    board = c_newboard();

    if(gameMode == AIVAI) {
        int rand;
        for(int i = 0; i < 4; i++) {
            do {
                rand = random() % C_WIDTH;
            } while(!c_canplace(board, rand));
            c_place(board, rand);
        }
    }
}

void game_update(unsigned long delta) {
    if(game_winner == 0) {
        doMoveLogic();
    }
    if(game_winner == 0 && c_getwinner(board) != 0) {
        game_winner = c_getwinner(board);
        game_over_init();
    }
}

void handleUserInput() {
    int currentWinner = c_getwinner(board);
    if(kb_IsDown(kb_KeyEnter) && lastInput != kb_KeyEnter) {
        c_place(board, currentPlace);
        lastPlace = currentPlace;
        lastInput = kb_KeyEnter;
        currentWinner = c_getwinner(board);
        while(c_canplace(board, currentPlace) == 0 && currentWinner == 0) {
            currentPlace++;
            currentPlace %= C_WIDTH;
        }
        
        while(kb_IsDown(kb_KeyEnter)) kb_Scan(); // block enter (TERRIBLE)
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
            handleUserInput();
            break;
        }
        case PVAI: {
            if(c_nexttoken(board) == YELLOW) {
                int bestMove = c_findbestmove(board, getMoveDepth(board), YELLOW);
                c_place(board, bestMove);
                lastPlace = bestMove;
            } else {
                handleUserInput();
            }
            break;
        }
    }
}

void game_draw() {
    drawBoard(board, LCD_WIDTH / 2, LCD_HEIGHT / 2, 1, lastPlace);
    if(game_winner == 0 && gameMode != AIVAI && (gameMode != PVAI || (gameMode == PVAI && c_nexttoken(board) != YELLOW)))
        drawPlacer(LCD_WIDTH / 2, LCD_HEIGHT / 2, currentPlace, c_nexttoken(board), 1);

    if(game_winner != 0) {
        draw_game_over();
    }
}

void setGameMode(char g) {
    gameMode = g;
}

char getGameMode() {
    return gameMode;
}

int getMoveDepth(Board board) {
    int count = c_counttoken(board);
    if(count <= 6) return 2;
    else if (count <= 20) return 3;
    else return 4;
}