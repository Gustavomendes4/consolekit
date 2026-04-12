
// #include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

char getch(void) {
    struct termios oldt, newt;
    char ch;

    // Pega configuração atual do terminal
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Desativa modo canônico e echo
    newt.c_lflag &= ~(ICANON | ECHO);

    // Aplica imediatamente
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Lê um caractere
    read(STDIN_FILENO, &ch, 1);

    // Restaura configuração original
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

char getche(void){
    char ch = getch();
    putchar(ch);
    return ch;
}

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int getInt(){

}

int getFloat(){

}

int getStr(char* str){

}

int getnStr(char* str, int max){

}
