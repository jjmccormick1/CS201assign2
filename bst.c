//Jeremy McCormick
// bst.c
#include "bst.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

int minHeightBST(BSTNODE *node);
int maxHeightBST(BSTNODE *node);
void preorder(BST *t, BSTNODE * node, FILE * fp);
BSTNODE *findBSTrecurse(BST *t, BSTNODE *node, void * value);
BSTNODE *insertBSTrecurse(BST* t,BSTNODE *root, BSTNODE * newNode, void *value);
void freeRecurse(BST * t,BSTNODE * node);

struct bstnode
{
    void * value;
    BSTNODE * parent;
    BSTNODE * left;
    BSTNODE * right;
};

BSTNODE *newBSTNODE(void *v)
{
        BSTNODE * node = malloc(sizeof(BSTNODE));
        node->value = v;
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
        return node;
}

void    *getBSTNODEvalue(BSTNODE *n){ return n->value; }
void    setBSTNODEvalue(BSTNODE *n,void *value) { n->value = value; }
BSTNODE *getBSTNODEleft(BSTNODE *n) { return n->left; }
void    setBSTNODEleft(BSTNODE *n,BSTNODE *replacement) { n->left = replacement; }
BSTNODE *getBSTNODEright(BSTNODE *n) {return n->right; }
void    setBSTNODEright(BSTNODE *n,BSTNODE *replacement) {n->right = replacement; }
BSTNODE *getBSTNODEparent(BSTNODE *n) {return n->parent; }
void    setBSTNODEparent(BSTNODE *n,BSTNODE *replacement) {n->parent = replacement; }

void    freeBSTNODE(BSTNODE *n,void (*free)(void *))
{
        free(n->value);
        free(n->parent);
        free(n->left);
        free(n->right);
}

struct bst
{
        BSTNODE * root;
        int size;
        void (*display)(void *, FILE *);
        int (*compare)(void *, void *);
        void (*swapper)(BSTNODE*, BSTNODE*);
        void (*free)(void *);
};

BST *newBST( void (*display)(void *,FILE *),int (*compare)(void *,void *), void (*swapper)(BSTNODE *,BSTNODE *), void (*free)(void *))
{
    BST * bst = malloc(sizeof(BST));
    bst->root = NULL;
    bst->size =0;
    bst->display = display;
    bst->swapper = swapper;
    bst->compare = compare;
    bst->free = free;
    return bst;
}
    
BSTNODE *getBSTroot(BST *t){return t->root;}
void    setBSTroot(BST *t,BSTNODE *replacement){ t->root = replacement; }
void    setBSTsize(BST *t,int s) {t->size = s; }

BSTNODE *insertBST(BST *t,void *value)
{
    BSTNODE * newNode = newBSTNODE(value); //create new bstnode
    t->size += 1;  //incerment size 
    return insertBSTrecurse(t,t->root,newNode,value); //call recursive helper
}

BSTNODE *insertBSTrecurse(BST* t,BSTNODE *root, BSTNODE * newNode, void *value)
{
    
    int cmp = t->compare(getBSTNODEvalue(root), value);
    
        if(cmp <= 0 && getBSTNODEleft(root) == NULL)// if its less and the spot is empty
        {
            setBSTNODEleft(root, newNode);
            setBSTNODEparent(newNode, root);
            return newNode;
        }
        if(cmp > 0 && getBSTNODEright(root) == NULL) //if its more and the sport is empty
        {
            setBSTNODEright(root, newNode);
            setBSTNODEparent(newNode, root);
            return newNode;
        }
        if(cmp <= 0 & getBSTNODEleft(root) != NULL) //recure if spot isnt empty
                insertBSTrecurse(t,getBSTNODEleft(root),newNode, value);
        if(cmp > 0 & getBSTNODEright(root) != NULL) //recurse if not empty
                insertBSTrecurse(t,getBSTNODEright(root),newNode, value);
        return NULL;
        
}

BSTNODE *findBST(BST *t,void *value)
{
    return findBSTrecurse(t, t->root, value);
}

BSTNODE *findBSTrecurse(BST *t, BSTNODE *node, void * value)
{
    int cmp = t->compare(getBSTNODEvalue(node), value);
    if(node == NULL)
        return NULL;
    if(cmp ==0)
        return node;
    if(cmp <= 0)
        findBSTrecurse(t, getBSTNODEleft(node), value);
    if(cmp > 0)
        findBSTrecurse(t, getBSTNODEright(node), value);
    
    return NULL;
}

