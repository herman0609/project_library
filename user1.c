#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "user.h"
#include "library.h"


// Code module for the library user
// They can look for borrow and return books
void user(char* name, Book* head, User* uhead){             //Different from the librarian part, the user part is an independent part
    Borrow * borrow_head = (Borrow *)malloc((sizeof(Borrow)));  //Every time you enter and leave this function, the data will be updated again
    borrow_head->next = NULL;
    FILE *fr, *fw;
    char input[50];
    fr = fopen("borrower_data.txt", "r");
    if(load_borrow(fr, borrow_head)){
        return;
    }
    int option = 0;
                printf("\t\t\t\033[43;34m                                          \033[0m\n");  
                printf("\t\t\t\033[43;31m   ------------------------------------   \033[0m\n"); 
                printf("\t\033[43;31m\t\t   *          Hello! Dear User        *   \033[0m\n");    
                printf("\t\t\t\033[43;31m   ------------------------------------   \033[0m\n"); 
                printf("\t\t\t\033[43;34m                                          \033[0m\n");  
                printf("\n");  
                printf("\t\t\t\033[47;34m                                          \033[0m\n");
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");  
                printf("\t\033[47;34m\t\t   *          1. Borrow books         *   \033[0m\n");  
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
                printf("\t\t\t\033[47;34m                                          \033[0m\n");
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n"); 
                printf("\t\033[47;34m\t\t   *          2. Return books         *   \033[0m\n");    
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
                printf("\t\t\t\033[47;34m                                          \033[0m\n");
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n"); 
                printf("\t\033[47;34m\t\t   *          3. Search books         *   \033[0m\n");    
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
                printf("\t\t\t\033[47;34m                                          \033[0m\n");
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n"); 
                printf("\t\033[47;34m\t\t   *        4. Display All books      *   \033[0m\n");    
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
                printf("\t\t\t\033[47;34m                                          \033[0m\n");
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n"); 
                printf("\t\033[47;34m\t\t   *            5. Log out            *   \033[0m\n");    
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
                printf("\t\t\t\033[47;34m                                          \033[0m\n");
    do{
        printf("\t\t\tUser Option:");
        scanf("%s", input);
        option = OutputOption(input);
        printf("\n");
        if(option!=1 && option!=2 && option!=3 && option!=4 && option!=5){
            printf("\t\t\tInvalid option! Please input again!\n");
        }
    } while (option!=1 && option!=2 && option!=3 && option!=4 && option!=5);
    switch (option) {
        case 1:
            printBookList(head);
            if(borrowBook(head, borrow_head, name)){
                printf("\n\t\t\tBorrow Book Failed!\n\n");
            } else{
                printf("\t\t\tBorrow Book Successfully!\n\n");
            }
            fw = fopen("borrower_data.txt", "w");
            store_borrow(fw, borrow_head);
            deleteBorrow(borrow_head);
            fclose(fw);
            user(name, head, uhead);
            break;
        case 2:
            if(returnBook(head, borrow_head, name)){
                printf("\n\t\t\tReturn Book Failed!\n\n");
            } else{
                printf("\n\t\t\tReturn Book Successfully!\n\n");
            }
            fw = fopen("borrower_data.txt", "w");
            store_borrow(fw, borrow_head);
            deleteBorrow(borrow_head);
            fclose(fw);
            user(name, head, uhead);
            break;
        case 3:
            findBooks(head);
            user(name, head, uhead);
            break;
        case 4:
            printBookList(head);
            user(name, head, uhead);
			break;
        case 5:
            printf("\t\t\tLog out successfully!\n\n");
            fw = fopen("borrower_data.txt", "w");
            store_borrow(fw, borrow_head);
            deleteBorrow(borrow_head);
            fclose(fw);
            Login(uhead, head);
            break;
        default:
            break;
    }
}

int returnBook(Book *head, Borrow *borrow_head, char *name){
    printf("\t\t\tThe books you have borrowed:\n");
    Borrow *node = borrow_head->next;
    Book book;
    char input[50];
    int i = 0, check_num, option;
    while(node){
        check_num = strcmp(name, node->borrower);
        if(check_num==0){
            i++;
            printf("\t%d--%s-%s-%d\n", i, node->title, node->authors, node->year);
        }
        node = node->next;
    }
    if(i==0){
        printf("\t\t\t\tNONE\n\n");
        printf("\t\t\tYou haven't borrow any book!");
        return 1;
    } else{
        do {
            printf("\t\t\tChoose one book you want to return:");
            scanf("%s", input);
            option = OutputOption(input);
            if(option<0 || option>i){
                printf("\n\t\t\tInvalid Option!\n\t\t\tPlease input again!\n\n");
            }
        } while (option<0 || option>i);
        i = 0;
        Borrow *new_node = borrow_head->next;
        while (new_node){
            check_num = strcmp(name, new_node->borrower);
            if(check_num==0){
                i++;
                if(option==i){
                    book.id = new_node->id;
                    book.title = new_node->title;
                    book.authors = new_node->authors;
                    book.year = new_node->year;
                    break;
                }
            }
            new_node = new_node->next;
        }
        add_book(book, head);                       //In the process of returning books, not only the data of borrowing
        remove_borrow(book, borrow_head, name);     //books will be deleted, but also the data of books will be added
        store_books("book_data.txt", head);
    }
    return 0;
}

