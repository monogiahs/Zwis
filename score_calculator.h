#ifndef _SCORE_CALCULATOR_H_
#define _SCORE_CALCULATOR_H_

#include "stdio.h"
#include "map.h"

#define k1 1.2
#define b 0.75

double  inverse_document_frequency(struct word *current_word);
double average_document_length(void);
void zero_initialize_all_scores(void);
void score_calculator(struct word *current_word);
void call_calculations(struct word* current_word);

#endif /* _SCORE_CALCULATOR_H_ */
