#include "utils.h"

double *generate_random_vector_c(int size) {
    double *values = (double *)malloc(size * sizeof(double));
    for (int i = 0; i < size; ++i) {
        values[i] = (double)rand() / RAND_MAX * 100.0;  // 生成0到100的随机数
    }
    return values;
}

svfloat64_t generate_random_vector(svbool_t pg) {
    double* values = malloc(svcntd()*sizeof(double));
    for (int i = 0; i < svcntd(); ++i) {
        values[i] = (double)rand() / RAND_MAX * 100.0;  // 生成0到100的随机数
    }
    svfloat64_t result = svld1(pg, values);
    free(values);
    return result;
}

svfloat64_t generate_sequence_vector(svbool_t pg, double start, double step) {
    double* values = malloc(svcntd()*sizeof(double));
    for (int i = 0; i < svcntd(); ++i) {
        values[i] = start + i * step;
    }
    svfloat64_t result = svld1(pg, values);
    free(values);
    return result;
}

void print_vector(svfloat64_t vector, svbool_t pg) {
    double* values = malloc(svcntd()*sizeof(double));
    svst1(pg, values, vector);
    printf("Vector elements:\n");
    for (int i = 0; i < svcntd(); ++i) {
        printf("%.2f ", values[i]);
    }
    printf("\n");
    free(values);
}

void print_vector_c(double *vector, int size) {
    printf("Vector elements:\n");
    for (int i = 0; i < size; ++i) {
        printf("%.2f ", vector[i]);
    }
    printf("\n");
}