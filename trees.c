#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "scanner.h"

int isGST = 0;

static int processOptions(int,char **);
void Fatal(char *,...);
char * getNext(FILE *);


int
main(int argc,char **argv)
{
    char * corpus = NULL;
    char * commands = NULL;
    
    if(argc < 1 || argc > 3)
    {
        printf("Not right amount of arguments");
        return 0;
    }
    if(argc == 2)
    {
        corpus = argv[0];
        commands = argv[1];
    }
    else
    {
        if(strcmp(argv[0],"-v") == 0)
        {
            printf("Jeremy McCormick");
            retirn 0;
        }
        if(strcmp(argv[0],"-g") == 0)
            isGST = 1;
        corpus = argv[1];
        commands = argv[2];
    }
    FILE * corpusfp = fopen(corpus, "r");
    FILE commandsfp = fopen(commands, "r");
    
    if(commandsfp == NULL || corpusfp == NULL)
    {
        printf("Files not found");
        return 0;
    }
    
    char * incorpus = getNext(incorpus);
    char incommand;
    
    while(!feof(incommand) && !feof(incorpus))
    {
        incorpus = getNext(incorpus);
        incommand = readChar(incommands);
        
        switch(incommand)
        {
            case 'i': 
                insertTree(incorpus);
                incorpus = getNext(incorpus);
                break;
            case 'd':
                deleteTree(incorpus);
                incorpus = getNext(incorpus);
                break;
            case 'f':
                frequencyTree(incorpus);
                incorpus = getNext(incorpus);
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
