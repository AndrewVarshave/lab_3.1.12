#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>

typedef enum {
    MODE_GENERATE,
    MODE_SORT,
    MODE_PRINT,
    MODE_INVALID
} Mode;

typedef enum {
    SORT_ASC,
    SORT_DESC
} SortType;

typedef struct {
    Mode mode;
    int num_records;
    char *input_file;
    char *output_file;
    SortType sort_type;
} Args;

void parse_args(int argc, char *argv[], Args *args);

#endif