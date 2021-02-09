#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
    int aflag = 0;
    int bflag = 0;
    char *cvalue = NULL;
    int index;
    int c;

    while ((c = getopt (argc, argv, "abcij:")) != -1)
        switch (c)
        {
            case 'a':
                aflag = 1;
                printf("Case, a");
                break;
            case 'b':
                bflag = 1;
                break;
            case 'c':
                cvalue = optarg;
                break;
            case 'i':
                aflag = 1;
                //getenv(3);
                printf("Case i\n");
                break;
            case '?':
                if (optopt == 'c')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Unknown option character `\\x%x'.\n",
                             optopt);
                return 1;
            default:
                abort ();
        }

    printf("End\n");
    return 0;
