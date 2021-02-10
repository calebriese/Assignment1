#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char * argv[], char ** environ)
{
    char myError[256] = ""; //weird symbols if i dont set it to ""
    strcat(myError, argv[0]); //we always want the name first
    strcat(myError, ": Error"); //how to do this prettier?

    int opt;
    if (argc == 1) //No arguments, act like getenv. I could have just looped through environ but the rubric said to use getenv()
    {
        for (int i = 0; environ[i] != NULL; i++)
        {
            char envVar[1028];
            const char x[2] = "=";
            strcpy(envVar, environ[i]);
            strtok(envVar, x);
            printf("%s = %s\n", envVar, getenv(envVar));
        }
    }
    while ((opt = getopt (argc, argv, ":i:h")) != -1) //Arguments passed, process them and perror if wrong
    {
        switch (opt)
        {
            case 'i':
                printf("Case i With Argument: %s\n", optarg);
                //getenv(3);
                break;
            case ':':
                printf("Case i Without Argument\n");
                break;
            case 'h': //if argument is supplied it is ignored
                printf("Usage: doenv [-i] [name=value ...] [utility [argument ...]]\n");
                break;
            case '?':
                errno = EINVAL;
                perror(myError);
                return 1;
        }
    }
    if (optind == 1 && argc > 1) //optind was incremented once already for line 11
    {
        errno = EINVAL;
        perror(myError);
        return 1;
    }

    return 0;
}