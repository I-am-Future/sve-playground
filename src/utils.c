#include "utils.h"

svfloat32_t generate_random_vector(svbool_t pg) {
    float* values = malloc(svcntw()*sizeof(float));
    for (int i = 0; i < svcntw(); ++i) {
        values[i] = (float)rand() / RAND_MAX * 100.0;  // 生成0到100的随机数
    }
    svfloat32_t result = svld1(pg, values);
    free(values);
    return result;
}

svfloat32_t generate_sequence_vector(svbool_t pg, float start, float step) {
    float* values = malloc(svcntw()*sizeof(float));
    for (int i = 0; i < svcntw(); ++i) {
        values[i] = start + i * step;
    }
    svfloat32_t result = svld1(pg, values);
    free(values);
    return result;
}

void print_vector(svfloat32_t vector, svbool_t pg) {
    float* values = malloc(svcntw()*sizeof(float));
    svst1(pg, values, vector);
    printf("Vector elements:\n");
    for (int i = 0; i < svcntw(); ++i) {
        printf("%.2f ", values[i]);
    }
    printf("\n");
    free(values);
}
