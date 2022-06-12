#include <stdlib.h>
#include <string.h>
#include "library.h"


/*void entry_destroy(entry* self) {
    book_destroy(self->b);
    free(self->b);
    free(self);
}*/

library* library_init(int initial_capacity) {
    library* l = malloc(sizeof(library));
    l->capacity = initial_capacity;
    l->entryNumber = 0;
    l->entries = malloc(initial_capacity*sizeof(entry));
    return l;
}

void library_destroy(library* self) {
    //for(int i=0; i < self->entryNumber; i++) book_destroy(self->entries[i].b);
    free(self->entries);
    free(self);
}


int library_books_count(library* self) {
    return self->entryNumber;
}

void library_register_book(library* self, book* some_book) {
    for(int i=0; i < self->entryNumber; i++) {
        if(self->entries[i].b->id == some_book->id) {
            //Si le livre est déjà présent on incrémente le nombre d'exemplaire
            self->entries[i].n++;
            return;
        }
    }
    //Sinon on l'ajoute à la bibliothèque si il reste de la place
    if(self->entryNumber < self->capacity) {
        entry entree;
        entree.b = some_book;
        entree.n = 1;
        self->entries[self->entryNumber++] = entree;
    }
}

book* library_find_by_id(library* self, int id) {
    for(int i=0; i < self->entryNumber; i++) {
        if(self->entries[i].b->id == id) {
            return self->entries[i].b;
        }
    }
    return NULL;
}

book* library_find_by_title(library* self, char* title) {
    for(int i=0; i < self->entryNumber; i++) {
        if(strcmp(self->entries[i].b->title,title) == 0) {
            return self->entries[i].b;
        }
    }
    return NULL;
}

int library_is_book_available(library* self, char* title) {
    for(int i=0; i < self->entryNumber; i++) {
        if(strcmp(self->entries[i].b->title,title) == 0) {
            return self->entries[i].n;
        }
    }
    return 0;
}

book* library_borrow_book(library* self, char* title) {
    for(int i=0; i < self->entryNumber; i++) {
        if(strcmp(self->entries[i].b->title,title) == 0) {
            if(self->entries[i].n <= 0) return NULL;
            self->entries[i].n--;
            return self->entries[i].b;
        }
    }
    return NULL;
}

int library_return_book(library* self, book* some_book) {
    for(int i=0; i < self->entryNumber; i++) {
        if(strcmp(self->entries[i].b->title,some_book->title) == 0) {
            return ++self->entries[i].n;
        }
    }
    return 0;
}

book** library_find_by_author(library* self, char* author) {
    book** resultArray = NULL;
    int results = 0;
    for(int i=0; i < self->entryNumber; i++) {
        if(strcmp(self->entries[i].b->author,author) == 0) {
            resultArray = realloc(resultArray, ++results*sizeof(book*));
            resultArray[results-1] = self->entries[i].b;
        }
    }
    return resultArray;
}
