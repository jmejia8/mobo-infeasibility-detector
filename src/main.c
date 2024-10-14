#include <float.h>
#include <math.h>
#include "csv.h"
#include "distance_calculator.h"
#include "infeasibility_detector.h"

int count_coors(CSV *csv, char token) {
    int nx = 0;
    for (int i = 0; i < csv->col_count; i++) {
        if (csv->header[i][0] == token) {
            ++nx;
        }
    }
    return nx;
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

void print_matrix(float *M, int nrow, int ncol)
{
    for (int i = 0; i < nrow; ++i) {
        for (int j = 0; j < ncol; ++j) {
            printf("%.3f ", M[i*ncol + j]);
        }
        printf("\n");
    }

    
}

float *get_x(CSV *csv, int nrow, int nx)
{
    return get_slice(csv, 0, nrow, 0, nx);
}


float *get_f(CSV *csv, int nrow, int nf)
{

    int nx = count_coors(csv, 'x');
    int ny = count_coors(csv, 'y');
    int nF = count_coors(csv, 'F');
    int c = nx + ny + nF;
    return get_slice(csv, 0, nrow, c, c+nf);
}

void normalize_by_row(float* X, int nrow, int ncol) {
    // Allocate memory for the normalized matrix
    float* X_norm = X;//(float*) malloc(sizeof(float) * nrow * ncol);
    if (X_norm == NULL) {
        return ;
    }

    // Loop over each row
    for (int j = 0; j < ncol; j++) {
        // Find the min and max values for the current row
        float col_min = FLT_MAX;
        float col_max = -FLT_MAX;

        for (int i = 0; i < nrow; i++) {
            float value = X[i * ncol + j];
            if (value < col_min) col_min = value;
            else if (value > col_max) col_max = value;
        }

        // Normalize the current row
        for (int i = 0; i < nrow; i++) {
            float value = X[i * ncol + j];
            if (abs(col_max - col_min) > 1e-8) {
                X_norm[i * ncol + j] = (value - col_min) / (col_max - col_min);
            } else {
                // In case all values are the same, set normalized values to 0
                X_norm[i * ncol + j] = 0.0f;
            }
        }
    }

}

void save_labels(char *filename, int *L, int n)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error: cannot write file file %s\n", filename);
        return;
    }

    // header
    fprintf(f, "label\n");
    // labels
    for (int i = 0; i < n; ++i)
        fprintf(f, "%i\n", L[i]);
    
    fclose(f);
    printf("Data saved at %s\n", filename);
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <csv_file> [epsilon=1e-8]\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    printf("Loading data...\n");
    // Read CSV file from argv
    CSV *csv = read_csv(filename);

    if (csv == NULL) {
        printf("Fail to load data.\n");
        return 1;
    }
    printf("File loaded: %s\n", filename);

    float eps = 1e-8;
    if (argc == 3)
        eps = strtof(argv[2], NULL);


    printf("Parameters: Manhattan distance, with epsilon = %e\n", eps);

    // Print the header
    printf("Header: \n");
    print_header(csv);


    printf("Selecting UL decisions (X)...\n");
    int nx = count_coors(csv, 'x');
    int nrow = csv->row_count;
    float *X = get_x(csv, nrow, nx);

    if (X==NULL) {
        printf("Fail loading X\n");
        return 1;
    }

    printf("Normalizing X via (X - x_min) / (x_max - x_min)\n");
    normalize_by_row(X, nrow, nx);


    printf("Computing distance matrix...\n");
    float *dist_matrix = compute_distance_matrix(X, nrow, nx);
    
    printf("Selecting LL objectives (f)...\n");
    int nf = count_coors(csv, 'f');
    float *f = get_f(csv, nrow, nf);
    if (f==NULL) {
        printf("f is empty\n");
        return 1;
    }

    printf("Labeling data with epsilon = %e\n", eps);
    int *L = solution_labeling(dist_matrix, f, nrow, nf, eps);
    save_labels(strcat(filename,"_labels.csv"), L, nrow);
    // Free memory
    free_csv(csv);
    free(X);
    free(f);
    free(L);
    printf("Done!\n");

    return 0;
}
