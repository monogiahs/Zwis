#ifndef _POSTING_LIST_H_
#define _POSTING_LIST_H_

#include "map.h"

struct post_list_node
{
        int line_id;
        int freq;
        struct post_list_node *post_next;
        int first_line_id;
        int word_length;
        char actual_word[0];
};

struct post_list_node *update_post_list(struct post_list_node *post_list_head, struct word *current_word);

void free_post_list(struct post_list_node *post_list_head);

struct post_list_node *search_post_list(struct post_list_node *post_list_head,struct word *cli_word);

#endif /* _POSTING_LIST_H_ */


