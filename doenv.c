#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[])
{
    int c;


    if (argc == 1) //No arguments, act like getenv
    {
        printf("No Options\n");
    }
    while ((c = getopt (argc, argv, "ih")) != -1) //Arguments passed, process them and perror if wrong
    {
        switch (c)
        {
            case 'i':
                //getenv(3);
                printf("Case i\n");
                break;
            case 'h':
                printf("Case h\n");
                break;
            case '?':
                fprintf(stderr, "Unknown Option\n", optopt); //optopt stores unrecognized option
                char myError[100];
                strcat(myError, argv[0]);
                strcat(myError, ":This is my Error");
                perror(myError);
                return 1;
        }
    }

    printf("End\n");
    return 0;
}
