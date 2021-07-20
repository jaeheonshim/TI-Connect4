#include <tice.h>
#include <stdlib.h>
#include <graphx.h>
#include <keypadc.h>
#include "include/drawing.h"
#include "include/connect.h"
#include "include/connectai.h"

char **board;
int lastInput = -1;
int digitInput;

void render();
int getDigitInput();
void loop();

/* Main function, called first */
int main(void)
{
    board = c_newboard();
    /* Clear the homescreen */
    os_ClrHome();

    gfx_Begin();
    gfx_SetDrawBuffer();

    /* Waits for a key */
    while (os_GetCSC() != sk_Clear) loop();

    /* Return 0 for success */
    return 0;
}

void loop() {
    kb_Scan();
    if((digitInput = getDigitInput()) != -1 && digitInput != lastInput) {
        if(digitInput >= 0 && digitInput < C_WIDTH) {
            c_place(board, digitInput);
            c_place(board, c_findbestmove(board, 1, c_nexttoken(board)));
        }
    }

    lastInput = digitInput;

    render();
}

int getDigitInput() {
    if(kb_Data[3] & kb_0) return 0;
    else if(kb_Data[3] & kb_1) return 1;
    else if(kb_Data[3] & kb_4) return 4;
    else if(kb_Data[3] & kb_7) return 7;

    else if(kb_Data[4] & kb_2) return 2;
    else if(kb_Data[4] & kb_5) return 5;
    else if(kb_Data[4] & kb_8) return 8;

    else if(kb_Data[5] & kb_3) return 3;
    else if(kb_Data[5] & kb_6) return 6;
    else if(kb_Data[5] & kb_9) return 9;

    else return -1;
}

void render() {
    drawBoard(board, LCD_WIDTH / 2, LCD_HEIGHT / 2);

    gfx_BlitBuffer();
}