
#include <stdio.h>
#include <arm_sve.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "mat_utils.h"
#include "tests.h"


//////////////////////////////////////////////////////////
// Matrix Multiplication Test Space
//
// 1. implement the micro kernel at `bl_micro_kernel`
// 2. add tests at `mat_test`
// 3. run the tests at `main`: make && ./main
//////////////////////////////////////////////////////////

void bl_micro_kernel(
        int k,
        int m,
        int n,
        const double *restrict a,
        const double *restrict b,
        double *restrict c,
        unsigned long long ldc)
{
    // develop the micro kernel here! The func signature is generally same...

    // example code:
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            c[i * ldc + j] = 0;
            for (int l = 0; l < k; l++) {
                c[i * ldc + j] += a[i * k + l] * b[l * n + j];
            }
        }
    }
}

void mat_test_size(int m, int n, int k)
{
    double *matrix1 = gen_rand_mat_ROW(m, k);
    double *matrix2 = gen_rand_mat_ROW(k, n);
    double *result = (double *)malloc(m * n * sizeof(double));
    double *result_ref = (double *)malloc(m * n * sizeof(double));

    // reference answer
    matrix_multiply(matrix1, matrix2, result_ref, m, n, k);

    // SVE answer
    bl_micro_kernel(k, m, n, matrix1, matrix2, result, n);

    // compare the results
    int cmp = matrix_compare(result_ref, result, m, n, 1e-4);
    if (cmp) {
        printf("Test passed with size [%d x %d] x [%d x %d]\n", m, k, k, n);
    } else {
        printf("Test failed with size [%d x %d] x [%d x %d]\n", m, k, k, n);

        printf("reference result:\n");
        print_matrix(result_ref, m, n);

        printf("SVE result:\n");
        print_matrix(result, m, n);
    }

}


void mat_test() 
{
    mat_test_size(2, 4, 4);
    mat_test_size(4, 4, 4);
}

int main()
{
    srand(time(NULL));

    printf("Hello, SVE! Vec Length is: %ld doubles \n\n", svcntd());

    // test0();

    // test1();

    // test2();

    // test3();

    // test4();

    // test5();

    test6();

    // mat_test();

    return 0;
}