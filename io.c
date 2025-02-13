#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_stack_from_csv(Stack *stack, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    char line[1024];
    if (fgets(line, sizeof(line), fp) == NULL){
        fclose(fp);
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) {
        Publication pub;
        char *token = strtok(line, ",");
        if (!token) break;
        strncpy(pub.title, token, MAX_STRING_LENGTH - 1);
        pub.title[MAX_STRING_LENGTH - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token) break;
        strncpy(pub.first_author_surname, token, MAX_STRING_LENGTH - 1);
         pub.first_author_surname[MAX_STRING_LENGTH - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token) break;
        strncpy(pub.first_author_initials, token, MAX_STRING_LENGTH - 1);
        pub.first_author_initials[MAX_STRING_LENGTH - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token) break;
        strncpy(pub.journal_name, token, MAX_STRING_LENGTH - 1);
        pub.journal_name[MAX_STRING_LENGTH - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token) break;
        pub.publication_year = atoi(token);

        token = strtok(NULL, ",");
        if (!token) break;
        pub.journal_volume = atoi(token);

        token = strtok(NULL, ",");
        if (!token) break;
        pub.is_rints = (strcmp(token, "TRUE") == 0 || strcmp(token, "YES") == 0 || strcmp(token, "1") == 0);

        token = strtok(NULL, ",");
        if (!token) break;
        pub.page_count = atoi(token);

        token = strtok(NULL, ",");
        if (!token) break;
        pub.citation_count = atoi(token);

        stack_push(stack, pub);
    }

    fclose(fp);
    return 0;
}

void write_stack_to_csv(const Stack *stack, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    fprintf(fp, "Title,First Author Surname,First Author Initials,Journal Name,Publication Year,Journal Volume,Is RINTS,Page Count,Citation Count\n"); // Header

    for (int i = 0; i < stack_size(stack); ++i) {
        Publication pub = stack->data[i];
        fprintf(fp, "%s,%s,%s,%s,%d,%d,%s,%d,%d\n",
            pub.title, pub.first_author_surname, pub.first_author_initials, pub.journal_name,
            pub.publication_year, pub.journal_volume, pub.is_rints ? "TRUE" : "FALSE",
            pub.page_count, pub.citation_count);
}

fclose(fp);
}

void print_stack_csv(const Stack *stack, FILE *stream) {
 fprintf(stream, "Title,First Author Surname,First Author Initials,Journal Name,Publication Year,Journal Volume,Is RINTS,Page Count,Citation Count\n"); // Header
for (int i = 0; i < stack_size(stack); ++i) {
    Publication pub = stack->data[i];
    fprintf(stream, "%s,%s,%s,%s,%d,%d,%s,%d,%d\n",
            pub.title, pub.first_author_surname, pub.first_author_initials, pub.journal_name,
            pub.publication_year, pub.journal_volume, pub.is_rints ? "TRUE" : "FALSE",
            pub.page_count, pub.citation_count);
}
}

void print_stack_table(const Stack *stack, FILE *stream) {
fprintf(stream, "+----------------------------------+-------------------------+----------------------+-------------------------+-------+------+-------+-------+-------+\n");
fprintf(stream, "| %-33s | %-23s | %-20s | %-23s | %-5s | %-4s | %-5s | %-5s | %-5s |\n",
        "Title", "First Author Surname", "First Author Initials", "Journal Name", "Year", "Vol", "RINTS", "Pages", "Cites");
fprintf(stream, "+----------------------------------+-------------------------+----------------------+-------------------------+-------+------+-------+-------+-------+\n");

for (int i = 0; i < stack_size(stack); ++i) {
    Publication pub = stack->data[i];
    fprintf(stream, "| %-33s | %-23s | %-20s | %-23s | %5d | %4d | %-5s | %5d | %5d |\n",
            pub.title, pub.first_author_surname, pub.first_author_initials, pub.journal_name,
            pub.publication_year, pub.journal_volume, pub.is_rints ? "YES" : "NO",
            pub.page_count, pub.citation_count);
}

fprintf(stream, "+----------------------------------+-------------------------+----------------------+-------------------------+-------+------+-------+-------+-------+\n");
}