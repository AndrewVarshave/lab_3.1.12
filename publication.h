#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <stdbool.h>

typedef struct {
    char title[50];
    char first_author_surname[50];
    char first_author_initials[50];
    char journal_name[50];
    int publication_year;
    int journal_volume;
    bool is_rints;
    int page_count;
    int citation_count;
} Publication;

#endif