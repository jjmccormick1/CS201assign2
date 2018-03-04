//Jeremy McCormick

#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

void displayInt(void *, FILE * fp);
int compareInt(void *, void *);
void freeInt(void * in);
void swapInt(BSTNODE * a, BSTNODE * b);

int main (void)
{
    int num[] = {1, 2, 3 ,4 ,5};
    BST * bst = newBST(displayInt, compareInt,  swapInt, freeInt);
    for(int i =0;i < 5; i++)
    {
      insertBST(bst, &num[i]);   
    }
    
    printf("Printing stats:\n");
    statisticsBST(bst,stdout);
    printf("\n");
    printf("Printing displayBST()\n");
    displayBST(bst, stdout);
    printf("\n");
    fflush(stdout);
    printf("Printing displayBSTdebug()\n");
    displayBSTdebug(bst,stdout);
    printf("\n");
    deleteBST(bst, &num[1]);
    deleteBST(bst, &num[3]);
    printf("Printing displayBSTdebug() after deletes\n");
    displayBSTdebug(bst,stdout);
    printf("\n");
    //freeBST(bst);
}

void displayInt(void * in, FILE * fp)
{
    int * tmp = (int*)in;
    int out = *tmp;
    fprintf(fp,"%d",out);
}

int compareInt(void * ina, void * inb)
{
    int * tmpa = (int*)ina;
    int * tmpb = (int*)inb;
    int outa = *tmpa;
    int outb = *tmpb;
    
    return outa - outb;
}

void freeInt(void * in)
{
    free(in);
}

void swapInt(BSTNODE * a, BSTNODE * b)
{
        void * tmp = getBSTNODEvalue(a);
        setBSTNODEvalue(a, getBSTNODEvalue(b));
        setBSTNODEvalue(b, tmp);
}
