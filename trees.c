#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"
#include "gst.h"
#include "avl.h"


int isGST = 0;
void * tree;

char * getNext(FILE *);
void makeTree();
void printString(void * , FILE *);
int compareString(void *, void *);
void freeString(void *);
char * cleanupString(char *);

void insertTree(void *); //Wrapper for tree insert
void deleteTree(void *); //Wrapper for tree delete
int frequencyTree(void *); //Wrapper for tree frequency
void statsTree(); //wrapper for tree stats
void showTree(); //Wrapper for tree display

int
main(int argc,char **argv)
{
    char * corpus = NULL;
    char * commands = NULL;
    
    if(argc < 1 || argc > 3) // Make sure we have the right number of args
    {
        printf("Not right amount of arguments");
        return 0;
    }
    if(argc == 2) //2 args means no specifier for tree type, just file names
    {
        corpus = argv[0];
        commands = argv[1];
    }
    else
    {
        if(strcmp(argv[0],"-v") == 0) // -v option to print name
        {
            printf("Jeremy McCormick");
            return 0;
        }
        if(strcmp(argv[0],"-g") == 0) // -g option to make gst, -a not parsed because set as default in global def
            isGST = 1;
        corpus = argv[1];
        commands = argv[2];
    }
    FILE * corpusfp = fopen(corpus, "r"); //open up files
    FILE * commandsfp = fopen(commands, "r");
    
    if(commandsfp == NULL || corpusfp == NULL) //Check to make sure files are open
    {
        printf("Files not found");
        return 0;
    }
    
    makeTree(); //make tree, saving it to global void pointer "tree"
    
    char * incorpus;
    char incommand;
    
    while(!feof(commandsfp) && !feof(corpusfp)) // While were not at the end of any file
    {
        incorpus = getNext(corpusfp);
        incommand = readChar(commandsfp);
        cleanupString(incorpus);
        
        switch(incommand)
        {
            case 'i': 
                insertTree(incorpus);
                incorpus = getNext(corpusfp);
                break;
            case 'd':
                deleteTree(incorpus);
                incorpus = getNext(corpusfp);
                break;
            case 'f':
                printf("%d",frequencyTree(incorpus));
                incorpus = getNext(corpusfp);
                break;
            case 's':
                showTree();
                break;
            case 'r':
                statsTree();
                break;
            default:
                printf("command not understood");
        }
    }
    
    

    return 0;
}

char * getNext(FILE * in)
{
    if(stringPending(in))
    {
        return readString(in);
    }
    else
    {
        return readToken(in);
    }
    return NULL;
}

void makeTree()
{
    if(isGST == 1)
    {
        tree = newGST(printString, compareString, freeString);
    }
    else
    {
        tree = newAVL(printString, compareString, freeString);
    }
}
void printString(void * in, FILE * fp)
{
        char * string = in;
        fprintf(fp, "%s", string);
}

int compareString(void * a, void * b)
{
    char * stringa = a;
    char * stringb = b;
    return strcmp(stringa, stringb);
}

void freeString(void * in)
{
    free(in);
}

void insertTree(void * in)
{
    if(isGST == 1)
    {
        insertGST((GST*)tree, in);
    }
    else
    {
        insertAVL((AVL*)tree, in);
    }
}

void deleteTree(void * in)
{
    if(isGST == 1)
    {
        deleteGST((GST*)tree, in);
    }
    else
    {
        deleteAVL((AVL*)tree, in);
    }
}

int frequencyTree(void * in)
{
    if(isGST == 1)
    {
        return findGSTcount((GST*)tree, in);
    }
    else
    {
        return findAVLcount((AVL*)tree, in);
    }
}

void showTree()
{
    if(isGST == 1)
    {
        displayGST((GST*)tree, stdout);
    }
    else
    {
        displayAVL((AVL*)tree, stdout);
    }
}

void statsTree()
{
    if(isGST == 1)
    {
        statisticsGST(tree, stdout);
    }
    else
    {
        statisticsAVL(tree, stdout);
    }
}

char * cleanupString(char * in)
{
    char * out = in;
    for(unsigned int i = 0, j = 0; i < strlen(in); i++)
    {
        if(ispunct(in[i]))
        {
            continue;
        }
        
        else if(isupper(in[i]))
        {
            out[j] = tolower(in[i]);
            j++;
        }
        
        else if(isspace(in[i]))
        {
            out[j] = in[i];
            while(isspace(in[i]) && i < strlen(in) )
            {
                i++;
            }
            j++;
        }
        else
        {
            out[j] = in[i];
            j++;
        }
    }
    
    return out;
}
