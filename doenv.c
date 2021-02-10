#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


void handleI(int argc, char * argv[], char ** environ)
{

    //
    //gets size of environ so i can set arrays and loops easier
    //
    int sizeOfEnviron;
    for (sizeOfEnviron = 0; environ[sizeOfEnviron] != NULL; sizeOfEnviron++)
    {
        //counting
    }


    //
    // Seperates environ name/values into differnent arrays with corresponding indexes to environ
    //
    char nameArray[sizeOfEnviron][2048];
    char valueArray[sizeOfEnviron][2048]; //DO I EVEN NEED THE VALUES IF IM JUST UNSETTING BY THE NAMES
    for (int i = 0; environ[i] != NULL; i++)
    {
        char nameValueHolder[2048];//probably double of name/value
        strcpy(nameValueHolder, environ[i]); //do sizeOfEnviron need to do this or can sizeOfEnviron just use environ[]? it changes environ strtok

        char * token = strtok(nameValueHolder, "="); //TOKEN IS NOW HOLDING NAME
        memcpy(nameArray[i],token,2047);
        token = strtok(NULL, "="); //TOKEN IS NOW HOLDING VALUE
        memcpy(valueArray[i],token,2047);
    }


    //
    //only for -i, unsets all of environ vars
    //
    for (int i = 0; i < sizeOfEnviron; i++)
    {
        unsetenv(nameArray[i]);
    }


    //
    // takes the arguments list argv and splits it into two seperate arrays; commands and name=values
    //
    char * envArgs[argc - 2];
    char * commandArgs[argc - 2];
    int envCounter = 0;
    int commandCounter = 0;
    for (int j = 2; j < argc; j++) //only use this with -i because it's counted as 1 in argc
    {
        if (strstr(argv[j], "=") != NULL)//puts name=value pairs into their own array
        {
            envArgs[envCounter] = argv[j];
            envCounter++;
        }
        else //puts commands into their own array
        {
            commandArgs[commandCounter] = argv[j];
            commandCounter++;
        }
    }


    //
    //sets all of the passed in pairs for the new environment, needs envCounter and envArgs
    // HAVE TO SET ALL BEFORE EXECUTING ANY COMMANDS
    for (int i = 0; i < envCounter; i++) //sets all of these values
    {
        char * name;
        char * value;
        name = strtok(envArgs[i], "=");
        value = strtok(NULL, "=");
        setenv(name, value, 1);
        //printf("GETENV: %s\n",getenv(name));
    }



    //
    //Executes arguments passed, do this after environment vars are set/unset
    //
    if (commandCounter == 0)
    {
        system("env");
    }
    else {
        for (int i = 0; i < commandCounter; i++) //sets all of these values
        {
            system(commandArgs[i]); //check for return value and handle incorrect command
        }
    }
}



int main(int argc, char * argv[], char ** environ)
{
    char myError[256] = ""; //weird symbols if i dont set it to ""
    strcat(myError, argv[0]); //we always want the name first
    strcat(myError, ": Error"); //how to do this prettier?
    int opt;

    if (argc == 1) //I could have just looped through environ but the rubric said to use getenv()
    {
        for (int i = 0; environ[i] != NULL; i++)
        {
            char envVar[2048];
            const char x[2] = "=";
            strcpy(envVar, environ[i]);
            strtok(envVar, x);
            printf("%s = %s\n", envVar, getenv(envVar));
        }
    }
    while ((opt = getopt (argc, argv, ":ih")) != -1) //Arguments passed, process them and perror if wrong
    {
        switch (opt)
        {
            case 'i':
                handleI(argc, argv, environ);
                break;
            case 'h':
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