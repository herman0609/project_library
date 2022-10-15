#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "book_management.h"
#include "tourist.h"
#include <stdlib.h>
#include <string.h>



char *ask_question(const char *question) {
	printf("%s",question);

	const int size_step = 2;
	char *answer = malloc(size_step);
	answer[0] = 0; 
	char *next_chunk = answer;
	int iteration = 0;
	do {
		answer = realloc(answer, size_step + iteration*size_step);
		next_chunk = answer + strlen(answer); 
		fgets(next_chunk, size_step, stdin);

		next_chunk = answer + strlen(answer); 
		++iteration;
	} while (* (next_chunk-1) != '\n');

	*(next_chunk-1) = 0; 

	return answer;
}

void initial_tourist_user_system(){
	librarian=(tourist_user*)malloc(sizeof(tourist_user));
    librarian->tourist_user_name="librarian";
    librarian->code="librarian";
    librarian->is_librarian=1;
    librarian->next=NULL;   
}





int borrow_book(tourist_user *tourist_user){
	unsigned int book_id;
	book_id=strtoul(ask_question("\t\t\tInput the id of the book you want to borrow:"),NULL,10);
    

	Borrowed *copy_book=(Borrowed*)malloc(sizeof(Borrowed));
	Book *book=tourist_find_book_by_id(book_id);
	if(book->copies==0){
		printf("\t\t\tThe book has been borrowed in full.\n");
		return 0;
	}
	copy_book->tourist_user_name=(char *)malloc(sizeof(char)*120);
	copy_book->authors = (char *)malloc(sizeof(char)*120);
	copy_book->title=(char *)malloc(sizeof(char)*120);
    strcpy(copy_book->tourist_user_name,tourist_user->tourist_user_name);
	strcpy(copy_book->authors,book->authors);
	copy_book->id=book->id;
	strcpy(copy_book->title,book->title);
	copy_book->year=book->year;
	book->copies--;

    Borrowed *current=Borrowedhead->next;
    
    for(current;current->next != NULL; current = current->next);
    current->next=copy_book;
    copy_book->next=NULL;
	printf("\t\t\tBorrow successfully!\n\n\t\t\tYou have to pay a deposit of 10 pounds\n");
	FILE *file = fopen("deposit.txt", "r");
	int deposit;
	fscanf(file, "%d", &deposit);
	fclose(file);
	FILE *file0 = fopen("deposit.txt", "w");
	deposit += 10;
    fprintf(file0, "%d", deposit);
	store_tourist_books();
	store_tourist_borrow();
    return 0;
}

Borrowed *find_borrowed_book_by_id(unsigned int book_id,tourist_user *tourist_user){
    Borrowed *current=Borrowedhead->next;
    for(current;current != NULL; current = current->next){
        if(strcmp(current->tourist_user_name,tourist_user->tourist_user_name)==0){
            if(current->id==book_id){
                return current;
                break;
            }
        }
    }
    return NULL;
}

int return_book(tourist_user *tourist_user){
    Borrowed *current=Borrowedhead->next;
	char *a="ID";
	char *b="Title";
	char *c="Authors";
	char *d="Year";
	printf("\t\t%-8s%-32s%-32s%-16s\n",a,b,c,d);
    for(current;current != NULL; current = current->next){
        if(strcmp(current->tourist_user_name,tourist_user->tourist_user_name)==0){
            printf("\t\t%-8u%-32s%-32s%-16u\n",current->id,current->title,current->authors,current->year);
        }
    }
	unsigned int book_id;
	book_id=strtoul(ask_question("\t\t\tInput the id of the book you want to return:"),NULL,10);
    Borrowed *fore=Borrowedhead->next;
    Borrowed *returned=find_borrowed_book_by_id(book_id,tourist_user);
	Book *book=tourist_find_book_by_id(book_id);
    book->copies++;	
	if(fore==returned){
		Borrowedhead->next=returned->next;
		free(returned);
		printf("\t\t\tReturn successfully!\n\n\t\t\tHere are a deposit of 10 pounds\n");
		FILE *file = fopen("deposit.txt", "r");
		int deposit;
		fscanf(file, "%d", &deposit);
		fclose(file);
		FILE *file0 = fopen("deposit.txt", "w");
		deposit -= 10;
		fprintf(file0, "%d", deposit);
		return 1;
	}
	else{
		for (fore; fore->next != returned; fore = fore->next);
		if (returned != NULL) {
			fore->next = returned->next;
			free(returned);
			printf("\t\t\tReturn successfully!\n\n\t\t\tHere are a deposit of 10 pounds\n");
			FILE *file = fopen("deposit.txt", "r");
			int deposit;
			fscanf(file, "%d", &deposit);
			fclose(file);
			FILE *file0 = fopen("deposit.txt", "w");
			deposit -= 10;
			fprintf(file0, "%d", deposit);
			return 1;
		}
		else {
			puts("\t\t\tbook does not exist");
			return 0;
		}
	}
	store_tourist_books();
	store_tourist_borrow();
    
}
void Display_tourist_user_books(tourist_user *tourist_user){
	Borrowed *current=Borrowedhead->next;
	char *a="Id";
	char *b="Title";
	char *c="Authors";
	char *d="Year";
	printf("\t\t\t%-8s%-32s%-32s%-16s\n",a,b,c,d);
    for(current;current != NULL; current = current->next){
        if(strcmp(current->tourist_user_name,tourist_user->tourist_user_name)==0){
            printf("\t\t\t%-8u%-32s%-32s%-16u\n",current->id,current->title,current->authors,current->year);
        }
    }
}
