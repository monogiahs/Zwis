#ifndef _MAP_H_
#define _MAP_H_

struct map_node
{
    struct map_node* next;
    int id;
    int text_length;
    char text[0];
};

void free_map_list(void);

void print_map_list_node(struct map_node *map_node_next);

void print_map_list(void);

int add_map_node_to_list(int numb_of_chars_per_line,int numb_of_line, FILE* fp);

struct map_node *load_map_list(char *docfile);

#endif /* _MAP_H_ */
