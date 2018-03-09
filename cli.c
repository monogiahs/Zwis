#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "command_line_utils.h"
#include "cli.h"
#include "posting_list.h"
#include "map.h"

#define MAX_ARG_STR 256

void command_line_user(void)
{
    char *str=malloc(MAX_ARG_STR*sizeof(char));
    char *temp_str=malloc(MAX_ARG_STR*sizeof(char));
    char *tokenSpace,*args, *word;

    int CLIcount, k, line_id, cli_word_length;

    char cchar;

    struct word *cli_word;

    cli_word_length = 0;
    line_id= 0;
    CLIcount = 0;
    k = 1;


    /***************CLI***************/
    while(1)
    {
        if(CLIcount>=1)
        {
            printf("Do you want to continue;(y/n)");
            scanf("%c", &cchar);
            //To continue running commands
            if(cchar=='y')
            {
                printf("\n");
                getchar();
            }
            //To exit CLI
            else if(cchar=='n')
            {
                puts("Exiting");
                exit(0);
            }
        }

        printf(">>>");

        //Read a line from stdin and store it to str
        if(fgets (str,MAX_ARG_STR,stdin)!=NULL)
        {
            strcpy(temp_str,str);
            CLIcount++;
        }

        //Get first argument
        tokenSpace = strtok_r(str, " ", &args);

        k = 1;

        //First argument is /search
        if(strcmp(tokenSpace, "/search") == 0)
        {
            while(k <= get_arg_k_val())
            {
                tokenSpace = strtok_r(NULL, " ", &args);
                if(tokenSpace == NULL)
                    break;
                printf("%s ", tokenSpace);
                k++;
            }
            puts("\n");
            CLIcount++;
        }
        //First argument is /df
        else if((strcmp(tokenSpace, "/df\n") == 0) || (strcmp(tokenSpace, "/df") == 0))
        {
            CLIcount++;
        }
        //First argument is /tf
        else if(strcmp(tokenSpace, "/tf") == 0)
        {
            line_id = atoi(strtok_r(NULL, " ", &args));
            word = strcat(strtok_r(NULL, " ", &args), "\0");
            if(word == NULL)
            {
                printf("Wrong Arguments\n");
                CLIcount++;
                continue;
            }
            cli_word_length = strlen(word);

            //Memory allocated is sizeof(struct)+sizeof(word from cli + "\0")
            cli_word = (struct word*) malloc(sizeof(struct word) + cli_word_length*sizeof(char));
            memset(cli_word, 0, (sizeof(struct word) + cli_word_length*sizeof(char)));
            if(cli_word == NULL)
            {
                printf("Not enough memory in heap\n");
                exit(EXIT_FAILURE);
            }
            //fill word struct
            strcpy(cli_word->actual_word, word);
            cli_word->number_of_line = line_id;
            cli_word->word_length = cli_word_length;
            //search(word, 3);
            free(cli_word);
            CLIcount++;
        }
        //Wrong arguments
        else
        {
            printf("Wrong Arguments\n");
            CLIcount++;
            continue;
        }
    }
}


