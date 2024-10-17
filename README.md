# Infeasibility detector for Multiobjective Bilevel Optimization

This project implements the labeling process to identify infeasible solutions in multi-objective bilevel optimization.

## Project Structure

- **include/**: Contains the header files.
- **src/**: Contains the C++ source files.
- **data/**: Contains the input data file.
- **bin/**: The compiled executable will be placed here.
- **obj/**: Object files will be placed here.
- **Makefile**: To compile the project.

## How to Run

1. Compile the project:

   ```
   make
   ```

2. Run the program to obtain the labels for an archive, with `epsilon=0.001` (`1e-8` by default if not provided) and known Pareto-optimal front (optional):

   ```
   ./bin/detector archive.csv 0.001 pof.csv
   ```

The `archive.csv` is a comma-separated value file, which must contain the decision variables, UL objectives and LL objectives by row. The program assumes that solutions violating equality and inequality constraints are not included. The following table illustrates the necessary format.

```csv
x1,x2,F1,F2,f1,f2
0.58,0.42,0.16,0.52,0.75,0.84
0.59,0.14,0.51,0.45,0.81,0.86
0.52,0.94,0.06,0.63,0.58,0.79
0.37,0.32,0.92,0.45,0.87,0.84
0.62,0.73,0.39,0.44,0.09,0.47
0.90,0.90,0.37,0.81,0.23,0.78
0.34,0.03,0.88,0.06,0.01,0.44
```

The header specifies each upper-level decisions **x**, upper-level objectives **F**, lower-level objectives **f**.
A similar format is required for the Pareto-optimal front `pof.csv`, only upper-level objectives are mandatory.
Note that if `pof.csv` is given, the `epsilon` parameter should be given.

3. The resulting labels are saved next to `archive.csv` with name `archive.csv_labels.csv`
