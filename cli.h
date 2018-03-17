#ifndef _CLI_H_
#define _CLI_H_

#include "map.h"

struct word *get_word_list();

void command_line_user(void);

void free_all(void);

void add_word_to_list(struct word* cli_word);

void free_word_list(void);

#endif /* _CLI_H_ */
