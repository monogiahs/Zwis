#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "map.h"
#include "doc_utils.h"

//node for the head of map list
struct map_node *map_node_head = NULL;
//node for the tail of map list
struct map_node *map_node_tail = NULL;


void free_map_list(void)
{
        struct map_node *map_node_next = map_node_head;
        struct map_node *map_node_tmp = NULL;

        while (map_node_next != NULL)
        {
            map_node_tmp = map_node_next;
            map_node_next = map_node_next->next;
            free(map_node_tmp);
        }

}

void print_map_list_node(struct map_node *map_node_next)
{
        printf("The id is %d and the text \"%.*s\"\n",map_node_next->id,map_node_next->text_length,map_node_next->text);
}

void print_map_list(void)
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
                        //print current map node
                        print_map_list_node(map_node_next);
                        //go to the next map node
                        map_node_next = map_node_next->next;
                }
        }
}

int add_map_node_to_list(int number_of_character_line,int number_of_line, FILE* fp)
{
        struct map_node *map_node_next = NULL;

        if (number_of_line == 0)
        {
                //allocate first map_node
                map_node_next = (struct map_node*) malloc(sizeof(struct map_node) + number_of_character_line*sizeof(char) + 1*sizeof(char));
                //Memory allocated is sizeof(struct)+(length of array)*sizeof(char)+1*sizeof("\n")


                if(map_node_next == NULL)
                {
                    printf("Not enough memory in heap\n");
                    exit(EXIT_FAILURE);
                }

                //initialize fields
                //add 1 in text_length for character \n
                map_node_next->text_length = number_of_character_line + 1;
                fread(map_node_next->text, 1, number_of_character_line, fp);
                //add NULL character to end of each line
                strcat(map_node_next->text, "\n");
                map_node_next->id = number_of_line;
                map_node_next->next = NULL;
                map_node_head = map_node_next;
                map_node_tail = map_node_next;
                //set fp to the new line
                fseek(fp, 1, SEEK_CUR);
                printf("The numb of chars in line %d is %d\n", number_of_line, number_of_character_line);
                printf("%.*s>>>\n", number_of_character_line + 1, map_node_head->text);
        }
        else
        {
                //allocate map_node
                map_node_next = (struct map_node*) malloc(sizeof(struct map_node) + number_of_character_line*sizeof(char) + 1*sizeof(char));
                //Memory allocated is sizeof(struct)+(length of array)*sizeof(char)+1*sizeof("\n")

                if(map_node_next == NULL)
                {
                    printf("Not enough memory in heap\n");
                    exit(EXIT_FAILURE);
                }

                //initialize fields
                //add 1 in text_length for character \n
                map_node_next->text_length = number_of_character_line + 1;
                fread(map_node_next->text, 1, number_of_character_line, fp);
                //add NULL character to end of each line
                strcat(map_node_next->text, "\n");
                map_node_next->id = number_of_line;
                map_node_next->next = NULL;
                map_node_tail->next = map_node_next;
                map_node_tail = map_node_next;
                //set fp to the new line
                fseek(fp, 1, SEEK_CUR);
                printf("The numb of chars in line %d is %d\n", number_of_line, number_of_character_line);
                printf("%.*s>>>\n", number_of_character_line + 1, map_node_next->text);

        }
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
