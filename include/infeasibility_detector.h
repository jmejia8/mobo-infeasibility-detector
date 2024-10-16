#ifndef INFEASIBILITY_DETECTOR_H
#define INFEASIBILITY_DETECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "csv.h"
#include "distance_calculator.h"
void infeasibility_detector(char *archive_fname, char *true_front_fname, float eps, char *distance);

#endif
