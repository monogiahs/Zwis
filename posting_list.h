#ifndef _POSTING_LIST_H_
#define _POSTING_LIST_H_

#include "map.h"

struct post_list_node
{
        int line_id;
        int freq;
        struct post_list_node *post_next;
};

#endif /* _POSTING_LIST_H_ */

struct post_list_node *update_post_list(struct post_list_node *post_list_head, struct word *current_word);
