#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "include/connect.h"

#define FINDWIN(a, b) ((a) > (b) ? (a) : (b))
#define TRANSFORM_COUNT (sizeof transforms / (sizeof(int) * 2))

static const int transforms[][2] = {
    {0, 1},
    {1, 0},
    {1, -1},
    {1, 1}
};

char **c_newboard() {
    char **board = (char **) malloc(sizeof(char *) * C_HEIGHT);
    for(int i = 0; i < C_HEIGHT; i++) {
        board[i] = (char *) malloc(sizeof(char) * C_WIDTH);
        for(int j = 0; j < C_WIDTH; j++) {
            board[i][j] = EMPTY;
        }
    }

    return board;
}

void c_freeboard(char **board) {
    for(int i = C_HEIGHT - 1; i >= 0; i--) {
        free(board[i]);
    }

    free(board);
}

int c_place(char **board, int x) {
    if(!c_canplace(board, x)) return 0;

    int token = c_nexttoken(board);
    for(int i = C_HEIGHT - 1; i >= 0; i--) {
        if(board[i][x] == EMPTY) {
            board[i][x] = token;
            return 1;
        }
    }

    return 0;
}

int c_canplace(char **board, int x) {
    return board[0][x] == EMPTY;
}

int c_getwinner(char **board) {
    int i;
    for(i = 0; i < C_WIDTH; i++) {
        if(c_canplace(board, i)) break;
    }

    if(i == C_WIDTH) return TIE;

    for(int row = 0; row < C_HEIGHT; row++) {
        for(int col = 0; col < C_WIDTH; col++) {
            if(board[row][col] == EMPTY) continue;

            int chains[4] = {board[row][col], board[row][col], board[row][col], board[row][col]};
            int tRow, tCol;

            for(int i = 1; i < 4; i++) {
                for(int t = 0; t < TRANSFORM_COUNT; t++) {
                    tRow = row + transforms[t][0] * i;
                    tCol = col + transforms[t][1] * i;

                    if(validpos(tRow, tCol)) {
                        if(board[tRow][tCol] != chains[t]) {
                            chains[t] = 0;
                        }
                    } else {
                        chains[t] = 0;
                    }
                }
            }

            for(int i = 0; i < 4; i++) {
                if(chains[i] != 0) {
                    return chains[i];
                }
            }
        }
    }

    return 0;
}

void c_printboard(char **board) {
    for(int i = 0; i < C_HEIGHT; i++) {
        for(int j = 0; j < C_WIDTH; j++) {
            printf("%c ", C_COLCHAR(board[i][j]));
        }
        printf("\n");
    }

    for(int i = 0; i < C_WIDTH; i++) {
        printf("%d ", i);
    }
    printf("\n");
}

int c_nexttoken(char **board) {
    int rCount, yCount;
    rCount = yCount = 0;

    for(int i = 0; i < C_HEIGHT; i++) {
        for(int j = 0; j < C_WIDTH; j++) {
            if(board[i][j] == RED) {
                rCount++;
            } else if(board[i][j] == YELLOW) {
                yCount++;
            }
        }
    }

    if(rCount > yCount) {
        return YELLOW;
    } else {
        return RED;
    }
}

int validpos(int row, int col) {
    return row >= 0 && row < C_HEIGHT && col >= 0 && col < C_WIDTH;
}

char **c_copyboard(char **board) {
    char **newboard = c_newboard();
    for(int i = 0; i < C_HEIGHT; i++) {
        for(int j = 0; j < C_WIDTH; j++) {
            newboard[i][j] = board[i][j];
        }
    }

    return newboard;
}