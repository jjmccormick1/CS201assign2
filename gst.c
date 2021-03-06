//Jeremy McCormick
//Feb 28 2018
//gst.c
//green search tree module based on bst. handles duplicates better
#include<stdio.h>
#include<stdlib.h>
#include "bst.h"
#include "gst.h"

GSTVALUE * newGSTVALUE(GST *,void * val);
void swapperGST(BSTNODE *, BSTNODE *);
int compareGST(void *, void *);
void printGST(void *, FILE *);
void freeGSTVALUE(void * in);

int numInsert = 0;

struct gst{
    BST * bst;
    void (*display)(void *, FILE *);
    int (*compare)(void *, void *);
    void (*free)(void *);
};

struct gstvalue {
    void * value;
    int frequency;
    void (*display)(void *, FILE *);
    int (*compare)(void *, void *);
    void (*free)(void *);
};

GST *newGST(void (*display)(void *,FILE *), int (*compare)(void *,void *), void (*free)(void *))
{
    GST * gst = malloc(sizeof(GST));
    gst->bst = newBST(printGST,compareGST, swapperGST , freeGSTVALUE);
    gst->display = display;
    gst->compare = compare;
    gst->free = free;
    return gst;
}

GSTVALUE * newGSTVALUE(GST * gst,void * val)
{
    GSTVALUE * gstvalue = calloc(1,sizeof(GSTVALUE));
    gstvalue->value = val;
    gstvalue->frequency  = 1;
    gstvalue->display = gst->display;
    gstvalue->compare = gst->compare;
    gstvalue->free    = gst->free;
    return gstvalue;
}

void swapperGST(BSTNODE * a, BSTNODE * b)
{
    GSTVALUE * gsta = (GSTVALUE*)getBSTNODEvalue(a);
    GSTVALUE * gstb = (GSTVALUE*)getBSTNODEvalue(b);
    void * tmp = gsta->value;
    gsta->value = gstb->value;
    gstb->value = tmp;
    
    int tempint = gsta->frequency;
    gsta->frequency = gstb->frequency;
    gstb->frequency = tempint;
}

int compareGST(void * a, void * b)
{
    GSTVALUE * gsta = (GSTVALUE*)a;
    GSTVALUE * gstb = (GSTVALUE*)b;

    return gstb->compare(gsta->value, gstb->value);
}

void freeGSTVALUE(void * in)
{
        GSTVALUE * gstval = in;
        //gstval->free(gstval->value);
        free(gstval);
        gstval=NULL;
}
void printGST(void * node, FILE * fp)
{
        GSTVALUE * gstnode = node;
        gstnode->display(gstnode->value,fp);
}
void insertGST(GST * gst,void * value)
{
    GSTVALUE * gstval = newGSTVALUE(gst, value); //make a new gstval for comparison
    BSTNODE * found = findBST(gst->bst, gstval); //pass it as the value instead of raw val
    numInsert++;
    if(found == NULL) //if not in tree, add it
    {
        insertBST(gst->bst, gstval);
        return;
    }
    GSTVALUE * gstfound = getBSTNODEvalue(found); //if is in tree, increment frequency
    gstfound->frequency += 1; 
    freeGSTVALUE(gstval);
}
int findGSTcount(GST * gst,void * value)
{
     GSTVALUE * gstval = newGSTVALUE(gst, value); //make a new gstval for comparison
    BSTNODE * found = findBST(gst->bst, gstval); //pass it as the value instead of raw val, see if its in the tree
     
     if(found == NULL)
         return 0;
     
     gstval = getBSTNODEvalue(found);
     int freq = gstval->frequency;
     freeGSTVALUE(gstval);
     return freq;
}

void *findGST(GST * gst,void * value)
{
    GSTVALUE * gstval = newGSTVALUE(gst, value); //make a new gstval for comparison
    BSTNODE * found = findBST(gst->bst, gstval); //pass it as the value instead of raw val
    freeGSTVALUE(gstval);
    if(found == NULL)
        return NULL;
    return value;
}
void *deleteGST(GST * gst,void * value)
{
    GSTVALUE * gstval = newGSTVALUE(gst, value); //Make value for comparison

    BSTNODE * found = findBST(gst->bst, gstval);//Look for value in BST
    
    if(found == NULL)//If not found return NULL
        return NULL;
    
    numInsert--;
    GSTVALUE * gstfound = getBSTNODEvalue(found);
    
    if(gstfound->frequency > 1)
        gstfound->frequency--;
    else if(gstfound->frequency == 1)
        deleteBST(gst->bst, gstval);
    free(gstval);
    return gstfound->value;
}

int sizeGST(GST * gst)
{
    return sizeBST(gst->bst);
}

int duplicates(GST * gst)
{
    return numInsert - sizeBST(gst->bst);
}

void statisticsGST(GST *gst,FILE * fp)
{
    fprintf(fp,"Duplicates: %d\n", duplicates(gst) );
    statisticsBST(gst->bst, fp);
}

void displayGST(GST * gst,FILE * fp)
{
    displayBSTdecorated(gst->bst, fp);
}

void displayGSTdebug(GST *gst,FILE * fp)
{
    displayBST(gst->bst, fp);
}

void freeGST(GST * gst)
{
    freeBST(gst->bst);
    free(gst);
}

 
