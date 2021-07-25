#include <limits.h>
#include <stdio.h>
#include <debug.h>
#include "include/connect.h"
#include "include/connectai.h"

#define TRANSFORM_COUNT (sizeof transforms / (sizeof(int) * 2))

#define MAXVAL 1000
#define MINVAL -1000

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

static const char eval_order[7] = {
    3, 4, 2, 5, 1, 6, 0
};

int placeable(char **board, int row, int col, int color);

static int d_heuristic = 0;

int c_findbestmove(char **board, int depth, int player) {
    dbg_printf("Finding best move: Depth: %d, Player: %c\n", depth, C_COLCHAR(player));
    d_heuristic = 0;

    int bestCol = 0;
    int maxVal = MINVAL;
    int mid = C_WIDTH / 2;
    int pos;

    for(int i = 0; i < C_WIDTH; i++) {
        pos = eval_order[i];
        if(c_canplace(board, pos)) {
            c_place(board, pos);
            int res = c_minimax(board, depth, 0, MINVAL, MAXVAL, player);
            c_remove(board, pos);
            if(res > maxVal) {
                bestCol = pos;
                maxVal = res;
            }
        }
    }

    dbg_printf("Found best move: %d. Heuristic function called %d times\n", bestCol, d_heuristic);

    return bestCol;
}

/**
 * Returns the maximum score possible for the "maximizer" in a certain position, given both parties play optimally.
 */
int c_minimax(char **board, int depth, int maximizing, int alpha, int beta, int player) {
    char i, pos;
    int res, max, min;
    if(depth <= 0 || c_getwinner(board) != 0) {
        return c_evalpos(board, player);
    }

    if(maximizing) {
        max = MINVAL;
        for(i = 0; i < C_WIDTH; i++) {
            pos = eval_order[i];
            if(c_canplace(board, pos)) {
                c_place(board, pos);
                res = c_minimax(board, depth - 1, !maximizing, alpha, beta, player);
                c_remove(board, pos);
                max = MAX(res, max);
                alpha = MAX(res, alpha);

                if(beta <= alpha) {
                    break;
                }
            }
        }

        return max;
    } else {
        // assuming opponent plays optimally, if they don't they're fucked anyway
        min = MAXVAL;
        for(i = 0; i < C_WIDTH; i++) {
            pos = eval_order[i];
            if(c_canplace(board, pos)) {
                c_place(board, pos);
                res = c_minimax(board, depth - 1, !maximizing, alpha, beta, player);
                c_remove(board, pos);

                min = MIN(res, min);
                beta = MIN(beta, min);

                if(beta <= alpha) {
                    break;
                }
            }
        }

        return min;
    }
}

int c_evalpos(char **board, int evaluator) {
    d_heuristic++;
    int netPts = 0;
    int winner;

    if((winner = c_getwinner(board)) != 0) {
        if(winner == evaluator) return MAXVAL;
        else return MINVAL;
    }

    int tRow, tCol, i, color;
    int row, col, t;
    
    for(row = 0; row < C_HEIGHT; row++) {
        for(col = 0; col < C_WIDTH; col++) {
            if(board[row][col] == EMPTY) continue;
            color = board[row][col];

            for(t = 0; t < TRANSFORM_COUNT; t++) {
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