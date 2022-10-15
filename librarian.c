#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "librarian.h"
#include "library.h"
#include "tourist.h"

// Code module for librarian
// They can add and remove the books

void librarianin(Book *head, User *uhead){
    int option;
    printf("\t\t\t\033[43;34m                                                          \033[0m\n");  
    printf("\t\t\t\033[43;31m   ----------------------------------------------------   \033[0m\n"); 
    printf("\t\033[43;31m\t\t   *               Hello! Dear librarian              *   \033[0m\n");    
    printf("\t\t\t\033[43;31m   ----------------------------------------------------   \033[0m\n"); 
    printf("\t\t\t\033[43;34m                                                          \033[0m\n");  
    printf("\n");   
    printf("\t\t\t\033[47;34m                                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");  
    printf("\t\033[47;34m\t\t   *                   1. Add books                   *   \033[0m\n");  
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n"); 
    printf("\t\033[47;34m\t\t   *                  2. Delete books                 *   \033[0m\n");    
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\033[47;34m\t\t   *                  3. Change books                 *   \033[0m\n");    
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\033[47;34m\t\t   *                4. Display all books              *   \033[0m\n");   
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                                          \033[0m\n");  
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\033[47;34m\t\t   *                5. Show all deposit               *   \033[0m\n");   
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                                          \033[0m\n");  
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\033[47;34m\t\t   *                    6. Log out                    *   \033[0m\n");   
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                                          \033[0m\n"); 
    do {
        printf("\t\t\tLibrarian Option:");
        scanf("%d", &option);
        printf("\n");
        if(option!=1 && option!=2 && option!=3 && option!=4 && option!=5 && option!=6){
            printf("\t\t\tInvalid option!\n\t\t\tPlease input again!\n\n");
        }
    } while (option!=1 && option!=2 && option!=3 && option!=4 && option!=5 && option!=6);
    switch (option) {
        case 1:
            printBookList(head);
            librarianAddBooks(head);
            printf("\n\t\t\tAdd books successfully!\n\n");
            librarianin(head, uhead);
            break;
        case 2:
            printBookList(head);
            librarianRemoveBooks(head);
            printf("\n\t\t\tRemove books successfully!\n\n");
            librarianin(head, uhead);
            break;
        case 6:
            printf("\t\t\tLog out successfully!\n");
            Login(uhead, head);
            break;
        case 5:
            read_deposit();
            librarianin(head, uhead);
            break;
        case 4:
            printBookList(head);
            librarianin(head, uhead);
			break;
        case 3:
            librarianChangeBooks(head);
            librarianin(head, uhead);
			break;
        default:
            break;
    }
}
void read_deposit(){
        FILE *file = fopen("deposit.txt", "r");
        int deposit;
        fscanf(file, "%d", &deposit);
        fclose(file);
    printf("\t\t\t\033[47;34m                                                          \033[0m\n");  
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\033[47;34m\t\t   *          The deposit of all tourist is %d        *   \033[0m\n", deposit);   
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                                          \033[0m\n"); 
    printf("\n");
}

void librarianChangeBooks(Book *head){
    int id, num;
    Book book;
    Book *node= head->next;
    printBookList(head);
    printf("\t\t\tPlease choose which books you want to change (input the ID):");
    scanf("%d", &id);
    while (checkIfIn(head, id)){
        printf("\n\t\t\tThis book is not in the library!\n");
        printf("\t\t\tPlease input again:");
        scanf("%d", &id);
    }
    printf("\n");
    printf("\t\t\tThe book whose ID is %d\n", id);
    while (node){
        if(id==node->id){
            printf("\t\t\t%d--%s-%s-%d\n", node->id, node->title, node->authors, node->year);
            book.id = node->id;
            book.title = node->title;
            book.authors = node->authors;
            book.year = node->year;
            if(node->copies==1){
                printf("\n\t\t\tAnd there is only one book you want to change\n");
            } else{
                printf("\n\t\t\tAnd there are %d books you want to change\n", node->copies);
            }
            num=1;
            change_book(book, head);
            break;
        }
        node = node->next;
    }
    store_books("book_data.txt", head);
}



void printBookList(Book *head){
    printf("\t\t\tThe Books in the library\n");
    Book *node = head->next;
    while(node){
        printf("\t\t\t%d\t\t%s\t\t%s\t\t%d\n", node->id, node->title, node->authors, node->year);
        node=node->next;
    }
    printf("\n");
}

void librarianRemoveBooks(Book *head){
    int id, num;
    Book book;
    Book *node= head->next;
    printf("\t\t\tPlease choose which books you want to remove (input the ID):");
    scanf("%d", &id);
    while (checkIfIn(head, id)){
        printf("\n\t\t\tThis book is not in the library!\n");
        printf("\t\t\tPlease input again:");
        scanf("%d", &id);
    }
    printf("\n");
    printf("\t\t\tThe book whose ID is %d\n", id);
    while (node){
        if(id==node->id){
            printf("\t\t\t%d--%s-%s-%d\n", node->id, node->title, node->authors, node->year);
            book.id = node->id;
            book.title = node->title;
            book.authors = node->authors;
            book.year = node->year;
            if(node->copies==1){
                printf("\n\t\t\tThere is only one book you want to remove\n");
            } else{
                printf("\n\t\t\tThere are %d books you want to remove\n", node->copies);
            }
            printf("\t\t\tHow many books you want remove:");
            scanf("%d", &num);
            while (num<0 || num>node->copies){
                printf("\n\t\t\tInvalid number!\nPlease input another number:");
                scanf("%d", &num);
            }
            int i;
            for(i=0; i<num; i++){
                remove_book(book, head);
            }
            break;
        }
        node = node->next;
    }
    store_books("book_data.txt", head);
}

void librarianAddBooks(Book *head){
    int option;
    printf("\n\t\t\tDo you want to add an existing book or a new book\n");
    printf("\t\t\t1. Existing book\n\t\t\t2. New book\n");
    do {
        printf("\t\t\tChoice:");
        scanf("%d", &option);
        printf("\n");
        if(option!=1 && option!=2){
            printf("\t\t\tInvalid choice!\n\t\t\tPlease input again!\n");
        }
    } while (option!=1 && option!=2);
    switch (option) {
        case 1:
            addExisting(head);
            break;
        case 2:
            addInexisting(head);
            break;
        default:
            break;
    }
    store_books("book_data.txt", head);
}

void addInexisting(Book *head){
    int id, num;

    char *title = (char *)malloc(sizeof(char) * 100);
    char *authors = (char *)malloc(sizeof(char) * 100);

    Book book;
    printf("\t\t\tPlease input the book ID of the book you want to add:");
    scanf("%d", &id);
    while (checkIfIn(head, id)==0){
        printf("\n\t\t\tThe library already has books with this ID!\n");
        printf("\t\t\tPlease input again:");
        scanf("%d", &id);
    }
    printf("\n");
    book.id = id;
    printf("\t\t\tPlease input the title of this book:");
    scanf("%s", title);
    book.title = title;
    printf("\t\t\tPlease input the author of this book:");
    scanf("%s", authors);
    book.authors = authors;
    printf("\t\t\tPlease input the year of this book:");
    scanf("%d", &book.year);
    printf("\t\t\tHow many books you want to add:");
    scanf("%d", &num);
    while (num<0){
        printf("\t\t\tInvalid number!\nPlease input a positive number:\n");
        scanf("%d", &num);
    }
    for(int i=0; i<num; i++){
        add_book(book, head);
    }
    store_books("book_data.txt", head);
}

void addExisting(Book *head){
    int id, num;
    Book *node = head->next;
    Book book;
    printf("\t\t\tPlease input the book ID of the book you want to add:");
    scanf("%d", &id);
    while (checkIfIn(head, id)){
        printf("\n\t\t\tThis book is not in the library!\n");
        printf("\t\t\tPlease input again:");
        scanf("%d", &id);
    }
    printf("\n");
    printf("\t\t\tThe book whose ID is %d\n", id);
    while (node){
        if(id == node->id){
            printf("\t%d--%s-%s-%d\n", node->id, node->title, node->authors, node->year);
            book.id = node->id;
            book.title = node->title;
            book.authors = node->authors;
            book.year = node->year;
            break;
        }
        node = node->next;
    }
    printf("\t\t\tHow many books you want to add:");
    scanf("%d", &num);
    while (num<0){
        printf("\t\t\tInvalid number!\n\t\t\tPlease input a positive number:\n");
        scanf("%d", &num);
    }
    for(int i=0; i<num; i++){
        add_book(book, head);
    }
    store_books("book_data.txt", head);
}

int checkIfIn(Book *head, int id){
    Book *node = head->next;
    while (node){
        if(id == node->id){
            return 0;
        }
        node = node->next;
    }
    return 1;
}