#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "publication.h"
#include "stack.h"
#include "args.h"
#include "sort.h"
#include "io.h"

Publication generate_publication() {
    Publication pub;
    snprintf(pub.title, MAX_STRING_LENGTH, "Title %d", rand() % 100);
    snprintf(pub.first_author_surname, MAX_STRING_LENGTH, "Author %d", rand() % 50);
    snprintf(pub.first_author_initials, MAX_STRING_LENGTH, "%c.%c.", 'A' + rand() % 26, 'B' + rand() % 26);
    snprintf(pub.journal_name, MAX_STRING_LENGTH, "Journal %d", rand() % 20);
    pub.publication_year = 2000 + rand() % 24;
    pub.journal_volume = rand() % 50 + 1;
    pub.is_rints = rand() % 2 == 0;
    pub.page_count = rand() % 200 + 10;
    pub.citation_count = rand() % 100;
    return pub;
}

int compare_publications(const Publication *a, const Publication *b) {
    return strcmp(a->title, b->title);
}


int main(int argc, char *argv[]) {
    Args args;
    parse_args(argc, argv, &args);

    if (args.mode == MODE_GENERATE) {
        Stack stack;
        stack_init(&stack);

        for (int i = 0; i < args.num_records; ++i) {
            Publication pub = generate_publication();
            stack_push(&stack, pub);
        }

        if (args.output_file) {
            write_stack_to_csv(&stack, args.output_file);
        } else {
            print_stack_csv(&stack, stdout);
        }
        stack_free(&stack);
    } else if (args.mode == MODE_SORT) {
        Stack stack;
        stack_init(&stack);

        if (args.input_file) {
            if (read_stack_from_csv(&stack, args.input_file) != 0) {
                fprintf(stderr, "Error reading from file.\n");
                return 1;
            }
        } else {
            char filename[256];
            if (fgets(filename, sizeof(filename), stdin) == NULL) {
                fprintf(stderr, "Error reading filename from stdin.\n");
                return 1;
            }

            size_t len = strlen(filename);
            if (len > 0 && filename[len - 1] == '\n') {
                filename[len - 1] = '\0';
            }

            if (read_stack_from_csv(&stack, filename) != 0) {
                fprintf(stderr, "Error reading from file: %s\n", filename);
                return 1;
            }
        }

        if (args.sort_type == SORT_ASC) {
             gnome_sort(&stack, compare_publications);
        } else {
            gnome_sort_desc(&stack, compare_publications);
        }

        if (args.output_file) {
            write_stack_to_csv(&stack, args.output_file);
        } else {
            print_stack_csv(&stack, stdout);
        }
        stack_free(&stack);

    } else if (args.mode == MODE_PRINT) {
         Stack stack;
        stack_init(&stack);

        if (args.input_file) {
            if (read_stack_from_csv(&stack, args.input_file) != 0) {
                fprintf(stderr, "Error reading from file.\n");
                return 1;
            }
        } else {
            char filename[256];
            if (scanf("%255s", filename) != 1) {
                fprintf(stderr, "Error reading filename from stdin.\n");
                return 1;
            }
            if (read_stack_from_csv(&stack, filename) != 0) {
                fprintf(stderr, "Error reading from file: %s\n", filename);
                return 1;
            }
        }

        FILE *output = stdout;
        if (args.output_file) {
            output = fopen(args.output_file, "w");
            if (!output) {
                perror("Error opening output file");
                return 1;
            }
        }

        print_stack_table(&stack, output);

        if (args.output_file) {
            fclose(output);
        }

        stack_free(&stack);

    } else {
        fprintf(stderr, "Invalid mode.  Use -g, -s, or -p.\n");
        return 1;
    }


    return 0;
}