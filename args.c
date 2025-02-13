#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"

void parse_args(int argc, char *argv[], Args *args) {
    args->mode = MODE_INVALID;
    args->num_records = 0;
    args->input_file = NULL;
    args->output_file = NULL;
    args->sort_type = SORT_ASC; 

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--generate") == 0 || strcmp(argv[i], "-g") == 0) {
            args->mode = MODE_GENERATE;
            if (i + 1 < argc) {
                args->num_records = atoi(argv[i + 1]);
                i++;
            } else {
                fprintf(stderr, "Error: Missing number of records for --generate/-g\n");
                exit(1);
            }
        } else if (strcmp(argv[i], "--sort") == 0 || strcmp(argv[i], "-s") == 0) {
            args->mode = MODE_SORT;
        } else if (strcmp(argv[i], "--print") == 0 || strcmp(argv[i], "-P") == 0) {
            args->mode = MODE_PRINT;
        } else if (strncmp(argv[i], "--out=", 6) == 0 || strncmp(argv[i], "-o", 2) == 0) {
            char *filename;
            if(strncmp(argv[i], "--out=", 6) == 0) {
                filename = argv[i] + 6;
            } else {
                if(i+1 < argc){
                    filename = argv[i+1];
                    i++;
                } else {
                    fprintf(stderr, "Error: Missing filename for -o\n");
                    exit(1);
                }
            }

            args->output_file = strdup(filename);
            if(args->output_file == NULL){
                perror("strdup failed");
                exit(1);
            }

        } else if (strncmp(argv[i], "--in=", 5) == 0 || strncmp(argv[i], "-i", 2) == 0) {
            char *filename;
            if(strncmp(argv[i], "--in=", 5) == 0) {
                filename = argv[i] + 5;
            } else {
                if(i+1 < argc){
                    filename = argv[i+1];
                    i++;
                } else {
                    fprintf(stderr, "Error: Missing filename for -i\n");
                    exit(1);
                }
            }

            args->input_file = strdup(filename);
            if(args->input_file == NULL){
                perror("strdup failed");
                exit(1);
            }


        } else if (strncmp(argv[i], "--type=", 7) == 0 || strncmp(argv[i], "-t", 2) == 0) {
             char *type_str;
             if(strncmp(argv[i], "--type=", 7) == 0) {
                type_str = argv[i] + 7;
             } else {
                 if(i+1 < argc){
                    type_str = argv[i+1];
                    i++;
                 } else {
                    fprintf(stderr, "Error: Missing type for -t\n");
                    exit(1);
                 }

             }

            if (strcmp(type_str, "asc") == 0 || strcmp(type_str, "A") == 0) {
                args->sort_type = SORT_ASC;
            } else if (strcmp(type_str, "desc") == 0 || strcmp(type_str, "D") == 0) {
                args->sort_type = SORT_DESC;
            } else {
                fprintf(stderr, "Error: Invalid sort type. Use 'asc' or 'desc'.\n");
                exit(1);
            }
        } else {
            fprintf(stderr, "Error: Unknown argument %s\n", argv[i]);
            exit(1);
        }
    }

     if (args->mode == MODE_INVALID) {
        fprintf(stderr, "Error: No mode specified. Use --generate/-g, --sort/-s, or --print/-P.\n");
        exit(1);
    }
}