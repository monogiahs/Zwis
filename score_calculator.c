#include <math.h>

#include "score_calculator.h"
#include "map.h"
#include "doc_utils.h"
#include "retrie.h"

struct map_short_node top_k[10];


double  inverse_document_frequency(struct word *current_word)
{
        double IDF;
        int nqi;
        int N;

        N = get_numb_of_lines();
        nqi = get_line_id_counter(current_word);
        IDF = log((N - nqi + 0.5)/(nqi + 0.5));

        return IDF;
}


double average_document_length(void)
{
        double avgdl;
        avgdl = ((double)total_word_counter) / get_numb_of_lines();
        return avgdl;
}

void zero_initialize_all_scores(void)
{
        initialize_to_zero_score_of_map_nodes();
}

void score_calculator(struct word *current_word)
{
        struct map_node *map_temp = NULL;
        struct trie_node *trie_temp = NULL;
        struct post_list_node *post_temp = NULL;
        double temp_score = 0;
        double idf = 0;
        int fqid = 0;
        double avgdl = 0;
        int D = 0;
        double num;
        double denom;

        trie_temp = search_word_to_trie(current_word);

        if (trie_temp == NULL)
        {
                printf("NOT_FOUND");
                return;
        }
        else
        {
                post_temp = trie_temp->post_list_head;
                while (post_temp != NULL)
                {
                        idf = inverse_document_frequency(current_word);
                        fqid = post_temp->freq;
                        avgdl = average_document_length();
                        map_temp = search_map_node_to_list_with_id(post_temp->line_id);
                        D = map_temp->number_of_words;
                        num = (idf * fqid * (k1 + 1));
                        denom = (fqid +(k1 * (1 - b + (b * (D/avgdl)))));

                        temp_score = num / denom;
                        map_temp->score += temp_score;
                        post_temp = post_temp->post_next;
                }

        }

}


void call_calculations(struct word* current_word)
{
    struct word* current_word_tmp = current_word;

    zero_initialize_all_scores();
    while(current_word_tmp != NULL)
    {
        score_calculator(current_word_tmp);
        current_word_tmp = current_word_tmp->word_next;
    }
    //print_map_list();
    create_replicate_map_list();
    //print_map_short_list();
    sort_replicate_map_list();
    print_map_short_list();
    get_top_k(top_k);
    free_replica();
}








