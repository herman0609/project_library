#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_management.h"
#include "library.h"
#include "tourist.h"

// Code module for main()
// It's a collection of all the functions

int main(void){
    User * uhead = (User*)malloc((sizeof(User)));
    uhead->next = NULL;
    Book * bhead = (Book *)malloc((sizeof(Book)));
    bhead->next = NULL;
    if(load(uhead, bhead)){
        return 0;
    }
    if(store(uhead, bhead)){
        return 0;
    }
    return 0;
}
