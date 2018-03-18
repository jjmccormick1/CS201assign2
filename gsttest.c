//Jeremy McCormick

#include <stdlib.h>
#include <stdio.h>
#include "gst.h"
#include "bst.h"
#include "integer.h"

void displayInt(void *, FILE * fp);
int compareInt(void *, void *);
void freeInt(void * in);
void swapInt(BSTNODE * a, BSTNODE * b);
static int num[5] = {2,3,1,5,4};

int main (void)
{
    GST * gst = newGST(displayInt, compareInt, freeInt);
    for(int i =0;i < 5; i++)
    {
        //num[i] = i;
      insertGST(gst, &num[i]);   
    }
    printf("Printing GST stats \n");
    statisticsGST(gst,stdout);
    printf("\n");
    printf("Printing displayGST()\n");
    displayGST(gst, stdout);
    printf("\n");
    fflush(stdout);
    printf("Printing displayGSTdebug()\n");
    displayGSTdebug(gst,stdout);

    deleteGST(gst, &num[0]);
    deleteGST(gst, &num[3]);
    printf("\n");
    printf("Printing displayGSTdebug() after deletes\n");
    displayGSTdebug(gst,stdout);
    printf("\n");
    displayGST(gst, stdout);
    fflush(stdout);
    freeGST(gst);
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
    (void)in;
    //free(in);
}

void swapInt(BSTNODE * a, BSTNODE * b)
{
        void * tmp = getBSTNODEvalue(a);
        setBSTNODEvalue(a, getBSTNODEvalue(b));
        setBSTNODEvalue(b, tmp);
}
 
