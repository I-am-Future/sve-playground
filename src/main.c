
#include <stdio.h>
#include <arm_sve.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "mat_utils.h"

void test0()
{
    LOG("Test on basics");

    // a predicate that is true for all lanes
    svbool_t pg = svptrue_b64();

    svfloat64_t random_vector = generate_random_vector(pg);
    print_vector(random_vector, pg);

    svfloat64_t sequence_vector = generate_sequence_vector(pg, 1.0f, 1.0f);
    print_vector(sequence_vector, pg);

    // use this to make some "patterns!"
    svbool_t pg1 = svptrue_pat_b64(SV_VL5);
    sequence_vector = generate_sequence_vector(pg1, 1.0f, 1.0f);
    print_vector(sequence_vector, pg);
}

void test1()
{
    LOG("Test on matrix multiplication");

    int m = 3, n = 4, k = 5;
    double *matrix1 = generate_random_matrix(m, k);
    double *matrix2 = generate_random_matrix(k, n);
    double *result = (double *)malloc(m * n * sizeof(double));

    print_matrix(matrix1, m, k);
    print_matrix(matrix2, k, n);

    matrix_multiply(matrix1, matrix2, result, m, n, k);
    print_matrix(result, m, n);
}

void sveVecAdd(int N, double *C, double *A, double *B)
{
    int i = 0;
    svbool_t pred = svwhilelt_b64(i, N);
    svfloat64_t veca;
    svfloat64_t vecb;
    svfloat64_t vecc;
    while (svptest_any(svptrue_b64(), pred))
    {
        veca = svld1(pred, A + i);
        vecb = svld1(pred, B + i);
        vecc = svadd_f64_x(pred, veca, vecb);
        svst1_f64(pred, C + i, vecc);
        i += svcntd();
        pred = svwhilelt_b64(i, N);
    }
}

void sveVecAdd2(int N, double *C, double *A, double *B)
{
    int i = 0;
    svbool_t pred = svwhilelt_b64(i, N);
    svfloat64_t veca;
    svfloat64_t vecb;
    svfloat64_t vecc;
    if (svptest_any(svptrue_b64(), pred))
    {
        do
        {
            veca = svld1(pred, A + i);
            vecb = svld1(pred, B + i);
            vecc = svadd_f64_x(pred, veca, vecb);
            svst1_f64(pred, C + i, vecc);
            i += svcntd();
            pred = svwhilelt_b64(i, N);
        } while (svptest_any(svptrue_b64(), pred));
    }
}

void vecAdd(int N, double *C, double *A, double *B)
{
    for (int i = 0; i < N; i++)
    {
        C[i] = A[i] + B[i];
    }
}

void test2()
{
    LOG("Example code: vec add");

    const int ARRAY_SIZE = 10;
    double *array_a = generate_random_vector_c(ARRAY_SIZE);
    double *array_b = generate_random_vector_c(ARRAY_SIZE);
    double *array_c = (double *)malloc(ARRAY_SIZE * sizeof(double));
    double *array_c2 = (double *)malloc(ARRAY_SIZE * sizeof(double));

    sveVecAdd(ARRAY_SIZE, array_c, array_a, array_b);
    vecAdd(ARRAY_SIZE, array_c2, array_a, array_b);

    print_vector_c(array_a, 5);
    print_vector_c(array_b, 5);
    print_vector_c(array_c, 5);
    print_vector_c(array_c2, 5);
}

void test3()
{
    LOG("Test on predicate");

    svbool_t pg = svwhilelt_b64(10, 10);

    svfloat64_t vec = svdup_f64(1.0f);
    print_vector(vec, pg);

    int res = svptest_any(svptrue_b64(), pg);
    printf("res: %d\n", res);
}

