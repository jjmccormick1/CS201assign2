//Jeremy McCormick

#include <stdlib.h>
#include <stdio.h>
#include "gst.h"

void displayInt(void *, FILE * fp);
int compareInt(void *, void *);
void freeInt(void * in);
void swapInt(BSTNODE * a, BSTNODE * b);

int main (void)
{
    int num[] = {1, 2, 3 ,4 ,5};
    BST * gst = newGST(displayInt, compareInt, freeInt);
    for(int i =0;i < 5; i++)
    {
      insertGST(gst, &num[i]);   
    }
    statisticsGST(gst,stdout);
    printf("\n");
    displayGST(gst, stdout);
    fflush(stdout);
    displayGSTdebug(gst,stdout);

    deleteGST(gst, &num[0]);
    deleteGST(gst, &num[3]);
    
    displayGSTdebug(gst,stdout);
    freeBST(bst);
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
 
