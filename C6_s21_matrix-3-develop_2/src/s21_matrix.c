#include "s21_matrix.h"

// Basic function that creates a matrix of some size
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if ((rows <= NULLValue) || (columns <= NULLValue)) return INPUT_ERROR;
  int flag = CALCULATION_SUCCESS;
  if (result != NULL) {
    if (!s21_matrix_allocation(rows, columns, result)) {
      flag = INPUT_ERROR;
    } else {
      flag = CALCULATION_SUCCESS;
    }
  } else {
    flag = INPUT_ERROR;
  }
  return flag;
}

// Function that fills sizes of matrix and allocating place for it
int s21_matrix_allocation(int rows, int columns, matrix_t *result) {
  int flag = SUCCESS;
  result->matrix = (double **)malloc(rows * sizeof(double *));
  if (result->matrix == NULL) return FAILURE;
  result->rows = rows;
  result->columns = columns;
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)malloc(columns * sizeof(double));
    if (result->matrix[i] == NULL) {
      flag = FAILURE;
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      result->matrix = NULL;
      return flag;
    }
  }
  return flag;
}

// Basic function that able to remove the matrix
void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL && (A->rows) > NULLValue) {
      for (int i = 0; i < (A->rows); i++) {
        if (A->matrix[i] != NULL) free(A->matrix[i]);
      }
      free(A->matrix);
      A->matrix = NULL;
    }
    A->rows = NULLValue;
    A->columns = NULLValue;
  }
}

// Function that checks matrix legit
int s21_check_matrix_correction(const matrix_t *A) {
  int flag = SUCCESS;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    flag = SUCCESS;
  } else {
    flag = FAILURE;
  }
  return flag;
}

// Function that checks matrix elements for legit
int s21_check_matrix_elems(const matrix_t *A) {
  int flag = SUCCESS;
  for (int i = 0; flag == SUCCESS && i < (A->rows); i++) {
    if (A->matrix[i] == NULL) flag = FAILURE;
    for (int j = 0; flag == SUCCESS && j < (A->columns); j++) {
      if (!s21_check_double_correction(A->matrix[i][j])) flag = FAILURE;
    }
  }
  return flag;
}

// Function that checks matrix row for legit
int s21_check_rows(const matrix_t *A) {
  int flag = SUCCESS;
  for (int i = 0; i < (A->rows); i++) {
    if (A->matrix[i] == NULL) flag = FAILURE;
  }
  return flag;
}

// Function that checks matrix row for legit with big precision
int s21_check_row_big_precision(const matrix_t *A) {
  int flag = SUCCESS;
  if (s21_check_matrix_correction(A) && s21_check_matrix_elems(A) &&
      s21_check_rows(A)) {
    flag = SUCCESS;
  } else {
    flag = FAILURE;
  }
  return flag;
}

// Checking for double being alright
int s21_check_double_correction(double a) {
  int flag = SUCCESS;
  if (!isnan(a) && !isinf(a)) {
    flag = SUCCESS;
  } else {
    flag = FAILURE;
  }
  return flag;
}

// Function that compares 2 doubles
int s21_double_compare(double a, double b) {
  int flag;
  if (isnan(a) || isnan(b) ||
      (isinf(a) && isinf(b) &&
       ((a < DOUBLE_ZERO && b < DOUBLE_ZERO) ||
        (a > DOUBLE_ZERO && b > DOUBLE_ZERO))))
    return COMPARISON_ERROR;

  if (a >= b) {
    flag = COMPARISON_BIGGER_FLAG;
  } else {
    flag = COMPARISON_SMALLER_FLAG;
  }
  if (fabs(a - b) >= 1e-7) {
    flag = NOT_EQUAL * flag;
  } else {
    flag = EQUAL;
  }
  return flag;
}

// Function that checks if the size of matrix are equal
int s21_size_comparison(const matrix_t *A, const matrix_t *B) {
  int flag = SUCCESS;
  if ((A->rows != B->rows) || (A->columns != B->columns)) {
    flag = FAILURE;
  } else {
    flag = SUCCESS;
  }
  return flag;
}

// Function that removes and recreating matrix
int s21_loop_matrix_creator(int rows, int columns, matrix_t *result) {
  if (!s21_check_matrix_correction(result) || (rows <= NULLValue) ||
      (columns <= NULLValue))
    return INPUT_ERROR;
  s21_remove_matrix(result);
  int flag = s21_create_matrix(rows, columns, result);
  return flag;
}

// Function that fills matrix from the array
int s21_matrix_array_fill(matrix_t *A, const double *list) {
  if (!s21_check_matrix_correction(A) || !s21_check_rows(A) || list == NULL)
    return INPUT_ERROR;
  for (int i = 0, k = 0; i < (A->rows); i++) {
    for (int j = 0; j < (A->columns); j++, k++) {
      A->matrix[i][j] = list[k];
    }
  }
  return CALCULATION_SUCCESS;
}

// Function that creates and fills matrix
int s21_matrix_creator(int rows, int columns, matrix_t *result,
                       const double *list) {
  if (s21_create_matrix(rows, columns, result)) return INPUT_ERROR;
  return s21_matrix_array_fill(result, list);
}

