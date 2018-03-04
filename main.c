#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "command_line_utils.h"
#include "doc_utils.h"
#include "map.h"


int main(int argc, char **argv)
{
        int arg_val;

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

        free_map_list();
}
