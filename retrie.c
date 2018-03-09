#include <stdio.h>
#include <stdlib.h>
#include "retrie.h"
#include "map.h"

//head node for map list
struct trie_node *trie_node_head = NULL;

//make a new trie node and zero initialize them
struct trie_node *new_trie_node(char character)
{
        struct trie_node *trie_node_current = (struct trie_node *) malloc(sizeof(struct trie_node));
        trie_node_current->key = character;
        trie_node_current->right_node = NULL;
        trie_node_current->down_node = NULL;
        trie_node_current->post_list_head = NULL;
        trie_node_current->end = NO;
        return trie_node_current;
}

void clean_trie(void)
{
        free_trie(trie_node_head);
}

void free_trie(struct trie_node *root)
{
        if (root->right_node != NULL)
        {
                free_trie(root->right_node);
        }
        if (root->down_node != NULL)
        {
                free_trie(root->down_node);
        }
        if (root->post_list_head != NULL)
        {
                //free_post_list(root->post_list_head);
        }
        free(root);
}

struct trie_node *search_char_to_trie(struct trie_node *root, char character, int i)
{
        static int previous;
        if (root == NULL)
        {
                return NULL;
        }

        if (i==0)
        {//for first stage only
               while(1)
               {
                       //character is here
                       if(root->key == character)
                       {
                               return root;
                       }
                       //character isn't here but I have more right nodes
                       else if((root->key != character) && (root->right_node != NULL))
                       {
                               root = root->right_node;
                       }
                       //character isn't here but and I don't have more right nodes
                       else
                       {
                               return NULL;
                       }
               }
         }
         else
         {//for other stages

                 previous = FOUND;
                 while(1)
                 {
                         if(previous == FOUND)//previous found
                         {
                                 if(root->down_node != NULL)
                                 {
                                         if(root->down_node->key == character)
                                         {
                                                 previous = FOUND;
                                                 return root->down_node;
                                         }
                                         else
                                         {
                                                 if(root->down_node->right_node != NULL)
                                                 {
                                                         root = root->down_node->right_node;
                                                         previous = NOT_FOUND;
                                                 }
                                                 else
                                                 {
                                                         previous = NOT_FOUND;
                                                         return NULL;
                                                 }
                                         }
                                 }
                                 else
                                 {
                                         previous = NOT_FOUND;
                                         return NULL;
                                 }
                         }
                         else//previous not found
                         {
                                 if(root->key == character)
                                 {
                                         previous = FOUND;
                                         return root;
                                 }
                                 else
                                 {
                                         if(root->right_node != NULL)
                                         {
                                                 previous = NOT_FOUND;
                                                 root = root->right_node;
                                         }
                                         else
                                         {

                                                 previous = NOT_FOUND;
                                                 return NULL;
                                         }
                                 }
                         }

                 }
         }
  }

struct trie_node *search_word_to_trie(struct word *current_word)
{
        struct trie_node *trie_node_current = trie_node_head;

        if (current_word == NULL)
        {
                return NULL;
        }

        for (int i=0; i < current_word->word_length; i++)
        {
                if(current_word->actual_word[i] != '\0')
                {
                        trie_node_current = search_char_to_trie(trie_node_current, current_word->actual_word[i], i);
                }
                if (trie_node_current == NULL)
                {
                        return NULL;
                }

        }

        if (trie_node_current->end == YES)
        {
                return trie_node_current;
        }
        else
        {
                return NULL;
        }
}


struct trie_node * insert_char_to_trie(struct trie_node *root, char character, int i)
{
//
       static int previous = NOT_FOUND;

       if (root == NULL)
       {
               trie_node_head = new_trie_node(character);
               return (trie_node_head);
       }


       if (i==0)
       {//for first stage only
               while(1)
               {
                       //character is here
                       if(root->key == character)
                       {
                               return root;
                       }
                       //character isn't here but I have more right nodes
                       else if((root->key != character) && (root->right_node != NULL))
                       {
                               root = root->right_node;
                               continue;
                       }
                       //character isn't here but and I don't have more right nodes (create one and initialize them)
                       else
                       {
                               root->right_node = new_trie_node(character);
                               return root->right_node;
                       }
               }
       }
       else
       {//for other stages

               previous = FOUND;
               while(1)
               {
                       if(previous == FOUND)//previous found
                       {
                               if(root->down_node != NULL)
                               {
                                       if(root->down_node->key == character)
                                       {
                                               previous = FOUND;
                                               return root->down_node;
                                       }
                                       else
                                       {
                                               if(root->down_node->right_node != NULL)
                                               {
                                                       root = root->down_node->right_node;
                                                       previous = NOT_FOUND;
                                               }
                                               else
                                               {
                                                       root->down_node->right_node = new_trie_node(character);
                                                       previous = FOUND;
                                                       return root->down_node->right_node;
                                               }
                                       }
                               }
                               else
                               {
                                       root->down_node = new_trie_node(character);
                                       previous = FOUND;
                                       return root->down_node;
                               }
                       }
                       else//previous not found
                       {
                               if(root->key == character)
                               {
                                       previous = FOUND;
                                       return root;
                               }
                               else
                               {
                                       if(root->right_node != NULL)
                                       {
                                               previous = NOT_FOUND;
                                               root = root->right_node;
                                       }
                                       else
                                       {
                                               root->right_node = new_trie_node(character);
                                               previous = FOUND;
                                               return root->right_node;
                                       }
                               }
                       }

                       }
               }
}


int insert_word_to_trie(struct word *current_word)
{
        int dummy = 0;
        //from the root
        struct trie_node *trie_node_current = trie_node_head;

        for (int i=0; i < current_word->word_length; i++)
        {
                if(current_word->actual_word[i] != '\0')
                trie_node_current = insert_char_to_trie(trie_node_current, current_word->actual_word[i], i);
        }

        trie_node_current->end = YES;
        trie_node_current->post_list_head = update_post_list(trie_node_current->post_list_head,current_word);
        return dummy;
}

struct trie_node *load_retrie(void)
{
        struct word *current_word;
        set_word();
        while(1)
        {
                current_word = get_word();
                if (current_word == NULL)
                {
                        break;
                }
                insert_word_to_trie(current_word);
                free(current_word);
        }
        return trie_node_head;
}

