#include <math.h>
#include "distance_calculator.h"

float manhattan_distance(float *X, int ncol, int i, int j) {
    float dist = 0.0;
    for (int k = 0; k < ncol; ++k) {
        float diff = X[i * ncol + k] - X[j * ncol + k];
        dist += fabs(diff);
    }
    return dist;
}

float euclidean_distance(float *X, int ncol, int i, int j) {
    float dist = 0.0;
    for (int k = 0; k < ncol; ++k) {
        float diff = X[i * ncol + k] - X[j * ncol + k];
        dist += diff * diff;
    }
    return sqrt(dist);
}

// Function to compute the distance matrix between rows
float* compute_distance_matrix(float *X, int nrow, int ncol) {
    // Allocate memory for the distance matrix (nrow x nrow)
    float *dist_matrix = (float*) malloc(sizeof(float) * nrow * nrow);
    if (dist_matrix == NULL) {
        printf("Error: Memory allocation failed (distance matrix)\n");
        //printf("%d, %d^2 = %d\n", sizeof(float), nrow, nrow*nrow);
        printf("\tMemory required: %.2f GB\n", (double)(sizeof(float) * nrow * nrow) * (double)  9.3132257461548E-10);
        exit(1);
    }

    // Compute the distance between each pair of rows
    for (int i = 0; i < nrow; ++i) {
        dist_matrix[i * nrow + i] = 0.0;  // Distance to self is 0
        for (int j = i+1; j < nrow; ++j) {
            float d = manhattan_distance(X, ncol, i, j);
            dist_matrix[i * nrow + j] = d;
            dist_matrix[j * nrow + i] = d;
        }
    }

    return dist_matrix;
}
