#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "include/connect.h"

#define FINDWIN(a, b) ((a) > (b) ? (a) : (b))

Board c_newboard() {
    Board board = (char **) malloc(sizeof(char *) * C_HEIGHT);
    for(int i = 0; i < C_HEIGHT; i++) {
        board[i] = (char *) malloc(sizeof(char) * C_WIDTH);
        for(int j = 0; j < C_WIDTH; j++) {
            board[i][j] = EMPTY;
        }
    }

    return board;
}

void c_freeboard(Board board) {
    for(int i = C_HEIGHT - 1; i >= 0; i--) {
        free(board[i]);
    }

    free(board);
}

int c_place(Board board, int x) {
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

int c_iswinningmove(Board board, int x) {
    int w;

    c_place(board, x);
    w = c_getwinner(board);
    c_remove(board, x);

    return w;
}

int c_remove(Board board, int x) {
    for(int i = 0; i < C_HEIGHT; i++) {
        if(board[i][x] != EMPTY) {
            board[i][x] = EMPTY;
            return 1;
        }
    }

    return 0;
}

int c_canplace(Board board, int x) {
    return board[0][x] == EMPTY;
}

int c_lastplace(Board board, int col) {
    for(int i = 0; i < C_HEIGHT; i++) {
        if(board[i][col] != EMPTY) return i;
    }

    return 0;
}

int c_getwinner(Board board) {
    int i, row, col, color;
    for(i = 0; i < C_WIDTH; i++) {
        if(c_canplace(board, i)) break;
    }

    if(i == C_WIDTH) return TIE;

    for(row = 0; row < C_HEIGHT; row++) {
        for(col = 0; col < C_WIDTH; col++) {
            if(board[row][col] == EMPTY) continue;

            color = board[row][col];

            if(CHECKLOCS(board, row, col, row, col + 1, row, col + 2, row, col + 3) || 
                CHECKLOCS(board, row, col, row + 1, col, row + 2, col, row + 3, col) || 
                CHECKLOCS(board, row, col, row + 1, col + 1, row + 2, col + 2, row + 3, col + 3) ||
                CHECKLOCS(board, row, col, row + 1, col - 1, row + 2, col - 2, row + 3, col - 3)) {
                return color;
            }
        }
    }

    return 0;
}

void c_printboard(Board board) {
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

int c_nexttoken(Board board) {
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

int c_counttoken(Board board) {
    int count = 0;

    for(int i = 0; i < C_HEIGHT; i++) {
        for(int j = 0; j < C_WIDTH; j++) {
            if(board[i][j] != EMPTY) count++;
        }
    }

    return count;
}

Board c_copyboard(Board board) {
    Board newboard = c_newboard();
    for(int i = 0; i < C_HEIGHT; i++) {
        for(int j = 0; j < C_WIDTH; j++) {
            newboard[i][j] = board[i][j];
        }
    }

    return newboard;
}