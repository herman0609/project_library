
# code details

EXE = ./bin/lib
SRC= main.c file.c book.c user.c library.c librarian.c user1.c tool.c

# generic build details

CC=      gcc
CFLAGS= -std=c99 -Wall
CLINK= 

# compile to object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# build executable: type 'make'

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CLINK) -o $(EXE) 

# clean up and remove object code and executable: type 'make clean'

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:      main.c book_management.h library.h tourist.h
file.o:   file.c book_management.h tourist.h
book.o: book.c book_management.h tourist.h
user.o:      user.c book_management.h tourist.h
library.o:   library.c library.h book_management.h librarian.h user.h tourist.h
librarian.o: librarian.c librarian.h book_management.h library.h tourist.h
user1.o:      user1.c user.h book_management.h library.h tourist.h
tool.o:   tool.c book_management.h tourist.h