void dgemm_2x4x4(int lda, int ldb, int ldc, int n,
                 double *A, double *B, double *C)
{
    register svfloat64_t ax;
    register svfloat64_t bx;
    register svfloat64_t c0x, c1x;
    svbool_t npred = svwhilelt_b64_u64(0, n);
    c0x = svld1_f64(npred, C);
    c1x = svld1_f64(npred, C + ldc);
    for (int kk = 0; kk < 4; kk++)
    {
        register float64_t aval = *(A + 0 * lda + kk);
        ax = svdup_f64(aval);
        bx = svld1_f64(svptrue_b64(), B + kk * ldb);
        c0x = svmla_f64_m(npred, c0x, bx, ax);
        aval = *(A + 1 * lda + kk);
        ax = svdup_f64(aval);
        c1x = svmla_f64_m(npred, c1x, bx, ax);
    }
    svst1_f64(npred, C, c0x);
    svst1_f64(npred, C + ldc, c1x);
}

void test4()
{
    LOG("Test on matrix multiplication 2x4x4");

    double *matrix1 = generate_random_matrix(2, 4);
    double *matrix2 = generate_random_matrix(4, 4);
    double *result = (double *)malloc(2 * 4 * sizeof(double));
    double *result_ref = (double *)malloc(2 * 4 * sizeof(double));

    // reference answer
    matrix_multiply(matrix1, matrix2, result_ref, 2, 4, 4);

    // SVE answer
    dgemm_2x4x4(4, 4, 4, 4, matrix1, matrix2, result);

    print_matrix(result_ref, 2, 4);
    print_matrix(result, 2, 4);
}

void dgemm_4x4x4(int lda, int ldb, int ldc, int n,
                 double *A, double *B, double *C)
{
    register svfloat64_t ax;
    register svfloat64_t bx;
    register svfloat64_t c0x, c1x, c2x, c3x;
    svbool_t npred = svwhilelt_b64_u64(0, n);
    c0x = svld1_f64(npred, C);
    c1x = svld1_f64(npred, C + ldc);
    c2x = svld1_f64(npred, C + 2 * ldc);
    c3x = svld1_f64(npred, C + 3 * ldc);
    for (int kk = 0; kk < 4; kk++)
    {
        register float64_t aval = *(A + 0 * lda + kk);
        ax = svdup_f64(aval);
        bx = svld1_f64(svptrue_b64(), B + kk * ldb);
        c0x = svmla_f64_m(npred, c0x, bx, ax);
        aval = *(A + 1 * lda + kk);
        ax = svdup_f64(aval);
        c1x = svmla_f64_m(npred, c1x, bx, ax);
        aval = *(A + 2 * lda + kk);
        ax = svdup_f64(aval);
        c2x = svmla_f64_m(npred, c2x, bx, ax);
        aval = *(A + 3 * lda + kk);
        ax = svdup_f64(aval);
        c3x = svmla_f64_m(npred, c3x, bx, ax);
    }
    svst1_f64(npred, C, c0x);
    svst1_f64(npred, C + ldc, c1x);
    svst1_f64(npred, C + 2 * ldc, c2x);
    svst1_f64(npred, C + 3 * ldc, c3x);
}

void test5() 
{
    LOG("Test on matrix multiplication 4x4x4, with butterfly structure");

    double *matrix1 = generate_random_matrix(4, 4);
    double *matrix2 = generate_random_matrix(4, 4);
    double *result = (double *)malloc(4 * 4 * sizeof(double));
    double *result_ref = (double *)malloc(4 * 4 * sizeof(double));

    // reference answer
    matrix_multiply(matrix1, matrix2, result_ref, 4, 4, 4);

    // SVE answer
    dgemm_4x4x4(4, 4, 4, 4, matrix1, matrix2, result);

    print_matrix(result_ref, 4, 4);
    print_matrix(result, 4, 4);

}

int main()
{
    srand(time(NULL));

    printf("Hello, SVE! Vec Length is: %ld words\n", svcntd());

    test0();

    test1();

    test2();

    test3();

    test4();

    test5();

    return 0;
}