#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "command_line_utils.h"
#include "doc_utils.h"
#include "map.h"
#include "retrie.h"

#define MAX_ARG_STR 256


int main(int argc, char **argv)
{
//        char *str=malloc(MAX_ARG_STR*sizeof(char));
//        char *temp_str=malloc(MAX_ARG_STR*sizeof(char));
//        char *tokenSpace;
//        char *args;

//        int CLIcount;

//        char cchar;

//        CLIcount = 0;

        int arg_val;
        struct word *current_word;

        arg_val = parse_cmd_line_args(argc, argv);
        if (arg_val == 1)
        {
            exit(EXIT_FAILURE);
        }

        if (validate_doc(argv[get_arg_doc()]) == 0)
        {
            exit(EXIT_FAILURE);
        }


        load_map_list(argv[get_arg_doc()]);
        print_map_list();
        //load_inverted_index();
        set_word();
        while(1)
        {
            current_word = get_word();
            if(current_word == NULL)
                break;
            free(current_word);
        }

        load_retrie();

        free_map_list();
}






//        /***************CLI***************/
//        while(1)
//        {
//            if(CLIcount>=1)
//            {
//                printf("Do you want to continue;(y/n)");
//                scanf("%c", &cchar);
//                if(cchar=='y')                      //To continue running commands
//                {                                   //Reinitialize  below variables
//                    printf("\n");
//                    getchar();
//                }
//                else if(cchar=='n')                 //To exit CLI
//                {
//                    puts("Exiting");
//                    exit(0);
//                }
//            }

//            printf(">>>");

//            //Read a line from stdin and store it to str
//            if(fgets (str,MAX_ARG_STR,stdin)!=NULL)
//                strcpy(temp_str,str);

//            tokenSpace = strtok_r(str, " ", &args);
//            while(tokenSpace != NULL)
//            {
//                tokenSpace = strtok_r(NULL," ",&args);
//            }
//        }
