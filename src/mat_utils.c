#include "mat_utils.h"

double *generate_random_matrix(int rows, int cols) {
    double *matrix = (double *)malloc(rows * cols * sizeof(double));
    for (int i = 0; i < rows * cols; i++) {
        matrix[i] = (double)rand() / RAND_MAX;
    }
    return matrix;
}

void print_matrix(double *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", matrix[i * cols + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void matrix_multiply(double *matrix1, double *matrix2, double *result, int m, int n, int k) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i * n + j] = 0;
            for (int l = 0; l < k; l++) {
                result[i * n + j] += matrix1[i * k + l] * matrix2[l * n + j];
            }
        }
    }
}

int matrix_compare(double *matrix1, double *matrix2, int rows, int cols, double epsilon) {
    for (int i = 0; i < rows * cols; i++) {
        if (fabs(matrix1[i] - matrix2[i]) > epsilon) {
            return 0;
        }
    }
    return 1;
}
