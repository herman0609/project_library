#include "book_management.h"

void user(char* name, Book* head, User* uhead);
int borrowBook(Book *head, Borrow *borrow_head, char *name);
int returnBook(Book *head, Borrow *borrow_head, char *name);
int add_borrow(Book book, Borrow *head, char *name);
int remove_borrow(Book book, Borrow *head, char *name);
void deleteBorrow(Borrow* head);