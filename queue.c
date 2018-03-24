 //Jeremy McCormick
 //queue.c
 //CS 201 Assignment 0
 

#include <assert.h>
#include <stdlib.h>
#include "queue.h"

NODE * newNODE(void *);

struct queue {
    NODE * head;
    NODE * last;
    int size;
    void (*display)(void *, FILE *);
    void (*free)(void *);
};

struct node {
    void * value;
    NODE * next;
};

QUEUE *newQUEUE(void (*d)(void *,FILE *),void (*f)(void *))
{
    QUEUE * items = malloc(sizeof(QUEUE));
    items->head = NULL;
    items->last = NULL;
    items->display = d;
    items->free = f;
    items->size = 0;
    return items;
}

NODE * newNODE(void * value)
{
    NODE * node = malloc(sizeof(NODE));
    node->value = value;
    node->next = NULL;
    return node;
}
void enqueue(QUEUE *items,void *value)
{
    NODE * newNode = newNODE(value);
    items->size++;
    if(items->head == NULL)
    {
        items->head = newNode;
        items->last = newNode;
    }
    else
    {
        (items->last)->next = newNode;
        items->last = newNode;
    }
}

void *dequeue(QUEUE *items)
{
    items->size--;
       NODE * out = items->head;
       void * outval = out->value;
       items->head = (items->head)->next;
       free(out);
       out = NULL;
       return outval;
}

void *peekQUEUE(QUEUE *items)
{
        return (items->head)->value;
}
int sizeQUEUE(QUEUE *items)
{
    return items->size;
}

void displayQUEUE(QUEUE *items,FILE * fp)
{
    NODE * step = items->head;
    printf("<");
        for(int i = 0; i < items->size; i++)
        {
            items->display(step->value, fp);
             if(i != items->size-1)
                printf(",");
             step = step->next;
        }
        printf(">");
}
void displayQUEUEdebug(QUEUE *items,FILE * fp)
{
     
    if(items->size == 0)
    {
        printf("head->{},tail->{}");
        return;
    }
    if(items->size == 1)
    {
            printf("head->{");
            items->display((items->head)->value, fp);
            printf("},tail->{");
            items->display((items->head)->value, fp);
            printf("}");
            return;
    }
    printf("head->{");
    NODE * step = items->head;
    for(int i = 0; i < items->size ; i++)
    {
        //if(i == (items->size) - 1)
        //    printf("},tail->{");
        items->display(step->value, fp);
        if(i < items->size-1)
            printf(",");
        step = step->next;
    }
    printf("},tail->{");
    items->display((items->last)->value, fp);
    printf("}");
}

void freeQUEUE(QUEUE *items)
{
    NODE * step = items->head;
    while(step != NULL)
    {   
        NODE * next = step;
        step = step->next;
        if(items->free != NULL)
            items->free(next->value);
        free(next);
        
    }
    free(items);
    items=NULL;
}
