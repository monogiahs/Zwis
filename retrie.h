#ifndef _RETRIE_H_
#define _RETRIE_H_

#include "posting_list.h"
#include "map.h"

#define YES 1
#define NO 0

#define FOUND 1
#define NOT_FOUND 0

struct trie_node
{
        int last_text_id;
        int line_id_counter;
        char key;
        struct trie_node *right_node;
        struct trie_node *down_node;
        struct post_list_node *post_list_head;
        int end;
        int printed;
        int text_length;
        char text[0];
};

struct trie_node *new_trie_node(char character, int word_length);

void clean_trie(void);

void free_trie(struct trie_node *root);

void df_print_retrie(void);

void print_retrie(struct trie_node *root);

struct trie_node *insert_char_to_trie(struct trie_node *root, char character, int i, int word_length);

struct trie_node *search_word_to_trie(struct word *current_word);

int insert_word_to_trie(struct word *current_word);

struct trie_node *load_retrie(void);

#endif /* _RETRIE_H_ */