int borrowBook(Book *head, Borrow *borrow_head, char *name){    //Same way, in the process of borrowing books, not only the data of borrowing
    int option;                                                 //books will be added, but also the data of books will be deleted
    char findChar[50], input[50];
    int findYear;
    Book borrowBook;
    Book *node;
    Book *new_node;
    BookList bookFind;
                printf("\t\t\t\033[43;34m                                          \033[0m\n");  
                printf("\t\t\t\033[43;31m   ------------------------------------   \033[0m\n"); 
                printf("\t\033[43;31m\t\t   *           Borrow a book          *   \033[0m\n");    
                printf("\t\t\t\033[43;31m   ------------------------------------   \033[0m\n"); 
                printf("\t\t\t\033[43;34m                                          \033[0m\n");  
                printf("\n");  
                printf("\t\t\t\033[47;34m                                          \033[0m\n");
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");  
                printf("\t\033[47;34m\t\t   *            1. by tittle          *   \033[0m\n");  
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
                printf("\t\t\t\033[47;34m                                          \033[0m\n");
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n"); 
                printf("\t\033[47;34m\t\t   *            2. by author          *   \033[0m\n");    
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
                printf("\t\t\t\033[47;34m                                          \033[0m\n");
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n"); 
                printf("\t\033[47;34m\t\t   *             3. by year           *   \033[0m\n");    
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
                printf("\t\t\t\033[47;34m                                          \033[0m\n");
  
    do {
        printf("\t\t\tBook borrowing Option:");
        scanf("%s", input);
        option = OutputOption(input);
        printf("\n");
        if(option != 1 && option != 2 && option != 3){
            printf("\t\t\tInvalid option! Please input again!\n");
        }
    } while (option != 1 && option != 2 && option != 3);
    switch (option) {
        case 1:
            printf("\t\t\tPlease input the title of the book:");
            scanf("%s", findChar);
            printf("\n");
            bookFind = find_book_by_title(findChar, head);
            if(bookFind.length == 0){
                printf("\t\t\tNo books were found!\n");
                deleteBookList(bookFind.list);
                return 1;
            }
            node = bookFind.list->next;
            if(bookFind.length == 1){
                node = bookFind.list->next;
                printf("\t\t\tOne book found!\n");
                printf("\t\t\t\t%d - %s - %s - %d\n", 1, node->title, node->authors, node->year);
                printf("\t\t\tPlease check\n");
                printf("\t\t\t\t1. Yes, This is the book I want\n\t\t\t\t2. No, I want to exit\n");
                do {
                    printf("\t\t\tOption:");
                    scanf("%s", input);
                    option = OutputOption(input);
                    if(option != 1 && option != 2){
                        printf("Invalid option! Please input again!\n");
                    }
                }while (option != 1 && option != 2);
                printf("\n");
                if(option == 1){
                    borrowBook.id = node->id;
                    borrowBook.title = node->title;
                    borrowBook.authors = node->authors;
                    borrowBook.year = node->year;
                    borrowBook.copies = node->copies;
                    if(add_borrow(borrowBook, borrow_head, name)){
                        printf("\t\t\tYou have already borrowed this book before!\n");
                        return 1;
                    }
                    deleteBookList(bookFind.list);
                    remove_book(borrowBook, head);
                    store_books("book_data.txt", head);
                    break;
                } else{
                    return 1;
                }
            } else{
                printf("\t\t\t%d books have been found!\n", bookFind.length);
                for(int i =1; i<bookFind.length+1; i++){
                    printf("\t\t\t\t%d - %s - %s - %d\n", i, node->title, node->authors, node->year);
                    node = node->next;
                }
                do {
                    printf("\t\t\tPlease choose which book you want to borrow:");
                    scanf("%s", input);
                    option = OutputOption(input);
                    if(option<1 || option>bookFind.length){
                        printf("\t\t\tInvalid option! Please input again!\n");
                    }
                } while (option<1 || option>bookFind.length);
                printf("\n");
                new_node = bookFind.list->next;
                for(int i =1; i<bookFind.length+1; i++){
                    if(option==i){
                        borrowBook.id = new_node->id;
                        borrowBook.title = node->title;
                        borrowBook.authors = node->authors;
                        borrowBook.year = new_node->year;
                        borrowBook.copies = new_node->copies;
                        deleteBookList(bookFind.list);
                        if(add_borrow(borrowBook, borrow_head, name)){
                            printf("\t\t\tYou have already borrowed this book before!\n");
                            return 1;
                        }
                        remove_book(borrowBook, head);
                        store_books("book_data.txt", head);
                        break;
                    }
                    new_node = new_node->next;
                }
            }
            break;
        case 2:
            printf("\t\t\tPlease input the author of the book you want to borrow:");
            scanf("%s", findChar);
            printf("\n");
            bookFind = find_book_by_author(findChar, head);
            if(bookFind.length == 0){
                printf("\t\t\tNo books were found!");
                deleteBookList(bookFind.list);
                return 1;
            }
            node = bookFind.list->next;
            if(bookFind.length == 1){
                node = bookFind.list->next;
                printf("\t\t\tOnly one book has been found!\n");
                printf("\t\t\t\t%d - %s - %s - %d\n", 1, node->title, node->authors, node->year);
                printf("\t\t\tPlease check if this is the book you want to borrow\n");
                printf("\t\t\t\t1. Yes, I want to borrow it\n\t\t\t\t2. No, I want to exit\n");
                do {
                    printf("\t\t\tOption:");
                    scanf("%s", input);
                    option = OutputOption(input);
                    if(option != 1 && option != 2){
                        printf("\t\t\tInvalid option! Please input again!\n");
                    }
                }while (option != 1 && option != 2);
                printf("\n");
                if(option == 1){
                    borrowBook.id = node->id;
                    borrowBook.title = node->title;
                    borrowBook.authors = node->authors;
                    borrowBook.year = node->year;
                    borrowBook.copies = node->copies;
                    deleteBookList(bookFind.list);
                    if(add_borrow(borrowBook, borrow_head, name)){
                        printf("\t\t\tYou have already borrowed this book before!\n");
                        return 1;
                    }
                    remove_book(borrowBook, head);
                    store_books("book_data.txt", head);
                    break;
                } else{
                    return 1;
                }
            } else{
                printf("\t\t\t%d books have been found!\n", bookFind.length);
                for(int i =1; i<bookFind.length+1; i++){
                    printf("\t%d - %s - %s - %d\n", i, node->title, node->authors, node->year);
                    node = node->next;
                }
                do {
                    printf("\t\t\tPlease choose which book you want to borrow:");
                    scanf("%s", input);
                    option = OutputOption(input);
                    if(option<1 || option>bookFind.length){
                        printf("\t\t\tInvalid option! Please input again!\n");
                    }
                } while (option<1 || option>bookFind.length);
                printf("\n");
                new_node = bookFind.list->next;
                for(int i =1; i<bookFind.length+1; i++){
                    if(option==i){
                        borrowBook.id = new_node->id;
                        borrowBook.title = node->title;
                        borrowBook.authors = node->authors;
                        borrowBook.year = new_node->year;
                        borrowBook.copies = new_node->copies;
                        deleteBookList(bookFind.list);
                        if(add_borrow(borrowBook, borrow_head, name)){
                            printf("\t\t\tYou have already borrowed this book before!\n");
                            return 1;
                        }
                        remove_book(borrowBook, head);
                        store_books("book_data.txt", head);
                        break;
                    }
                    new_node = new_node->next;
                }
            }
            break;
        case 3:
            printf("\t\t\tPlease input the published year of the book you want to borrow:");
            scanf("%s", input);
            findYear = OutputOption(input);
            printf("\n");
            bookFind = find_book_by_year(findYear, head);
            if(bookFind.length == 0){
                printf("\t\t\tNo books were found!");
                deleteBookList(bookFind.list);
                return 1;
            }
            node = bookFind.list->next;
            if(bookFind.length == 1){
                node = bookFind.list->next;
                printf("\t\t\tOnly one book has been found!\n");
                printf("\t\t\t\t%d - %s - %s - %d\n", 1, node->title, node->authors, node->year);
                printf("\t\t\tPlease check if this is the book you want to borrow\n");
                printf("\t\t\t\t1. Yes, I want to borrow it\n\t\t\t\t2. No, I want to exit\n");
                do {
                    printf("\t\t\tOption:");
                    scanf("%s", input);
                    option = OutputOption(input);
                    if(option != 1 && option != 2){
                        printf("\t\t\tInvalid option! Please input again!\n");
                    }
                }while (option != 1 && option != 2);
                printf("\n");
                if(option == 1){
                    borrowBook.id = node->id;
                    borrowBook.title = node->title;
                    borrowBook.authors = node->authors;
                    borrowBook.year = node->year;
                    borrowBook.copies = node->copies;
                    deleteBookList(bookFind.list);
                    if(add_borrow(borrowBook, borrow_head, name)){
                        printf("\t\t\tYou have already borrowed this book before!\n");
                        return 1;
                    }
                    remove_book(borrowBook, head);
                    store_books("book_data.txt", head);
                    break;
                } else{
                    return 1;
                }
            } else{
                printf("\t\t\t%d books have been found!\n", bookFind.length);
                for(int i =1; i<bookFind.length+1; i++){
                    printf("\t%d - %s - %s - %d\n", i, node->title, node->authors, node->year);
                    node = node->next;
                }
                do {
                    printf("\t\t\tPlease choose which book you want to borrow:");
                    scanf("%s", input);
                    option = OutputOption(input);
                    if(option<1 || option>bookFind.length){
                        printf("\t\t\tInvalid option! Please input again!\n");
                    }
                } while (option<1 || option>bookFind.length);
                printf("\n");
                new_node = bookFind.list->next;
                for(int i =1; i<bookFind.length+1; i++){
                    if(option==i){
                        borrowBook.id = new_node->id;
                        borrowBook.title = new_node->title;
                        borrowBook.authors = new_node->authors;
                        borrowBook.year = new_node->year;
                        borrowBook.copies = new_node->copies;
                        deleteBookList(bookFind.list);
                        if(add_borrow(borrowBook, borrow_head, name)){
                            printf("\t\t\tYou have already borrowed this book before!\n");
                            return 1;
                        }
                        remove_book(borrowBook, head);
                        store_books("book_data.txt", head);
                        break;
                    }
                    new_node = new_node->next;
                }
            }
            break;
        default:
            break;
    }
    return 0;
}

