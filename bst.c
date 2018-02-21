
struct bstnode
{
    void * value;
    BSTNODE * parent;
    BSTNODE * left;
    BSTNODE * right;
};

BSTNODE *newBSTNODE(void *v)[
{
        BSTNODE * node = malloc(sizeof(BSTNODE));
        node->value = v;
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
}

void    *getBSTNODEvalue(BSTNODE *n){ return n->value; }
void    setBSTNODEvalue(BSTNODE *n,void *value) { n->value = value;
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
    BST bst = malloc(sizeof(BST));
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
    
}

BSTNODE *insertBSTrecurse(BST* t,BSTNODE *node, void *value)
{
        if(t->comapre(getBSTNODEvalue(node), value) < 0 && getBSTNODEleft(root) != NULL)
                insertBSTrecurse(t,getBSTNODEleft(node),value);
        
}
 extern BSTNODE *findBST(BST *t,void *value);
    extern BSTNODE *deleteBST(BST *t,void *value);
    extern BSTNODE *swapToLeafBST(BST *t,BSTNODE *node);
    extern void    pruneLeafBST(BST *t,BSTNODE *leaf);
    extern int     sizeBST(BST *t);
    extern void    statisticsBST(BST *t,FILE *fp);
    extern void    displayBST(BST *t,FILE *fp);
    extern void    displayBSTdebug(BST *t,FILE *fp);
    extern void    freeBST(BST *t);
    #endif 
