
#include <stdio.h>
#include <windows.h>

#include "../../consolekit.h"

WORD defaultAttributes;
HANDLE hnd = NULL;

TermColor curBG, curFG;

static HANDLE initHandle(){
    if(hnd == NULL)
        hnd = GetStdHandle(STD_OUTPUT_HANDLE);

    return hnd;
}

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
