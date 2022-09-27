#include "sqlite3.h"
#include <stdio.h>

int main()
{
    int x=sqlite3_keyword_check("BEGIN", 1);
    //returns 0 if it is not keyword
    //returns non-0 if it is keyword

    int y=sqlite3_keyword_count();
    //returns the number of keywords recogzied by Sqlite3

    printf("%d\n", y);
    printf("%d\n", x);
}