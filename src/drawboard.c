#include <tice.h>
#include <graphx.h>
#include "include/connect.h"

#define C_BLUE 26
#define C_RED 224
#define C_YELLOW 231
#define C_WHITE 255

#define BOARD_WIDTH 255
#define BOARD_HEIGHT 216

#define SPACING 7
#define RADIUS 14

void drawBoard(char **board, int x, int y) {
    int leftX = (x - (BOARD_WIDTH / 2)), topY = (y - BOARD_HEIGHT / 2);
    gfx_SetColor(C_BLUE);
    gfx_FillRectangle_NoClip(leftX, topY, BOARD_WIDTH, BOARD_HEIGHT);

    for(int row = 0; row < C_HEIGHT; row++) {
        for(int col = 0; col < C_WIDTH; col++) {
            if(board[row][col] == EMPTY) gfx_SetColor(C_WHITE);
            if(board[row][col] == YELLOW) gfx_SetColor(C_YELLOW);
            if(board[row][col] == RED) gfx_SetColor(C_RED);
                
            gfx_FillCircle(
                leftX + (col * RADIUS * 2) + ((col + 1) * SPACING + RADIUS),
                topY + (row * RADIUS * 2) + ((row + 1) * SPACING) + RADIUS, RADIUS);
        }
    }
}