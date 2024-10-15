#include "mat_utils.h"

float *generate_random_matrix(int rows, int cols) {
    float *matrix = (float *)malloc(rows * cols * sizeof(float));
    for (int i = 0; i < rows * cols; i++) {
        matrix[i] = (float)rand() / RAND_MAX;
    }
    return matrix;
}

void print_matrix(float *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", matrix[i * cols + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void matrix_multiply(float *matrix1, float *matrix2, float *result, int m, int n, int k) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i * n + j] = 0;
            for (int l = 0; l < k; l++) {
                result[i * n + j] += matrix1[i * k + l] * matrix2[l * n + j];
            }
        }
    }
}