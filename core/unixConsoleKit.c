
#include <stdio.h>
#include "../consolekit.h"

void initTerminal(){

    #ifdef BOOKMARK_H_INCLUDED
    initBookMark();
    #endif

    return;
}

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

void gotoxy(int x, int y) {
    if (x < 0) x = 0;
    if (y < 0) y = 0;

    printf("\033[%d;%dH", y+1, x+1);
}

void moveCursor(int dx, int dy){

    if(dx > 0) printf("\033[%dC", dx);
    else if(dx < 0) printf("\033[%dD", -dx);

    if(dy > 0) printf("\033[%dB", dy);
    else if(dy < 0) printf("\033[%dA", -dy);
}

void moveUp(int n){
    moveCursor(0, -n);
}

void moveDown(int n){
    moveCursor(0, n);
}

void moveRight(int n){
    moveCursor(n, 0);
}

void moveLeft(int n){
    moveCursor(-n, 0);
}

void saveCursor(){
    printf("\033[s");
}

void restoreCursor(){
    printf("\033[u");
}

void hideCursor(){
    printf("\033[?25l");
}

void showCursor(){
    printf("\033[?25h");
}

void clearScreen(){
    printf("\033[2J\033[H");
}

void home(){
    printf("\033[H");
}

void clearLine(){
    printf("\033[2K");
}

void clearToEnd(){
    printf("\033[0K");
}

void clearToStart(){
    printf("\033[1K");
}

