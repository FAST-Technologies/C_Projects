#ifndef S21_MATRIX_H
#define S21_MATRIX_H
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constant values
typedef enum values { NULLValue = 0, ONEValue = 1 } values;

// FLAGS USING To check the equality of matrices
#define SUCCESS 1
#define FAILURE 0

// precision for comparing with zero
#define TOLERANCE (double)1e-8

// FLAGS USING To check the equality of matrices
typedef enum equality { EQUAL = 0, NOT_EQUAL = 1 } equality;

// Structure for zero in double type
#define DOUBLE_ZERO (double)0

// Basic matrix class structure
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// enum of flags to check the comparison of elements
// If elements equal, returns cmEqual flag
// If first element smaller than second, returns cmSMALLER flag
// If first element bigger than second, returns cmBIGGER flag
// If the error occurs, returns  COMP_ERR flag
// MAY BE UNUSED
typedef enum Comparison {
  COMPARISON_SMALLER_FLAG = -1,
  COMPARISON_EQUAL_FLAG = 0,
  COMPARISON_BIGGER_FLAG = 1,
  COMPARISON_ERROR = 2
} Comparison;

// CALCULATION_SUCCESS - flag that shows that we made a calculation successfully
// INPUT_ERR - Error, that returns if we have the incorrect matrix
// CALC_ERR - Returns if we have a Calculation error (mismatched matrix sizes;
// matrix for which calculations can't be performed, etc.)
typedef enum ReturnCodes {
  CALCULATION_SUCCESS = 0,
  INPUT_ERROR = 1,
  CALCULATION_ERROR = 2
} ReturnCodes;

// Basic functions that creates a matrix of some size
int s21_create_matrix(int rows, int columns, matrix_t *result);

// Basic function that able to remove the matrix
void s21_remove_matrix(matrix_t *A);

// Function that fills sizes of matrix and allocating place for it
int s21_matrix_allocation(int rows, int columns, matrix_t *result);

// Function that checks matrix legit
int s21_check_matrix_correction(const matrix_t *A);

// Function that checks matrix elements for legit
int s21_check_matrix_elems(const matrix_t *A);

// Function that checks matrix row for legit
int s21_check_rows(const matrix_t *A);

// Function that checks matrix row for legit with big precision
int s21_check_row_big_precision(const matrix_t *A);

// Checking for double being alright
int s21_check_double_correction(double a);

// int s21_is_legit_and_equal(matrix_t *A, matrix_t *result);

// Function that compares 2 doubles
int s21_double_compare(double a, double b);

// Function that checks if the size of matrix are equal
int s21_size_comparison(const matrix_t *A, const matrix_t *B);

// Function that removes and recreating matrix
int s21_loop_matrix_creator(int rows, int columns, matrix_t *result);

// Function that fills matrix from the array
int s21_matrix_array_fill(matrix_t *A, const double *list);

// Function that creates and fills matrix
int s21_matrix_creator(int rows, int columns, matrix_t *result,
                       const double *list);

// Function that recreates and fills matrix
int s21_matrix_recreator(int rows, int columns, matrix_t *result,
                         const double *list);

// Function that calculates determinant by recursion
double s21_solve_determ(matrix_t A);

// Function that creates minors from row and column that are removing from input
// matrix
int s21_create_minor(matrix_t *A, int row, int column, matrix_t *result);

// Creating minor and allocating place for it
int s21_create_minor_main(matrix_t *A, int row, int column, matrix_t *result);

// Help function for s21_mult_matrix function
void s21_help_mult_matrix_func(matrix_t *A, matrix_t *B, matrix_t *result);

// Help function for s21_calc_complements
int s21_help_calc_complements_func(matrix_t *A, matrix_t *result);

// int eq_doubles(double num1, double num2);

// Comparison function that check equality of 2 matrices
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Matrix operations functions
// Sum operation for 2 matrices
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Sub operation for 2 matrices
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Multiply operation for matrix and number
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

// Multiply operation for 2 matrices
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Matrix convert functions
// Function that transpose matrix
int s21_transpose(matrix_t *A, matrix_t *result);

// Function that is calculating minor and matrix of additional elements
int s21_calc_complements(matrix_t *A, matrix_t *result);

// Printing the determinant of matrix
int s21_determinant(matrix_t *A, double *result);

// Inversing matrix by |A|^(-1) = (1/|A|)*A^T
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif  // S21_MATRIX_H