 
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "bst.h"
void displayInt(void *, FILE * fp);
void freeInt(void * in);


int main (void)
{
    int num[] = {1, 2, 3 ,4 ,5};
    BSTNODE * root = newBSTNODE(&num[0]);
    BSTNODE * node1 = newBSTNODE(&num[2]);
    BSTNODE * node2 = newBSTNODE(&num[4]);
    QUEUE * queue = newQUEUE(displayInt, freeInt);
    
    setBSTNODEparent(node1, root);
    setBSTNODEparent(node2, root);
    setBSTNODEleft(root,node1);
    setBSTNODEright(root, node2);
    
    enqueue(queue, root);
    printf("Printing BSTNODE value from queue\n");
    displayQUEUE(queue, stdout);
    printf("\n");
    void * out = dequeue(queue);
    printf("printing removed value\n");
    displayInt(out, stdout);
    printf("\n");
    freeQUEUE(queue);
}

void displayInt(void * in, FILE * fp)
{   
    BSTNODE * node = in;
    int * tmp = getBSTNODEvalue(node);
    int out = *tmp;
    fprintf(fp,"%d",out);
}

void freeInt(void * in)
{
    free(in);
}
