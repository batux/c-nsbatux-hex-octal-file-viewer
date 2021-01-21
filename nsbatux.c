/*
    Batuhan Düzgün - 22.01.2021
    nsbatux: file content viewer in hexadecimal or octal format.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>

#define VERSION_DESC            "@Copyright 2021 - Version 1.0 - MIT License Custom nsbatux software module. Developed by Batuhan Düzgün\n"


#define HELP_DESC               " ******** HELP DOCUMENT ********\n" \
                                " Sample usage: ‘nsbatux -A x -t x1 -N 100 helloworld.c‘ \n" \
                                " -A x (value required option) ‘x‘ or ‘o‘ => option values can be specified. \n" \
                                " -t x (value required option) ‘x‘ or ‘o‘ => option values can be specified. \n" \
                                " -p => it shows only printable characters. \n" \
                                " -n or --length (value required option) => it determines character length which will be printed in console. \n" \
                                " --help => it shows help document. \n" \
                                " --version => it shows version of software and developer details. \n"

#define OPTION_PATTERN          "A:t:n:p"
#define HEX_OCTAL_LINE_LENGTH   16

void parse_opts(int *argc, char *argv[], struct option *options,
                char **A_arg, char **t_arg, char **n_arg,
                int *result, int *error_flag, int *A_flag, int *t_flag, int *p_flag, int *n_flag, int *help_flag, int *version_flag);

void validity_check(int *error_flag, char *A_arg, char *t_arg, char *n_arg,
                    int *A_flag, int *t_flag, int *p_flag, int *n_flag, int *help_flag, int *version_flag);

void run(int *argc, char *argv[], char *A_arg, char *t_arg, char *n_arg,
         int *A_flag, int *t_flag, int *p_flag, int *n_flag, int *help_flag, int *version_flag);

int open_file(FILE **file, char *file_name);

void read_from_stdin();

void print_in_hex_or_octal_format(FILE *file, char *A_arg, char *t_arg, int *n_arg_val, int *p_flag);


int main(int argc, char *argv[])
{
    int result;
    int error_flag = 0;
    int A_flag, t_flag, p_flag, n_flag, help_flag, version_flag;
    char *A_arg = NULL, *t_arg = NULL, *n_arg = NULL;

    struct option options[] = {
        { "length", required_argument, NULL, 'n' },
        { "help", no_argument, NULL, 1 },
        { "version", no_argument, NULL, 2 },
        { 0, 0, 0, 0 }
    };

    A_flag = t_flag = p_flag = n_flag = help_flag = version_flag = 0;
    opterr = 0;

    parse_opts(&argc, argv, options, 
                &A_arg, &t_arg, &n_arg, &result, &error_flag,
                &A_flag, &t_flag, &p_flag, &n_flag, &help_flag, &version_flag);

    validity_check(&error_flag, A_arg, t_arg, n_arg, 
                   &A_flag, &t_flag, &p_flag, &n_flag, &help_flag, &version_flag);

    run(&argc, argv, A_arg, t_arg, n_arg, &A_flag, &t_flag, &p_flag, &n_flag, &help_flag, &version_flag);

    return 0;
}

void run(int *argc, char *argv[], char *A_arg, char *t_arg, char *n_arg,
         int *A_flag, int *t_flag, int *p_flag, int *n_flag, int *help_flag, int *version_flag)
{
    FILE *file = NULL;
    char *file_name;

    if(*help_flag)
    {
        printf("%s\n", HELP_DESC);
        return;
    }
    else if(*version_flag)
    {
        printf("%s\n", VERSION_DESC);
        return;
    }
    
    if( (*argc) == optind )
    {
        read_from_stdin();
        return;
    }

    int n_arg_val = EOF;
    int major_options_used = (*A_flag) + (*t_flag) + (*n_flag);
    if(major_options_used == 0)
    {
        *A_flag = *t_flag = *n_flag = 1;
        *A_arg = *t_arg = 'x';
    }

    if((*n_flag))
    {
        n_arg_val = atoi(n_arg);
        if(!n_arg_val)
        {
            n_arg_val = EOF;
        }
    }

    for (int i = optind; i < *argc; i++)
    {
        file_name = argv[i];
        int opened_file = open_file(&file, file_name);
        if(opened_file != 0)
        {
            continue;
        }

        printf("====> %s <====\n", file_name);
        print_in_hex_or_octal_format(file, A_arg, t_arg, &n_arg_val, p_flag);

        fclose(file);
    }
}

void print_in_hex_or_octal_format(FILE *file, char *A_arg, char *t_arg, int *n_arg_val, int *p_flag)
{
    int val;
    long byte_counter = 0;
    long printable_byte_counter = 0;
    long offset_counter = 0;
    char new_line = '\n';
    char space_line = ' ';
    char *printable_char_arr = NULL;
    const char *offset_text_format = (*A_arg) == 'x' ? "%07X    " : "%07o    ";
    const char *data_text_format = (*t_arg) == 'x' ? "%02X%c" : "%03o%c";
    
    if(*p_flag)
    {
        if ((printable_char_arr = (char *)malloc(HEX_OCTAL_LINE_LENGTH * sizeof(char))) == NULL) 
        {
            *p_flag = 0;
        }
    }

    if(file == NULL)
    {
        return;
    }

    fseek(file, 0, SEEK_SET);

    while( (val = fgetc(file)) != EOF && ( *n_arg_val == -1 ? 1 : (*n_arg_val) >  byte_counter) )
    {
        int line_step = byte_counter % HEX_OCTAL_LINE_LENGTH;
        if(line_step == 0)
        {
            if((*p_flag) && printable_byte_counter > 0)
            {   
                printf("  |");
                for(int i = 0; i < HEX_OCTAL_LINE_LENGTH; i++)
                {
                    printf("%c", printable_char_arr[i]);
                }
                printf("|\n");
                printable_byte_counter = 0;
            }
            printf(offset_text_format, offset_counter);
            offset_counter = offset_counter + HEX_OCTAL_LINE_LENGTH;
        }

        printf(data_text_format, val, 
                ( line_step == HEX_OCTAL_LINE_LENGTH - 1 ) ? ( (*p_flag) ? space_line : new_line ) : space_line );

        if((*p_flag))
        {
            printable_char_arr[printable_byte_counter] = (isprint(val) == 0) ? '.' : val;
            printable_byte_counter++;
        }
        byte_counter++;
    }

    if(byte_counter)
    {
        printf("\n");
    }

    if(*p_flag)
    {
        if(printable_char_arr != NULL)
        {
            free(printable_char_arr);
        }
    }
}

int open_file(FILE **file, char *file_name)
{
    if ((*file = fopen(file_name, "r")) == NULL) 
    {   
        fprintf(stderr, "file %s cannot open!..\n", file_name);
        return 1;
    }
    return 0;
}

void read_from_stdin()
{
    char ch;
    while(read(STDIN_FILENO, &ch, 1) > 0)
    {
        if(ch == '\n')
        {
            printf("%c",ch);
        }
    }
}

void validity_check(int *error_flag, char *A_arg, char *t_arg, char *n_arg,
                    int *A_flag, int *t_flag, int *p_flag, int *n_flag, int *help_flag, int *version_flag)
{
    if(*error_flag)
    {
        exit(EXIT_FAILURE);
    }

    int major_options_used = (*A_flag) + (*t_flag) + (*p_flag) + (*n_flag);

    if((*help_flag) && major_options_used > 0)
    {
        fprintf(stderr, "--help cannot be used with another option...\n");
        exit(EXIT_FAILURE);   
    }

    if((*version_flag) && major_options_used > 0)
    {
        fprintf(stderr, "--version cannot be used with another option...\n");
        exit(EXIT_FAILURE);
    }

    if((*A_flag) && !( *A_arg == 'x' || *A_arg == 'o' ))
    {
        fprintf(stderr, "-A can be used only with 'x' or 'o' option...\n");
        exit(EXIT_FAILURE);
    }

    if((*t_flag) && !( *t_arg == 'x' || *t_arg == 'o' ))
    {
        fprintf(stderr, "-t can be used only with 'x' or 'o' option...\n");
        exit(EXIT_FAILURE);
    }
    
    if((*n_flag))
    {
        int n_arg_val = atoi(n_arg);
        if(n_arg_val <= 0)
        {
            fprintf(stderr, "-n or --length can be used only with number...\n");
            exit(EXIT_FAILURE);
        }
    }
}

void parse_opts(int *argc, char *argv[], struct option *options,
                char **A_arg, char **t_arg, char **n_arg,
                int *result, int *error_flag, int *A_flag, int *t_flag, int *p_flag, int *n_flag, int *help_flag, int *version_flag)
{
    while( ( *result = getopt_long(*argc, argv, OPTION_PATTERN, options, NULL)) != -1 )
    {
        switch( (*result) )
        {
            case 'A':
                *A_flag = 1;
                *A_arg = optarg;
                break;
            case 't':
                *t_flag = 1;
                *t_arg = optarg;
                break;
            case 'n':
                *n_flag = 1;
                *n_arg = optarg;
                break;
            case 'p':
                *p_flag = 1;
                break;
            case 1:
                *help_flag = 1;
                break;
            case 2:
                *version_flag = 1;
                break;
            case '?':
                if(optopt == 'A')
                {
                    fprintf(stderr, "-A option must have an argument!\n");
                }
                else if(optopt == 't')
                {
                    fprintf(stderr, "-t option must have an argument!\n");
                }
                else if(optopt == 'n')
                {
                    fprintf(stderr, "-n or --length option must have an argument!\n");
                }
                else if(optopt != 0)
                {
                    fprintf(stderr, "invalid option -%c\n", optopt);
                }
                else
                {
                    fprintf(stderr, "invalid long option!\n");
                }
                *error_flag = 1;
                break;
        }
    }
}