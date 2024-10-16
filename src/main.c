#include <float.h>
#include <math.h>
#include "distance_calculator.h"
#include "infeasibility_detector.h"



int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <csv_archive> [epsilon=1e-8] [csv_true_front]\n", argv[0]);
        return 1;
    }

    char* archive_fname = argv[1];
    char* true_front_fname = NULL;
    float eps = 1e-8;

    if (argc >= 3)
        eps = strtof(argv[2], NULL);

    if (argc == 4)
        true_front_fname = argv[3];


    infeasibility_detector(archive_fname, true_front_fname, eps, "manhattan");

    return 0;
}
