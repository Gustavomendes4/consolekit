
#include <stdio.h>
#include <windows.h>

#include "../consolekit.h"

#define MY_HANDLE initHandle()

WORD defaultAttributes;
HANDLE hnd = NULL;

TermColor curBG, curFG;

COORD savedPos = {0, 0};

//  Funçoes usada para manipulação interna no WINDOWS

static HANDLE initHandle(){
    if(hnd == NULL)
        hnd = GetStdHandle(STD_OUTPUT_HANDLE);

    return hnd;
}

static COORD getCursorPos(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(MY_HANDLE, &csbi);
    return csbi.dwCursorPosition;
}

//

void initTerminal(){
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(MY_HANDLE, &info);

    defaultAttributes = info.wAttributes;

    curBG = TERM_BLACK;
    curFG = TERM_BRIGHT_WHITE;

    #ifdef BOOKMARK_H_INCLUDED
    initBookMark();
    #endif

}

void setColor(TermColor fgColor, TermColor bgColor){

    WORD fg, bg;
    // FOREGROUND
    switch(fgColor){
        case TERM_BLACK:         fg = 0; break;
        case TERM_BLUE:          fg = FOREGROUND_BLUE; break;
        case TERM_GREEN:         fg = FOREGROUND_GREEN; break;
        case TERM_CYAN:          fg = FOREGROUND_BLUE | FOREGROUND_GREEN; break;
        case TERM_RED:           fg = FOREGROUND_RED; break;
        case TERM_MAGENTA:       fg = FOREGROUND_RED | FOREGROUND_BLUE; break;
        case TERM_YELLOW:        fg = FOREGROUND_RED | FOREGROUND_GREEN; break;
        case TERM_WHITE:         fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;

        case TERM_GRAY:          fg = FOREGROUND_INTENSITY; break;
        case TERM_LIGHT_BLUE:    fg = FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
        case TERM_LIGHT_GREEN:   fg = FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
        case TERM_LIGHT_CYAN:    fg = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
        case TERM_LIGHT_RED:     fg = FOREGROUND_RED | FOREGROUND_INTENSITY; break;
        case TERM_LIGHT_MAGENTA: fg = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
        case TERM_LIGHT_YELLOW:  fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
        case TERM_BRIGHT_WHITE:  fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;

        default: return;
    }

    // BACKGROUND
    switch(bgColor){
        case TERM_BLACK:         bg = 0; break;
        case TERM_BLUE:          bg = BACKGROUND_BLUE; break;
        case TERM_GREEN:         bg = BACKGROUND_GREEN; break;
        case TERM_CYAN:          bg = BACKGROUND_BLUE | BACKGROUND_GREEN; break;
        case TERM_RED:           bg = BACKGROUND_RED; break;
        case TERM_MAGENTA:       bg = BACKGROUND_RED | BACKGROUND_BLUE; break;
        case TERM_YELLOW:        bg = BACKGROUND_RED | BACKGROUND_GREEN; break;
        case TERM_WHITE:         bg = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; break;

        case TERM_GRAY:          bg = BACKGROUND_INTENSITY; break;
        case TERM_LIGHT_BLUE:    bg = BACKGROUND_BLUE | BACKGROUND_INTENSITY; break;
        case TERM_LIGHT_GREEN:   bg = BACKGROUND_GREEN | BACKGROUND_INTENSITY; break;
        case TERM_LIGHT_CYAN:    bg = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY; break;
        case TERM_LIGHT_RED:     bg = BACKGROUND_RED | BACKGROUND_INTENSITY; break;
        case TERM_LIGHT_MAGENTA: bg = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY; break;
        case TERM_LIGHT_YELLOW:  bg = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY; break;
        case TERM_BRIGHT_WHITE:  bg = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY; break;

        default: return;
    }

    curFG = fgColor;
    curBG = bgColor;
    SetConsoleTextAttribute(MY_HANDLE, fg | bg);

}

void setTextColor(TermColor color) { 
    setColor(color, curBG);
}

void setBackgroundColor(TermColor color){
    setColor(curFG, color);
}

