#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_management.h"
#include "tourist.h"
#define BUF_LEN  128
int store_tourist_books(){
	Book *book=head->next;
	FILE *file;
	file=fopen("book_data.txt","w+");
	if(!file){
		printf("fail to open file");
		return -1;
	}
	
	while(1){
		
		fprintf(file,"%u\n",book->id);
		fprintf(file,"%s\n",book->title);
		fprintf(file,"%s\n",book->authors);
		fprintf(file,"%u\n",book->year);
		fprintf(file,"%u",book->copies);
		book=book->next;
		if(book==NULL){
			break;
		}
		fprintf(file,"\n");
	}
	
	fclose(file);
	return 1;
}

int store_tourist_tourist_users(){
	tourist_user *tourist_user=librarian->next;
	FILE *file;
	file=fopen("user.txt","w+");
	if(!file){
		printf("fail to open file");
		return -1;
	}
	while(1){
		fprintf(file,"%s\n",tourist_user->true_name);
		fprintf(file,"%s\n",tourist_user->tourist_user_name);
		fprintf(file,"%s\n",tourist_user->code);
		fprintf(file,"%d",tourist_user->is_librarian);
		tourist_user=tourist_user->next;
		if(tourist_user==NULL){
			break;
		}
		fprintf(file,"\n");
	}
	
	fclose(file);
	return 1;
}

int store_tourist_borrow(){
	Borrowed *borrowed=Borrowedhead->next;
	FILE *file;
	file=fopen("borrowed.txt","w+");
	if(!file){
		printf("fail to open file");
		return -1;
	}
	while(1){		
		fprintf(file,"%s\n",borrowed->tourist_user_name);
		fprintf(file,"%u\n",borrowed->id);
		fprintf(file,"%s\n",borrowed->title);
        fprintf(file,"%s\n",borrowed->authors);
        fprintf(file,"%u",borrowed->year);
		borrowed=borrowed->next;
		if(borrowed==NULL){
			break;
		}
		fprintf(file,"\n");
	}
	
	fclose(file);
	return 1;
}

Book *load_tourist_books(const char *filename){
	Book *bhead;
	Book *next_book;
	Book *current_book;
	
	next_book=(Book*)malloc(sizeof(Book));
	bhead=next_book;
	current_book=next_book;
	bhead->next=NULL;
	FILE *file=fopen(filename,"r");
	if(file==NULL){
		printf("fail to open file!");
		return NULL;
	}
	char str[50];
	while(!feof(file)){
		next_book=(Book*)malloc(sizeof(Book));
		fscanf(file,"%u",&next_book->id);
		fgetc(file);
		fscanf(file,"%[^\n]s",str);
		next_book->title=(char*)malloc(sizeof(str));
		strcpy(next_book->title,str);
		memset(str,'\0',strlen(str));
		fgetc(file);
		fscanf(file,"%[^\n]s",str);
		next_book->authors=(char*)malloc(sizeof(str));
		strcpy(next_book->authors,str);
		memset(str,'\0',strlen(str));
		fgetc(file);
		fscanf(file,"%u",&next_book->year);
		fgetc(file);
		fscanf(file,"%u",&next_book->copies);
		fgetc(file);
		current_book->next=next_book;
		current_book=next_book;
	}
	
	current_book->next=NULL;
	fclose(file);
	return bhead;
}

tourist_user *load_tourist_tourist_users(const char *filename){
	tourist_user *tourist_uhead;
	tourist_user *next_tourist_user;
	tourist_user *current_tourist_user;
	next_tourist_user=(tourist_user*)malloc(sizeof(tourist_user));
	tourist_uhead=next_tourist_user;
	current_tourist_user=next_tourist_user;
	tourist_uhead->next=NULL;
	FILE *file=fopen(filename,"r");
	if(file==NULL){
		printf("fail to open file!");
		return NULL;
	}
	char str[50];
	while(!feof(file)){
		next_tourist_user=(tourist_user*)malloc(sizeof(tourist_user));
		fscanf(file,"%[^\n]s",str);
		next_tourist_user->true_name=(char*)malloc(sizeof(str));
		strcpy(next_tourist_user->true_name,str);
		memset(str,'\0',strlen(str));
		fgetc(file);
		fscanf(file,"%[^\n]s",str);
		next_tourist_user->tourist_user_name=(char*)malloc(sizeof(str));
		strcpy(next_tourist_user->tourist_user_name,str);
		memset(str,'\0',strlen(str));
		fgetc(file);
		fscanf(file,"%[^\n]s",str);
		next_tourist_user->code=(char*)malloc(sizeof(str));
		strcpy(next_tourist_user->code,str);
		memset(str,'\0',strlen(str));
		fgetc(file);
		fscanf(file,"%d",&next_tourist_user->is_librarian);
		fgetc(file);
		current_tourist_user->next=next_tourist_user;
		current_tourist_user=current_tourist_user->next;
		
	}
	
	current_tourist_user->next=NULL;
	fclose(file);
	return tourist_uhead;
}

Borrowed *load_tourist_Borrowed(const char *filename){
	Borrowed *Borrowedhead;
	Borrowed *next_Borrowed;
	Borrowed *current_Borrowed;

	next_Borrowed=(Borrowed*)malloc(sizeof(Borrowed));
	Borrowedhead=next_Borrowed;
	current_Borrowed=next_Borrowed;
	Borrowedhead->next=NULL;
	FILE *file=fopen(filename,"r");
	if(file==NULL){
		printf("fail to open file!");
		return NULL;
	}
	char str[50];
	while(!feof(file)){
		next_Borrowed=(Borrowed*)malloc(sizeof(Borrowed));
		fscanf(file,"%[^\n]s",str);
		next_Borrowed->tourist_user_name=(char*)malloc(sizeof(str));
		strcpy(next_Borrowed->tourist_user_name,str);
		memset(str,'\0',strlen(str));
		fgetc(file);
		fscanf(file,"%u",&next_Borrowed->id);
		fgetc(file);
		fscanf(file,"%[^\n]s",str);
		next_Borrowed->title=(char*)malloc(sizeof(str));
		strcpy(next_Borrowed->title,str);
		memset(str,'\0',strlen(str));
		fgetc(file);
		fscanf(file,"%[^\n]s",str);
		next_Borrowed->authors=(char*)malloc(sizeof(str));
		strcpy(next_Borrowed->authors,str);
		memset(str,'\0',strlen(str));
		fgetc(file);
		fscanf(file,"%u",&next_Borrowed->year);
		fgetc(file);		
		current_Borrowed->next=next_Borrowed;
		current_Borrowed=next_Borrowed;
	}
	
	current_Borrowed->next=NULL;
	fclose(file);
	return Borrowedhead;
}
