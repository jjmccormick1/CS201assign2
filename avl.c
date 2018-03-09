#include "avl.h"
#include "bst.h"
#include <stdlib.h>

AVLVALUE * newAVLVALUE(AVL *, void *);
void printAVL(void *,FILE *);
int compareAVL(void *, void *);
void swapperAVL(BSTNODE *, BSTNODE *);
void freeAVLVALUE(void *);

struct avl {
    BST * bst;
    void (*display)(void *, FILE *);
    int (*compare)(void *, void *);
    void (*free)(void *);
};

struct avlvalue {
    void * value;
    int frequency;
    void (*display)(void *, FILE *);
    int (*compare)(void *, void *);
    void (*free)(void *);
};

AVL *newAVL(void (*display)(void *,FILE *),int (*compare)(void *,void *),void (*free)(void *))
{
    AVL * avl = malloc(sizeof(AVL));
    avl->bst = newBST(printAVL, compareAVL, swapperAVL, freeAVLVALUE);
    avl->display = display;
    avl->compare = compare;
    avl->free = free;
    return avl;
}

AVLVALUE * newAVLVALUE(AVL * avl, void * value)
{
    AVLVALUE * avlval = malloc(sizeof(AVLVALUE));
    avlval->value = value;
    avlval->frequency = 1;
    avlval->display = avl->display;
    avlval->compare = avl->compare;
    avlval->free = avl->free;
    return avlval;
}

void printAVL(void * in,FILE * fp)
{
        AVLVALUE * avlval = in;
        avlval->display(avlval->value, fp);
}
void insertAVL(AVL *,void *)
{
    
}
int findAVLcount(AVL *,void *)
{
    
}
void *findAVL(AVL *,void *)
{
    
}
void *deleteAVL(AVL *,void *)
{
    
}
int sizeAVL(AVL *)
{
    
}
int duplicatesAVL(AVL *)
{
    
}
void statisticsAVL(AVL *,FILE *)
{
    
}
void displayAVL(AVL *,FILE *)
{
    
}
void displayAVLdebug(AVL *,FILE *)
{
    
}
void freeAVL(AVL *)
{
    
}

    #endif 
