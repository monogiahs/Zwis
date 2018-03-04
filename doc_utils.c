#include <stdio.h>
#include "doc_utils.h"

#define linux_machine

int number_of_lines;

void set_numb_of_lines(FILE *fp)
{
    int c, lc;

    lc = 0;
    while(1)
    {
            c = fgetc( fp );
            if ( c == '\n' )
            {
                    lc++;
            }
            else if (c == EOF)
            {
                    break;
            }
    }

    fseek(fp, 0, SEEK_SET);
    number_of_lines = lc;
}


int get_numb_of_lines(void)
{
        return (number_of_lines);
}

int get_line_numb(FILE *fp)
{
        int numb,c;

        fscanf(fp, "%d", &numb);
        //go to the end of the line
        while(1)
        {
                c = fgetc( fp );
                if ( c == '\n' )
                {
                        break;
                }
        }
        return numb;
}

int check_line_numbs(FILE *fp, int numb_of_lines)
{
        for (int i = 0; i < numb_of_lines; i++)
        {
               if (get_line_numb(fp) != i)
               {
                       return -1;
               }
        }
        return 0;
}

int validate_doc(char *docfile)
{
        FILE *fp;

        fp = fopen(docfile, "r");
        if (!fp)
        {
                printf("can not open file \n");
                return 0;
        }

        set_numb_of_lines(fp);

        if (check_line_numbs(fp, get_numb_of_lines()) == -1)
        {
                printf("invalid file \n");
                return 0;
        }



        fclose(fp);
        return 1;
}

void skip_space_chars(FILE *fp)
{
        int c;
        while(1)
        {
                c = fgetc(fp);
                if ( c != ' ' )
                {
                        break;
                }
        }
        fseek(fp, -1, SEEK_CUR);
}

int get_numb_of_chars_per_line(FILE *fp)
{
        int c, clc, numb;
        clc = 0;

        fscanf(fp, "%d", &numb);

        skip_space_chars(fp);
        while(1)
        {
                c = fgetc(fp);
#ifdef linux_machine
                if ( c != '\r' )
#else
                if ( c != '\n' )
#endif
                {
                        clc++;
                }
                else
                {
                        break;
                }
        }
#ifdef linux_machine
        fseek(fp, -(clc+1), SEEK_CUR);
#else
        fseek(fp, -(clc+2), SEEK_CUR);
#endif
        //for windows -(clc+2)  for linux -(clc+1)
        return clc;

}