// Function that recreates and fills matrix
int s21_matrix_recreator(int rows, int columns, matrix_t *result,
                         const double *list) {
  if (s21_loop_matrix_creator(rows, columns, result)) return INPUT_ERROR;
  return s21_matrix_array_fill(result, list);
}

// Function that calculates determinant by recursion
double s21_solve_determ(matrix_t A) {
  double det = 0;
  if (A.columns == 1)
    det = A.matrix[0][0];
  else {
    double det_min = 0;
    for (int j = 0; !isnan(det) && !isinf(det) && j < (A.columns); j++) {
      matrix_t minor;
      if (s21_create_minor_main(&A, 0, j, &minor)) {
        det = NAN;
        continue;
      }
      det_min = s21_solve_determ(minor);
      s21_remove_matrix(&minor);
      if (isnan(det_min)) {
        det = NAN;
        continue;
      }
      det += (pow(-1, j) * A.matrix[0][j] * det_min);
    }
  }
  return det;
}

// Function that creates minors from row and column that are removing from input
// matrix
int s21_create_minor(matrix_t *A, int row, int column, matrix_t *result) {
  int flag;
  if (!s21_check_matrix_correction(A) || !s21_check_rows(A) ||
      !s21_check_matrix_correction(result) || !s21_check_rows(result) ||
      (row < NULLValue) || (column < NULLValue))
    return INPUT_ERROR;
  if (!((row < (A->rows)) && (column < (A->columns)))) {
    flag = CALCULATION_ERROR;
  } else {
    flag = CALCULATION_SUCCESS;
  }
  if (flag || ((result->rows) != (A->rows - ONEValue)) ||
      ((result->columns) != (A->columns - ONEValue))) {
    flag = CALCULATION_ERROR;
  } else {
    flag = CALCULATION_SUCCESS;
  }
  if (!flag) {
    for (int i = 0, k = 0; k < (result->rows); i++, k++) {
      if (i == row) i++;
      for (int j = 0, l = 0; l < (result->columns); j++, l++) {
        if (j == column) j++;
        result->matrix[k][l] = A->matrix[i][j];
      }
    }
  }
  return flag;
}

// Creating minor and allocating place for it
int s21_create_minor_main(matrix_t *A, int row, int column, matrix_t *result) {
  if (A == NULL ||
      s21_create_matrix(A->rows - ONEValue, A->columns - ONEValue, result))
    return INPUT_ERROR;
  int flag = s21_create_minor(A, row, column, result);
  if (flag) s21_remove_matrix(result);
  return flag;
}

// Help function for s21_mult_matrix function
void s21_help_mult_matrix_func(matrix_t *A, matrix_t *B, matrix_t *result) {
  for (int i = 0; i < (result->rows); i++) {
    for (int j = 0; j < (result->columns); j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < (A->columns); k++) {
        result->matrix[i][j] += (A->matrix[i][k]) * (B->matrix[k][j]);
      }
    }
  }
}

// Help function for s21_calc_complements
int s21_help_calc_complements_func(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (A->rows == ONEValue) {
    result->matrix[0][0] = 1;
  } else {
    double det;
    for (int i = 0; !flag && i < (A->rows); i++) {
      for (int j = 0; !flag && j < (A->columns); j++) {
        matrix_t temp;
        det = 0;
        flag = s21_create_minor_main(A, i, j, &temp);
        if (!flag) {
          flag = s21_determinant(&temp, &det);
          s21_remove_matrix(&temp);
        }
        if (!flag) result->matrix[i][j] = pow(-1, i + j) * det;
      }
    }
  }
  return flag;
}

// Comparison function that check equality of 2 matrices
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;
  if (!s21_check_matrix_correction(A) || !s21_check_matrix_correction(B) ||
      !s21_size_comparison(A, B))
    return FAILURE;

  for (int i = 0; i < (A->rows); i++) {
    for (int j = 0; j < (A->columns); j++) {
      if (s21_double_compare(A->matrix[i][j], B->matrix[i][j]) != 0)
        flag = FAILURE;
    }
  }
  return flag;
}

