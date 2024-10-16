#include "csv.h"

// Function to dynamically allocate memory for a string
char *copy_string(const char *source) {
    char *copy = (char *)malloc(strlen(source) + 1);
    strcpy(copy, source);
    return copy;
}

// Function to read the CSV file
CSV *read_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        // printf("Error: Cannot open file.\n");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    CSV *csv = (CSV *)malloc(sizeof(CSV));
    csv->header = NULL;
    csv->data = NULL;
    csv->row_count = 0;
    csv->col_count = 0;

    // Read the header
    if (fgets(line, sizeof(line), file)) {
        csv->header = (char **)malloc(MAX_COLUMNS * sizeof(char *));
        char *token = strtok(line, ",\n");
        while (token) {
            csv->header[csv->col_count++] = copy_string(token);
            token = strtok(NULL, ",\n");
        }
    }

    // Read the data rows
    while (fgets(line, sizeof(line), file)) {
        csv->data = (float **)realloc(csv->data, (csv->row_count + 1) * sizeof(float *));
        csv->data[csv->row_count] = (float *)malloc(csv->col_count * sizeof(float));

        char *token = strtok(line, ",\n");
        for (int i = 0; i < csv->col_count; i++) {
            if (token) {
                csv->data[csv->row_count][i] = strtof(token, NULL);
                token = strtok(NULL, ",\n");
            }
        }
        csv->row_count++;
    }

    fclose(file);
    return csv;
}

// Function to print the header
void print_header(CSV *csv) {
    for (int i = 0; i < csv->col_count; i++) {
        printf("%s ", csv->header[i]);
    }
    printf("\n");
}


void get_columns_range(int col_range[2], CSV *csv, char token){
    col_range[0] = -1; col_range[1] = -1;
    for (int i = 0; i < csv->col_count; i++) {
        if (csv->header[i][0] != token)
            continue;
        col_range[1] = i+1;
        if (col_range[0] == -1)
            col_range[0] = i;
    }
}

float* get_slice(CSV *csv, int row_start, int row_end, int col_start, int col_end)
{
    int nrow = row_end - row_start;
    int ncol = col_end - col_start;

    if (nrow == 0 || ncol == 0) {
        return NULL;
    }

    float *X = (float*) malloc(sizeof(float)*nrow*ncol);
    for (int i = 0; i < nrow; ++i) {
        int ii = i*ncol;
        for (int j = 0; j < ncol; ++j) {
            X[ii + j] = csv->data[row_start + i][col_start + j];
        }
    }
    return X;
}


float* get_columns(int *nx, CSV *archive, char token)
{
    if (archive == NULL) return NULL;

    int col_range[2];
    int nrow = archive->row_count;
    get_columns_range(col_range, archive, token);
    nx[0] = col_range[1] - col_range[0];
    return get_slice(archive, 0, nrow, col_range[0], col_range[1]);
}


// Function to print a row by index
void print_row(CSV *csv, int index) {
    if (index < 0 || index >= csv->row_count) {
        printf("Error: Invalid row index.\n");
        return;
    }
    for (int i = 0; i < csv->col_count; i++) {
        printf("%.2f ", csv->data[index][i]);
    }
    printf("\n");
}

// Function to free the allocated memory
void free_csv(CSV *csv) {
    if (csv == NULL) {
        return;
    }
    for (int i = 0; i < csv->col_count; i++) {
        free(csv->header[i]);
    }
    free(csv->header);

    for (int i = 0; i < csv->row_count; i++) {
        free(csv->data[i]);
    }
    free(csv->data);
    free(csv);
}


CSV *read_data(const char *archive_fname)
{
    CSV *csv = read_csv(archive_fname);
    return csv;
}


