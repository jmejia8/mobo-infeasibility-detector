#include <float.h>
#include <math.h>
//#include "csv.h"
#include "distance_calculator.h"
#include "infeasibility_detector.h"



int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <csv_file> [epsilon=1e-8]\n", argv[0]);
        return 1;
    }

    char* archive_fname = argv[1];
    char* true_front_fname = NULL;
    float eps = 1e-8;
    infeasibility_detector(archive_fname, true_front_fname, eps, "abc");

    /*
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

    float* POF = NULL;

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
    int *L = solution_labeling(dist_matrix, f, POF, nrow, nf, eps);
    save_labels(strcat(filename,"_labels.csv"), L, nrow);
    // Free memory
    free_csv(csv);
    free(X);
    free(f);
    free(L);
    printf("Done!\n");
    */

    return 0;
}
