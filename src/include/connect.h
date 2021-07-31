#define EMPTY 0

#define RED 1
#define YELLOW 2
#define TIE 3

#define C_WIDTH 7
#define C_HEIGHT 6

#define C_COLCHAR(color) (((color) == RED) ? 'X' : ((color) == YELLOW) ? 'O' : '*')
#define otherPlayer(color) ((color) == RED ? YELLOW : RED)
#define validpos(row, col) ((row) >= 0 && (row) < C_HEIGHT && (col) >= 0 && (col) < C_WIDTH)

#define CHECKLOCS(board, r1, c1, r2, c2, r3, c3, r4, c4) ( \
    validpos((r1), (c1)) && \
    validpos((r2), (c2)) && \
    validpos((r3), (c3)) && \
    validpos((r4), (c4)) && \
    board[r1][c1] != 0 && \
    board[r1][c1] == board[r2][c2] && board[r2][c2] == board[r3][c3] && board[r3][c3] == board[r4][c4])

typedef char **Board;

Board c_newboard();
int c_place(Board board, int x);
void c_printboard(Board board);
int c_getwinner(Board board);
int c_nexttoken(Board board);
Board c_copyboard(Board board);
int c_canplace(Board board, int x);
void c_freeboard(Board board);
int c_remove(Board board, int x);
int c_lastplace(Board board, int col);
int c_counttoken(Board board);
int c_iswinningmove(Board board, int x);