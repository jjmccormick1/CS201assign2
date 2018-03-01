//Jeremy McCormick
//Feb 28 2018
//gst.c
//green search tree module based on bst. handles duplicates better
#include<stdio.h>
#include "bst.h"

GSTVALUE * newGSTVALUE(void * val);
void swapperGST(BSTNODE *, BSTNODE *);
int compareGST(void *, void *);

struct gst{
    BST * bst;
    void (*display)(void *, FILE *);
    int (*compare)(void *, void *);
    void (*free)(void *);
};

typedef struct gstvalue {
    void * value;
    int frequency;
    void (*display)(void *, FILE *);
    int (*compare)(void *, void *);
}GSTVALUE;

GST *newGST(void (*display)(void *,FILE *), int (*compare)(void *,void *), void (*free)(void *))
{
    GST * gst = malloc(sizeof(GST));
    gst->bst = newBST(display,compare, swapperGST , free);
    gst->display = display;
    gst->compare = comapre;
    gst->free = free;
}

GSTVALUE * newGSTVALUE(GST * gst,void * val)
{
    GSTVALUE * gstvalue = malloc(sizeof(GSTVALUE));
    gstvalue->value = value;
    gstvalue->frequency  = 1;
    gstvalue->display = gst->display;
    gstvalue->compare = gst->compare;
}

void swapperGST(BSTNODE * a, BSTNODE * b)
{
    GSTVALUE * gsta = (GSTVALUE*)getBSTNODEvalue(a);
    GSTVALUE * gstb = (GSTVALUE*)getBSTNODEvalue(b);
    void * tmp = gsta->value;
    gsta->value = gstb->value;
    gstb->value = tmp;
}

int compareGST(void * a, void * b)
{
    GSTVALUE * gsta = (GSTVALUE*)a;
    GSTVALUE * gstb = (GSTVALUE*)b;
    
    return gsta->compare(gsta->value, gstb->value);
}
void insertGST(GST * gst,void * value)
{
    BSTNODE * found = findBST(gst->bst, value); //See if its in the tree
    
    if(found == NULL) //if not in tree, add it
    {
        GSTVALUE * gstvalue = malloc(sizeof(GSTVALUE));
        gstvalue->value = value;
        gstvalue->frequency  = 1;
        insertBST(gst->bst, gstvalue);
        return;
    }
    GSTVALUE * gstval = getBSTNODEvalue(found); //if is in tree, increment frequency
    gstval->frequency += 1; 
}
int findGSTcount(GST * gst,void * value)
{
     BSTNODE * found = findBST(gst->bst, value); //See if its in the tree
     
     if(found == NULL)
         return 0;
     
     GSTVALUE * gstval = getBSTNODEvalue(found);
     return gstval->frequency;
}

void *findGST(GST * gst,void * value)
{
    BSTNODE * found = findBST(gst->bst, value);
    if(found == NULL)
        return NULL;
    return value;
}
void *deleteGST(GST * gst,void * value)
{
    return deleteBST(gst->bst, value);
}
    extern int sizeGST(GST *);
    extern int duplicates(GST *);
    extern void statisticsGST(GST *,FILE *);
    extern void displayGST(GST *,FILE *);
    extern void displayGSTdebug(GST *,FILE *);
    extern void freeGST(GST *);

    #endif
