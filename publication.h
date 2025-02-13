#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <stdbool.h>

#define MAX_STRING_LENGTH 256

typedef struct {
    char title[MAX_STRING_LENGTH];
    char first_author_surname[MAX_STRING_LENGTH];
    char first_author_initials[MAX_STRING_LENGTH];
    char journal_name[MAX_STRING_LENGTH];
    int publication_year;
    int journal_volume;
    bool is_rints;
    int page_count;
    int citation_count;
} Publication;

#endif