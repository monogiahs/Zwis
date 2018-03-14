#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "map.h"
#include "doc_utils.h"
#include "command_line_utils.h"

//node for the head of map list
struct map_node *map_node_head = NULL;
//node for the tail of map list
struct map_node *map_node_tail = NULL;

//node for the head of map short list
struct map_short_node *map_short_node_head = NULL;
//node for the tail of map short list
struct map_short_node *map_short_node_tail = NULL;

struct map_node *map_node_current = NULL;

void initialize_to_zero_score_of_map_nodes(void)
{
        struct map_node *map_node_next = map_node_head;

        //case of empty map list
        if (map_node_next == NULL)
        {
                printf("EMPTY MAP LIST");
        }
        else
        {
                while(map_node_next != NULL)
                {
                        map_node_next->score = 0;
                        //go to the next map node
                        map_node_next = map_node_next -> next;
                }
        }
}

//make a new map_short node and zero initialize them
struct map_short_node *new_map_short_node(void)
{
        struct map_short_node *map_short_node_current = (struct map_short_node *) malloc(sizeof(struct map_short_node));
        map_short_node_current->next = NULL;
        map_short_node_current->id = 0;
        map_short_node_current->score = 0;
        return map_short_node_current;
}

struct map_node * get_map_list_head(void)
{
        return map_node_head;
}

void free_map_list(void)
{
        struct map_node *map_node_next = map_node_head;
        struct map_node *map_node_tmp = NULL;

        while (map_node_next != NULL)
        {
            map_node_tmp = map_node_next;
            //go to the next map node
            map_node_next = map_node_next->next;
            free(map_node_tmp);
        }

}

void free_replica(void)
{
    struct map_short_node* map_short_tmp;

    while(1)
    {
        map_short_tmp = map_short_node_head;
        if(map_short_node_head->next != NULL)
        {
            map_short_node_head = map_short_node_head->next;
            free(map_short_tmp);
        }

        else
        {
            free(map_short_tmp);
            map_short_node_head = NULL;
            return;
        }
    }
}

void print_map_list_node(struct map_node *map_node_next)
{
        //printf("Score = %f.    The id is %d and the text \"%.*s\"\n",map_node_next->score, map_node_next->id,map_node_next->text_length,map_node_next->text);
        printf("Score = %f.    The id is %d\n",map_node_next->score, map_node_next->id);
}

void print_map_short_list_node(struct map_short_node *map_short_node_next)
{
        //printf("Score = %f.    The id is %d and the text \"%.*s\"\n",map_node_next->score, map_node_next->id,map_node_next->text_length,map_node_next->text);
        printf("Score = %f.    The id is %d\n",map_short_node_next->score, map_short_node_next->id);
}

void print_map_list(void)
{
        struct map_node *map_node_next = map_node_head;

        //case of empty map list
        if (map_node_next == NULL)
        {
                printf("EMPTY MAP LIST");
        }
        else
        {
                while(map_node_next !=NULL)
                {
                        //print current map node
                        print_map_list_node(map_node_next);
                        //go to the next map node
                        map_node_next = map_node_next->next;
                }
        }
}

void print_map_short_list(void)
{
    struct map_short_node *map_short_node_next = map_short_node_head;

    //case of empty map list
    if (map_short_node_next == NULL)
    {
            printf("EMPTY MAP LIST");
    }
    else
    {
            while(map_short_node_next !=NULL)
            {
                    //print current map node
                    print_map_short_list_node(map_short_node_next);
                    //go to the next map node
                    map_short_node_next = map_short_node_next->next;
            }
    }
}



struct map_node * search_map_node_to_list_with_id(int id)
{
        struct map_node *map_node_next = map_node_head;

        //case of empty map list
        if(map_node_next == NULL)
        {
                printf("EMPTY MAP LIST");
        }
        else
        {
                while(map_node_next !=NULL)
                {
                        if (map_node_next->id == id)
                        {
                            return map_node_next;
                        }

                        //go to the next map node
                        map_node_next = map_node_next->next;
                }
        }
        return NULL;
}

void free_replicate_map_list(void)
{
        struct map_short_node *map_short_node_next = map_short_node_head;
        struct map_short_node *map_short_node_tmp = NULL;

        while (map_short_node_next != NULL)
        {
            map_short_node_tmp = map_short_node_next;
            //go to the next map node
            map_short_node_next = map_short_node_next->next;
            free(map_short_node_tmp);
        }
}


