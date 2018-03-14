#ifndef _MAP_H_
#define _MAP_H_

struct map_node
{
    struct map_node* next;
    int id;
    int text_length;
    int number_of_words;
    double score;
    char text[0];
};

struct map_short_node
{
        struct map_short_node* next;
        int id;
        double score;
};

struct word
{
    struct word* word_next;
    int number_of_line;
    int word_length;
    char actual_word[0];
};

void initialize_to_zero_score_of_map_nodes(void);

struct map_node * get_map_list_head(void);

void free_map_list(void);

void free_replica(void);

void print_map_list_node(struct map_node *map_node_next);

void print_map_list(void);

//void search_word_to_map_node(struct post_list_node *cli_post_node, struct word *cli_word);

void print_map_short_list(void);

struct map_node * search_map_node_to_list_with_id(int id);

void free_replicate_map_list(void);

void sort_replicate_map_list(void);

void get_top_k(struct map_short_node *tmp);

void create_replicate_map_list(void);

int add_map_node_to_list(int numb_of_chars_per_line,int numb_of_line, FILE* fp);

struct map_node *load_map_list(char *docfile);

struct word *get_word(void);

void set_word(void);

int get_words_per_line(struct map_node *map_node_next);

#endif /* _MAP_H_ */
