
#include <stdio.h>
#include <arm_sve.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "mat_utils.h"

int main() {
    srand(time(NULL));  

    printf("Hello, SVE! Vec Length is: %ld floats\n", svcntw());

    LOG("Test on basics");

    // a predicate that is true for all lanes
    svbool_t pg = svptrue_b32();  

    svfloat32_t random_vector = generate_random_vector(pg);
    print_vector(random_vector, pg);

    svfloat32_t sequence_vector = generate_sequence_vector(pg, 1.0f, 1.0f);
    print_vector(sequence_vector, pg);

    // use this to make some "patterns!"
    svbool_t pg1 = svptrue_pat_b32(SV_VL5);
    sequence_vector = generate_sequence_vector(pg1, 1.0f, 1.0f);
    print_vector(sequence_vector, pg);

    LOG("Test on matrix multiplication");

    int m = 3, n = 3, k = 3;
    float *matrix1 = generate_random_matrix(m, k);
    float *matrix2 = generate_random_matrix(k, n);
    float *result = (float *)malloc(m * n * sizeof(float));

    print_matrix(matrix1, m, k);
    print_matrix(matrix2, k, n);

    matrix_multiply(matrix1, matrix2, result, m, n, k);
    print_matrix(result, m, n);

    return 0;
}