#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "command_line_utils.h"
#include "cli.h"
#include "posting_list.h"
#include "map.h"
#include "retrie.h"
#include "doc_utils.h"
#include "score_calculator.h"

#define MAX_ARG_STR 256

//node for the head of search_words list
struct word *search_words_head = NULL;

<<<<<<< HEAD
struct word *get_word_list()
{
    return search_words_head;
}

=======
>>>>>>> eb2886be7fb1a7b4d23652af65d9ea0c98392f63
struct word *new_word(int cli_word_length)
{
    //Memory allocated is sizeof(struct) + sizeof(word from cli) + sizeof("\0")
    struct word *cli_word_current = (struct word*) malloc(sizeof(struct word) + cli_word_length*sizeof(char)/* + 1*sizeof(char)*/);
    memset(cli_word_current, 0, (sizeof(struct word) + cli_word_length*sizeof(char)/* + 1*sizeof(char)*/));
    cli_word_current->word_next = NULL;
    cli_word_current->word_length = cli_word_length;
    return cli_word_current;
}

void command_line_user(void)
{
    char *str=malloc(MAX_ARG_STR*sizeof(char));
    char *temp_str=malloc(MAX_ARG_STR*sizeof(char));
    char *tokenSpace1, *tokenSpace2, *word;

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
        tokenSpace1 = strtok(temp_str, " \t\n");


        k = 1;

        //First argument is /search
        if(strcmp(str, "\n") == 0)
        {
<<<<<<< HEAD
            CLIcount++;
            continue;
        }
        else if(strcmp(tokenSpace1, "/search") == 0)
        {
            word = strtok (str," \t");
            while (word != NULL && k <= get_arg_k_val())
              {
                word = strtok (NULL, " \t\n");
                if(word == NULL && k == 1)
                {
                    printf("Wrong Arguments\n");
                    CLIcount++;
                    break;
                }
                else if(word == NULL && k <= get_arg_k_val())
                {
                    CLIcount++;
                    break;
                }
                cli_word_length = strlen(word) + 1;
                cli_word = new_word(cli_word_length);
                if(cli_word == NULL)
                {
                    printf("Not enough memory in heap\n");
                    exit(EXIT_FAILURE);
                }
                //fill word struct
                strcpy(cli_word->actual_word, word);
                strcat(cli_word->actual_word, "\0");
                cli_trie_node = search_word_to_trie(cli_word);
                if(cli_trie_node == NULL)
                {
                    printf("Couldn't find word:%s\n\n", cli_word->actual_word);
                    k++;
                    free(cli_word);
                    continue;
                }
                cli_post_node = cli_trie_node->post_list_head;
//                while(1)
//                {
//                    if(cli_post_node->post_next != NULL)
//                    {
//                        printf("%s\n", (search_map_node_to_list_with_id(cli_post_node->line_id)->text));
//                        //search_word_to_map_node(cli_post_node, cli_word);
//                        cli_post_node = cli_post_node->post_next;
//                    }
//                    else
//                    {
//                        printf("%s\n\n", (search_map_node_to_list_with_id(cli_post_node->line_id)->text));
//                        break;
//                    }

//                }
                //score_calculator(cli_word);
                add_word_to_list(cli_word);
                k++;
              }

            call_calculations(search_words_head);

            if(search_words_head != NULL)
              free_word_list();
        }
=======
            word = strtok (str," \t");
            while (word != NULL && k <= get_arg_k_val())
              {
                word = strtok (NULL, " \t\n");
                if(word == NULL && k == 1)
                {
                    printf("Wrong Arguments\n");
                    CLIcount++;
                    break;
                }
                else if(word == NULL && k <= get_arg_k_val())
                {
                    CLIcount++;
                    break;
                }
                cli_word_length = strlen(word) + 1;
                cli_word = new_word(cli_word_length);
                if(cli_word == NULL)
                {
                    printf("Not enough memory in heap\n");
                    exit(EXIT_FAILURE);
                }
                //fill word struct
                strcpy(cli_word->actual_word, word);
                strcat(cli_word->actual_word, "\0");
                cli_trie_node = search_word_to_trie(cli_word);
                if(cli_trie_node == NULL)
                {
                    printf("Couldn't find word:%s\n\n", cli_word->actual_word);
                    k++;
                    free(cli_word);
                    continue;
                }
                cli_post_node = cli_trie_node->post_list_head;
//                while(1)
//                {
//                    if(cli_post_node->post_next != NULL)
//                    {
//                        printf("%s\n", (search_map_node_to_list_with_id(cli_post_node->line_id)->text));
//                        //search_word_to_map_node(cli_post_node, cli_word);
//                        cli_post_node = cli_post_node->post_next;
//                    }
//                    else
//                    {
//                        printf("%s\n\n", (search_map_node_to_list_with_id(cli_post_node->line_id)->text));
//                        break;
//                    }

//                }
                //score_calculator(cli_word);
                add_word_to_list(cli_word);
                k++;
              }

            call_calculations(search_words_head);

            if(search_words_head != NULL)
              free_word_list();
        }
