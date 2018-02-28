CC=gcc
CFLAGS=  -Wall -Wextra -c -ggdb -pedantic -std=c99 -O0
LFLAGS=  -Wall -Wextra -pedantic  -std=c99 -ggdb

all: test  clean

sll.o: 
	$(CC) $(CFLAGS) sll.c sll.h 


queue.o:  sll.o
	$(CC) $(CFLAGS) queue.c queue.h 
queuetest.o: queue.o
	$(CC) $(CFLAGS) queuetest.c
queuetest: queuetest.o
	$(CC) $(LFLAGS) sll.o queue.o queuetest.o -o queuetest


bst.o:  queue.o
	$(CC) $(CFLAGS)  bst.c bst.h
bsttest.o: bst.o
	$(CC) $(CFLAGS) bsttest.c
bsttest:  bsttest.o  
	$(CC) $(LFLAGS) sll.o  queue.o bst.o bsttest.o -o bsttest


test: bsttest queuetest
	@./queuetest	
	@./bsttest
clean:
	@rm -rf *.o
	@rm -rf *.gch
	@rm -rf bsttest
	@rm -rf queuetest
