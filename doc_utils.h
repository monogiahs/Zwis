#ifndef _DOC_UTILS_H_
#define _DOC_UTILS_H_

void set_numb_of_lines(FILE *fp);

int get_numb_of_lines(void);

int get_line_numb(FILE *fp);

int check_line_numb(FILE *fp, int number_of_lines);

int validate_doc(char *docfile);

//get fp and number of line and returns number of chars of current line and fp in start of current line
int get_numb_of_chars_per_line(FILE *fp);

int get_words_per_line(FILE *fp);

#endif /* _DOC_UTILS_H_ */

