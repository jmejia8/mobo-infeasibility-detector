void solution_labeling(float *D, float *f, int n_solutions, int n_objectives)
{
    int i,j;
    int *L = (int*) malloc(sizeof(int)*n_solutions);

    // initialize labels as deceptive
    for (i = 0; i < n_solutions; ++i) L[i] = 5;

    // assign labels
    for (i = 0; i < n_solutions; ++i) {
        for (j = i+1; j < n_solutions; ++j) {
            if (D[i*n_solutions + j]) {
                update_label(L, i, j, f, n_objectives);
            }
        }
    }
}

void update_label(int *L, int i, int j, float *f, int n_objectives)
{
    char c = compare(f[i*n_objectives], f[j*n_objectives], n_objectives);

    if (c == 'd') {
        
    }else if (c == 'D'){

    } else if (c == 'i'){

    }

    
}
