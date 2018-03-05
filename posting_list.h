#ifndef _POSTING_LIST_H_
#define _POSTING_LIST_H_

struct posting_list_node
{
        int line_id;
        int freq;
        struct posting_list_node *post_next;
};

#endif /* _POSTING_LIST_H_ */

