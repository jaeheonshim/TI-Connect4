#include <limits.h>
#include <stdio.h>
#include <debug.h>
#include "include/connect.h"
#include "include/connectai.h"

#define MAXVAL 1000
#define MINVAL -1000

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

#define CALCPTS(col, evaluator) ((col) == (evaluator) ? 1 : -1)

static const int transforms[][2] = {
    {0, -1},
    {1, 0},
    {1, -1},
    {-1, -1}
};

static const char eval_order[7] = {
    3, 4, 2, 5, 1, 6, 0
};

int placeable(Board board, int row, int col, int color);

static int d_heuristic = 0;
struct debugframe debug;

int c_findbestmove(Board board, int depth, int player) {
    debug.depth = depth;
    dbg_printf("Finding best move: Depth: %d, Player: %c\n", depth, C_COLCHAR(player));
    d_heuristic = 0;

    int bestCol = 0;
    int maxVal = MINVAL;
    int pos;

    for(int i = 0; i < C_WIDTH; i++) {
        pos = eval_order[i];
        if(c_canplace(board, pos)) {
            bestCol = pos;
            break;
        }
    }

    for(int i = 0; i < C_WIDTH; i++) {
        pos = eval_order[i];
        if(c_canplace(board, pos) && c_iswinningmove(board, pos)) return pos;
        if(c_canplace(board, pos)) {
            c_place(board, pos);
            int res = c_minimax(board, depth, 0, MINVAL, MAXVAL, player);
            debug.poseval[pos] = res;
            c_remove(board, pos);
            if(res > maxVal) {
                bestCol = pos;
                maxVal = res;
            }
        }
    }

    debug.heuristic_count = d_heuristic;
    dbg_printf("Found best move: %d. Heuristic function called %d times\n", bestCol, d_heuristic);

    return bestCol;
}

/**
 * Returns the maximum score possible for the "maximizer" in a certain position, given both parties play optimally.
 */
int c_minimax(Board board, int depth, int maximizing, int alpha, int beta, int player) {
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

int c_evalpos(Board board, int evaluator) {
    d_heuristic++;
    int netPts = 0;
    int winner;

    if((winner = c_getwinner(board)) != 0) {
        if(winner == evaluator) return MAXVAL;
        else return MINVAL;
    }

    int color;
    int row, col, found;
    
    for(row = 0; row < C_HEIGHT; row++) {
        found = 0;
        for(col = 0; col < C_WIDTH; col++) {
            if(board[row][col] == EMPTY) continue;
            color = board[row][col];
            found = 1;

            int pts = CALCPTS(color, evaluator);

            if(CHECKLOCS(board, row, col, row, col + 1, row, col + 2, row, col + 3)) netPts += pts * 3;
            if(CHECKLOCS(board, row, col, row + 1, col, row + 2, col, row + 3, col)) netPts += pts * 3;
            if(CHECKLOCS(board, row, col, row + 1, col + 1, row + 2, col + 2, row + 3, col + 3)) netPts += pts * 3;
            if(CHECKLOCS(board, row, col, row + 1, col - 1, row + 2, col - 2, row + 3, col - 3)) netPts += pts * 3;

            if(CHECKLOCS3(board, row, col, row, col + 1, row, col + 2)) netPts += pts * 2;
            if(CHECKLOCS3(board, row, col, row + 1, col, row + 2, col)) netPts += pts * 2;
            if(CHECKLOCS3(board, row, col, row + 1, col + 1, row + 2, col + 2)) netPts += pts * 2;
            if(CHECKLOCS3(board, row, col, row + 1, col - 1, row + 2, col - 2)) netPts += pts * 2;
        }

        if(!found) break;
    }

    return netPts;
}

int placeable(Board board, int row, int col, int color) {
    if(row + 1 < C_HEIGHT) {
        return validpos(row, col) && board[row + 1][col] != EMPTY && (board[row][col] == EMPTY || board[row][col] == color);
    } else {
        return validpos(row, col) && (board[row][col] == EMPTY || board[row][col] == color);
    }
}