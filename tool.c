#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "library.h"
#include "tourist.h"

// Utility functions to handle some important functions
// The specific operation of removing, adding and finding

BookList find_book_by_title(const char *title, Book* head){

    BookList book;
    int i = 0;
    Book *new_head, *p, *q;
    new_head = (Book *)malloc((sizeof(Book)));
    p = new_head;
    int check_num;
    Book* node = head->next;
    while (node){
        check_num = strcmp(title, node->title);

        if(check_num == 0){
            i++;
            q = (Book *)malloc((sizeof(Book)));
            q->id = node->id;
            q->title = node->title;
            q->authors = node->authors;
            q->year = node->year;
            q->copies = node->copies;
            p->next = q;
            p = q;
        }
        node = node->next;
    }
    p->next = NULL;
    book.list = new_head;
    book.length = i;
    return book;
}

BookList find_book_by_author (const char *author, Book* head){
    BookList book;
    int i = 0;
    Book *new_head, *p, *q;
    new_head = (Book *)malloc((sizeof(Book)));
    p = new_head;
    int check_num;
    Book* node = head->next;
    while (node){
        check_num = strcmp(author, node->authors);
        if(check_num == 0){
            i++;
            q = (Book *)malloc((sizeof(Book)));
            q->id = node->id;
            q->title = node->title;
            q->authors = node->authors;
            q->year = node->year;
            q->copies = node->copies;
            p->next = q;
            p = q;
        }
        node = node->next;
    }
    p->next = NULL;
    book.list = new_head;
    book.length = i;
    return book;
}

BookList find_book_by_year (unsigned int year, Book* head){
    BookList book;
    int i = 0;
    Book *new_head, *p, *q;
    new_head = (Book *)malloc((sizeof(Book)));
    p = new_head;
    Book* node = head->next;
    while (node){
        if(year == node->year){
            i++;
            q = (Book *)malloc((sizeof(Book)));
            q->id = node->id;
            q->title = node->title;
            q->authors = node->authors;
            q->year = node->year;
            q->copies = node->copies;
            p->next = q;
            p = q;
        }
        node = node->next;
    }
    p->next = NULL;
    book.list = new_head;
    book.length = i;
    return book;
}

int remove_book(Book book, Book *head){
    Book *node = head->next;
    Book *last = head;
    while(node){
        if(node->id == book.id){
            if(node->copies == 0){
                return 1;
            }
            node->copies = node->copies-1;
            if(node->copies == 0){
                last->next = node->next;
                free((void*)node);
            }
        }
        last = last->next;
        node = node->next;
    }
    return 0;
}

int change_book(Book book, Book *head){
    Book *node = head->next;
    Book *last = head;
    char *name;
    name=(char*)malloc(sizeof(char)*100);
    char *author;
    author=(char*)malloc(sizeof(char)*100);
    printf("\t\t\tNew name:");
    scanf("%s", name);
    printf("\t\t\tNew author name:");
    scanf("%s", author);
    while(node){
        if(node->id == book.id){
            if(strcmp(node->title, name)==0){
                return 1;
            }
            node->title = name;
            node->authors = author;
            printf("\n\t\t\tChange information successfully!\n");
            if(node->copies == 0){
                last->next = node->next;
                free((void*)node);
            }
        }
        last = last->next;
        node = node->next;
    }
    return 0;
}

int add_book(Book book, Book *head){
    Book *node = head->next;
    while (node){
        if(book.id == node->id){
            node->copies++;
            break;
        }
        if(node->next == NULL){
            Book *p = (Book *)malloc((sizeof(Book)));
            p->id = book.id;
            p->title = book.title;
            p->authors = book.authors;
            p->year = book.year;
            p->copies = 1;
            node->next = p;
            p->next = NULL;
            break;
        }
        if(node->id<book.id && book.id<node->next->id){
            Book *p = (Book *)malloc((sizeof(Book)));
            p->id = book.id;
            p->title = book.title;
            p->authors = book.authors;
            p->year = book.year;
            p->copies = 1;
            p->next = node->next;
            node->next = p;
            break;
        }
        node = node->next;
    }
    return 0;
}

int OutputOption(char *input){
    int ret = 0;
    int length;
    length = strlen(input);
    do {
        if(isInteger(input)){
            printf("\n\t\t\tInvalid input!\n\t\t\tPlease input again:");
            scanf("%s", input);
            length = strlen(input);
        }
    } while (isInteger(input));
    for(int i=0; i<length; i++){
        ret = ret*10 + (input[i]-'0');
    }
    return ret;
}

int isInteger(char *input){
    int length = strlen(input);
    for(int i=0; i<length; i++){
        if(input[i]<'0' || input[i]>'9'){
            return 1;
        }
    }
    return 0;
}