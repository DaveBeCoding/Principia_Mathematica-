// tests/triple_integral_test.c
#include <assert.h>
#include "../src/utils.h"
#include <stdlib.h>
#include <stdio.h>

#define N 10

int main() {
    double ***grid = (double ***)malloc(N * sizeof(double **));
    for (int i = 0; i < N; i++) {
        grid[i] = (double **)malloc(N * sizeof(double *));
        for (int j = 0; j < N; j++) {
            grid[i][j] = (double *)malloc(N * sizeof(double));
        }
    }

    fill_grid(grid, N);
    double result = compute_integral(grid, N);
    assert(result > 0);
    printf("Triple integral test passed. Result: %lf\n", result);
    free_grid(grid, N);
    return 0;
}