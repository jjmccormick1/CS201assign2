CC=gcc
CFLAGS=  -Wall -Wextra -c -ggdb  -std=c99 -Og 
LFLAGS=  -Wall -Wextra  -std=c99 -ggdb  -Og

all: trees.o

integer.o: 
	$(CC) $(CFLAGS) integer.c integer.h

sll.o: 
	$(CC) $(CFLAGS) sll.c sll.h
slltest.o: sll.o
	$(CC) $(CFLAGS) sll-0-40.c
slltest: slltest.o integer.o
	$(CC) $(LFLAGS) integer.o sll.o sll-0-40.o -o slltest

queue.o:
	$(CC) $(CFLAGS) queue.c queue.h 
queuetest.o: queue.o
	$(CC) $(CFLAGS) queuetest.c
	$(CC) $(CFLAGS) queue-0-40.c
queuetest: queuetest.o bst.o integer.o
	$(CC) $(LFLAGS) bst.o  queue.o queuetest.o  -o queuetest
	$(CC) $(LFLAGS) integer.o bst.o queue.o queue-0-40.o -o queuetestnew

bst.o:  queue.o
	$(CC) $(CFLAGS)  bst.c bst.h
bsttest.o: bst.o
	$(CC) $(CFLAGS) bsttest.c
	$(CC) $(CFLAGS) bst-0-0.c
bsttest:  bsttest.o integer.o
	$(CC) $(LFLAGS)  queue.o bst.o bsttest.o -o bsttest
	$(CC) $(LFLAGS) integer.o  queue.o bst.o bst-0-0.o -o bsttestnew	

gst.o: bst.o
	$(CC) $(CFLAGS) gst.c gst.h
gsttest.o: gst.o
	$(CC) $(CFLAGS) gsttest.c
	$(CC) $(CFLAGS) gst-0-0.c
gsttest: gsttest.o integer.o
	$(CC) $(LFLAGS)  queue.o bst.o gst.o gsttest.o -o gsttest
	$(CC) $(LFLAGS) integer.o queue.o bst.o gst.o gst-0-0.o -o gsttestnew
	
avl.o: bst.o
	$(CC) $(CFLAGS) avl.c avl.h

trees.o: gst.o  avl.o
	$(CC) $(CFLAGS) trees.c
treees:
	$(CC) $(LFLAGS) queue.o bst.o gst.o avl.o trees.o -o trees



test: slltest gsttest  bsttest queuetest
	@echo "TESTING SLL WITH LUSTHS TESTER\n"
	@./slltest
	@echo "TESTING QUEUE WITH LUSTHS TESTER"
	@./queuetestnew
	@echo "\nTESTING QUEUE WITH MY TESTER"
	@./queuetest
	@echo "\nTESTING BST WITH MY TESTER"	
	@./bsttest
	@echo "\nTESTING BST WITH LUSTHS TESTER"
	@./bsttestnew
	@echo "\nTESTING GST WITH MY TESTER\n"
	@./gsttest
	@echo "\nTESTING GST WITH LUSTHS TESTER\n"
	@./gsttestnew

valgrind: slltest queuetest bsttest gsttest
	@valgrind slltest
	@valgrind queuetestnew
	@valgrind bsttestnew
	@valgrind gsttestnew

clean:
	@rm -rf *.o
	@rm -rf *.gch
	@rm -rf slltest
	@rm -rf bsttest
	@rm -rf queuetest
	@rm -rf gsttest
	@rm -rf queuetestnew
	@rm -rf bsttestnew
	@rm -rf gsttestnew
