#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_COLUMNS 100

// Structure to store CSV data
typedef struct {
    char **header;       // Array of strings for header
    float **data;        // 2D array for float data
    int row_count;       // Number of rows
    int col_count;       // Number of columns
} CSV;

CSV *read_csv(const char *filename);
void print_header(CSV *csv) ;
void print_row(CSV *csv, int index);
void free_csv(CSV *csv);
