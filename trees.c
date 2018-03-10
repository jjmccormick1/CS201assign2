#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int isGST = 0;

static int processOptions(int,char **);
void Fatal(char *,...);

int
main(int argc,char **argv)
{
    char * corpus = NULL;
    char * commands = NULL;
    
    if(argc < 2 || argc > 3)
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
        if(strcmp(argv[0],"-g") == 0)
            isGST = 1;
        corpus = argv[1];
        commands = argv[2];
    }

    return 0;
}


