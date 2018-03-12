#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "command_line_utils.h"
#include "cli.h"
#include "posting_list.h"
#include "map.h"
#include "retrie.h"
#include "doc_utils.h"

#define MAX_ARG_STR 256

void command_line_user(void)
{
    char *str=malloc(MAX_ARG_STR*sizeof(char));
    char *temp_str=malloc(MAX_ARG_STR*sizeof(char));
    char *tokenSpace1, *tokenSpace2, *args, *word;

    int CLIcount, k, line_id, cli_word_length;

    struct word *cli_word;
    struct trie_node *cli_trie_node;
    struct post_list_node *cli_post_node;

    cli_word_length = 0;
    line_id= 0;
    CLIcount = 0;
    k = 1;


    /***************CLI***************/
    while(1)
    {
        printf(">>>");
        //Read a line from stdin and store it to str
        if(fgets (str,MAX_ARG_STR,stdin)!=NULL)
        {
            CLIcount++;
        }

        //Get first argument from stdin
        strcpy(temp_str,str);
        tokenSpace1 = strtok_r(temp_str, " ", &args);
        tokenSpace2 = strtok_r(NULL, " ", &args);

        k = 1;

        //First argument is /search
        if(strcmp(tokenSpace1, "/search") == 0)
        {
            while(k <= get_arg_k_val())
            {
                tokenSpace1 = strtok_r(NULL, " ", &args);
                if(tokenSpace1 == NULL)
                    break;
                printf("%s ", tokenSpace1);
                k++;
            }
            puts("\n");
            CLIcount++;
        }
        //First argument is /df
        else if ((strcmp(tokenSpace1, "/df\n") == 0) || ((strcmp(tokenSpace1, "/df") == 0) && (strcmp(tokenSpace2, "\n") == 0)))
        {
            df_print_retrie();
            CLIcount++;
        }
//        else if (strcmp(tokenSpace1, "/df") == 0)
//        {

//        }
        //First argument is /tf
        else if(strcmp(tokenSpace1, "/tf") == 0)
        {
            //if second argument is not an integer and not zero
            if(atoi(tokenSpace2) == 0 && strcmp(tokenSpace2, "0") != 0)
            {
                printf("Wrong Arguments\n");
                CLIcount++;
                continue;
            }
            else
            {
                line_id = atoi(tokenSpace2);
                if(line_id > (get_numb_of_lines() - 1))
                {
                    printf("Incorrect document id\n");
                    continue;
                }
            }
            if((word = strtok_r(NULL, " ", &args)) == NULL)
            {
                printf("Wrong Arguments\n");
                CLIcount++;
                continue;
            }
            strtok_r(word, "\n", &args);
            cli_word_length = strlen(word) + 1;

            //Memory allocated is sizeof(struct) + sizeof(word from cli) + sizeof("\0")
            cli_word = (struct word*) malloc(sizeof(struct word) + cli_word_length*sizeof(char) + 1*sizeof(char));
            memset(cli_word, 0, (sizeof(struct word) + cli_word_length*sizeof(char) + 1*sizeof(char)));
            if(cli_word == NULL)
            {
                printf("Not enough memory in heap\n");
                exit(EXIT_FAILURE);
            }
            //fill word struct
            strcpy(cli_word->actual_word, word);
            strcat(cli_word->actual_word, "\0");
            cli_word->number_of_line = line_id;
            cli_word->word_length = cli_word_length;
            //search for cli_word inside trie
            if((cli_trie_node = search_word_to_trie(cli_word)) == NULL)
            {
                printf("Couldn't find word:%s \n", cli_word->actual_word);
                free(cli_word);
                continue;
            }
            //search in posting list, starting from head
            if((cli_post_node = search_post_list(cli_trie_node->post_list_head, cli_word)) == NULL)
            {
                printf("Couldn't find word:%s \n", cli_word->actual_word);
                free(cli_word);
                continue;
            }
            printf("%d %s %d\n", cli_post_node->line_id, cli_word->actual_word, cli_post_node->freq);
            free(cli_word);
            CLIcount++;
        }
        else if(strcmp(tokenSpace1, "/exit\n") == 0 ||(strcmp(tokenSpace1, "/exit") == 0 && strcmp(tokenSpace2, "\n") == 0))
        {
            free_all();
            free(str);
            free(temp_str);
            puts("Exiting");
            exit(0);
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

void free_all(void)
{
    printf("Freeing allocated memory\n");
    clean_trie();
    free_map_list();
}


