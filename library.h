#include "book_management.h"

//this function is used to assemble the following functions
void Login(User* uhead, Book* bhead);

int getCustomerType();

char* userLogin(User* head);

char* registerUser(User *head);

void librarianLogin();



//These functions are used to delete linked lists
void deleteUserList(User* head);
void deleteBookList(Book* head);

//these functions are used to assemble several functions to make the main function look simpler
int load(User* uhead, Book* bhead);
int store(User* uhead, Book* bhead);
int checkUser(User* head, char *name, char *user_name);

void findBooks(Book* head);