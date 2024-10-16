#include "infeasibility_detector.h"
/*
 * a and b are vectors with size k
 * 'i' means a and b are incomparable
 * 'd' a dominates b
 * 'D' b dominates a
 * 'e' for a == b
 * */
char compare(float* a, float* b, int k)
{
    int i = 0, j;
    while (i < k && a[i] == b[i]) ++i;

    if ( i >= k) return 'e'; // a == b

    if (a[i] < b[i]){

        for (j = i+1; j < k; ++j)
            if (b[j] < a[j]) return 'i'; // a and b are incomparable

        return 'd'; // a dominates b
    }

    for (j = i+1; j < k; ++j) {
        if (a[j] < b[j])
            return 'i'; // a and b are incomparable
    }

    return 'D'; // b dominates a
}


////////////////////////////////////////////////////////
///
///




void print_matrix(float *M, int nrow, int ncol)
{
    for (int i = 0; i < nrow; ++i) {
        for (int j = 0; j < ncol; ++j) {
            printf("%.3f ", M[i*ncol + j]);
        }
        printf("\n");
    }

    
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
            if (fabs(col_max - col_min) > 1e-8) {
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

///
///
/////////////////////////////////////////////////////



void update_label(int *L, int i, int j, float *f, int n_objectives)
{
    char c = compare(&f[i*n_objectives], &f[j*n_objectives], n_objectives);

    if (c == 'd') {
        L[j] = 4;
        if (L[i] == 2 || L[i] == 5)
            L[i] = 1;
    }else if (c == 'D'){
        L[i] = 4;
        if (L[j] == 2 || L[j] == 5)
            L[j] = 1;
    } else if (c == 'i'){
        if (L[i] == 5 ) L[i] = 3;
        if (L[j] == 5 ) L[j] = 3;
    }else{
        if (L[i] == 5 ) L[i] = 2;
        if (L[j] == 5 ) L[j] = 2;
    }
}

int *solution_labeling(float *D, float *f, float* POF, int n_solutions, int n_objectives, float eps)
{
    int i,j;
    int *L = (int*) malloc(sizeof(int)*n_solutions);
    if (L==NULL) {
        printf("Error: Fail allocating memory (solution labeling)\n");
        exit(1);
    }

    // initialize labels as deceptive
    for (i = 0; i < n_solutions; ++i) L[i] = 5;

    // assign labels
    for (i = 0; i < n_solutions; ++i) {
        for (j = i+1; j < n_solutions; ++j) {
            if (D[i*n_solutions + j] <= eps) {
                update_label(L, i, j, f, n_objectives);
            }
        }
    }

    if (POF == NULL)
        return L;

    /*
    int n_ul_objectives = 2; // FIXME
    float *F = NULL;
    for (i = 0; i < n_solutions; ++i) {
        for (j = 0; j < n_pof; ++j) {
            char c = compare(&POF[j*n_ul_objectives, &F[i*n_ul_objectives]], n_ul_objectives);
            if (c == 'd') {
                L[i] = 4;
                break;
            }
        }
    }
    */
    

    return L;
}


void infeasibility_detector(const char *archive_fname, const char *true_front_fname, float eps, char *distance)
{


    printf("Loading data...\n");
    // read CSV files
    CSV *archive = NULL, *true_front = NULL;
    archive = read_data(archive_fname);
    if (archive == NULL) {
        printf("Error: Fail loading archive.\n");
        exit(1);
    }


    printf("File loaded: %s\n", archive_fname);

    // loading upper-level decisions
    printf("Selecting UL decisions (X)...\n");
    int nrow = archive->row_count;
    printf("%d\n", nrow);
    int n_ul_decisions;
    float *X = get_columns(&n_ul_decisions, archive, 'x');
    printf("Num. of UL decisions: %d\n", n_ul_decisions);

    if (X==NULL) {
        printf("Error: Fail loading UL decisions (X) required.\n");
        exit(1);
    }
    //print_matrix(X, nrow, n_ul_decisions);
    // normalizing X
    printf("Normalizing X via (X - x_min) / (x_max - x_min)\n");
    normalize_by_row(X, nrow, n_ul_decisions);
    //print_matrix(X, nrow, n_ul_decisions);

    // loading lower-level objectives (f)
    printf("Selecting LL objectives (f)...\n");
    int nf;
    float *f = get_columns(&nf, archive, 'f');

    if (f==NULL) {
        printf("Error: Lower-level objectives are required but no provided.\n");
        exit(1);
    }
    print_matrix(f, nrow, nf);


    /*
    // labeling procedure
    printf("Labeling data with epsilon = %e\n", eps);
    int *L = solution_labeling(dist_matrix, f, POF, nrow, nf, eps);
    save_labels(strcat(filename,"_labels.csv"), L, nrow);

    // Free memory
    free_csv(archive);
    free_csv(true_front);
    free(X);
    free(f);
    free(L);
    */

    printf("Done!\n");
}

