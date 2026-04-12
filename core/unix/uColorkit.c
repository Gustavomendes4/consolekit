
#include "../../consolekit.h"

void setColor(TermColor fgColor, TermColor bgColor){
    printf("\033[%d;%dm", (int)fgColor, ((int)bgColor) + 10);
}

void setTextColor(TermColor color){
    printf("\033[%dm", (int)color);
}

void setBackgroundColor(TermColor color){
    printf("\033[%dm", ((int)color) + 10);
}

void setTextColorRGB(int r, int g, int b){

    if( (r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
        return;

    printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void setBackgroundColorRGB(int r, int g, int b){

    if( (r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
        return;

    printf("\033[48;2;%d;%d;%dm", r, g, b);
}

void setTextStyle(TermTextStyle style){
    printf("\033[%dm", (int)style);
}

void resetColor(){
    printf("\033[0m");
}
