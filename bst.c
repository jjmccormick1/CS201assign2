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
void freeBSTrecurse(BST *, BSTNODE *);
void genericSwapper(BSTNODE *, BSTNODE *);

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

void    freeBSTNODE(BSTNODE *n,void (*infree)(void *))
{
        infree(n->value);
        //free(n);
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
    
    if(swapper == NULL || swapper == 0)
        bst->swapper = genericSwapper;
    else
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
    if(t->size == 0)
    {
        t->root = newNode;
        t->size = 1;
        newNode->parent = newNode;
        return t->root;
    }
    t->size += 1;  //incerment size 
    return insertBSTrecurse(t,t->root,newNode,value); //call recursive helper
}

BSTNODE *insertBSTrecurse(BST* t,BSTNODE *root, BSTNODE * newNode, void *value)
{
    
        if(root == NULL)
        {
            return NULL;
        }
        int cmp = t->compare(getBSTNODEvalue(root), value);
    
        if(cmp > 0 && getBSTNODEleft(root) == NULL)// if its less and the spot is empty
        {
            setBSTNODEleft(root, newNode);
            setBSTNODEparent(newNode, root);
            return newNode;
        }
        if(cmp < 0 && getBSTNODEright(root) == NULL) //if its more and the sport is empty
        {
            setBSTNODEright(root, newNode);
            setBSTNODEparent(newNode, root);
            return newNode;
        }
        if(cmp > 0 && getBSTNODEleft(root) != NULL) //recure if spot isnt empty
                insertBSTrecurse(t,getBSTNODEleft(root),newNode, value);
        if(cmp < 0 && getBSTNODEright(root) != NULL) //recurse if not empty
                insertBSTrecurse(t,getBSTNODEright(root),newNode, value);
        return NULL;
        
}

BSTNODE *findBST(BST *t,void *value)
{
    BSTNODE * step = t->root;
    while(step != NULL)
    {
        int cmp = t->compare(getBSTNODEvalue(step), value);
        if(cmp == 0)
        {
            return step;
        }
        if(cmp > 0)
            step = getBSTNODEleft(step);
        if(cmp < 0)
            step = getBSTNODEright(step);
    }
    return NULL;
    
    
    //return findBSTrecurse(t, t->root, value);
}

BSTNODE *findBSTrecurse(BST *t, BSTNODE *node, void * value)
{   
    if(node == NULL || node == 0)
        return NULL;
    void * tmp = getBSTNODEvalue(node);
    int cmp = t->compare(tmp, value);
    
    if(cmp == 0)
        return node;
    if(cmp < 0)
        findBSTrecurse(t, getBSTNODEleft(node), value);
    if(cmp > 0)
        findBSTrecurse(t, getBSTNODEright(node), value);
    
    return NULL;
}

BSTNODE *deleteBST(BST *t,void *value)
{
    BSTNODE * delNode = findBST(t,value);
    
    if(t->size == 0)
        return NULL;
    
    if(delNode == NULL)
        return NULL;
    
    if(getBSTNODEleft(delNode) == NULL && getBSTNODEright(delNode) == NULL) // case 1 - node is a leaf
    {
        pruneLeafBST(t, delNode);
    }
    
    else if(getBSTNODEleft(delNode) == NULL && getBSTNODEright(delNode) != NULL ) //Case 2 - node has on child, right in this case
    {

            
        BSTNODE * child = getBSTNODEright(delNode);
        BSTNODE * parent = getBSTNODEparent(delNode);
        
        if(getBSTNODEleft(parent) == delNode)
            setBSTNODEleft(parent, child);
        else
            setBSTNODEright(parent, child);
        setBSTNODEparent(child, parent);
    }
    else if(getBSTNODEleft(delNode) != NULL && getBSTNODEright(delNode) == NULL ) //Case 2 - node has on child, left in this case
    {
        BSTNODE * child = getBSTNODEleft(delNode);
        BSTNODE * parent = getBSTNODEparent(delNode);
        
        if(getBSTNODEleft(parent) == delNode)
            setBSTNODEleft(parent, child);
        else
            setBSTNODEright(parent, child);
        
       setBSTNODEparent(child, parent);
        
    }
    else                // Case 3, 2 children. Swap with predecessor and delete
    {
        BSTNODE * leaf = swapToLeafBST(t,delNode);
        deleteBST(t, getBSTNODEvalue(leaf));
    }
    //freeBSTNODE(delNode, t->free);
    t->size -= 1; //decrement size
    return delNode;
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
        step = getBSTNODEright(node); //Go right once
    
        while(getBSTNODEleft(step) != NULL)
        {
            step = getBSTNODEleft(step); // Then go all the way left
        }
    }
    else
    {
       step = getBSTNODEleft(node); //Go left once
    
        while(getBSTNODEright(step) != NULL)
        {
            step = getBSTNODEright(step); // Then go all the way right
        }
    }
    t->swapper(node, step); //Swap the nodees
    //setBSTNODEvalue(node, getBSTNODEvalue(step));
    return step;
}