BSTNODE *deleteBST(BST *t,void *value)
{
    BSTNODE * delNode = findBST(t,value);
    if(delNode == NULL)
        return NULL;
    
    BSTNODE * leaf = swapToLeafBST(t,delNode);
    pruneLeafBST(t,leaf);
    t->size -= 1; //decrement size
    return leaf;
}

BSTNODE *swapToLeafBST(BST *t,BSTNODE *node)
{
    if(node == NULL)
        return NULL;
    
    if(getBSTNODEleft(node) == NULL && getBSTNODEright(node) == NULL) // make sure its not already a leaf
        return node;
    
    BSTNODE * step;
    
    if(getBSTNODEright(node) != NULL)
    {
        step = getBSTNODEright(node); //Go left once
    
        while(step != NULL)
        {
            step = getBSTNODEleft(step); // Then go all the way right
        }
    }
    else
    {
       step = getBSTNODEleft(node); //Go left once
    
        while(step != NULL)
        {
            step = getBSTNODEright(step); // Then go all the way right
        }
    }
    t->swapper(node, step); //Swap the nodees
    return step;
}

void    pruneLeafBST(BST *t,BSTNODE *leaf)
{
    BSTNODE * parent = getBSTNODEparent(leaf);
    sizeBST(t); //Stops error complain of unused var
    if(getBSTNODEleft(parent) == leaf)
    {
        setBSTNODEleft(parent, NULL);
    }
    else
    {
        setBSTNODEright(parent,NULL);
    }
    setBSTNODEparent(leaf,NULL);
}

int     sizeBST(BST *t)
{
    return t->size;
}

void    statisticsBST(BST *t,FILE *fp)
{
    fprintf(fp, "Nodes: %d",sizeBST(t));
    fprintf(fp, "Minimum Depth: %d",minHeightBST(t->root));
    fprintf(fp, "Maximum Depth: %d",maxHeightBST(t->root));
}

int maxHeightBST(BSTNODE *node)
{
  if (!node) return 0;
  int lefth = maxHeightBST(node->left);
  int righth = maxHeightBST(node->right);
  return (lefth > righth) ? lefth + 1 : righth + 1;
}
int minHeightBST(BSTNODE *node)
{
  if (!node) return 0;
  int lefth = maxHeightBST(node->left);
  int righth = maxHeightBST(node->right);
  return (lefth < righth) ? lefth + 1 : righth + 1;
}

void    displayBST(BST *t,FILE *fp)
{
    preorder(t,t->root,fp);
}
void preorder(BST *t, BSTNODE * node, FILE * fp)
{
    fprintf(fp,"[");
        if(node == NULL)
        {
            fprintf(fp,"]");
            return;
        }
        t->display(getBSTNODEvalue(node), fp);
        preorder(t, getBSTNODEleft(node), fp);
        preorder(t, getBSTNODEright(node), fp);
}

void    displayBSTdebug(BST *t,FILE *fp)
{
    QUEUE * queue = newQUEUE(t->display, t->free);
    enqueue(queue,t->root); //put root into queue to start things off
    
    while(sizeQUEUE(queue) > 0)
    {
        int level = sizeQUEUE(queue); //get queue size for newline
        while(level > 0)
        {
            BSTNODE * node = (BSTNODE*)dequeue(queue);
            t->display(getBSTNODEvalue(t->root), fp);
            
            if(level > 1)
                fprintf(fp, " ");
            if(getBSTNODEleft(node) != NULL)
                enqueue(queue, getBSTNODEleft(node) ); //add left into queue
            if(getBSTNODEright(node) != NULL)
                enqueue(queue, getBSTNODEright(node) ); //add right into queue
            level--;
        }
        fprintf(fp,"\n");
    }
}

void    freeBST(BST *t)
{
    freeRecurse(t, t->root);
    free(t);
}

void freeRecurse(BST *t,BSTNODE * node)
{
    if(getBSTNODEleft(node) != NULL)
        freeRecurse(t, getBSTNODEleft(node));
    if(getBSTNODEright(node) != NULL)
        freeRecurse(t, getBSTNODEright(node));
    
    freeBSTNODE(node, t->free);
}
