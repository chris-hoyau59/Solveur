#include <stdlib.h>
#include <string.h>
#include "book.h"

book* book_init(char* title, char* author) {
    book* b = malloc(sizeof(book));
    b->author = malloc((1+strlen(author))*sizeof(char));
    strcpy(b->author, author);
    b->title = malloc((1+strlen(title))*sizeof(char));
    strcpy(b->title, title);
    b->id = rand(); //Pas super mais fonctionnel
    return b;
}

void book_destroy(book* self) {
    free(self->author);
    free(self->title);
    free(self);
}

int book_get_id(book* self) {
    return self->id;
}

char* book_get_title(book* self) {
    return self->title;
}

char* book_get_author(book* self) {
    return self->author;
}

book* book_deep_copy(book* b) {
    book* newB = book_init(b->title,b->author);
    newB->id = b->id;
    return newB;
}