void setTextColorRGB(int r, int g, int b){ //ANSI

    if( (r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
        return;

    printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void setBackgroundColorRGB(int r, int g, int b){ // ANSI

    if( (r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
        return;

    printf("\033[48;2;%d;%d;%dm", r, g, b);
}

void setTextStyle(TermTextStyle style){

    switch(style){

        case RESET:
        case BOLD:
        case LIGHT:
        case ITALIC:
        case UNDERLINE:
        case BLINKF:
        case BLINKS:
        case REVERSED:
        case HIDDEN:
        case STRIKE:

        case NO_BOLD:
        case NO_UNDERLINE:
        case RESET_FG:
        case RESET_BG:;
    }
}

void resetColor() {
    SetConsoleTextAttribute(MY_HANDLE, defaultAttributes);
}

void gotoxy(int x, int y){
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(MY_HANDLE, dwPos);
}

void moveCursor(int dx, int dy){

    //gotoxy com validacao

    if(dx == 0 && dy == 0)
        return;

    COORD pos = getCursorPos();

    int newX = pos.X + dx;
    int newY = pos.Y + dy;

    if(newX < 0) newX = 0;
    if(newY < 0) newY = 0;

    int maxX = getMaxX();
    int maxY = getMaxY();

    if(newX > maxX) newX = maxX;
    if(newY > maxY) newY = maxY;

    gotoxy(newX, newY);
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
    savedPos = getCursorPos();
}

void restoreCursor(){
    gotoxy((int)savedPos.X, (int)savedPos.Y);
}

void hideCursor(){
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(MY_HANDLE, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(MY_HANDLE, &cursorInfo);
}

void showCursor(){
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(MY_HANDLE, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(MY_HANDLE, &cursorInfo);
}

void clearScreen(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(MY_HANDLE, &csbi);

    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
    DWORD charsWritten;

    COORD homeCoords = {0, 0};

    FillConsoleOutputCharacter(MY_HANDLE, ' ', consoleSize, homeCoords, &charsWritten);
    FillConsoleOutputAttribute(MY_HANDLE, csbi.wAttributes, consoleSize, homeCoords, &charsWritten);

    SetConsoleCursorPosition(MY_HANDLE, homeCoords);
}

void home(){
    SetConsoleCursorPosition(MY_HANDLE, (COORD){0, 0});
}

void clearLine(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(MY_HANDLE, &csbi);

    DWORD charsWritten;

    COORD lineStart = {0, csbi.dwCursorPosition.Y};

    FillConsoleOutputCharacter(MY_HANDLE, ' ', csbi.dwSize.X, lineStart, &charsWritten);
    FillConsoleOutputAttribute(MY_HANDLE, csbi.wAttributes, csbi.dwSize.X, lineStart, &charsWritten);

    SetConsoleCursorPosition(MY_HANDLE, lineStart);
}

void clearToEnd(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(MY_HANDLE, &csbi);

    DWORD charsWritten;

    int remaining = csbi.dwSize.X - csbi.dwCursorPosition.X;

    COORD start = csbi.dwCursorPosition;

    FillConsoleOutputCharacter(MY_HANDLE, ' ', remaining, start, &charsWritten);
    FillConsoleOutputAttribute(MY_HANDLE, csbi.wAttributes, remaining, start, &charsWritten);
}

void clearToStart(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(MY_HANDLE, &csbi);

    DWORD charsWritten;

    COORD start = {0, csbi.dwCursorPosition.Y};

    int count = csbi.dwCursorPosition.X + 1;

    FillConsoleOutputCharacter(MY_HANDLE, ' ', count, start, &charsWritten);
    FillConsoleOutputAttribute(MY_HANDLE, csbi.wAttributes, count, start, &charsWritten);
}

int getMaxX(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(MY_HANDLE, &csbi);
    return csbi.srWindow.Right;
}

int getMaxY(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(MY_HANDLE, &csbi);
    return csbi.srWindow.Bottom;
}

int getCursorX(){
    COORD c = getCursorPos();
    return c.X;
}

int getCursorY(){
    COORD c = getCursorPos();
    return c.Y;
}
