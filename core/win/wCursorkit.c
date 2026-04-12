
#include <stdio.h>
#include <windows.h>

#include "../../consolekit.h"

COORD savedPos = {0, 0};

static COORD getCursorPos(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(MY_HANDLE, &csbi);
    return csbi.dwCursorPosition;
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

void home(){
    SetConsoleCursorPosition(MY_HANDLE, (COORD){0, 0});
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
