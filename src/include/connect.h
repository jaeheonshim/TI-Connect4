#define EMPTY 0

#define RED 1
#define YELLOW -1
#define TIE 2

#define C_WIDTH 7
#define C_HEIGHT 6

#define C_COLCHAR(color) (((color) == RED) ? 'X' : ((color) == YELLOW) ? 'O' : '*')

char **c_newboard();
int c_place(char **board, int x);
void c_printboard(char **board);
int c_getwinner(char **board);
int c_nexttoken(char **board);
int validpos(int row, int col);
char **c_copyboard(char **board);
int c_canplace(char **board, int x);
void c_freeboard(char **board);
int c_remove(char **board, int x);