int load_borrow(FILE *file, Borrow *head){
    int a;
    char *borrow;
    char *title;
    char *authors;
    if(file){
        Borrow *last = head;
        while(1){
            Borrow *node = (Borrow *)malloc((sizeof(Borrow)));
            borrow = (char *)malloc(sizeof(char) * 100);
            title = (char *)malloc(sizeof(char) * 100);
            authors = (char *)malloc(sizeof(char) * 100);
            a = fscanf(file, "%s%d%s%s%d", borrow, &node->id, title, authors, &node->year);
            if(a !=5){
                free((void*)node);
                break;
            }
            node->borrower = borrow;
            node->title = title;
            node->authors = authors;
            last->next = node;
            last = node;
        }
        last->next = NULL;
        fclose(file);
        return 0;
    }
    printf("\t\t\tData load failure!");
    fclose(file);
    return 1;
}

int store_borrow(FILE *file, Borrow * head){
    Borrow *node = head->next;
    while (node){
        fprintf(file, node->borrower);
        fprintf(file, "\n");
        fprintf(file, "%d", node->id);
        fprintf(file, "\n");
        fprintf(file, node->title);
        fprintf(file, "\n");
        fprintf(file, node->authors);
        fprintf(file, "\n");
        fprintf(file, "%d", node->year);
        fprintf(file, "\n");
        fprintf(file, "\n");

        node = node->next;
    }
    return 0;
}

