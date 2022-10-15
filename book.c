#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "book_management.h"
#include "tourist.h"
#include <stdlib.h>
#include <string.h>


void print_book(Book *pointer){
	printf("\t\t%-8u%-32s%-16s%-16u%-8u\n",pointer->id,pointer->title,pointer->authors,pointer->year,pointer->copies);
}

void tourist_find_book_by_title(){
	Book *current=head->next;
	char *title;
	title=(char*)malloc(sizeof(char));
	title=ask_question("\t\t\tPlease enter title:"); 
	char *a="id";
	char *b="title";
	char *c="authors";
	char *d="year";
	char *e="copies";
	printf("\t\t%-8s%-32s%-16s%-16s%-8s\n",a,b,c,d,e);
	for(current;current != NULL; current = current->next){
		if(strcmp(current->title,title)==0){
			print_book(current);
		}
	}
}

void tourist_find_book_by_author(){
	Book *current=head->next;
	char *author;
	author=(char*)malloc(sizeof(char));
	author=ask_question("\t\t\tPlease enter author:");
	char *a="id";
	char *b="title";
	char *c="authors";
	char *d="year";
	char *e="copies";
	printf("\t\t%-8s%-32s%-16s%-16s%-8s\n",a,b,c,d,e);
	for(current;current != NULL; current = current->next){
		if(strcmp(current->authors,author)==0){
			print_book(current);
		}
	}
}

void tourist_find_book_by_year(){
	unsigned int year;
	Book *current=head->next;
	year=strtoul(ask_question("\t\t\tPlease enter year:"),NULL,10);
	if(year==0){
		printf("\t\t\tPlease enter a valid number.\n");
		tourist_find_book_by_year();
		return;
	}
	char *a="id";
	char *b="title";
	char *c="authors";
	char *d="year";
	char *e="copies";
	printf("\t\t%-8s%-32s%-16s%-16s%-8s\n",a,b,c,d,e);
	for(current;current != NULL; current = current->next){
		if(current->year==year){
			print_book(current);
		}
	}
}

Book *tourist_find_book_by_id(unsigned int id){
	for(Book *current=head->next;current != NULL; current = current->next){
		if(current->id==id){
			return current;
			break;
		}
	}
	printf("\t\tCan not find this book.");
	return NULL;
}

void Display_books(){
	Book *current=head->next;
	char *a="ID";
	char *b="Tittle";
	char *c="Authors";
	char *d="Year";
	char *e="Copies";
	printf("\t\t%-8s%-32s%-16s%-16s%-8s\n",a,b,c,d,e);
	for(current;current != NULL; current = current->next){
		print_book(current);
	}
}

void Search_books(){
	int choice =5;
	do {
		char * answer = ask_question("\n\t\t\tPlease enter next action:\n\t\t\t1)Find books by title\n\t\t\t2)Find Books by author\n\t\t\t3)Find books by year\n\t\t\t4)Display books\n\t\t\t5)Return to previous menu\n\t\t\tchoice: ");
		choice = atoi(answer);
		free(answer);
		switch (choice) {
			case 1:
				tourist_find_book_by_title();
				break;
			case 2:
				tourist_find_book_by_author();
				break;
			case 3:
				tourist_find_book_by_year();
				break;
			case 4:
				Display_books();
				break;
			case 5:
				printf("\t\t\tReturn to previous menu successfully.\n");
				break;
			default:
				printf("\t\t\tSorry, that doesn't seem to be an option\n");
		}
	} while (choice != 5);
	return;

}



