#include "mat_utils.h"

/* Generate Row major matrix

    rows and cols define the size of the matrix
    validrows and validcols define where the non-zero elements are

e.g.,
    gen_rand_mat_ROW(2, 3, 2, 2) will generate like:
    0.1 0.2 0.0
    0.3 0.4 0.0 (saved as row major)
*/
double *gen_rand_mat_ROW(int rows, int cols, int validrows, int validcols)
{
    double *matrix = (double *)malloc(rows * cols * sizeof(double));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i < validrows && j < validcols)
            {
                matrix[i * cols + j] = (double)(rand() % 100) / 10;
            }
            else
            {
                matrix[i * cols + j] = 0;
            }
        }
    }
}

/* Generate Col major matrix

    rows and cols define the size of the matrix
    validrows and validcols define where the non-zero elements are

e.g.,
    gen_rand_mat_COL(3, 2, 2, 2) will generate like:
    0.1 0.2
    0.3 0.4
    0.0 0.0 (saved as col major)
*/
double *gen_rand_mat_COL(int rows, int cols, int validrows, int validcols)
{
    double *matrix = (double *)malloc(rows * cols * sizeof(double));
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (i < validcols && j < validrows)
            {
                matrix[i * rows + j] = (double)(rand() % 100) / 10;
            }
            else
            {
                matrix[i * rows + j] = 0;
            }
        }
    }
}

/* Print matrix, with row major */
void print_matrix_ROW(double *matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%f ", matrix[i * cols + j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* Print matrix, with col major */
void print_matrix_COL(double *matrix, int rows, int cols)
{
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            printf("%f ", matrix[i * rows + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void transpose_matrix(double *matrix, double *result, int rows, int cols)
{
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            result[i * rows + j] = matrix[j * cols + i];
        }
    }
}

void matrix_multiply(double *matrix1, double *matrix2, double *result,
                     int mat1_is_row_major, int mat2_is_row_major,
                     int m, int n, int k)
{
    
}

int matrix_compare(double *matrix1, double *matrix2, int rows, int cols, double epsilon)
{
    for (int i = 0; i < rows * cols; i++)
    {
        if (fabs(matrix1[i] - matrix2[i]) > epsilon)
        {
            return 0;
        }
    }
    return 1;
}
