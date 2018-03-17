#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "posting_list.h"
#include "map.h"

//head node for posting_list
//struct post_list_node *post_list_head = NULL;

//create a new posting list node and initialize it
struct post_list_node *new_list_node(int word_length)
{
    struct post_list_node *list_node_current = (struct post_list_node *) malloc(sizeof(struct post_list_node) + word_length*sizeof(char) + 1*sizeof(char));
    list_node_current->line_id = 0;
    list_node_current->freq = 0;
    list_node_current->post_next = NULL;
    list_node_current->first_line_id = -1;
    return list_node_current;
}

void free_post_list(struct post_list_node *post_list_head)
{
    if(post_list_head->post_next != NULL)
        free_post_list(post_list_head->post_next);
    free(post_list_head);
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
            post_list_temp = new_list_node(current_word->word_length);
            post_list_temp->first_line_id = current_word->number_of_line;
            memcpy(post_list_temp->actual_word, current_word->actual_word, current_word->word_length);
            //strcpy(post_list_temp->actual_word, current_word->actual_word);
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
                post_list_temp->post_next = new_list_node(0);
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


struct post_list_node *search_post_list(struct post_list_node *post_list_head, struct word *cli_word)
{
    while(1)
    {
        if(post_list_head == NULL)
            return NULL;
        if(post_list_head->line_id == cli_word->number_of_line)
            return post_list_head;
        else
            post_list_head = post_list_head->post_next;

    }
}