int add_borrow(Book book, Borrow *head, char *name){
    Borrow *node = head->next;
    if(node==NULL){
        Borrow *p = (Borrow *)malloc((sizeof(Borrow)));
        p->borrower = name;
        p->id = book.id;
        p->title = book.title;
        p->authors = book.authors;
        p->year = book.year;
        head->next = p;
        p->next = NULL;
        return 0;
    }
    int check_num;
    while(node){
        check_num = strcmp(name, node->borrower);
        if(book.id == node->id && check_num == 0){
            return 1;
        }
        if(node->next == NULL){
            Borrow *p = (Borrow *)malloc((sizeof(Borrow)));
            p->borrower = name;
            p->id = book.id;
            p->title = book.title;
            p->authors = book.authors;
            p->year = book.year;
            node->next = p;
            p->next = NULL;
            return 0;
        }
        node = node->next;
    }
    return 0;
}

int remove_borrow(Book book, Borrow *head, char *name){
    Borrow *node = head->next, *last = head;
    int check_num;
    while(node){
        check_num = strcmp(name, node->borrower);
        if(book.id == node->id && check_num == 0){
            last->next = node->next;
            free(node->authors);
            free(node->borrower);
            free(node->title);
            break;
        }
        last = last->next;
        node = node->next;
    }
    return 0;
}

void deleteBorrow(Borrow* head){
    Borrow *p=head, *q;
    while (p!=NULL){
        q = p;
        p = p->next;
        free((void*)q);
    }
}