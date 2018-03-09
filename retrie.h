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
        char key;
        struct trie_node *right_node;
        struct trie_node *down_node;
        struct post_list_node *post_list_head;
        int end;
};

void clean_trie(void);

void free_trie(struct trie_node *root);

struct trie_node *search_char_to_trie(struct trie_node *root, char character, int i);

struct trie_node *search_word_to_trie(struct word *current_word);

int insert_word_to_trie(struct word *current_word);

struct trie_node *load_retrie(void);

#endif /* _RETRIE_H_ */

