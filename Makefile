CC=gcc
CFLAGS=  -Wall -Wextra -c -ggdb -pedantic -std=c99 -O0
LFLAGS=  -Wall -Wextra -pedantic  -std=c99 -ggdb

sll.o: 
	$(CC) $(CFLAGS) sll.c sll.h 
queue.o:  sll.o
	$(CC) $(CFLAGS) queue.c queue.h 
bst.o:  queue.o
	$(CC) $(CFLAGS)  bst.c bst.h
bsttest.o:
	$(CC) $(CFLAGS) bsttest.c
bsttest: bst.o bsttest.o  
	$(CC) $(LFLAGS) sll.o  queue.o bst.o bsttest.o -o bsttest
test: bsttest
	./bsttest
clean:
	rm -rf *.o
	rm -rf *.gch
