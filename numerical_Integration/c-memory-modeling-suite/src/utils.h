// src/utils.h
#ifndef UTILS_H
#define UTILS_H

double f(double x, double y, double z);
void fill_grid(double ***grid, int N);
double compute_integral(double ***grid, int N);
void free_grid(double ***grid, int N);

#endif // UTILS_H