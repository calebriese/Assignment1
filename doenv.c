//Author: Caleb Riese
//Date: 2/9/2021

#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


void processArgs(int argc, char **argv, char myError[])
{
    // takes the arguments list argv and splits it into two seperate arrays, commands and name=values
    char * envArgs[argc - 1]; //max amount of env vars or commands is argc -1
    char * commandArgs[argc - 1];
    int envCounter = 0;
    int commandCounter = 0;
    for (int j = optind; j < argc; j++)// depending on if there is an option (-i) we start at either 1 or 2.
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

    //sets all of the passed in pairs for the new environment, needs envCounter and envArgs
    for (int i = 0; i < envCounter; i++) //sets all of these values
    {
        char * name;
        char * value;
        name = strtok(envArgs[i], "=");
        value = strtok(NULL, "=");
        setenv(name, value, 1);
    }

    //Executes arguments passed
    if (commandCounter == 0)
    {
        system("env");
    }
    else {
        for (int i = 0; i < commandCounter; i++)
        {
            int ret = system(commandArgs[i]); //I couldnt silece the child shell from displaying to stderr
            if (ret > 0)
            {
                errno = ENOENT;
                perror(myError);
            }
        }
    }
}

void replaceEnv(char ** environ)
{
    //Gets size of environ so i can set arrays and loops easier
    int sizeOfEnviron;
    for (sizeOfEnviron = 0; environ[sizeOfEnviron] != NULL; sizeOfEnviron++)
    {
        //counting
    }
    //Separates environ name/values into different arrays with corresponding indexes to environ
    char nameArray[sizeOfEnviron][2048];
    for (int i = 0; environ[i] != NULL; i++)
    {
        char nameValueHolder[2048];
        strcpy(nameValueHolder, environ[i]);
        char * token = strtok(nameValueHolder, "=");
        memcpy(nameArray[i],token,2047);
    }
    //Unsets all environ variables
    for (int i = 0; i < sizeOfEnviron; i++)
    {
        unsetenv(nameArray[i]);
    }
}

int main(int argc, char * argv[], char ** environ)
{
    int opt;
    char myError[256] = "";
    strcat(myError, argv[0]);
    strcat(myError, ": Error");

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
    while ((opt = getopt (argc, argv, ":ih")) != -1)
    {
        switch (opt)
        {
            case 'i':
                replaceEnv(environ);
                break;
            case 'h':
                printf("Usage: doenv [-i] [name=value ...] [utility [argument ...]]\n");
                return 0;
            case '?':
                errno = EINVAL;
                perror(myError);
                return 1;
        }
    }
    processArgs(argc, argv, myError); //goes through all arguments and handles name=value and commands
    return 0;
}