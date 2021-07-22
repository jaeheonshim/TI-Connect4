#include <limits.h>
#include <stdio.h>
#include "include/connect.h"
#include "include/connectai.h"

#define TRANSFORM_COUNT (sizeof transforms / (sizeof(int) * 2))

#define MAX 1000
#define MIN -1000

static const int transforms[][2] = {
    {0, 1},
    {1, 0},
    {-1, 1},
    {1, 1},
    {0, -1},
    {-1, 0},
    {1, -1},
    {-1, -1}
};



int placeable(char **board, int row, int col, int color);

int c_findbestmove(char **board, int depth, int player) {
    int bestCol = 0;
    int maxVal = MIN;

    for(int i = 0; i < C_WIDTH; i++) {
        if(c_canplace(board, i)) {
            char **copyboard = c_copyboard(board);
            c_place(copyboard, i);
            int res = c_minimax(copyboard, depth, 0, player);
            c_freeboard(copyboard);
            if(res > maxVal) {
                bestCol = i;
                maxVal = res;
            }
        }
    }

    return bestCol;
}

/**
 * Returns the maximum score possible for the "maximizer" in a certain position, given both parties play optimally.
 */
int c_minimax(char **board, int depth, int maximizing, int player) {
    if(depth <= 0 || c_getwinner(board) != 0) {
        return c_evalpos(board, player);
    }

    if(maximizing) {
        int max = MIN;
        for(int i = 0; i < C_WIDTH; i++) {
            if(c_canplace(board, i)) {
                char **copyboard = c_copyboard(board);
                c_place(copyboard, i);
                int res = c_minimax(copyboard, depth - 1, !maximizing, player);
                c_freeboard(copyboard);
                if(res > max) {
                    max = res;
                }
            }
        }

        return max;
    } else {
        // assuming opponent plays optimally, if they don't they're fucked anyway
        int min = MAX;
        for(int i = 0; i < C_WIDTH; i++) {
            if(c_canplace(board, i)) {
                char **copyboard = c_copyboard(board);
                c_place(copyboard, i);
                int res = c_minimax(copyboard, depth - 1, !maximizing, player);
                c_freeboard(copyboard);

                if(res < min) {
                    min = res;
                }
            }
        }

        return min;
    }
}

int c_evalpos(char **board, int evaluator) {
    int netPts = 0;
    int winner;

    if((winner = c_getwinner(board)) != 0) {
        if(winner == evaluator) return MAX;
        else return MIN;
    }

    int tRow, tCol, i, color;
    
    for(int row = 0; row < C_HEIGHT; row++) {
        for(int col = 0; col < C_WIDTH; col++) {
            if(board[row][col] == EMPTY) continue;

            color = board[row][col];

            for(int t = 0; t < TRANSFORM_COUNT; t++) {
                for(i = 1; i < 4; i++) {
                    tRow = row + transforms[t][0] * i;
                    tCol = col + transforms[t][1] * i;
                    
                    if(!placeable(board, tRow, tCol, color)) break;
                }

                netPts += (i - 1) * (color == evaluator ? 1 : -1);
            }
        }
    }

    return netPts;
}

int placeable(char **board, int row, int col, int color) {
    if(row + 1 < C_HEIGHT) {
        return validpos(row, col) && board[row + 1][col] != EMPTY && (board[row][col] == EMPTY || board[row][col] == color);
    } else {
        return validpos(row, col) && (board[row][col] == EMPTY || board[row][col] == color);
    }
}