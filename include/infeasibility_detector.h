#ifndef INFEASIBILITY_DETECTOR_H
#define INFEASIBILITY_DETECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "csv.h"
int *solution_labeling(float *D, float *f, float *POF, int n_solutions, int n_objectives, float eps);
void infeasibility_detector(const char *archive_fname, const char *true_front_fname, float eps, char *distance);

#endif
