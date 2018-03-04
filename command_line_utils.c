#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command_line_utils.h"

int arg_k_val;
int arg_doc;

int get_arg_k_val(void)
{
    return (arg_k_val);
}

int get_arg_doc(void)
{
    return (arg_doc);
}

int parse_cmd_line_args(int argc, char** argv)
{

    FILE *fp;

    if (argc == 5)
    {
        // Given arguments >>>./minisearch -i docfile -k 7
        if ((strcmp(argv[1],"-i")==0) && (strcmp(argv[3],"-k")==0) && atoi(argv[4]))
        {
            fp = fopen(argv[2], "r");
            if (!fp)
            {
                printf("can not open file \n");
                return 1;
            }
            fclose(fp);
            arg_k_val = atoi(argv[4]);
            arg_doc = 2;
        }
        // Given arguments >>>./minisearch -k 7 -i docfile
        else if ((strcmp(argv[1],"-k")==0) && (strcmp(argv[3],"-i")==0) && atoi(argv[2]))
        {
            fp = fopen(argv[4], "r");
            if (!fp)
            {
                printf("can not open file \n");
                return 1;
            }
            fclose(fp);
            arg_k_val = atoi(argv[2]);
            arg_doc = 4;
        }
        else
        {
            printf("Wrong Arguments\n");
            return 1;
        }
    }
    // Given arguments >>>./minisearch -i docfile
    else if ((argc == 3) && ((strcmp(argv[1],"-i")==0)))
    {
        fp = fopen(argv[2], "r");
        if (!fp)
        {
            printf("can not open file \n");
            return 1;
        }
        fclose(fp);
        arg_k_val = 10;
        arg_doc = 2;
    }

    else
    {
        printf("Wrong Arguments\n");
        return 1;
    }

    return 0;
}

