#include <tice.h>
#include <graphx.h>
#include <stdio.h>
#include "include/connect.h"
#include "include/drawing.h"

#define MOVE_TIME 500

static char **board;
static unsigned long timer = 0;

void menu_init() {
    board = c_newboard();
}

void menu_draw() {
    drawBoard(board, LCD_WIDTH / 2, (LCD_HEIGHT / 2) - 10, 0.6);

    gfx_SetTextFGColor(0);
    gfx_SetTextScale(3, 3);
    gfx_SetTextFGColor(224);
    gfx_PrintStringXY("CONNECT", 60, 14);
    gfx_SetTextFGColor(26);
    gfx_PrintStringXY("4", 240, 14);

    gfx_SetTextFGColor(0);
    gfx_SetTextScale(2, 2);
    gfx_PrintStringXY("Press [ENTER] to start", 9, 186);

    gfx_SetTextScale(1, 1);
    gfx_SetTextFGColor(74);
    gfx_SetColor(74);
    gfx_Line(0, 213, LCD_WIDTH, 213);
    gfx_PrintStringXY("github.com/jaeheonshim", 78, 223);
}

void menu_update(unsigned long delta) {
    timer += delta;
    if(timer >= MOVE_TIME) {
        timer = 0;

        if(c_getwinner(board) != 0) {
            c_freeboard(board);
            board = c_newboard();
        } else {
            int rand;
            do {
                rand = random() % C_WIDTH;
            } while(!c_canplace(board, rand));
            c_place(board, rand);
        }
    }
}