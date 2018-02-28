 
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

void displayInt(void *, FILE * fp);
void freeInt(void * in);


int main (void)
{
    int num[] = {1, 2, 3 ,4 ,5};
    QUEUE * queue = newQUEUE(displayInt, freeInt);
    for(int i =0;i < 5; i++)
    {
      enqueue(queue, &num[i]);   
    }
    displayQUEUE(queue, stdout);
    printf("\n");
    displayInt(dequeue(queue), stdout);
    freeQUEUE(queue);
}

void displayInt(void * in, FILE * fp)
{
    int * tmp = (int*)in;
    int out = *tmp;
    fprintf(fp,"%d",out);
}

void freeInt(void * in)
{
    free(in);
}