// Sum operation for 2 matrices
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag;
  if (!s21_check_row_big_precision(A) || !s21_check_row_big_precision(B) ||
      result == NULL || !s21_check_rows(A) || !s21_check_rows(B))
    return INPUT_ERROR;
  if (!s21_size_comparison(A, B)) {
    flag = CALCULATION_ERROR;
  } else {
    flag = CALCULATION_SUCCESS;
  }
  if (flag || s21_create_matrix(A->rows, A->columns, result)) {
    flag = CALCULATION_ERROR;
  } else {
    flag = CALCULATION_SUCCESS;
  }
  if (!flag) {
    for (int i = 0; i < (A->rows); i++) {
      for (int j = 0; j < (A->columns); j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return flag;
}

// Multiply operation for matrix and number
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!s21_check_row_big_precision(A) || !s21_check_rows(A) || result == NULL)
    return INPUT_ERROR;
  int flag;
  if (!s21_check_double_correction(number)) {
    flag = INPUT_ERROR;
  } else {
    flag = CALCULATION_SUCCESS;
  }
  if (!flag)
    flag = (s21_create_matrix(A->rows, A->columns, result))
               ? CALCULATION_ERROR
               : CALCULATION_SUCCESS;
  if (!flag) {
    for (int i = 0; i < (A->rows); i++) {
      for (int j = 0; j < (A->columns); j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return flag;
}

// Sub operation for 2 matrices
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_check_row_big_precision(A) || !s21_check_row_big_precision(B) ||
      result == NULL || !s21_check_rows(A) || !s21_check_rows(B))
    return INPUT_ERROR;
  int flag;
  if (!s21_size_comparison(A, B)) {
    flag = CALCULATION_ERROR;
  } else {
    flag = CALCULATION_SUCCESS;
  }
  if (flag || s21_create_matrix(A->rows, A->columns, result)) {
    flag = CALCULATION_ERROR;
  } else {
    flag = CALCULATION_SUCCESS;
  }
  if (!flag) {
    for (int i = 0; i < (A->rows); i++) {
      for (int j = 0; j < (A->columns); j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return flag;
}

// Multiply operation for 2 matrices
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_check_row_big_precision(A) || !s21_check_row_big_precision(B) ||
      result == NULL || !s21_check_rows(A) || !s21_check_rows(B))
    return INPUT_ERROR;
  int flag;
  if (B->rows != A->columns) {
    flag = CALCULATION_ERROR;
  } else {
    flag = CALCULATION_SUCCESS;
  }
  if (flag || s21_create_matrix(A->rows, B->columns, result)) {
    flag = CALCULATION_ERROR;
  } else {
    flag = CALCULATION_SUCCESS;
  }
  if (!flag) {
    s21_help_mult_matrix_func(A, B, result);
  }
  return flag;
}

// Function that transpose matrix
int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!s21_check_matrix_correction(A) || !s21_check_rows(A) || result == NULL)
    return INPUT_ERROR;
  int flag;
  if (s21_create_matrix(A->columns, A->rows, result)) {
    flag = CALCULATION_ERROR;
  } else {
    flag = CALCULATION_SUCCESS;
  }
  if (!flag) {
    for (int i = 0; i < (A->rows); i++) {
      for (int j = 0; j < (A->columns); j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return flag;
}

// Printing the determinant of matrix
int s21_determinant(matrix_t *A, double *result) {
  if (!s21_check_row_big_precision(A) || !s21_check_rows(A) || result == NULL)
    return INPUT_ERROR;
  int flag = CALCULATION_SUCCESS;
  if ((A->rows) != (A->columns)) {
    flag = CALCULATION_ERROR;
  } else {
    flag = CALCULATION_SUCCESS;
  }
  if (!flag) *result = s21_solve_determ(*A);
  if (isnan(*result)) {
    flag = CALCULATION_ERROR;
    *result = 0;
  }
  return flag;
}

// Function that is calculating minor and matrix of additional elements
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!s21_check_row_big_precision(A) || !s21_check_rows(A) || result == NULL)
    return INPUT_ERROR;
  int flag = CALCULATION_SUCCESS;
  if ((A->rows) != (A->columns)) {
    flag = CALCULATION_ERROR;
  }
  if (flag || s21_create_matrix(A->rows, A->columns, result)) {
    flag = CALCULATION_ERROR;
  } else {
    flag = CALCULATION_SUCCESS;
  }
  if (!flag) {
    flag = s21_help_calc_complements_func(A, result);
    if (flag) s21_remove_matrix(result);
  }
  return flag;
}

// Inversing matrix by |A|^(-1) = (1/|A|)*A^T
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  double det = 0;
  int flag = CALCULATION_SUCCESS;
  if (!s21_check_row_big_precision(A) || !s21_check_rows(A)) return INPUT_ERROR;
  if (!s21_check_matrix_correction(A) || !s21_check_matrix_elems(A) ||
      result == NULL)
    return INPUT_ERROR;
  if ((A->rows) != (A->columns)) {
    flag = CALCULATION_ERROR;
  } else {
    flag = CALCULATION_SUCCESS;
  }
  if (!flag && !s21_determinant(A, &det) && det != 0) {
    flag = CALCULATION_SUCCESS;
  } else {
    flag = CALCULATION_ERROR;
  }
  if (!flag) {
    matrix_t temp_1;
    flag = s21_calc_complements(A, &temp_1);
    if (!flag) {
      matrix_t temp_2;
      flag = (s21_transpose(&temp_1, &temp_2)) ? CALCULATION_ERROR
                                               : CALCULATION_SUCCESS;
      s21_remove_matrix(&temp_1);
      if (!flag && det != 0) {
        det = (double)(1.0 / det);
        flag = (s21_mult_number(&temp_2, det, result)) ? CALCULATION_ERROR
                                                       : CALCULATION_SUCCESS;
        s21_remove_matrix(&temp_2);
      }
    }
  }
  return flag;
}