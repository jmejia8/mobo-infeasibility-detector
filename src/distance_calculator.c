#include "distance_calculator.h"

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
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Compute the distance between each pair of rows
    for (int i = 0; i < nrow; ++i) {
        for (int j = 0; j < nrow; ++j) {
            if (i == j) {
                dist_matrix[i * nrow + j] = 0.0;  // Distance to self is 0
            } else {
                dist_matrix[i * nrow + j] = euclidean_distance(X, ncol, i, j);
            }
        }
    }

    return dist_matrix;
}
