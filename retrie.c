#include <stdio.h>
#include <stdlib.h>
#include "retrie.h"
#include "map.h"

//node for the head of map list
struct trie_node *trie_node_head = NULL;

//make a new trie node and zero initialize them
struct trie_node *new_trie_node(char character)
{
        struct trie_node *trie_node_current = (struct trie_node *) malloc(sizeof(struct trie_node));
        trie_node_current->key = character;
        trie_node_current->right_node = NULL;
        trie_node_current->down_node = NULL;
        trie_node_current->end = NO;
        return trie_node_current;
}


struct trie_node * insert_char_to_trie(struct trie_node *root, char character, int i)
{
       struct trie_node *trie_node_current = NULL;

       if (root == NULL)
       {
               return (new_trie_node(character));
       }


       if (i==0)
       {
               //for first stage only
               while(1)
               {
                       //character is here
                       if(root->key == character)
                       {
                               return root;
                       }
                       //character isn't here but I have more right nodes
                       else if ((root->key != character) && (root->right_node != NULL))
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
       {
               //for other stages
               while(1)
               {
                       if(root->down_node == NULL)
                       {
                               /*if (root->right_node == NULL)
                               {
                                       root->right_node = new_trie_node(character);
                                       return root->right_node;
                               }
                               else
                               {*/
                                       root->down_node = new_trie_node(character);
                                       return root->down_node;
                               /*}*/
                       }
                       else if (root->down_node->key == character)
                       {
                               return root->down_node;
                       }
                       else
                       {
                               if (root->down_node->right_node == NULL)
                               {
                                       root->down_node->right_node = new_trie_node(character);
                                       return root->down_node->right_node;
                               }
                               else if (root->down_node->right_node->key != character)
                               {
                                       root = root->down_node->right_node;
                                       continue;
                               }
                               else
                               {
                                       return root->right_node;
                               }

                       }
               }
       }


       return trie_node_current;
}

int insert_word_to_trie(struct word *current_word)
{
        struct trie_node *trie_node_current = trie_node_head;


        for (int i=0; i < current_word->word_length; i++)
        {
                if(current_word->actual_word[i] != '\0')
                trie_node_current = insert_char_to_trie(trie_node_current, current_word->actual_word[i], i);
        }

        trie_node_current->end = YES;
        //update_posting_list(trie_node_current->posting_list_node,current_word);

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
        }
        return trie_node_head;
}

