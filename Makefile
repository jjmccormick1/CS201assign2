CC=gcc
CFLAGS=  -Wall -Wextra -c -ggdb -pedantic -std=c99 -O0
LFLAGS=  -Wall -Wextra -pedantic  -std=c99 -ggdb
 
bst.o: 
	$(CC) $(CFLAGS)  bst.c bst.h
bst: bst.o
	$(CC) $(LFLAGS)  bst.o bsttest.c -o bsttest
clean:
	rm -rf *.o
	rm -rf *.gch
