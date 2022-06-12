#pragma once
#include "book.h"

typedef struct _entry
{
    int n;
    book* b;
} entry;


typedef struct _library
{
    int capacity;
    int entryNumber;
    entry* entries;
} library;

library* library_init(int initial_capacity);
void library_destroy(library* self);
int library_books_count(library* self);
void library_register_book(library* self, book* some_book);
book* library_find_by_id(library* self, int id);
book* library_find_by_title(library* self, char* title);
int library_is_book_available(library* self, char* title);
book* library_borrow_book(library* self, char* title);
int library_return_book(library* self, book* some_book);
book** library_find_by_author(library* self, char* author);
