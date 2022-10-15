#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "library.h"
#include "librarian.h"
#include "user.h"
#include "tourist.h"

// Code module for main library menu and file management
// It loads and store books and users

// Initialise library data

int main_tourist(){

    int choice = 5;
    printf("\t\t\t\033[43;34m                                          \033[0m\n");  
    printf("\t\t\t\033[43;31m   ------------------------------------   \033[0m\n"); 
    printf("\t\033[43;31m\t\t   *   Hello, dear tourist, welcome!  *   \033[0m\n");    
    printf("\t\t\t\033[43;31m   ------------------------------------   \033[0m\n"); 
    printf("\t\t\t\033[43;34m                                          \033[0m\n");  
    printf("\n");   
    printf("\t\t\t\033[47;34m                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");  
    printf("\t\033[47;34m\t\t   * 1. Borrow a book (Pay a deposit) *   \033[0m\n");  
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n"); 
    printf("\t\033[47;34m\t\t   *2. Return a book(Return a deposit)*   \033[0m\n");    
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
    printf("\t\033[47;34m\t\t   *       3. Search for books        *   \033[0m\n");    
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
    printf("\t\033[47;34m\t\t   *       4. Display all books       *   \033[0m\n");   
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                          \033[0m\n");  
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
    printf("\t\033[47;34m\t\t   *             5. Quit              *   \033[0m\n");   
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                          \033[0m\n"); 
    printf("\n");
    do {
        int i=0;

        char * answer = ask_question("-------------> ");
        
        choice = atoi(answer);

        free(answer);

    
 

        while (choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&i>0)
        {
            printf("\t\t\tSorry, that doesn't seem to be an option\nInput again: ");
            char * answer = ask_question("\n");

            choice = atoi(answer);

            free(answer);
            i++;
        }
        

        tourist_user *current=librarian->next;
        strcpy(current->true_name, "tourist");
        strcpy(current->tourist_user_name, "tourist");
        strcpy(current->code, "tourist");
        current->is_librarian=0;

		switch (choice) {

			case 1:
				Display_books();
                borrow_book(current);
                break;
                
			case 2:

				return_book(current);
				break;

			case 3:

				Search_books();

				break;

			case 4:

				Display_books();

				break;

            case 5:

                printf("goodbye");

				return 0;

		}

	} while (choice != 5);

	return 0;

}

int load(User* uhead, Book* bhead){
    FILE *fr_user, *fr_book;
    fr_user = fopen("user_data.txt", "r");
    fr_book = fopen("user_data.txt", "r");
    if(load_users(fr_user, uhead) || load_books(fr_book, bhead)){
        fclose(fr_user);
        fclose(fr_book);
        return 1;
    }
    fclose(fr_user);
    fclose(fr_book);
    Login(uhead, bhead);
    return 0;
}

int store(User* uhead, Book* bhead){
    FILE *fw_user, *fw_book;
    fw_user = fopen("user_data.txt", "w");
    fw_book = fopen("user_data.txt", "w");
    if(store_users(fw_user, uhead) || store_books(fw_book, bhead)){
        fclose(fw_book);
        fclose(fw_user);
        return 1;
    }
    deleteBookList(bhead);
    deleteUserList(uhead);
    fclose(fw_book);
    fclose(fw_user);
    return 0;
}



int load_users(FILE *file, User *head){
    char *name;
    char *usr_name;
    char *pass;
    file = fopen("user_data.txt", "r");
    if(file){
        int a;
        User *last = head;
        while(1){
            name = (char *)malloc(sizeof(char) * 100);
            usr_name = (char *)malloc(sizeof(char) * 100);
            pass = (char *)malloc(sizeof(char) * 100);
            User *node = (User*)malloc((sizeof(User)));
            a = fscanf(file, "%s%s%s", name, usr_name, pass);
            if(a !=3){
                free((void*)node);
                break;
            }
            node->name = name;
            node->user_name = usr_name;
            node->password = pass;
            last->next = node;
            last = node;
        }
        last->next = NULL;
        return 0;
    }
    printf("\t\t\tData load failure!");
    return 1;
}

int load_books(FILE *file, Book* head){
    file = fopen("book_data.txt", "r");
    char *title;
    char *author;
    if(file){
        int a;
        Book *last = head;
        while(1){
            Book *node = (Book *)malloc((sizeof(Book)));
            title = (char *)malloc(sizeof(char) * 100);
            author = (char *)malloc(sizeof(char) * 100);
            a = fscanf(file, "%d%s%s%d%d", &node->id, title, author, &node->year, &node->copies);
            if(a !=5){
                free((void*)node);
                break;
            }
            node->title = title;
            node->authors = author;
            last->next = node;
            last = node;
        }
        last->next = NULL;
        return 0;
    }
    printf("\t\t\tData load failure!");
    return 1;
}

void deleteUserList(User* head){
    User *p = head->next, *q;
    while (p!=NULL){
        q = p;
        p = p->next;
        free(q->name);
        free(q->password);
        free(q->user_name);
        free((void*)q);
    }
}

void deleteBookList(Book* head){
    Book *p=head->next, *q;
    while (p!=NULL){
        q = p;
        p = p->next;
        free((void*)q);
    }
}
int store_users(FILE *file, User* head){
    file = fopen("user_data.txt", "w");
    if(file){
        User *node = head->next;
        while (node){
            fprintf(file, node->name);
            fprintf(file, "\n");
            fprintf(file, node->user_name);
            fprintf(file, "\n");
            fprintf(file, node->password);
            fprintf(file, "\n");
            fprintf(file, "\n");
            node = node->next;
        }
        return 0;
    } else{
        printf("\t\t\tData storage failed!");
        return 1;
    }
}

int store_books(FILE *file, Book* head){
    file = fopen("book_data.txt", "w");
    if(file){
        Book *node = head->next;
        while (node){
            fprintf(file, "\n");
            fprintf(file, "%d", node->id);
            fprintf(file, "\n");
            fprintf(file, node->title);
            fprintf(file, "\n");
            fprintf(file, node->authors);
            fprintf(file, "\n");
            fprintf(file, "%d", node->year);
            fprintf(file, "\n");
            fprintf(file, "%d", node->copies);
            node = node->next;
        }
        return 0;
    } else{
        printf("\t\t\tData storage failed!");
        return 1;
    }
}



void Login(User* uhead, Book* bhead){
    int option;
    char *user_name;
    option = getCustomerType();
    switch (option) {
        case 1 :{
                printf("\t\t\t\033[43;34m                                          \033[0m\n");  
                printf("\t\t\t\033[43;31m   ------------------------------------   \033[0m\n"); 
                printf("\t\033[43;31m\t\t   *      Welcome to our library!     *   \033[0m\n");    
                printf("\t\t\t\033[43;31m   ------------------------------------   \033[0m\n"); 
                printf("\t\t\t\033[43;34m                                          \033[0m\n");  
                printf("\n");  
                printf("\t\t\t\033[47;34m                                          \033[0m\n");
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");  
                printf("\t\033[47;34m\t\t   *        1. Login for users        *   \033[0m\n");  
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
                printf("\t\t\t\033[47;34m                                          \033[0m\n");
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n"); 
                printf("\t\033[47;34m\t\t   *      2. Login for librarian      *   \033[0m\n");    
                printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
                printf("\t\t\t\033[47;34m                                          \033[0m\n");
            int i;
            printf("\n\t\t\tPlease choose an option: ");
            scanf("%d", &i);
            switch (i)
            {
            case 1:{

                user_name = userLogin(uhead);
                if(user_name == NULL){
                    Login(uhead, bhead);
                    printf("\nLog in successfully!\n\n");
                    free(user_name);
                    break;
                }
                user(user_name, bhead, uhead);
                free(user_name);
            }

            case 2:{
                librarianLogin();
                librarianin(bhead, uhead);
                break;
            }
            default:
                printf("\n\t\t\tplease input 1 or 2\n\t\t\tIt seems like you are a tourist\n\t\t\tThis is the tourist menu:\n\n");
                break;
            }
        }
        case 2 :{
            head=(Book*)malloc(sizeof(Book));
            Borrowedhead=(Borrowed*)malloc(sizeof(Borrowed));
            librarian= load_tourist_tourist_users("user.txt");
            head=load_tourist_books("book_data.txt");
            Borrowedhead=load_tourist_Borrowed("borrowed.txt");
            main_tourist();
            store_tourist_books();
            store_tourist_borrow();
            break;}
        case 3 :
            user_name = registerUser(uhead);
            printf("\n\t\t\tRegister successfully!\n\n");
            user(user_name, bhead, uhead);
            break;
        case 4:
            findBooks(bhead);
            printf("Click a key to be back to the main menu\n");
            system("pause");
            Login(uhead,bhead);
            break;
        case 5:{
            head=(Book*)malloc(sizeof(Book));
            Borrowedhead=(Borrowed*)malloc(sizeof(Borrowed));
            librarian= load_tourist_tourist_users("user.txt");
            head=load_tourist_books("book_data.txt");
            Borrowedhead=load_tourist_Borrowed("borrowed.txt");
            Display_books();
            printf("Click a key to be back to the main menu\n");
            system("pause");
            Login(uhead,bhead);
            break;
        }
        case 6:
            printf("\t\t\tQuit successfully!\n");
            exit(0);
            return;
        default:
            break;
    }
}

void findBooks(Book* head){
    int option;
    int findYear;
    char findChar[50];
    Book *node;
    BookList bookFind;
    printf("\t\t\t\033[43;34m                                          \033[0m\n");  
    printf("\t\t\t\033[43;31m   ------------------------------------   \033[0m\n"); 
    printf("\t\033[43;31m\t\t   *      Please choose an option     *   \033[0m\n");    
    printf("\t\t\t\033[43;31m   ------------------------------------   \033[0m\n"); 
    printf("\t\t\t\033[43;34m                                          \033[0m\n");  
    printf("\n");  
    printf("\t\t\t\033[47;34m                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");  
    printf("\t\033[47;34m\t\t   *      1. Find book by tittle      *   \033[0m\n");  
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n"); 
    printf("\t\033[47;34m\t\t   *       2. Find book by author     *   \033[0m\n");    
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n"); 
    printf("\t\033[47;34m\t\t   *        3. Find book by year      *   \033[0m\n");    
    printf("\t\t\t\033[47;34m   ------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                          \033[0m\n");
    do {
        printf("\n\t\t\tBook finding Option:");
        scanf("%d", &option);
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
            } else{
                node = bookFind.list->next;
                printf("\t\t\tThe books whose title is %s\n", findChar);
                while(node){
                    printf("\t\t\t%d--%s-%s-%d\n", node->id, node->title, node->authors, node->year);
                    node = node->next;
                }
            }
            printf("\n");
            deleteBookList(bookFind.list);
            break;
        case 2:
            printf("\t\t\tPlease input the author of the book:");
            scanf("%s", findChar);
            printf("\n");
            bookFind = find_book_by_author(findChar, head);
            if(bookFind.length == 0){
                printf("\t\t\tNo books were found!\n");
            } else{
                node = bookFind.list->next;
                printf("\t\t\tThe books whose author is %s\n", findChar);
                while(node){
                    printf("\t\t\t%d--%s-%s-%d\n", node->id, node->title, node->authors, node->year);
                    node = node->next;
                }
            }
            printf("\n");
            deleteBookList(bookFind.list);
            break;
        case 3:
            printf("\t\t\tPlease input the published year of the book:");
            scanf("%d", &findYear);
            printf("\n");
            bookFind = find_book_by_year(findYear, head);
            if(bookFind.length == 0){
                printf("\t\t\tNo books were found!\n");
            } else{
                node = bookFind.list->next;
                printf("\t\t\tThe books whose published year is %d\n", findYear);
                while(node){
                    printf("\t\t\t%d--%s-%s-%d\n", node->id, node->title, node->authors, node->year);
                    node = node->next;
                }
            }
            printf("\n");
            deleteBookList(bookFind.list);
            break;
        default:
            break;
    }
}

int getCustomerType(){
    int option;
    char input[50];
    printf("\n\n\n\n\n\n");  
    system("cls");
    printf("\t\t\t\033[43;34m                                                          \033[0m\n");  
    printf("\t\t\t\033[43;31m   ----------------------------------------------------   \033[0m\n"); 
    printf("\t\033[43;31m\t\t   *              Welcome To The Library              *   \033[0m\n");    
    printf("\t\t\t\033[43;31m   ----------------------------------------------------   \033[0m\n"); 
    printf("\t\t\t\033[43;34m                                                          \033[0m\n");  
    printf("\n");   
    printf("\t\t\t\033[47;34m                                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");  
    printf("\t\033[47;34m\t\t   *          1. I am a student or librarian          *   \033[0m\n");  
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n"); 
    printf("\t\033[47;34m\t\t   *           2. I am a tourist (No login)           *   \033[0m\n");    
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\033[47;34m\t\t   *            3. Registration for users             *   \033[0m\n");    
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                                          \033[0m\n");
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\033[47;34m\t\t   *                 4. Search books                  *   \033[0m\n");   
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                                          \033[0m\n");  
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\033[47;34m\t\t   *                 5. Display books                 *   \033[0m\n");   
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                                          \033[0m\n"); 
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\033[47;34m\t\t   *                     6. Exit                      *   \033[0m\n");   
    printf("\t\t\t\033[47;34m   ----------------------------------------------------   \033[0m\n");
    printf("\t\t\t\033[47;34m                                                          \033[0m\n"); 
    do {
        printf("\n\t\t\tLogin Option:");
        scanf("%s", input);
        option = OutputOption(input);
        printf("\n");
        if (option !=1 && option !=2 && option !=3 && option !=4 && option != 5 && option != 6){
            printf("\n\t\t\tInvalid option!\n\t\t\tPlease input again\n");
        }
    } while (option !=1 && option !=2 && option !=3 && option !=4 && option != 5 && option != 6);
    return option;
}

char* userLogin(User* head){
    int check_num;
    char *name, password[50];
    name = (char *)malloc(sizeof(char) * 50);
    do {
        printf("\t\t\tPlease input your user name:");
        scanf("%49s", name);
        check_num = strcmp("librarian", name);
        if(check_num == 0){
            printf("\n\t\t\tError: librarian please choose option 2!\n\n");
            return NULL;
        }
        User *node = head->next;
        while (node){
            check_num = strcmp(node->user_name, name);
            if(check_num == 0){
                break;
            }
            node = node->next;
        }
        if(check_num != 0){
            printf("\n\t\t\tInvalid user name!\n\n");
        }
    } while(check_num !=0);
    do {
        printf("\t\t\tPlease input your password:");
        scanf("%49s", password);
        User *node2 = head->next;
        while (node2){
            check_num = strcmp(node2->password, password);
            if(check_num == 0){
                break;
            }
            node2 = node2->next;
        }
        if(check_num != 0){
            printf("\n\t\t\tInvalid password!\n\n");
        }
    } while(check_num !=0);
    printf("\n\t\t\tLog in successfully!\n\n");
    return name;
}

int checkUser(User* head, char *name, char *user_name){
    User *node = head->next;
    int check_num1, check_num2;
    while(node){
        check_num1 = strcmp(name, node->name);
        check_num2 = strcmp(user_name, node->user_name);
        if(check_num1==0 || check_num2==0){
            return 1;
        }
        node = node->next;
    }
    return 0;
}

char* registerUser(User *head){
    User *node = (User*)malloc((sizeof(User)));
    User *last = head;

    char *name = (char *)malloc(sizeof(char) *100);
    char *user_name = (char *)malloc(sizeof(char) *100);
    char *password = (char *)malloc(sizeof(char) *100);
    do {
        printf("\t\t\tYour real name:");
        scanf("%49s", name);
        node->name = name;
        printf("\t\t\tYour username:");
        scanf("%49s", user_name);
        node->user_name = user_name;
        if(checkUser(head, node->name, node->user_name)){
            printf("\n\t\t\tUsername exists, please input again!\n\n");
        }
    } while (checkUser(head, node->name, node->user_name));
    printf("\t\t\tYour password:");
    scanf("%49s", password);
    node->password = password;
    while(last){
        if(last->next == NULL){
            node->next = last->next;
            last->next = node;
            node->next = NULL;
        }
        last = last->next;
    }
    store_users("user_data.txt", head);
    return node->user_name;
}

void librarianLogin(){
    char password[50];
    int check_num;
    printf("\t\t\tHello librarian!\n");
    do {
        printf("\t\t\tlibrarian's password:");
        scanf("%49s", password);
        check_num = strcmp(password,"librarian");
        if (check_num!=0){
            printf("\n\t\t\tInvalid password!\n\t\t\tPlease input again!\n\n");
        }
    } while (check_num != 0);
    printf("\n\t\t\tLog in successfully!\n\n");
}