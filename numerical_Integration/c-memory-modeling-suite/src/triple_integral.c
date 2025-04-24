// src/triple_integral.c
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define N 100

double f(double x, double y, double z) {
    return x * x + y * y + z * z;
}

void fill_grid(double ***grid, int N) {
    double dx = 1.0 / (N - 1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                double x = i * dx;
                double y = j * dx;
                double z = k * dx;
                grid[i][j][k] = f(x, y, z);
            }
        }
    }
}

double compute_integral(double ***grid, int N) {
    double dx = 1.0 / (N - 1);
    double sum = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                sum += grid[i][j][k];
            }
        }
    }
    return sum * dx * dx * dx;
}

void free_grid(double ***grid, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            free(grid[i][j]);
        }
        free(grid[i]);
    }
    free(grid);
}

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
    printf("Triple Integral Result: %lf\n", result);
    free_grid(grid, N);

    return 0;
}