>>>>>>> eb2886be7fb1a7b4d23652af65d9ea0c98392f63
        //First argument is /df
        else if(strcmp(tokenSpace1, "/df") == 0)
        {
            word = strtok (NULL, " \t\n");
            if(word == NULL)
            {
                df_print_retrie();
                CLIcount++;
            }
            else
            {
                while(word != NULL)
                {
                    cli_word_length = strlen(word) + 1;
                    cli_word = new_word(cli_word_length);
                    if(cli_word == NULL)
                    {
                        printf("Not enough memory in heap\n");
                        exit(EXIT_FAILURE);
                    }
                    //fill word struct
                    strcpy(cli_word->actual_word, word);
                    strcat(cli_word->actual_word, "\0");
                    if((cli_trie_node = search_word_to_trie(cli_word)) == NULL)
                    {
                        printf("Couldn't find word:%s \n", cli_word->actual_word);
                        free(cli_word);
                        word = strtok(NULL, " \t\n");
                        continue;
                    }
                    printf("%s %d\n", cli_trie_node->post_list_head->actual_word, cli_trie_node->line_id_counter);
                    free(cli_word);
                    CLIcount++;
                    word = strtok(NULL, " \t\n");
                }

            }
        }
        //First argument is /tf
        //FIX TF FOR MULTIPLE WORDS
        else if(strcmp(tokenSpace1, "/tf") == 0)
        {
            //if second argument is not an integer and not zero
            tokenSpace2 = strtok(NULL, " \t");
            if((tokenSpace2 == NULL) || (atoi(tokenSpace2) == 0 && strcmp(tokenSpace2, "0") != 0))
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
            if((word = strtok(NULL, " \t\n")) == NULL)
            {
                printf("Wrong Arguments\n");
                CLIcount++;
                continue;
            }
            while(word != NULL)
            {
                cli_word_length = strlen(word) + 1;
                cli_word = new_word(cli_word_length);
                if(cli_word == NULL)
                {
                    printf("Not enough memory in heap\n");
                    exit(EXIT_FAILURE);
                }
                //fill word struct
                strcpy(cli_word->actual_word, word);
                strcat(cli_word->actual_word, "\0");
                cli_word->number_of_line = line_id;
                //search for cli_word inside trie
                if((cli_trie_node = search_word_to_trie(cli_word)) == NULL)
                {
                    printf("Couldn't find word:%s \n", cli_word->actual_word);
                    word = strtok(NULL, " \t\n");
                    free(cli_word);
                    break;
                }
                //search in posting list, starting from head
                if((cli_post_node = search_post_list(cli_trie_node->post_list_head, cli_word)) == NULL)
                {
                    printf("Couldn't find word:%s \n", cli_word->actual_word);

                    free(cli_word);
                    break;
                }
                printf("%d %s %d\n", cli_post_node->line_id, cli_word->actual_word, cli_post_node->freq);
                word = strtok(NULL, " \t\n");
                free(cli_word);
                CLIcount++;
            }
        }
        else if(strcmp(tokenSpace1, "/exit") == 0)
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

void add_word_to_list(struct word* cli_word)
{
    if(search_words_head == NULL)
    {
        search_words_head = cli_word;
        return;
    }
    else
    {
        cli_word->word_next = search_words_head;
        search_words_head = cli_word;
    }
}


void free_word_list(void)
{
    struct word* search_words_tmp;

    while(1)
    {
        search_words_tmp = search_words_head;
        if(search_words_head->word_next != NULL)
        {
            search_words_head = search_words_head->word_next;
            free(search_words_tmp);
        }

        else
        {
            free(search_words_tmp);
            search_words_head = NULL;
            return;
        }
    }
}