void get_top_k(struct map_short_node *tmp)
{
    struct map_short_node *map_current = map_short_node_head;
    int i, k, l;

    k = get_arg_k_val();
    l = get_numb_of_lines();
    //skip top
    for(i=1;i<=l-k;i++)
    {
        map_current = map_current->next;
    }
    for(i = k-1; i >= 0; i--)
    {
        tmp[i].id = map_current->id;
        tmp[i].score = map_current->score;
        tmp[i].next = NULL;
        map_current = map_current->next;
        printf("score (%f) with id %d\n", tmp[i].score, tmp[i].id);
    }
}

void create_replicate_map_list(void)
{
        struct map_node *map_node_next = map_node_head;
        struct map_short_node *map_short_node_current = NULL;

        //case of empty map list
        if(map_node_next == NULL)
        {
                printf("EMPTY MAP LIST");
                return;
        }
        else
        {
                while(map_node_next !=NULL)
                {
                        map_short_node_current = new_map_short_node();
                        map_short_node_current->id = map_node_next->id;
                        map_short_node_current->score = map_node_next->score;
                        map_short_node_current->next = map_short_node_head;
                        map_short_node_head = map_short_node_current;

                        //go to the next map node
                        map_node_next = map_node_next->next;
                }
        }
}

void swap_map_short_node(struct map_short_node *a, struct map_short_node *b)
{
    int temp_id = a->id;
    double temp_score = a->score;

    a->id = b->id;
    b->id = temp_id;
    a->score = b->score;
    b->score = temp_score;
}

void sort_replicate_map_list(void)
{
    int swapped;
    struct map_short_node *map_short_node_current;
    struct map_short_node *lptr = NULL;

    /* Checking for empty list */
    if (map_short_node_head == NULL)
    {
            printf("EMPTY MAP SHORT LIST");
            return;
    }

    do
    {
        swapped = 0;
        map_short_node_current = map_short_node_head;

        while (map_short_node_current->next != lptr)
        {
            if (map_short_node_current->score > map_short_node_current->next->score)
            {
                    swap_map_short_node(map_short_node_current, map_short_node_current->next);
                swapped = 1;
            }
            map_short_node_current = map_short_node_current->next;
        }
        lptr = map_short_node_current;
    }
    while (swapped);
}

int add_map_node_to_list(int number_of_character_line,int number_of_line, FILE* fp)
{
        struct map_node *map_node_next;

        if (number_of_line == 0)
        {
                //allocate first map_node
                map_node_next = (struct map_node*) malloc(sizeof(struct map_node) + number_of_character_line*sizeof(char) + 1*sizeof(char));
                memset(map_node_next, 0, (sizeof(struct map_node) + number_of_character_line*sizeof(char) + 1*sizeof(char)));
                //Memory allocated is sizeof(struct)+(length of array)*sizeof(char)+1*sizeof("\0")
                if(map_node_next == NULL)
                {
                    printf("Not enough memory in heap\n");
                    exit(EXIT_FAILURE);
                }

                //initialize fields
                //add 1 in text_length for character \n
                map_node_next->text_length = number_of_character_line + 1;
                fread(map_node_next->text, 1, number_of_character_line, fp);
                //add "\n" character to end of each line
                strcat(map_node_next->text, "\0");
                //map_node_next->text[map_node_next->text_length] = '\0';
                map_node_next->id = number_of_line;
                map_node_next->next = NULL;
                map_node_head = map_node_next;
                map_node_tail = map_node_next;
                //set fp to the new line
                fseek(fp, 1, SEEK_CUR);
        }
        else
        {
                //allocate map_node
                map_node_next = (struct map_node*) malloc(sizeof(struct map_node) + number_of_character_line*sizeof(char) + 1*sizeof(char));
                memset(map_node_next, 0, (sizeof(struct map_node) + number_of_character_line*sizeof(char) + 1*sizeof(char)));
                //Memory allocated is sizeof(struct)+(length of array)*sizeof(char)+1*sizeof("\0")
                if(map_node_next == NULL)
                {
                    printf("Not enough memory in heap\n");
                    exit(EXIT_FAILURE);
                }

                //initialize fields
                //add 1 in text_length for character \n
                map_node_next->text_length = number_of_character_line + 1;
                fread(map_node_next->text, 1, number_of_character_line, fp);
                //add "\n" character to end of each line
                strcat(map_node_next->text, "\0");
                //map_node_next->text[map_node_next->text_length] = '\0';
                map_node_next->id = number_of_line;
                map_node_next->next = NULL;
                map_node_tail->next = map_node_next;
                map_node_tail = map_node_next;
                //set fp to the new line
                fseek(fp, 1, SEEK_CUR);
        }
        //printf("The numb of chars in line %d is %d\n", number_of_line, number_of_character_line);
        //printf("%.*s>>>\n", number_of_character_line + 1, map_node_head->text);


        //printf("%d\n", map_node_next->number_of_words = get_words_per_line(map_node_next));

        map_node_next->number_of_words = get_words_per_line(map_node_next);
        return 0;
}

