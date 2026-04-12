
#include <stdio.h>
#include <string.h>

#include "../consolekit.h"
#include "../bookmark.h"

Bookmark book[BOOKMARK_LIST_LEN];

// ========     INTERNAL FUNCTIONS  ==========

static int findBookmarkIndex(const char* name){

    if(!name) return -1;

    for(int i = 0; i < BOOKMARK_LIST_LEN; i++){

        if( book[i].valid &&
            book[i].name[0] != '\0' &&
            strcmp(name, book[i].name) == 0){
            return i;
        }
    }
    return -1;
}

static int getFreeIndex(){

    for(int i = 0; i < BOOKMARK_LIST_LEN; i++){
        if(book[i].valid == 0){
            return i;
        }
    }

    return -1;
}

static void clearBookmark(int index){

    if(index < 0 || index >= BOOKMARK_LIST_LEN)
        return;

    book[index].name[0] = '\0';
    book[index].valid = 0;
    book[index].x = 0;
    book[index].y = 0;
}

// ============================================

void initBookMark(){
    
    clearCursorBookmarks();
}

#ifdef _WIN32
int saveCursorBookmark(const char* name){

    short int x = getCursorX();
    short int y = getCursorY();

    return createCursorBookmark(name, x, y);
}
#endif

int createCursorBookmark(const char* name, short x, short y){

    if(!name) return -1;

    if(hasCursorBookmark(name)){
        return -1; // bookmark duplicado
    }

    int index = getFreeIndex();

    if(index < 0)
        return -2;

    strncpy(book[index].name, name, BOOKMARK_NAME_LEN);
    book[index].name[BOOKMARK_NAME_LEN - 1] = '\0';

    book[index].y = y;
    book[index].x = x;
    book[index].valid = 1;

    return index;
}

int gotoCursorBookmark(const char* name){
    if(!name) return 0;

    int index = findBookmarkIndex(name);

    if(index < 0 || !book[index].valid)
        return 0;

    gotoxy((int)book[index].x, (int)book[index].y);
    return 1;

}

int deleteCursorBookmark(const char* name){

    if(!name) return -1;

    int index = findBookmarkIndex(name);

    if(index < 0)
        return -1;

    clearBookmark(index);

    return 1;
}

int hasCursorBookmark(const char* name){
    if(!name) return 0;
    
    return findBookmarkIndex(name) >= 0;
}

void clearCursorBookmarks(){
    for(int i = 0; i < BOOKMARK_LIST_LEN; i++){
        clearBookmark(i);
    }
}

int updateCursorBookmark(const char* name, short x, short y){

    int index = findBookmarkIndex(name);

    if(index < 0) return -1;

    book[index].x = x;
    book[index].y = y;

    return index;
}
