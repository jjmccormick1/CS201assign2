CC=gcc
CFLAGS=  -Wall -Wextra -c -ggdb  -std=c99 -O0
LFLAGS=  -Wall -Wextra  -std=c99 -ggdb

all: trees.o

integer.o: 
	$(CC) $(CFLAGS) integer.c integer.h

queue.o:
	$(CC) $(CFLAGS) queue.c queue.h 
queuetest.o: queue.o
	$(CC) $(CFLAGS) queuetest.c
	$(CC) $(CFLAGS) queue-0-200.c
queuetest: queuetest.o bst.o integer.o
	$(CC) $(LFLAGS) bst.o  queue.o queuetest.o  -o queuetest
	$(CC) $(LFLAGS) integer.o bst.o queue.o queue-0-200.o -o queuetestnew

bst.o:  queue.o
	$(CC) $(CFLAGS)  bst.c bst.h
bsttest.o: bst.o
	$(CC) $(CFLAGS) bsttest.c
	$(CC) $(CFLAGS) bst-0-200.c
bsttest:  bsttest.o integer.o
	$(CC) $(LFLAGS)  queue.o bst.o bsttest.o -o bsttest
	$(CC) $(LFLAGS) integer.o  queue.o bst.o bst-0-200.o -o bsttestnew	

gst.o: bst.o
	$(CC) $(CFLAGS) gst.c gst.h
gsttest.o: gst.o
	$(CC) $(CFLAGS) gsttest.c
gsttest: gsttest.o
	$(CC) $(LFLAGS)  queue.o bst.o gst.o gsttest.o -o gsttest

avl.o: bst.o
	$(CC) $(CFLAGS) avl.c avl.h

trees.o: gst.o  
	$(CC) $(CFLAGS) trees.c
	$(CC) $(LFLAGS) queue.o bst.o gst.o avl.o trees.o -o trees



test:  gsttest  bsttest queuetest
	@echo "TESTING QUEUE WITH LUSTHS TESTER"
	@./queuetestnew
	@echo "\nTESTING QUEUE WITH MY TESTER"
	@./queuetest
	@echo "\nTESTING BST WITH LUSTHS TESTER"	
	@./bsttestnew
	@echo "\nTESTING BST WITH MY TESTER"
	@./bsttest
	@echo "\n"
	@./gsttest

valgrind:
	@valgrind queuetestnew
	@valgrind bsttestnew

clean:
	@rm -rf *.o
	@rm -rf *.gch
	@rm -rf bsttest
	@rm -rf queuetest
	@rm -rf gsttest
