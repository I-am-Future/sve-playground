#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

double *generate_random_matrix(int rows, int cols);

void print_matrix(double *matrix, int rows, int cols);

void matrix_multiply(double *matrix1, double *matrix2, double *result, int m, int n, int k);

int matrix_compare(double *matrix1, double *matrix2, int rows, int cols, double epsilon);