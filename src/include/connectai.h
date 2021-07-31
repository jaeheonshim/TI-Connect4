#include "include/connect.h"

int c_evalpos(Board board, int evaluator);
int c_minimax(Board board, int depth, int maximizing, int alpha, int beta, int player);
int c_findbestmove(Board board, int depth, int player);

struct debugframe {
    int poseval[7];
    int heuristic_count;
    int depth;
};