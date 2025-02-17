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
        pub.title[MAX_STRING_LENGTH - 1] = '0';

        token = strtok(NULL, ",");
        if (!token) break;
        strncpy(pub.first_author_surname, token, MAX_STRING_LENGTH - 1);
        pub.first_author_surname[MAX_STRING_LENGTH - 1] = '0';

        token = strtok(NULL, ",");
        if (!token) break;
        strncpy(pub.first_author_initials, token, MAX_STRING_LENGTH - 1);
        pub.first_author_initials[MAX_STRING_LENGTH - 1] = '0';

        token = strtok(NULL, ",");
        if (!token) break;
        strncpy(pub.journal_name, token, MAX_STRING_LENGTH - 1);
        pub.journal_name[MAX_STRING_LENGTH - 1] = '0';

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

    Node *current = stack->top;
    while (current != NULL) {
        Publication pub = current->data;
        fprintf(fp, "%s,%s,%s,%s,%d,%d,%s,%d,%d\n",
                pub.title, pub.first_author_surname, pub.first_author_initials, pub.journal_name,
                pub.publication_year, pub.journal_volume, pub.is_rints ? "TRUE" : "FALSE",
                pub.page_count, pub.citation_count);
        current = current->next;
    }

    fclose(fp);
}

void print_stack_csv(const Stack *stack, FILE *stream) {
    fprintf(stream, "Title,First Author Surname,First Author Initials,Journal Name,Publication Year,Journal Volume,Is RINTS,Page Count,Citation Count\n"); // Header

    Node *current = stack->top;
    while (current != NULL) {
        Publication pub = current->data;
        fprintf(stream, "%s,%s,%s,%s,%d,%d,%s,%d,%d\n",
                pub.title, pub.first_author_surname, pub.first_author_initials, pub.journal_name,
                pub.publication_year, pub.journal_volume, pub.is_rints ? "TRUE" : "FALSE",
                pub.page_count, pub.citation_count);
        current = current->next;
    }
}

void print_stack_table(const Stack *stack, FILE *stream) {
    fprintf(stream, "%-35s %-25s %-22s %-25s %-7s %-6s %-7s %-7s %-7s\n",
            "Title", "First Author Surname", "First Author Initials", "Journal Name", "Year", "Vol", "RINTS", "Pages", "Cites");

    Node *current = stack->top;
    while (current != NULL) {
        Publication pub = current->data;
        fprintf(stream, "%-35s %-25s %-22s %-25s %5d %5d %-7s %5d %5d\n",
                pub.title, pub.first_author_surname, pub.first_author_initials, pub.journal_name,
                pub.publication_year, pub.journal_volume, pub.is_rints ? "YES" : "NO",
                pub.page_count, pub.citation_count);
        current = current->next;
    }
}


