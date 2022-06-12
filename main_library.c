#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "book.h"
#include "library.h"

int main() {
    puts("= running book unit tests\n");

    book *le_silmarillion = book_init("Le Silmarillion", "J. R. R. Tolkien");
    char *copy = strdup("Le Silmarillion");
    assert(strcmp(book_get_title(le_silmarillion), copy) == 0);
    free(copy);
    copy = strdup("J. R. R. Tolkien");
    assert(strcmp(book_get_author(le_silmarillion), copy) == 0);
    free(copy);

    book *l_appel_de_cthulhu = book_init("L'Appel de Cthulhu", "H. P. Lovecraft");
    copy = strdup("L'Appel de Cthulhu");
    assert(strcmp(book_get_title(l_appel_de_cthulhu), copy) == 0);
    free(copy);
    copy = strdup("H. P. Lovecraft");
    assert(strcmp(book_get_author(l_appel_de_cthulhu), copy) == 0);
    free(copy);

    book * le_hobbit = book_init("Le Hobbit", "J. R. R. Tolkien");

    int le_silmarillion_id = book_get_id(le_silmarillion);
    int l_appel_de_cthulhu_id = book_get_id(l_appel_de_cthulhu);
    int le_hobbit_id = book_get_id(le_hobbit);

    assert(le_silmarillion_id != l_appel_de_cthulhu_id);
    assert(le_silmarillion_id != le_hobbit_id);
    assert(l_appel_de_cthulhu_id != le_hobbit_id);

    

    puts("= running library unit tests\n");

    library * bibliotheque = library_init(10);

    assert(library_books_count(bibliotheque) == 0);    
    assert(! library_is_book_available(bibliotheque, "Le Silmarillion"));    

    library_register_book(bibliotheque, le_silmarillion);
    assert(library_books_count(bibliotheque) == 1);    
    assert(library_is_book_available(bibliotheque, "Le Silmarillion"));    

    library_register_book(bibliotheque, le_silmarillion);
    assert(library_books_count(bibliotheque) == 1);    

    library_register_book(bibliotheque, l_appel_de_cthulhu);
    library_register_book(bibliotheque, le_hobbit);
    assert(library_books_count(bibliotheque) == 3);    


    book *res = library_find_by_id(bibliotheque, 420666042L);
    assert(res == NULL); // we expect that random id is not bound to any book

    res = library_find_by_id(bibliotheque, le_silmarillion_id);
    assert(res == le_silmarillion);

    res = library_find_by_id(bibliotheque, l_appel_de_cthulhu_id);
    assert(res == l_appel_de_cthulhu);

    res = library_find_by_id(bibliotheque, le_hobbit_id);
    assert(res == le_hobbit);


    res = library_find_by_title(bibliotheque, "Le Silmarillion");
    assert(res == le_silmarillion);

    res = library_find_by_title(bibliotheque, "L'Appel de Cthulhu");
    assert(res == l_appel_de_cthulhu);

    char *buffer = (char *) calloc(10, sizeof(char));
    strcat(buffer, "Le ");
    strcat(buffer, "Hobbit");
    res = library_find_by_title(bibliotheque, buffer);
    assert(res == le_hobbit);
    free(buffer);
    

    book* lookedfor_book = library_borrow_book(bibliotheque, "The Tales of Beedle the Bard");
    assert(lookedfor_book == NULL); 

    assert(library_is_book_available(bibliotheque, "L'Appel de Cthulhu"));    
    lookedfor_book = library_borrow_book(bibliotheque, "L'Appel de Cthulhu");
    assert(lookedfor_book == l_appel_de_cthulhu); 

    assert(! library_is_book_available(bibliotheque, "L'Appel de Cthulhu"));    
    lookedfor_book = library_borrow_book(bibliotheque, "L'Appel de Cthulhu");
    assert(lookedfor_book == NULL); // since there is no available copy 

    assert(library_is_book_available(bibliotheque, "Le Silmarillion"));    
    lookedfor_book = library_borrow_book(bibliotheque, "Le Silmarillion");
    assert(lookedfor_book == le_silmarillion); 
    assert(library_is_book_available(bibliotheque, "Le Silmarillion")); // since there exists 2 copies in the library  
    lookedfor_book = library_borrow_book(bibliotheque, "Le Silmarillion");
    assert(! library_is_book_available(bibliotheque, "Le Silmarillion"));  

    int status = library_return_book(bibliotheque, lookedfor_book);
    assert(status == 1);
    assert(library_is_book_available(bibliotheque, "Le Silmarillion"));    
    status = library_return_book(bibliotheque, lookedfor_book);
    assert(status == 2);
    
    book * les_contes_de_beedle_le_bard = book_init("The Tales of Beedle the Bard", "Beedle the Bard");
    status = library_return_book(bibliotheque, les_contes_de_beedle_le_bard);
    assert(! status); // since we can return a non register book


    book ** found_books = library_find_by_author(bibliotheque, "H. P. Lovecraft");
    assert(found_books[0]->title != NULL);
    assert(! strcmp(found_books[0]->title, "L'Appel de Cthulhu"));
    free(found_books);

    found_books = library_find_by_author(bibliotheque, "J. R. R. Tolkien");
    assert(found_books[0]->title != NULL);
    assert(found_books[1]->title != NULL);
    assert(strcmp(found_books[0]->title, found_books[1]->title)); // booktitles should differ
    // printf("%s\n", found_books[0]->title); // should return one of the booktitle from JRR Tolkien
    // printf("%s\n", found_books[1]->title); // should return another booktitle from JRR Tolkien
    free(found_books);

    found_books = library_find_by_author(bibliotheque, "Beedle the Bard");
    assert(found_books == NULL);
    
    puts("= cleaning up\n");

    library_destroy(bibliotheque);

    book_destroy(les_contes_de_beedle_le_bard);
    
    book_destroy(le_silmarillion);
    book_destroy(l_appel_de_cthulhu);
    book_destroy(le_hobbit);

    return EXIT_SUCCESS;
}
