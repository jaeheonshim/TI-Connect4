#include <tice.h>
#include <graphx.h>
#include <stdio.h>
#include "include/connectai.h"

extern struct debugframe debug;

static char s[50];

void draw_debug() {
    sprintf(s, "DEPTH: %d   H_RUN: %d", debug.depth, debug.heuristic_count);
    gfx_SetTextScale(1, 1);
    gfx_PrintStringXY(s, 2, 2);
}