#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "command_line_utils.h"
#include "doc_utils.h"
#include "map.h"
#include "retrie.h"
#include "cli.h"




int main(int argc, char **argv)
{

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
        command_line_user();
        df_print_retrie();
        clean_trie();
        free_map_list();
}
