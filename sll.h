 
 #ifndef __SLL_INCLUDED__
#define __SLL_INCLUDED__

#include <stdio.h>

typedef struct sll SLL;

extern SLL *newSLL(void (*d)(void *,FILE *),void (*f)(void *)); 
extern void insertSLL(SLL *items,int index,void *value);
extern void *removeSLL(SLL *items,int index);
extern void unionSLL(SLL *recipient,SLL *donor);
extern void *getSLL(SLL *items,int index);
extern void setSLL(SLL *items,int index,void *value);
extern int sizeSLL(SLL *items);
extern void displaySLL(SLL *items,FILE *);
extern void displaySLLdebug(SLL *items,FILE *);
extern void freeSLL(SLL *items);

typedef struct node NODE; /* forward declaration of our structure */

extern NODE  *newNODE(void *value,NODE *next);     /* constructor */
extern void  *getNODEvalue(NODE *n);
extern NODE  *getNODEnext(NODE *n);
extern NODE  *getNODEprev(NODE *n);
extern void  setNODEprev(NODE *n, NODE *);
extern void  setNODEvalue(NODE *n,void *);
extern void  setNODEnext(NODE *n,NODE *); //testing NODE * vs NODE * p
extern void  displayNODE(NODE *n,FILE *fp,void (*display)(FILE *,void *));
extern void  displayNODEdebug(NODE *n,FILE *fp,void (*display)(FILE *,void *));
extern void  freeNODE(NODE *n,void (*release)(void *));

#endif

