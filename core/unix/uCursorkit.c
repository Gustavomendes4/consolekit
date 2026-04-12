
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

void home(){
    printf("\033[H");
}
