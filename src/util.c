#include <tice.h>
#include <keypadc.h>

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