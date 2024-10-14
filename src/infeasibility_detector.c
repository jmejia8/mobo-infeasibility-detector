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

int *solution_labeling(float *D, float *f, int n_solutions, int n_objectives, float eps)
{
    int i,j;
    int *L = (int*) malloc(sizeof(int)*n_solutions);

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
    return L;
}
