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
int numInserted = 0;
int linear(BSTNODE * a, BSTNODE * b, BSTNODE * c);
BSTNODE * sibling(BSTNODE * in);

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
    avl->bst = newBST(NULL, NULL, NULL, NULL);
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
void insertAVL(AVL * avl,void * value)
{
    AVLVALUE * avlval = newAVLVALUE(avl, value); //make a new gstval for comparison
    BSTNODE * found = findBST(avl->bst, avlval); //pass it as the value instead of raw val
    numInserted++;
    if(found == NULL) //if not in tree, add it
    {
        insertBST(avl->bst, avlval);
        return;
    }
    AVLVALUE * avlfound = getBSTNODEvalue(found); //if is in tree, increment frequency
    avlfound->frequency += 1; 
   // freeAVLVALUE(avlval);
}
int findAVLcount(AVL * avl,void * value)
{   
    AVLVALUE * avlval = newAVLVALUE(avl, value);
    BSTNODE * found = findBST(avl->bst, avlval);
    if(found == NULL)
        return 0;
    AVLVALUE * avlfound = getBSTNODEvalue(found);
    return avlfound->frequency;
}
void *findAVL(AVL * avl,void * value)
{
    (void)avl;
    (void)value;
    return NULL;
}
void *deleteAVL(AVL * avl,void * value)
{
    (void)avl;
    (void)value;
    return NULL;
}
int sizeAVL(AVL *avl)
{
    (void)avl;
    return 0;
}
int duplicatesAVL(AVL * avl)
{
    (void)avl;
    return 0;
}
void statisticsAVL(AVL * avl,FILE * fp)
{
    (void)avl;
    (void)fp;
}
void displayAVL(AVL * avl,FILE * fp)
{
        (void)avl;
    (void)fp;
}
void displayAVLdebug(AVL * avl,FILE * fp)
{
        (void)avl;
    (void)fp;
}
void freeAVL(AVL * avl)
{
    free(avl);
}

void insertionFixup(BSTNODE * in)
{
        BSTNODE * node = in;
    while(node != NULL)
    {
        if(getBSTNODEparent(node) == node) // If node is the root
        {
            break;
        }
        BSTNODE * parent = getBSTNODEparent(node);
        AVLVALUE * avlvalParent = getBSTNODEvalue(parent); // Get avlval of parent
        AVLVALUE * avlval = getBSTNODEvalue(node);

         if(avlvalParent->height - avlval->height > 1)
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
        else
        {
            BSTNODE * favChild = NULL;
            if( avlval->heightLeft > avlval->heightLeft)
                favChild = getBSTNODEleft(node);
            else if( avlval->heightLeft < avlval->heightLeft)
                favChild = getBSTNODEright(node);
            
            if(favChild != NULL && !(linear(parent, node, favChild) )
            {
                rotate(favChild, node);
                rotate(favChild, parent);
                setBalance(node);
                setBalance(parent);
                setBalance(favChild);
            }
            else
            {
                rotate(node, parent);
                setBalance(parent);
                setBalance(node);
            }
        }
    }  
}
void deletionFixup(BSTNODE * node)
{

    
    while(getBSTNODEparent(node) != node)
    {
        AVLVALUE * avlval = getBSTNODEvalue(node);
        avlval->height = 0;
        BSTNODE * parent = getBSTNODEparent(node);
        AVLVALUE * avlvalParent = getBSTNODEvalue(parent);
        
        if(avlvalParent->height - avlval->height == 1 && avlvalParent->heightLeft != avlvalParent->heightRight) // node is parents favorite
        {
            setBalance(parent);
            node = parent;
        }
        else if(avlvalParent->heightLeft == avlvalParent->heightRight) //Parent has no favorite
        {
            setBalance(parent);
            break;
        }
        else
        {
            BSTNODE * sibling = sibling(node);
            AVLVALUE * avlSibling = getBSTNODEvalue(sibling);
            BSTNODE * favChild = NULL;
            if( avlSibling->heightLeft > avlSibling->heightLeft)
                favChild = getBSTNODEleft(sibling);
            else if( avlSibling->heightLeft < avlSibling->heightLeft)
                favChild = getBSTNODEright(sibling);
            
            if(favChild != NULL && !linear(parent, sibling, favChild) )
            {
                rotate(favChild, sibling);
                rotate(favChild, parent);
                setBalance(parent);
                setBalance(sibling);
                setBalance(favChild);
                node = favChild;
            }
            else
            {
                rotate(sibling, parent);
                setBalance(sibling);
                setBalance(parent);
                if(favChild == NULL)
                    break;
                node = sibling;
            }
        }
    }
}
int linear(BSTNODE * a, BSTNODE * b, BSTNODE * c)
{
    if(getBSTNODEleft(a) == b && getBSTNODEleft(b) == c)
        return 1;
    else if(getBSTNODEright(a) == b && getBSTNODEright(b) == c)
        return 1;
    return 0;
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
BSTNODE * sibling(BSTNODE * in)
{
    BSTNODE * parent = getBSTNODEparent(in);
    if(getBSTNODEleft(parent) == in)
        return getBSTNODEright(parent);
    else if(getBSTNODEright(parent) == in)
        return getBSTNODEleft(parent);
    return NULL;
}
void rotate(BSTNODE * a, BSTNODE *b)
{
}