void    pruneLeafBST(BST *t,BSTNODE *leaf)
{

    BSTNODE * parent = getBSTNODEparent(leaf);
    if(parent == NULL)
        return;
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
    fprintf(fp, "Nodes: %d\n",sizeBST(t));
    fprintf(fp, "Minimum Depth: %d\n",minHeightBST(t->root));
    fprintf(fp, "Maximum Depth: %d\n",maxHeightBST(t->root));
}

int maxHeightBST(BSTNODE *node)
{
  if (node == NULL) return 0;
  int lefth = maxHeightBST(getBSTNODEleft(node));
  int righth = maxHeightBST(getBSTNODEright(node));
  return (lefth > righth) ? lefth + 1 : righth + 1;
}
int minHeightBST(BSTNODE *node)
{
  if (node == NULL) return 0;
  int lefth = maxHeightBST(getBSTNODEleft(node));
  int righth = maxHeightBST(getBSTNODEright(node));
  return (lefth < righth) ? lefth + 1 : righth + 1;
}

void    displayBST(BST *t,FILE *fp)
{
    if(t->root == NULL)
        return;
    
    preorder(t,t->root,fp);
}

void preorder(BST *t, BSTNODE * node, FILE * fp)
{
    fprintf(fp,"[");
        t->display(getBSTNODEvalue(node), fp);
        
        if(getBSTNODEleft(node) != NULL)
            preorder(t, getBSTNODEleft(node), fp);
        if(getBSTNODEright(node) != NULL)
            preorder(t, getBSTNODEright(node), fp);
        fprintf(fp,"]");
}

void    displayBSTdebug(BST *t,FILE *fp)
{
     if(sizeBST(t) == 0)
    {
        fprintf(fp,"EMPTY");
        return;
    }
    QUEUE * queue = newQUEUE(t->display, t->free);
    enqueue(queue,t->root); //put root into queue to start things off
    int level = 0;
    while(sizeQUEUE(queue) > 0)
    {
        level = sizeQUEUE(queue); //get queue size for newline
        while(level > 0)
        {
            BSTNODE * node = (BSTNODE*)dequeue(queue);
            t->display(getBSTNODEvalue(node), fp);
            fflush(stdout);
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
    freeQUEUE(queue);
}

void displayBSTdecorated(BST * t, FILE * fp)
{
    if(sizeBST(t) == 0 || t->root == NULL)
    {
        fprintf(fp,"EMPTY");
        return;
    }
    QUEUE * queue = newQUEUE(t->display, t->free);
    enqueue(queue,t->root); //put root into queue to start things off
    int level = 0;
    int printLevel = 0;
    while(sizeQUEUE(queue) > 0)
    {
        level = sizeQUEUE(queue); //get queue size for newline
        fprintf(fp,"%d: ",printLevel);
        while(level > 0)
        {
            BSTNODE * node = (BSTNODE*)dequeue(queue);
            if(getBSTNODEleft(node) == NULL && getBSTNODEright(node) == NULL) //display = if leaf
                fprintf(fp,"=");
            
            
            t->display(getBSTNODEvalue(node), fp);
            fprintf(fp,"(");
            t->display(getBSTNODEvalue(getBSTNODEparent(node)), fp);
            fprintf(fp, ")");
            
            if(t->root == node)
                fprintf(fp,"X");
            else if(getBSTNODEleft(getBSTNODEparent(node)) == node)
                fprintf(fp,"L");
            else if(getBSTNODEright(getBSTNODEparent(node)) == node)
                fprintf(fp,"R");
            
            fflush(stdout);
            if(level > 1)
                fprintf(fp, " ");
            if(getBSTNODEleft(node) != NULL)
                enqueue(queue, getBSTNODEleft(node) ); //add left into queue
            if(getBSTNODEright(node) != NULL)
                enqueue(queue, getBSTNODEright(node) ); //add right into queue
            
            level--;
        }
        printLevel++;
        fprintf(fp,"\n");
    }
    freeQUEUE(queue);
}
void freeBST(BST *t)
{
   freeBSTrecurse(t, t->root);
    free(t);
}
void freeBSTrecurse(BST * bst,BSTNODE *node)
{
    if(node == NULL)
        return;
    freeBSTrecurse(bst, getBSTNODEleft(node));
    freeBSTrecurse(bst, getBSTNODEright(node));
    bst->free(getBSTNODEvalue(node));
    free(node);
}

void genericSwapper(BSTNODE * a, BSTNODE * b)
{
    void * tmp = a->value;
    a->value = b->value; 
    b->value = tmp;
}
