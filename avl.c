#include "avl.h"
#include "bst.h"
#include <stdlib.h>

AVLVALUE * newAVLVALUE(AVL *, void *);
void printAVL(void *,FILE *);
int compareAVL(void *, void *);
void swapperAVL(BSTNODE *, BSTNODE *);
void freeAVLVALUE(void *);
void setBalance(BSTNODE *);
void insertionFixup(BSTNODE *);

struct avl {
    BST * bst;
    void (*display)(void *, FILE *);
    int (*compare)(void *, void *);
    void (*free)(void *);
};

struct avlvalue {
    void * value;
    int height;
    int heightLeft;
    int heightRight;
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
    avlval->height = 0;
    avlval->heightRight = 0;
    avlval->heightLeft = 0;
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

void insertionFixup(BSTNODE * in)
{
        BSTNODE * node = in;
    while(node != NULL)
    {
        if(getBSTNODEparent == NULL) // If node is the root
        {
            break;
        }
        BSTNODE * parent = getBSTNODEparent(node);
        AVLVALUE * avlvalParent = getBSTNODEvalue(parent); // Get avlval of parent
        AVLVALUE * avlval = getBSTNODEvalue(node);
        int parentBF = avlvalParent->heightLeft - avlvalParent->heightRight;
        
        else if(avlvalParent->height - avlval->height > 1)
        {
            setBalance(parent);
            break;
        }
        else if(avlvalParent->heightLeft - avlvalParent->heightRight == 0)
        {
            setBalance(parent);
            node = parent;
            continue;
        }
        
        
}

void setBalance(BSTNODE * node)
{
    AVLVALUE * avlval = getBSTNODEvalue(node);
    if(getBSTNODEleft(node) == NULL)
    {
        avlval->heightLeft = 0;
    }
    else
    {
        AVLVALUE * avlvalLeft = getBSTNODEvalue(getBSTNODEleft(node));
        avlval->heightLeft = avlvalLeft->height;
    }
    
    if(getBSTNODEright(node) == NULL)
    {
        avlval->heightRight = 0;
    }
    else
    {
        AVLVALUE * avlvalRight = getBSTNODEvalue(getBSTNODEright(node));
        avlval->heightRight = avlvalRight->height;
    }
    
    if(avlval->heightRight > avlval->heightLeft)
    {
        avlval->height = avlval->heightRight + 1;
    }
    else
    {
        avlval->height = avlval->heightLeft + 1;
    }
}
