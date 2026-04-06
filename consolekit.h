
/*

    Ideias:
        - Criar uma lista de 'posicoes conhecidas', push e pop vinculado à uma string.






    Gustavo dos Santos Mendes, 05/04/2026.
*/

#ifndef CONSOLEKIT_H_INCLUDED
#define CONSOLEKIT_H_INCLUDED

typedef enum TermColor{

    TERM_BLACK      = 30,
    TERM_RED        = 31,
    TERM_GREEN      = 32,
    TERM_YELLOW     = 33,
    TERM_BLUE       = 34,
    TERM_MAGENTA    = 35,
    TERM_CYAN       = 36,
    TERM_WHITE      = 37,

    TERM_GRAY       = 90,
    TERM_LIGHT_BLUE = 94,
    TERM_LIGHT_GREEN= 92,
    TERM_LIGHT_CYAN = 96,
    TERM_LIGHT_RED  = 91,
    TERM_LIGHT_MAGENTA  = 95,
    TERM_LIGHT_YELLOW   = 93,
    TERM_BRIGHT_WHITE   = 97,



    TERM_INVALID_COLOR = 0

}TermColor;

typedef enum TermTextStyle{
    
    RESET   = 0,
    BOLD    = 1,
    LIGHT   = 2,
    ITALIC  = 3,
    UNDERLINE   = 4,
    BLINKF   = 5,
    BLINKS   = 6,
    REVERSED    = 7,
    HIDDEN  = 8,
    STRIKE  = 9,

    NO_BOLD = 22,
    NO_UNDERLINE = 24,
    RESET_FG = 39,
    RESET_BG = 49,

    _INVALID_STYLE = -1

}TermTextStyle;

void initTerminal();

void setColor(TermColor fgColor, TermColor bgColor);

void setTextColor(TermColor color);

void setBackgroundColor(TermColor color);

void setTextColorRGB(int r, int g, int b);

void setBackgroundColorRGB(int r, int g, int b);

void setTextStyle(TermTextStyle style);

void resetColor();

void gotoxy(int x, int y);

void moveUp(int n);

void moveDown(int n);

void moveRight(int n);

void moveLeft(int n);

void saveCursor();

void restoreCursor();

void hideCursor();

void showCursor();

void clearScreen();

void clearLine();

void clearToStart();

void clearToEnd();

int getMaxY();

int getMaxX();

void moveCursor(int dx, int dy);

void home();

int getCursorX();

int getCursorY();

#endif