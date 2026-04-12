#ifndef BOOKMARK_H_INCLUDED
#define BOOKMARK_H_INCLUDED

#define BOOKMARK_LIST_LEN 20

#define BOOKMARK_NAME_LEN 40

typedef struct{
    char name[BOOKMARK_NAME_LEN];
    int x, y;

    short int valid;
}Bookmark;

extern Bookmark book[BOOKMARK_LIST_LEN];

void initBookMark();

// Criação
#ifdef _WIN32
int saveCursorBookmark(const char* name);
#endif

int createCursorBookmark(const char* name, short x, short y);

// Uso
int gotoCursorBookmark(const char* name);

// Gerenciamento
int deleteCursorBookmark(const char* name);
int deleteCursorBookmark(const char* name);
int hasCursorBookmark(const char* name);
void clearCursorBookmarks();

//
int updateCursorBookmark(const char* name, short x, short y);

#endif