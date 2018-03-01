//Jeremy McCormick
//Feb 28 2018
//gst.c
//green search tree module based on bst. handles duplicates better
#include<stdio.h>
#include "bst.h"

struct gst{
    BST * bst;
    void (*display)(void *, FILE *);
    int (*compare)(void *, void *);
    void (*free)(void *);
};

typedef struct gstvalue {
    void * value;
    int frequency;
}GSTVALUE;

GST *newGST(void (*display)(void *,FILE *), int (*compare)(void *,void *), void (*free)(void *))
{
    GST * gst = malloc(sizeof(GST));
    gst->display = display;
    gst->compare = comapre;
    gst->free = free;
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
    
    
        
}
    extern int findGSTcount(GST *,void *);
    extern void *findGST(GST *,void *);
    extern void *deleteGST(GST *,void *);
    extern int sizeGST(GST *);
    extern int duplicates(GST *);
    extern void statisticsGST(GST *,FILE *);
    extern void displayGST(GST *,FILE *);
    extern void displayGSTdebug(GST *,FILE *);
    extern void freeGST(GST *);

    #endif
