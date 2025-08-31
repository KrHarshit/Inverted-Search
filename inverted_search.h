#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>

#define FAILURE -1
#define SUCCESS 0
#define FNAME_SIZE 15
#define WORD_SIZE 50
#define FILE_EMPTY -2
#define FILE_NOTAVAILABLE -3
#define REPEATATION -4

typedef struct file_node
{
    char file_name[FNAME_SIZE];
    struct file_node *link;
}Flist;

typedef struct linkTable_node
{
    int word_count;
    char file_name[FNAME_SIZE];
    struct linkTable_node *table_link;
}Ltable;

typedef struct word_node
{
    int file_count;
    char word[WORD_SIZE];
    struct word_node *link;
    struct Ltable *Tlink;
}Wlist;

int create_list_of_files(Flist **f_head, char *name);
void create_database(Flist *f_head, Wlist *head[]);
Wlist *read_datafile(Flist *file, Wlist *head[], char *filename);
int insert_at_last(Wlist **head, char *data);
int update_link_table(Wlist **head);
int update_word_count(Wlist **head, char *filename);
int print_word_count(Wlist *head);
int search(Wlist *head, char *word);
void display_database(Wlist *head[]);
void save_database(Wlist *head[]);
void write_databasefile(Wlist *head, FILE *databasefile);
void update_database(Wlist *head[], Flist **f_head);
int isFileEmpty(char *filename);
void file_validation_n_file_list(Flist **f_head, char *argv[]);
void clean_word(char *word);

#endif