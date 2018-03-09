#include<stdio.h>
#include<stdlib.h>

#include "posting_list.h"
#include "map.h"

//head node for posting_list
//struct post_list_node *post_list_head = NULL;

//create a new posting list node and initialize it
struct post_list_node *new_list_node()
{
    struct post_list_node *list_node_current = (struct post_list_node *) malloc(sizeof(struct post_list_node));
    list_node_current->line_id = 0;
    list_node_current->freq = 0;
    list_node_current->post_next = NULL;
    return list_node_current;
}


struct post_list_node *update_post_list(struct post_list_node *post_list_head, struct word *current_word)
{

    struct post_list_node *post_list_temp;
    post_list_temp = post_list_head;

    while(1)
    {
        //first word in posting_list
        if(post_list_temp == NULL)
        {
            post_list_temp = new_list_node();
            post_list_temp->line_id = current_word->number_of_line;
            post_list_temp->freq++;
            return post_list_temp;
        }
        //same word in posting list, but not first
        else if(post_list_temp != NULL && post_list_temp->post_next == NULL)
        {
            //same word, same line
            if(post_list_temp->line_id == current_word->number_of_line)
            {
                post_list_temp->freq++;
                return post_list_head;
            }
            //same word, different line
            else
            {
                post_list_temp->post_next = new_list_node();
                post_list_temp->post_next->line_id = current_word->number_of_line;
                post_list_temp->post_next->freq++;
                return post_list_head;
            }
        }
        //point to post_next to continue searching
        else
            post_list_temp = post_list_temp->post_next;
    }
}

