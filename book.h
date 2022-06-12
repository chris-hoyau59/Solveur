#pragma once

typedef struct _book {
    int id;
    char* author;
    char* title;
} book;


book* book_init(char* title, char* author);
void book_destroy(book* self);
int book_get_id(book* self);
char* book_get_title(book* self);
char* book_get_author(book* self);
book* book_deep_copy(book* b);