struct map_node *load_map_list(char *docfile)
{
        FILE *fp;
        int numb_of_lines;
        int numb_of_chars_per_line;

        //open file
        fp = fopen(docfile, "r");
        if (!fp)
        {
                printf("can not open file \n");
                return 0;
        }

        //get the number of lines of the document
        numb_of_lines = get_numb_of_lines();

        for (int i = 0; i < numb_of_lines; i++)
        {
                //for each line i, get the number of characters
                numb_of_chars_per_line = get_numb_of_chars_per_line(fp);
                //add node to map list
                add_map_node_to_list(numb_of_chars_per_line, i, fp);
        }

        //close file
        fclose(fp);
        //return the head of the map list
        return map_node_head;
}

void set_word(void)
{
    map_node_current = map_node_head;
}

struct word *get_word(void)
{
        static int i;

        int temp, j, temp_j;
        temp = 0;
        j = 0;
        temp_j = 0;

        struct word *current_word;

        if(map_node_current == NULL)
            return NULL;

        //first word in line
        if(i == 0)
        {
            while(i < map_node_current->text_length)
            {
                while(map_node_current->text[i] != ' ' && map_node_current->text[i] != '\t')
                {
                    i++;
                    //j is number of characters of word
                    j++;
                    if(i == map_node_current->text_length)
                        break;
                }
                if(i == map_node_current->text_length)
                    break;
                if((map_node_current->text[i] == ' ' || map_node_current->text[i] == '\t') && j != 0)
                    break;
                i++;
            }
            //Memory allocated is sizeof(struct)+(length of word)*sizeof(char)+1*sizeof("\0")
            current_word = (struct word*) malloc(sizeof(struct word) + j*sizeof(char) + 1*sizeof(char));
            memset(current_word, 0, (sizeof(struct word) + j*sizeof(char) + 1*sizeof(char)));
            if(current_word == NULL)
            {
                printf("Not enough memory in heap\n");
                exit(EXIT_FAILURE);
            }

            //fill word struct
            current_word->number_of_line = map_node_current->id;
            current_word->word_length = j + 1;
            for(temp=i-j;temp<=i-1;temp++)
            {
                current_word->actual_word[temp_j] = map_node_current->text[temp];
                temp_j++;
            }
            strcat(current_word->actual_word, "\0");
        }
        //not first word in line
        else
        {
            while(i < map_node_current->text_length)
            {
                while(map_node_current->text[i] != ' ' && map_node_current->text[i] != '\t')
                {
                    i++;
                     //j is number of characters of word
                    j++;
                    if(i == map_node_current->text_length)
                        break;
                }
                if(i == map_node_current->text_length)
                    break;
                if((map_node_current->text[i] == ' ' || map_node_current->text[i] == '\t') && j != 0)
                    break;
                i++;
            }
            //Memory allocated is sizeof(struct)+(length of word)*sizeof(char)+1*sizeof("\n")
            current_word = (struct word*) malloc(sizeof(struct word) + j*sizeof(char) + 1*sizeof(char));
            memset(current_word, 0, (sizeof(struct word) + j*sizeof(char) + 1*sizeof(char)));
            if(current_word == NULL)
            {
                printf("Not enough memory in heap\n");
                exit(EXIT_FAILURE);
            }

            //fill word struct
            current_word->number_of_line = map_node_current->id;
            current_word->word_length = j+1;
            for(temp=i-j;temp<=i-1;temp++)
            {
                current_word->actual_word[temp_j] = map_node_current->text[temp];
                temp_j++;
            }
            strcat(current_word->actual_word, "\0");
        }


        if(map_node_current->text[i-1] == '\0')
        {
            map_node_current = map_node_current->next;
            i = 0;
        }

        //printf("%d\t%d\t%s\n",
        //current_word->number_of_line, current_word->word_length,
        //current_word->actual_word);


        return current_word;
}



int get_words_per_line(struct map_node *map_node_next)
{
    int wchars, words, i;
    i = 0;
    words = 0;
    wchars = 0;

    while(map_node_next->text[i] != '\0')
    {
        if(map_node_next->text[i] != ' ' && map_node_next->text[i] != '\t' && map_node_next->text[i] != '0')
        {
            wchars++;
        }
        else if((map_node_next->text[i] == ' ' || map_node_next->text[i] == '\t' || map_node_next->text[i] == '0') && wchars != 0)
        {
            words++;
            wchars = 0;
        }
        i++;
    }
    return words + 1;
}

