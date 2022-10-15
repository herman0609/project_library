#include "book_management.h"

void librarianin(Book *head, User *uhead);
void librarianAddBooks(Book *head);
int checkIfIn(Book *head, int id);
void addExisting(Book *head);
void addInexisting(Book *head);
void printBookList(Book *head);
void librarianRemoveBooks(Book *head);
