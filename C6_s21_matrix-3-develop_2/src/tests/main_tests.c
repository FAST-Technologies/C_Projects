#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_matrix.h"
// elevator begining
START_TEST(test_m_legit_1_2) {
  const matrix_t *matrix_1 = NULL;
  int output = 0, check = 0;
  output = s21_check_matrix_correction(matrix_1);
  ck_assert_int_eq(output, check);
}

START_TEST(test_m_legit_1_4) {
  matrix_t matrix_1;
  int output = 0, check = 0;

  matrix_1.columns = 5;
  matrix_1.rows = 5;
  matrix_1.matrix = (double **)calloc(matrix_1.rows, sizeof(double *));
  check = 1;

  output = s21_check_matrix_correction(&matrix_1);
  ck_assert_int_eq(output, check);
  free(matrix_1.matrix);
}

START_TEST(test_m_legit_1_5) {
  matrix_t matrix_1;
  int output = 0, check = 0;

  matrix_1.columns = 5;
  matrix_1.rows = 5;
  matrix_1.matrix = (double **)malloc(matrix_1.rows * sizeof(double *));
  check = 1;

  output = s21_check_matrix_correction(&matrix_1);
  ck_assert_int_eq(output, check);
  free(matrix_1.matrix);
}

START_TEST(test_m_legit_1_6) {
  matrix_t matrix_1;
  int output = 0, check = 0;

  matrix_1.columns = 5;
  matrix_1.rows = 5;
  matrix_1.matrix = (double **)calloc(matrix_1.rows, sizeof(double *));
  matrix_1.rows = 0;
  check = 0;

  output = s21_check_matrix_correction(&matrix_1);
  ck_assert_int_eq(output, check);
  free(matrix_1.matrix);
}

START_TEST(test_m_legit_1_7) {
  matrix_t matrix_1;
  int output = 0, check = 0;

  matrix_1.columns = -5;
  matrix_1.rows = 5;
  matrix_1.matrix = (double **)calloc(matrix_1.rows, sizeof(double *));
  check = 0;

  output = s21_check_matrix_correction(&matrix_1);
  ck_assert_int_eq(output, check);
  free(matrix_1.matrix);
}

START_TEST(test_m_legit_1_8) {
  matrix_t matrix_1;
  int output = 0, check = 0;

  matrix_1.columns = -5;
  matrix_1.rows = 5;
  matrix_1.matrix = NULL;
  check = 0;

  output = s21_check_matrix_correction(&matrix_1);
  ck_assert_int_eq(output, check);
}

// elevator create matrix
START_TEST(test_m_create_1) {
  matrix_t matrix_1;
  int rows = 5, columns = 5;
  int output_1 = 0, output_2 = 0, check_1 = 0, check_2 = 1;

  output_1 = s21_create_matrix(rows, columns, &matrix_1);
  output_2 = s21_check_matrix_correction(&matrix_1);
  ck_assert_int_eq(output_1, check_1);
  ck_assert_int_eq(output_2, check_2);

  s21_remove_matrix(&matrix_1);
  ck_assert_int_eq(matrix_1.rows, 0);
  ck_assert_int_eq(matrix_1.columns, 0);
}

START_TEST(test_m_create_2) {
  matrix_t matrix_1 = {NULL, 0, 0};
  int rows = 5, columns = 0;
  int output_1 = 0, output_2 = 0, check_1 = 1, check_2 = 0;

  output_1 = s21_create_matrix(rows, columns, &matrix_1);
  output_2 = s21_check_matrix_correction(&matrix_1);
  ck_assert_int_eq(output_1, check_1);
  ck_assert_int_eq(output_2, check_2);
}

START_TEST(test_m_create_3) {
  matrix_t matrix_1 = {NULL, 0, 0};
  int rows = -5, columns = 5;
  int output_1 = 0, output_2 = 0, check_1 = 1, check_2 = 0;

  output_1 = s21_create_matrix(rows, columns, &matrix_1);
  output_2 = s21_check_matrix_correction(&matrix_1);
  ck_assert_int_eq(output_1, check_1);
  ck_assert_int_eq(output_2, check_2);
}
START_TEST(test_m_create_4) {
  matrix_t *matrix_1 = NULL;
  int rows = 5, columns = 5;
  int output_1 = 0, output_2 = 0, check_1 = 1, check_2 = 0;

  output_1 = s21_create_matrix(rows, columns, matrix_1);
  output_2 = s21_check_matrix_correction(matrix_1);
  ck_assert_int_eq(output_1, check_1);
  ck_assert_int_eq(output_2, check_2);
}

START_TEST(test_double_legit) {
  double a = 0;
  int check = 1;

  ck_assert_int_eq(s21_check_double_correction(a), check);

  a = -5555555.55555;
  check = 1;
  ck_assert_int_eq(s21_check_double_correction(a), check);
  a = 5555555.55555;
  check = 1;
  ck_assert_int_eq(s21_check_double_correction(a), check);
  a = NAN;
  check = 0;
  ck_assert_int_eq(s21_check_double_correction(a), check);
  a = -NAN;
  check = 0;
  ck_assert_int_eq(s21_check_double_correction(a), check);
  a = -INFINITY;
  check = 0;
  ck_assert_int_eq(s21_check_double_correction(a), check);
  a = INFINITY;
  check = 0;
  ck_assert_int_eq(s21_check_double_correction(a), check);
}

START_TEST(test_double_compare_1) {
  double a = 0, b = 0;
  int check = 0;

  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = 0.5;
  b = 0.5;
  check = 0;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = -0.5;
  b = 0.5;
  check = -1;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = 0.5;
  b = -0.5;
  check = 1;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = 1.0000001;
  b = 1.0;
  check = 1;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = 1.0000001;
  b = 1.0000001;
  check = 0;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = -1.0000000;
  b = -1.00000001;
  check = 0;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = 0.0000005;
  b = -0.0000005;
  check = 1;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = -0.0000005;
  b = -0.0000005;
  check = 0;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = 0.00000005;
  b = -0.00000005;
  check = 1;
  ck_assert_int_eq(s21_double_compare(a, b), check);
}
START_TEST(test_double_compare_2) {
  double a = 0, b = 0;
  int check = 0;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = INFINITY;
  b = 0.5;
  check = 1;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = -INFINITY;
  b = 0.5;
  check = -1;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = -INFINITY;
  b = 0;
  check = -1;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = INFINITY;
  b = 0;
  check = 1;
  ck_assert_int_eq(s21_double_compare(a, b), check);

  a = INFINITY;
  b = INFINITY;
  check = 2;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = INFINITY;
  b = -INFINITY;
  check = 1;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = -INFINITY;
  b = INFINITY;
  check = -1;
  ck_assert_int_eq(s21_double_compare(a, b), check);

  a = NAN;
  b = NAN;
  check = 2;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = NAN;
  b = 0.5;
  check = 2;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = NAN;
  b = -NAN;
  check = 2;
  ck_assert_int_eq(s21_double_compare(a, b), check);

  a = INFINITY;
  b = NAN;
  check = 2;
  ck_assert_int_eq(s21_double_compare(a, b), check);
  a = -INFINITY;
  b = NAN;
  check = 2;
  ck_assert_int_eq(s21_double_compare(a, b), check);
}

// START_TEST(test_m_size_comp) {
//   matrix_t A, B;
//   int check = 1;
//   A.columns = 5;
//   A.rows = 5;
//   B.columns = 5;
//   B.rows = 5;
////  for (int i = 0; i < A.columns * A.rows; i++) {
////    aA[i] = i;
////  }
////  for (int j = 0; j < b.columns * b.rows; j++) {
////    b[j] = j;
////  }
//  ck_assert_int_eq(s21_matrix_size_compare(&A, &B), check);
//  check = 0;
//  A.columns = 4;
//  A.rows = 5;
//  B.columns = 5;
//  B.rows = 5;
//  ck_assert_int_eq(s21_matrix_size_compare(&A, &B), check);
//  check = 1;
//  A.columns = 4;
//  A.rows = 5;
//  B.columns = 4;
//  B.rows = 5;
//  ck_assert_int_eq(s21_matrix_size_compare(&A, &B), check);
//  check = 0;
//  A.columns = 1;
//  A.rows = 2;
//  B.columns = 3;
//  B.rows = 4;
//  ck_assert_int_eq(s21_matrix_size_compare(&A, &B), check);
//  check = 0;
//  A.columns = 4;
//  A.rows = 5;
//  B.columns = 4;
//  B.rows = 3;
//  ck_assert_int_eq(s21_matrix_size_compare(&A, &B), check);
//}

START_TEST(test_m_build_1) {
  matrix_t matrix_1;
  int columns = 5, rows = 5;
  double arr[1000];
  int check = 1;

  check = 0;
  for (int i = 0; i < columns * rows; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrix_1, arr), check);
  ck_assert_int_eq(matrix_1.columns, columns);
  ck_assert_int_eq(matrix_1.rows, rows);
  ck_assert_int_eq(matrix_1.matrix[0][4], arr[4]);
  check = 1;
  ck_assert_int_eq(s21_check_matrix_correction(&matrix_1), check);
  s21_remove_matrix(&matrix_1);
}
START_TEST(test_m_build_2) {
  matrix_t matrix_1;
  int columns = 5, rows = -1;
  double arr[1000];
  int check = 1;
  arr[0] = 5;

  check = 1;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrix_1, arr), check);
}
START_TEST(test_m_build_3) {
  matrix_t matrix_1;
  int columns = 0, rows = 5;
  double arr[1000];
  int check = 1;
  arr[0] = 5;

  check = 1;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrix_1, arr), check);
}
START_TEST(test_m_build_4) {
  matrix_t *matrix_1 = NULL;
  int columns = 5, rows = 5;
  double arr[1000];
  int check = 1;

  check = 1;
  for (int i = 0; i < columns * rows; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, matrix_1, arr), check);
}
START_TEST(test_m_build_5) {
  matrix_t matrix_1;
  int columns = 5, rows = -1;
  const double *arr = NULL;
  int check = 1;

  check = 1;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrix_1, arr), check);
}
START_TEST(test_m_build_6) {
  matrix_t matrix_1;
  int columns = 5, rows = 5;
  double arr[1000];
  int check = 1;

  check = 0;
  for (int i = 0; i < columns * rows - 4; i++) {
    arr[i] = i;
  }
  arr[columns * rows - 4] = NAN;
  arr[columns * rows - 3] = -NAN;
  arr[columns * rows - 2] = INFINITY;
  arr[columns * rows - 1] = -INFINITY;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrix_1, arr), check);
  ck_assert_int_eq(matrix_1.columns, columns);
  ck_assert_int_eq(matrix_1.rows, rows);
  ck_assert_int_eq(matrix_1.matrix[0][4], arr[4]);
  ck_assert_int_eq(isnan(matrix_1.matrix[4][1]), 1);
  ck_assert_int_eq(isnan(matrix_1.matrix[4][2]), 1);
  ck_assert_int_eq(isinf(matrix_1.matrix[4][3]), 1);
  ck_assert_int_eq(isinf(matrix_1.matrix[4][4]), -1);
  check = 1;
  ck_assert_int_eq(s21_check_matrix_correction(&matrix_1), check);
  s21_remove_matrix(&matrix_1);
}
START_TEST(test_m_rebuild) {
  matrix_t matrix_1;
  int columns = 5, rows = 5;
  double arr[1000];
  int check = 1;

  check = 0;
  for (int i = 0; i < columns * rows; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrix_1, arr), check);
  ck_assert_int_eq(matrix_1.columns, columns);
  ck_assert_int_eq(matrix_1.rows, rows);
  ck_assert_int_eq(matrix_1.matrix[0][4], arr[4]);
  check = 1;
  ck_assert_int_eq(s21_check_matrix_correction(&matrix_1), check);

  columns = 10;
  rows = 15;
  for (int i = columns * rows; i > 0; i--) {
    arr[i] = columns * rows - i;
  }
  check = 0;
  ck_assert_int_eq(s21_matrix_recreator(rows, columns, &matrix_1, arr), check);
  ck_assert_int_eq(matrix_1.columns, columns);
  ck_assert_int_eq(matrix_1.rows, rows);
  ck_assert_int_eq(matrix_1.matrix[0][0], 0);
  ck_assert_int_eq(matrix_1.matrix[0][1], columns * rows - 1);
  ck_assert_int_eq(matrix_1.matrix[14][9], 1);
  check = 1;
  ck_assert_int_eq(s21_check_matrix_correction(&matrix_1), check);

  columns = 0;
  rows = 15;
  for (int i = 0; i < 15; i++) {
    arr[i] = columns * rows - i;
  }
  check = 1;
  ck_assert_int_eq(s21_matrix_recreator(rows, columns, &matrix_1, arr), check);
  ck_assert_int_eq(matrix_1.matrix[0][0], 0);
  ck_assert_int_eq(matrix_1.matrix[0][1], 150 - 1);
  ck_assert_int_eq(matrix_1.matrix[14][9], 1);
  check = 1;
  ck_assert_int_eq(s21_check_matrix_correction(&matrix_1), check);

  columns = 6;
  rows = -5;
  for (int i = 0; i < 30; i++) {
    arr[i] = i;
  }
  check = 1;
  ck_assert_int_eq(s21_matrix_recreator(rows, columns, &matrix_1, arr), check);
  ck_assert_int_eq(matrix_1.matrix[0][0], 0);
  ck_assert_int_eq(matrix_1.matrix[0][1], 150 - 1);
  ck_assert_int_eq(matrix_1.matrix[14][9], 1);
  check = 1;
  ck_assert_int_eq(s21_check_matrix_correction(&matrix_1), check);

  columns = 6;
  rows = 5;
  check = 1;
  matrix_t *matrix_2 = NULL;
  ck_assert_int_eq(s21_matrix_recreator(rows, columns, matrix_2, arr), check);

  s21_remove_matrix(&matrix_1);
}
START_TEST(test_m_lagit_2_1) {
  matrix_t matrix_1;
  int columns = 5, rows = 5;
  double arr[1000];
  int check = 0;

  matrix_1.columns = 2;
  matrix_1.rows = 2;
  matrix_1.matrix = NULL;
  ck_assert_int_eq(s21_check_matrix_correction(&matrix_1), check);
  ck_assert_int_eq(s21_check_row_big_precision(&matrix_1), check);

  for (int i = 0; i < columns * rows; i++) {
    arr[i] = i;
  }
  check = 0;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrix_1, arr), check);
  ck_assert_int_eq(matrix_1.columns, columns);
  ck_assert_int_eq(matrix_1.rows, rows);
  ck_assert_int_eq(matrix_1.matrix[0][4], arr[4]);
  check = 1;
  ck_assert_int_eq(s21_check_matrix_correction(&matrix_1), check);
  ck_assert_int_eq(s21_check_row_big_precision(&matrix_1), check);

  const matrix_t *matrix_2 = NULL;
  check = 0;
  ck_assert_int_eq(s21_check_matrix_correction(matrix_2), check);
  ck_assert_int_eq(s21_check_row_big_precision(matrix_2), check);

  matrix_1.columns = 0;
  ck_assert_int_eq(s21_check_matrix_correction(&matrix_1), check);
  ck_assert_int_eq(s21_check_row_big_precision(&matrix_1), check);

  matrix_1.columns = columns;

  arr[2] = NAN;
  ck_assert_int_eq(s21_matrix_recreator(rows, columns, &matrix_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_check_matrix_correction(&matrix_1), check);
  check = 0;
  ck_assert_int_eq(s21_check_row_big_precision(&matrix_1), check);

  arr[2] = INFINITY;
  ck_assert_int_eq(s21_matrix_recreator(rows, columns, &matrix_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_check_matrix_correction(&matrix_1), check);
  check = 0;
  ck_assert_int_eq(s21_check_row_big_precision(&matrix_1), check);
  s21_remove_matrix(&matrix_1);
}
// elevator comparison
START_TEST(test_m_equality_1) {
  matrix_t matrx_1, matrx_2;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&matrx_1, &matrx_2), check);
  matrx_2.matrix[2][4] = 5;
  check = 0;
  ck_assert_int_eq(s21_eq_matrix(&matrx_1, &matrx_2), check);

  matrx_2.matrix[2][4] = INFINITY;
  matrx_1.matrix[2][4] = INFINITY;
  check = 0;
  ck_assert_int_eq(s21_eq_matrix(&matrx_1, &matrx_2), check);
  matrx_1.matrix[2][4] = -INFINITY;
  check = 0;
  ck_assert_int_eq(s21_eq_matrix(&matrx_1, &matrx_2), check);
  matrx_2.matrix[2][4] = -INFINITY;
  check = 0;
  ck_assert_int_eq(s21_eq_matrix(&matrx_1, &matrx_2), check);
  matrx_2.matrix[2][4] = NAN;
  matrx_1.matrix[2][4] = NAN;
  check = 0;
  ck_assert_int_eq(s21_eq_matrix(&matrx_1, &matrx_2), check);
  matrx_1.matrix[2][4] = rows * columns - 1;
  check = 0;
  ck_assert_int_eq(s21_eq_matrix(&matrx_1, &matrx_2), check);
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * 2;
  }
  ck_assert_int_eq(s21_matrix_recreator(rows, columns, &matrx_2, arr), check);
  ck_assert_int_eq(s21_eq_matrix(&matrx_1, &matrx_2), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_equality_2) {
  matrix_t matrx_1, matrx_2;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = 1;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 2;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  ck_assert_int_eq(s21_eq_matrix(&matrx_1, &matrx_2), check);
  rows = 3;
  columns = 1;
  ck_assert_int_eq(s21_matrix_recreator(rows, columns, &matrx_2, arr), check);
  ck_assert_int_eq(s21_eq_matrix(&matrx_1, &matrx_2), check);
  columns = 5;
  ck_assert_int_eq(s21_matrix_recreator(rows, columns, &matrx_2, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&matrx_1, &matrx_2), check);
  matrx_1.rows = 0;
  check = 0;
  ck_assert_int_eq(s21_eq_matrix(&matrx_1, &matrx_2), check);
  matrx_1.rows = 3;
  matrx_2.columns = -5;
  ck_assert_int_eq(s21_eq_matrix(&matrx_1, &matrx_2), check);
  matrx_2.columns = 5;

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_equality_3) {
  matrix_t matrx_1, matrx_2;
  int rows = 1, columns = 1;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&matrx_1, &matrx_2), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
// elevator summ
START_TEST(test_m_summ_1) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 2;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 2;
  ck_assert_int_eq(s21_sum_matrix(&matrx_1, &matrx_2, &result), check);
  rows = 3;
  check = 0;
  ck_assert_int_eq(s21_matrix_recreator(rows, columns, &matrx_2, arr), check);
  ck_assert_int_eq(s21_sum_matrix(&matrx_1, &matrx_2, &result), check);
  double k = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++, k++) {
      ck_assert_double_eq(result.matrix[i][j], k * 2);
    }
  }
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
  s21_remove_matrix(&result);
}
START_TEST(test_m_summ_2) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  arr[5] = INFINITY;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 1;
  ck_assert_int_eq(s21_sum_matrix(&matrx_1, &matrx_2, &result), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_summ_3) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  arr[5] = NAN;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  arr[5] = 5;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 1;
  ck_assert_int_eq(s21_sum_matrix(&matrx_1, &matrx_2, &result), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}

START_TEST(test_m_summ_4) {
  matrix_t matrx_1, matrx_2;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  };
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  arr[5] = 5;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 1;
  matrix_t *result = NULL;
  ck_assert_int_eq(s21_sum_matrix(&matrx_1, &matrx_2, result), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}

START_TEST(test_m_summ_5) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 5, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 3;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 2;
  ck_assert_int_eq(s21_sum_matrix(&matrx_1, &matrx_2, &result), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_summ_6) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = rows * columns - i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  ck_assert_int_eq(s21_sum_matrix(&matrx_1, &matrx_2, &result), check);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], rows * columns);
    }
  }
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
  s21_remove_matrix(&result);
}
START_TEST(test_m_summ_7) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 1, columns = 1;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = rows * columns - i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  ck_assert_int_eq(s21_sum_matrix(&matrx_1, &matrx_2, &result), check);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], rows * columns);
    }
  }
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
  s21_remove_matrix(&result);
}
START_TEST(test_m_summ_8) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  matrx_1.rows = 0;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 1;
  ck_assert_int_eq(s21_sum_matrix(&matrx_1, &matrx_2, &result), check);
  matrx_1.rows = rows;
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_summ_9) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  matrx_2.columns = 0;
  check = 1;
  ck_assert_int_eq(s21_sum_matrix(&matrx_1, &matrx_2, &result), check);
  matrx_2.columns = columns;
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_summ_10) {
  matrix_t matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  matrix_t *matrx_1 = NULL;
  check = 1;
  ck_assert_int_eq(s21_sum_matrix(matrx_1, &matrx_2, &result), check);
  s21_remove_matrix(&matrx_2);
}
// elevator substraction
START_TEST(test_m_sub_1) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 2;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 2;
  ck_assert_int_eq(s21_sub_matrix(&matrx_1, &matrx_2, &result), check);
  rows = 3;
  check = 0;
  ck_assert_int_eq(s21_matrix_recreator(rows, columns, &matrx_2, arr), check);
  ck_assert_int_eq(s21_sub_matrix(&matrx_1, &matrx_2, &result), check);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], 0);
    }
  }
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
  s21_remove_matrix(&result);
}
START_TEST(test_m_sub_2) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  arr[5] = INFINITY;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 1;
  ck_assert_int_eq(s21_sub_matrix(&matrx_1, &matrx_2, &result), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_sub_3) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  arr[5] = NAN;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  arr[5] = 5;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 1;
  ck_assert_int_eq(s21_sub_matrix(&matrx_1, &matrx_2, &result), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_sub_4) {
  matrix_t matrx_1, matrx_2;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  matrix_t *result = NULL;
  check = 1;
  ck_assert_int_eq(s21_sub_matrix(&matrx_1, &matrx_2, result), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_sub_5) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 10, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 3;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 2;
  ck_assert_int_eq(s21_sub_matrix(&matrx_1, &matrx_2, &result), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_sub_6) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = rows * columns;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  ck_assert_int_eq(s21_sub_matrix(&matrx_1, &matrx_2, &result), check);
  double k = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++, k++) {
      ck_assert_double_eq(result.matrix[i][j], -rows * columns + k);
    }
  }
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
  s21_remove_matrix(&result);
}
START_TEST(test_m_sub_7) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 1, columns = 1;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = rows * columns;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  ck_assert_int_eq(s21_sub_matrix(&matrx_1, &matrx_2, &result), check);
  double k = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++, k++) {
      ck_assert_double_eq(result.matrix[i][j], -rows * columns + k);
    }
  }
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
  s21_remove_matrix(&result);
}
START_TEST(test_m_sub_8) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  matrx_1.rows = 0;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 1;
  ck_assert_int_eq(s21_sub_matrix(&matrx_1, &matrx_2, &result), check);
  matrx_1.rows = rows;
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_sub_9) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  matrx_2.columns = -5;
  check = 1;
  ck_assert_int_eq(s21_sub_matrix(&matrx_1, &matrx_2, &result), check);
  matrx_2.columns = columns;
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_sub_10) {
  matrix_t matrx_1, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  matrix_t *matrx_2 = NULL;
  check = 1;
  ck_assert_int_eq(s21_sub_matrix(&matrx_1, matrx_2, &result), check);
  s21_remove_matrix(&matrx_1);
}
// elevator multiplication by number
START_TEST(test_m_mult_num_1) {
  matrix_t matrx_1;
  int rows = 3, columns = 5;
  double arr[100], num = 5;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  matrix_t *result = NULL;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_mult_number(&matrx_1, num, result), check);
  matrix_t result_2;
  check = 0;
  ck_assert_int_eq(s21_mult_number(&matrx_1, num, &result_2), check);
  double k = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++, k++) {
      ck_assert_double_eq(result_2.matrix[i][j], k * num);
    }
  }
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result_2);
}
START_TEST(test_m_mult_num_2) {
  matrix_t matrx_1, result;
  int rows = 3, columns = 5;
  double arr[100], num = 5;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  arr[4] = NAN;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_mult_number(&matrx_1, num, &result), check);

  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_mult_num_3) {
  matrix_t matrx_1, result;
  int rows = 3, columns = 5;
  double arr[100], num = 5;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  arr[4] = INFINITY;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_mult_number(&matrx_1, num, &result), check);

  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_mult_num_4) {
  matrix_t matrx_1, result;
  int rows = 3, columns = 5;
  double arr[100], num = 5;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  matrx_1.rows = 0;
  check = 1;
  ck_assert_int_eq(s21_mult_number(&matrx_1, num, &result), check);
  matrx_1.rows = rows;
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_mult_num_5) {
  matrix_t matrx_1, result;
  int rows = 3, columns = 5;
  double arr[100], num = INFINITY;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_mult_number(&matrx_1, num, &result), check);

  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_mult_num_6) {
  matrix_t matrx_1, result;
  int rows = 3, columns = 5;
  double arr[100], num = NAN;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_mult_number(&matrx_1, num, &result), check);

  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_mult_num_7) {
  matrix_t matrx_1, result;
  int rows = 3, columns = 5;
  double arr[100], num = 0.0000001;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * 10;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_mult_number(&matrx_1, num, &result), check);
  double k = 0;
  num *= 10;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++, k++) {
      ck_assert_double_eq(result.matrix[i][j], k * num);
    }
  }
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
}
START_TEST(test_m_mult_num_8) {
  matrix_t matrx_1, result;
  int rows = 1, columns = 1;
  double arr[100], num = 0.0002;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = 500;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_mult_number(&matrx_1, num, &result), check);

  ck_assert_double_eq_tol(result.matrix[0][0], arr[0] * num, 0.0000001);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
}
START_TEST(test_m_mult_num_9) {
  matrix_t matrx_1, result;
  int rows = 5, columns = 1;
  double arr[100], num = 2;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * 10;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_mult_number(&matrx_1, num, &result), check);
  double k = 0;
  num *= 10;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++, k++) {
      ck_assert_double_eq(result.matrix[i][j], k * num);
    }
  }
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
}
START_TEST(test_m_mult_num_10) {
  matrix_t matrx_1, result;
  int rows = 3, columns = 5;
  double arr[100], num = 5;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  matrx_1.rows = -5;
  check = 1;
  ck_assert_int_eq(s21_mult_number(&matrx_1, num, &result), check);
  matrx_1.rows = rows;
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_mult_num_11) {
  matrix_t result;
  double num = 5;
  int check = 0;
  matrix_t *matrx_1 = NULL;
  check = 1;
  ck_assert_int_eq(s21_mult_number(matrx_1, num, &result), check);
}

START_TEST(test_m_complex_1) {
  matrix_t matrx_1, result;
  int rows = 3, columns = 5;
  double arr[100], num = 55.555;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_mult_number(&matrx_1, num, &result), check);
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * num;
  }
  ck_assert_int_eq(s21_matrix_recreator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_double_eq(s21_eq_matrix(&result, &matrx_1), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
}
// elevator multiplication by matrix
START_TEST(test_m_mult_m_1) {
  matrix_t matrx_1, matrx_2, result, check_m;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 5;
  columns = 3;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = rows * columns - i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  ck_assert_int_eq(s21_mult_matrix(&matrx_1, &matrx_2, &result), check);

  rows = 3;
  columns = 3;
  ck_assert_int_eq(s21_create_matrix(rows, columns, &check_m), check);
  check_m.matrix[0][0] = 60;
  check_m.matrix[0][1] = 50;
  check_m.matrix[0][2] = 40;
  check_m.matrix[1][0] = 285;
  check_m.matrix[1][1] = 250;
  check_m.matrix[1][2] = 215;
  check_m.matrix[2][0] = 510;
  check_m.matrix[2][1] = 450;
  check_m.matrix[2][2] = 390;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], check_m.matrix[i][j]);
    }
  }

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
  s21_remove_matrix(&check_m);
  s21_remove_matrix(&result);
}
START_TEST(test_m_mult_m_2) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 3;
  columns = 3;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = rows * columns - i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 2;
  ck_assert_int_eq(s21_mult_matrix(&matrx_1, &matrx_2, &result), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_mult_m_3) {
  matrix_t matrx_1, matrx_2;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 5;
  columns = 3;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = rows * columns - i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  matrix_t *result = NULL;
  check = 1;
  ck_assert_int_eq(s21_mult_matrix(&matrx_1, &matrx_2, result), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_mult_m_4) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  arr[5] = NAN;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 5;
  columns = 3;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = rows * columns - i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);

  check = 1;
  ck_assert_int_eq(s21_mult_matrix(&matrx_1, &matrx_2, &result), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_mult_m_5) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 5;
  columns = 3;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = rows * columns - i;
  }
  arr[5] = INFINITY;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  check = 1;
  ck_assert_int_eq(s21_mult_matrix(&matrx_1, &matrx_2, &result), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_mult_m_6) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 5;
  columns = 3;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = rows * columns - i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  matrx_1.rows = -5;
  check = 1;
  ck_assert_int_eq(s21_mult_matrix(&matrx_1, &matrx_2, &result), check);
  matrx_1.rows = 3;
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_mult_m_7) {
  matrix_t matrx_1, matrx_2, result, check_m;
  int rows = 5, columns = 10;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i / 100 + i * 2 - i * 0.5;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 10;
  columns = 1;
  arr[0] = 0.001;
  arr[1] = -0.001;
  arr[2] = 0.001;
  arr[3] = -0.001;
  arr[4] = 0.001;
  arr[5] = -0.001;
  arr[6] = 0.001;
  arr[7] = -0.001;
  arr[8] = 0.001;
  arr[9] = -0.001;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  ck_assert_int_eq(s21_mult_matrix(&matrx_1, &matrx_2, &result), check);
  rows = 5;
  columns = 1;
  ck_assert_int_eq(s21_create_matrix(rows, columns, &check_m), check);
  check_m.matrix[0][0] = -0.0075;
  check_m.matrix[1][0] = -0.0075;
  check_m.matrix[2][0] = -0.0075;
  check_m.matrix[3][0] = -0.0075;
  check_m.matrix[4][0] = -0.0075;

  for (int i = 0; i < rows; i++) {
    ck_assert_double_eq_tol(result.matrix[i][0], check_m.matrix[i][0],
                            0.00000005);
  }
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
  s21_remove_matrix(&check_m);
  s21_remove_matrix(&result);
}
START_TEST(test_m_mult_m_8) {
  matrix_t matrx_1, matrx_2, result, check_m;
  int rows = 15, columns = 1;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i / 100 + i * 2 - i * 0.5;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 1;
  columns = 1;
  arr[0] = 5.0;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  ck_assert_int_eq(s21_mult_matrix(&matrx_1, &matrx_2, &result), check);
  rows = 15;
  columns = 1;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i / 100 + i * 2 - i * 0.5;
    arr[i] *= 5.0;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  for (int i = 0; i < rows; i++) {
    ck_assert_double_eq_tol(result.matrix[i][0], check_m.matrix[i][0],
                            0.00000005);
  }
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
  s21_remove_matrix(&check_m);
  s21_remove_matrix(&result);
}
START_TEST(test_m_mult_m_9) {
  matrix_t matrx_1, matrx_2, result, check_m;
  int rows = 1, columns = 2;
  double arr[100];
  int check = 0;
  arr[0] = 15;
  arr[1] = 5;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 2;
  columns = 2;
  arr[0] = 0;
  arr[1] = -1;
  arr[2] = 1;
  arr[3] = 0;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  ck_assert_int_eq(s21_mult_matrix(&matrx_1, &matrx_2, &result), check);
  rows = 1;
  columns = 2;
  arr[0] = 5;
  arr[1] = -15;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
  s21_remove_matrix(&check_m);
  s21_remove_matrix(&result);
}
START_TEST(test_m_mult_m_10) {
  matrix_t result, matrx_2;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  rows = 5;
  columns = 3;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = rows * columns - i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  matrix_t *matrx_1 = NULL;
  check = 1;
  ck_assert_int_eq(s21_mult_matrix(matrx_1, &matrx_2, &result), check);

  s21_remove_matrix(&matrx_2);
}
START_TEST(test_m_mult_m_11) {
  matrix_t result, matrx_1;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  rows = 5;
  columns = 3;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = rows * columns - i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  matrix_t *matrx_2 = NULL;
  check = 1;
  ck_assert_int_eq(s21_mult_matrix(&matrx_1, matrx_2, &result), check);

  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_mult_m_12) {
  matrix_t matrx_1, matrx_2, result;
  int rows = 3, columns = 5;
  double arr[100];
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows = 5;
  columns = 3;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = rows * columns - i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_2, arr), check);
  matrx_2.columns = 0;
  check = 1;
  ck_assert_int_eq(s21_mult_matrix(&matrx_1, &matrx_2, &result), check);
  matrx_2.columns = columns;
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
}

START_TEST(test_m_minor_maker_1_1) {
  matrix_t matrx_1, result;
  int rows = 5, columns = 5;
  double arr[100];
  int rm_row = 0, rm_column = 0;
  int check = 0;

  matrix_t *tmp = NULL;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_create_matrix(rows, columns, &result), check);

  check = 1;
  ck_assert_int_eq(s21_check_matrix_correction(&matrx_1), check);
  ck_assert_int_eq(s21_check_matrix_correction(&result), check);
  // ck_assert_int_eq(s21_check_rows(&matrx_1), check);
  // ck_assert_int_eq(s21_check_rows(&result), check);

  ck_assert_int_eq(s21_create_minor(tmp, rm_row, rm_column, &result), check);
  ck_assert_int_eq(s21_create_minor(&matrx_1, rm_row, rm_column, tmp), check);
  matrx_1.columns = 0;
  matrx_1.rows = rows;
  result.columns = columns;
  result.rows = rows;
  ck_assert_int_eq(s21_create_minor(&matrx_1, rm_row, rm_column, &result),
                   check);
  matrx_1.columns = columns;
  result.rows = -5;
  ck_assert_int_eq(s21_create_minor(&matrx_1, rm_row, rm_column, &result),
                   check);
  result.rows = rows;
  rm_row = -5;
  ck_assert_int_eq(s21_create_minor(&matrx_1, rm_row, rm_column, &result),
                   check);
  rm_row = 0;
  rm_column = -5;
  ck_assert_int_eq(s21_create_minor(&matrx_1, rm_row, rm_column, &result),
                   check);
  rm_column = 5;
  result.columns = columns - 1;
  result.rows = rows - 1;
  check = 2;
  ck_assert_int_eq(s21_create_minor(&matrx_1, rm_row, rm_column, &result),
                   check);
  rm_column = 0;
  rm_row = 6;
  ck_assert_int_eq(s21_create_minor(&matrx_1, rm_row, rm_column, &result),
                   check);
  rm_row = 0;
  result.columns = columns;
  result.rows = rows;
  ck_assert_int_eq(s21_create_minor(&matrx_1, rm_row, rm_column, &result),
                   check);
  result.columns = columns + 1;
  ck_assert_int_eq(s21_create_minor(&matrx_1, rm_row, rm_column, &result),
                   check);
  result.columns = columns;
  result.rows = rows - 2;
  ck_assert_int_eq(s21_create_minor(&matrx_1, rm_row, rm_column, &result),
                   check);
  result.columns = columns;
  result.rows = rows;

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
}
START_TEST(test_m_minor_maker_1_2) {
  matrix_t matrx_1, result, check_m;
  int rows = 5, columns = 5;
  double arr[100];
  int rm_row = 0, rm_column = 0;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows--;
  columns--;
  ck_assert_int_eq(s21_create_matrix(rows, columns, &result), check);
  ck_assert_int_eq(s21_create_minor(&matrx_1, rm_row, rm_column, &result),
                   check);
  for (int i = 0, j = 6; i < rows * columns; i++, j++) {
    if (j % 5 == 0) j++;
    arr[i] = j;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}
START_TEST(test_m_minor_maker_1_3) {
  matrix_t matrx_1, result, check_m;
  int rows = 5, columns = 7;
  double arr[100];
  int rm_row = 1, rm_column = 3;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * 2;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows--;
  columns--;
  ck_assert_int_eq(s21_create_matrix(rows, columns, &result), check);
  ck_assert_int_eq(s21_create_minor(&matrx_1, rm_row, rm_column, &result),
                   check);

  for (int k = 0, l = 0; k < rows * columns; k++, l++) {
    if (l == 3 || l == 17 || l == 24 || l == 31) l++;
    if (l == 7) {
      l += 7;
    }
    arr[k] = l * 2;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}
START_TEST(test_m_minor_maker_1_4) {
  matrix_t matrx_1, result, check_m;
  int rows = 5, columns = 7;
  double arr[100];
  int rm_row = 4, rm_column = 6;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * 2;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  rows--;
  columns--;
  ck_assert_int_eq(s21_create_matrix(rows, columns, &result), check);
  ck_assert_int_eq(s21_create_minor(&matrx_1, rm_row, rm_column, &result),
                   check);

  for (int k = 0, l = 0; k < rows * columns; k++, l++) {
    if (l == 6 || l == 13 || l == 20 || l == 27) l++;
    arr[k] = l * 2;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}

START_TEST(test_m_minor_maker_2_1) {
  matrix_t matrx_1, result;
  int rows = 5, columns = 5;
  double arr[100];
  int rm_row = 0, rm_column = 0;
  int check = 0;

  matrix_t *tmp = NULL;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);

  check = 1;
  ck_assert_int_eq(s21_check_matrix_correction(&matrx_1), check);
  // ck_assert_int_eq(s21_check_rows(&matrx_1), check);
  ck_assert_int_eq(s21_create_minor_main(tmp, rm_row, rm_column, &result),
                   check);
  ck_assert_int_eq(s21_create_minor_main(&matrx_1, rm_row, rm_column, tmp),
                   check);
  matrx_1.columns = 0;
  ck_assert_int_eq(s21_create_minor_main(&matrx_1, rm_row, rm_column, &result),
                   check);
  matrx_1.columns = columns;
  matrx_1.rows = 1;
  ck_assert_int_eq(s21_create_minor_main(&matrx_1, rm_row, rm_column, &result),
                   check);
  matrx_1.rows = rows;
  matrx_1.columns = -5;
  ck_assert_int_eq(s21_create_minor_main(&matrx_1, rm_row, rm_column, &result),
                   check);
  matrx_1.columns = columns;
  rm_row = -5;
  ck_assert_int_eq(s21_create_minor_main(&matrx_1, rm_row, rm_column, &result),
                   check);
  rm_row = 0;
  rm_column = -5;
  ck_assert_int_eq(s21_create_minor_main(&matrx_1, rm_row, rm_column, &result),
                   check);
  rm_column = 5;
  check = 2;
  ck_assert_int_eq(s21_create_minor_main(&matrx_1, rm_row, rm_column, &result),
                   check);
  rm_column = 0;
  rm_row = 6;
  ck_assert_int_eq(s21_create_minor_main(&matrx_1, rm_row, rm_column, &result),
                   check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_minor_maker_2_2) {
  matrix_t matrx_1, result, check_m;
  int rows = 5, columns = 5;
  double arr[100];
  int rm_row = 0, rm_column = 0;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_create_minor_main(&matrx_1, rm_row, rm_column, &result),
                   check);
  rows--;
  columns--;
  for (int i = 0, j = 6; i < rows * columns; i++, j++) {
    if (j % 5 == 0) j++;
    arr[i] = j;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}
START_TEST(test_m_minor_maker_2_3) {
  matrix_t matrx_1, result, check_m;
  int rows = 5, columns = 7;
  double arr[100];
  int rm_row = 1, rm_column = 3;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * 2;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_create_minor_main(&matrx_1, rm_row, rm_column, &result),
                   check);
  rows--;
  columns--;
  for (int k = 0, l = 0; k < rows * columns; k++, l++) {
    if (l == 3 || l == 17 || l == 24 || l == 31) l++;
    if (l == 7) {
      l += 7;
    }
    arr[k] = l * 2;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}
START_TEST(test_m_minor_maker_2_4) {
  matrix_t matrx_1, result, check_m;
  int rows = 5, columns = 7;
  double arr[100];
  int rm_row = 4, rm_column = 6;
  int check = 0;

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * 2;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_create_minor_main(&matrx_1, rm_row, rm_column, &result),
                   check);
  rows--;
  columns--;
  for (int k = 0, l = 0; k < rows * columns; k++, l++) {
    if (l == 6 || l == 13 || l == 20 || l == 27) l++;
    arr[k] = l * 2;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}

START_TEST(test_m_determinant_1_1) {
  matrix_t matrx_1;
  int rows = 5, columns = 5;
  double arr[100];
  int check = 0;
  double det = 1, det_check = 0;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * 2;
  }

  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  det = s21_solve_determ(matrx_1);
  ck_assert_double_eq_tol(det, det_check, 0.00000005);

  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_determinant_1_2) {
  matrix_t matrx_1;
  int rows = 3, columns = 3;
  double arr[100];
  int check = 0;
  double det = 1, det_check = 4;
  arr[0] = 1;
  arr[1] = 2;
  arr[2] = 3;
  arr[3] = 2;
  arr[4] = 2;
  arr[5] = 3;
  arr[6] = 3;
  arr[7] = 2;
  arr[8] = 1;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  det = s21_solve_determ(matrx_1);
  ck_assert_double_eq_tol(det, det_check, 0.00000005);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_determinant_1_3) {
  matrix_t matrx_1;
  int rows = 4, columns = 4;
  double arr[100];
  int check = 0;
  double det = 1, det_check = 22;
  arr[0] = 1;
  arr[1] = 2;
  arr[2] = 3;
  arr[3] = 4;
  arr[4] = 3;
  arr[5] = 3;
  arr[6] = 3;
  arr[7] = 4;
  arr[8] = 2;
  arr[9] = 3;
  arr[10] = 2;
  arr[11] = 3;
  arr[12] = 1;
  arr[13] = 1;
  arr[14] = 1;
  arr[15] = 5;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  det = s21_solve_determ(matrx_1);
  ck_assert_double_eq_tol(det, det_check, 0.00000005);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_determinant_1_4) {
  matrix_t matrx_1;
  int rows = 3, columns = 3;
  double arr[100];
  int check = 0;
  double det = 1, det_check = 7986;
  for (int i = 0, j = 0; i < rows * columns; i++, j += 5) {
    arr[i] = j + (double)i / 2;
  }
  arr[rows * columns - 1] *= -1;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  det = s21_solve_determ(matrx_1);
  ck_assert_double_eq_tol(det, det_check, 0.00000005);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_determinant_1_5) {
  matrix_t matrx_1;
  int rows = 7, columns = 7;
  double arr[1000];
  int check = 0;
  double det = 1, det_check = 0;
  for (int i = 0, j = 0; i < rows * columns; i++, j += 5) {
    arr[i] = j + (double)i / 2 + j * i + ((double)j + 1.5) / 2;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  det = s21_solve_determ(matrx_1);
  ck_assert_double_eq_tol(det, det_check, 0.00000005);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_determinant_1_6) {
  matrix_t matrx_1;
  int rows = 4, columns = 4;
  double arr[1000];
  int check = 0;
  double det = 1, det_check = -20715209266.50003;
  for (int i = 0, j = 0; i < rows * columns; i++, j += 5) {
    arr[i] = j + (double)i / 2 + j * i + ((double)j + 1.5) / 2;
    if (i % 3 == 0) arr[i] *= -1;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  det = s21_solve_determ(matrx_1);
  ck_assert_double_eq_tol(det, det_check, 0.00009);
  s21_remove_matrix(&matrx_1);
}
// elevator determinant
START_TEST(test_m_determinant_2_1) {
  matrix_t matrx_1;
  int rows = 5, columns = 2;
  double arr[100];
  int check = 0;
  double det = 1;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * 2;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 2;
  ck_assert_int_eq(s21_determinant(&matrx_1, &det), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_determinant_2_2) {
  matrix_t matrx_1;
  int rows = 5, columns = 5;
  double arr[100];
  int check = 0;
  double det = 1, det_check = 0;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * 2;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_determinant(&matrx_1, &det), check);
  ck_assert_double_eq_tol(det, det_check, 0.00000005);

  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_determinant_2_3) {
  matrix_t matrx_1;
  int rows = 5, columns = 5;
  double arr[100];
  int check = 0;
  double det = 1;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * 2;
  }
  arr[3] = NAN;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_determinant(&matrx_1, &det), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_determinant_2_4) {
  matrix_t matrx_1;
  int rows = 5, columns = 5;
  double arr[100];
  int check = 0;
  double det = 1;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * 2;
  }
  arr[3] = -INFINITY;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_determinant(&matrx_1, &det), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_determinant_2_5) {
  matrix_t matrx_1;
  int rows = 5, columns = 5;
  double arr[100];
  int check = 0;
  double *det = NULL;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * 2;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_determinant(&matrx_1, det), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_determinant_2_6) {
  matrix_t matrx_1;
  int rows = 5, columns = 5;
  double arr[100];
  int check = 0;
  double det = 1;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i * 2;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  matrx_1.rows = 0;
  check = 1;
  ck_assert_int_eq(s21_determinant(&matrx_1, &det), check);
  matrx_1.rows = rows;
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_determinant_2_7) {
  matrix_t matrx_1;
  int rows = 3, columns = 3;
  double arr[100];
  int check = 0;
  double det = 1, det_check = 7986;
  for (int i = 0, j = 0; i < rows * columns; i++, j += 5) {
    arr[i] = j + (double)i / 2;
  }
  arr[rows * columns - 1] *= -1;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_determinant(&matrx_1, &det), check);
  ck_assert_double_eq_tol(det, det_check, 0.00000005);

  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_determinant_2_8) {
  matrix_t matrx_1;
  int rows = 6, columns = 6;
  double arr[100];
  int check = 0;
  double det = 1, det_check = -328870544041.22076;
  arr[0] = 1;
  arr[1] = 11;
  arr[2] = 23;
  arr[3] = 12;
  arr[4] = 123;
  arr[5] = -55;
  arr[6] = 556;
  arr[7] = -6;
  arr[8] = -0.005;
  arr[9] = 0.003;
  arr[10] = 0.003;
  arr[11] = 1000;
  arr[12] = 12;
  arr[13] = 423;
  arr[14] = 454;
  arr[15] = 656;
  arr[16] = 323;
  arr[17] = 213;
  arr[18] = 33;
  arr[19] = 0;
  arr[20] = 0;
  arr[21] = 0;
  arr[22] = 0;
  arr[23] = 88;
  arr[24] = 212;
  arr[25] = 34;
  arr[26] = 0;
  arr[27] = 43;
  arr[28] = -1;
  arr[29] = -1;
  arr[30] = -66;
  arr[31] = -5;
  arr[32] = -3;
  arr[33] = 1;
  arr[34] = 2;
  arr[35] = 3;

  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_determinant(&matrx_1, &det), check);
  ck_assert_double_eq_tol(det, det_check, 0.009);

  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_determinant_2_9) {
  matrix_t matrx_1;
  int rows = 1, columns = 1;
  double arr[100];
  int check = 0;
  double det = 1, det_check = 100;
  for (int i = 0; i < rows * columns; i++) {
    arr[i] = 50 * (i + 1) * 2;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_determinant(&matrx_1, &det), check);
  ck_assert_double_eq_tol(det, det_check, 0.00000005);

  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_determinant_2_10) {
  matrix_t matrx_1;
  int rows = 2, columns = 2;
  double arr[100];
  int check = 0;
  double det = 1, det_check = 56;
  arr[0] = 5;
  arr[1] = 2;
  arr[2] = -3;
  arr[3] = 10;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_determinant(&matrx_1, &det), check);
  ck_assert_double_eq_tol(det, det_check, 0.00000005);

  s21_remove_matrix(&matrx_1);
}
// elevator transpose
START_TEST(test_m_transpose_1) {
  matrix_t matrx_1, result, check_m;
  int rows = 3, columns = 3;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }

  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_transpose(&matrx_1, &result), check);

  arr[0] = 0;
  arr[1] = 3;
  arr[2] = 6;
  arr[3] = 1;
  arr[4] = 4;
  arr[5] = 7;
  arr[6] = 2;
  arr[7] = 5;
  arr[8] = 8;
  ck_assert_int_eq(s21_matrix_creator(columns, rows, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}
START_TEST(test_m_transpose_2) {
  matrix_t matrx_1, result;
  int rows = 3, columns = 3;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  matrx_1.rows = 0;
  ck_assert_int_eq(s21_transpose(&matrx_1, &result), check);
  matrx_1.rows = rows;
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_transpose_3) {
  matrix_t matrx_1, result;
  int rows = 3, columns = 3;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  matrx_1.columns = -5;
  ck_assert_int_eq(s21_transpose(&matrx_1, &result), check);
  matrx_1.columns = rows;
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_transpose_4) {
  matrix_t result;
  int check = 1;
  matrix_t *matrx_1 = NULL;
  ck_assert_int_eq(s21_transpose(matrx_1, &result), check);
}
START_TEST(test_m_transpose_5) {
  matrix_t matrx_1, result, check_m;
  int rows = 3, columns = 5;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i + (double)i / 10;
  }

  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_transpose(&matrx_1, &result), check);

  arr[0] = 0;
  arr[1] = 5.5;
  arr[2] = 11;

  arr[3] = 1.1;
  arr[4] = 6.6;
  arr[5] = 12.1;

  arr[6] = 2.2;
  arr[7] = 7.7;
  arr[8] = 13.2;

  arr[9] = 3.3;
  arr[10] = 8.8;
  arr[11] = 14.3;

  arr[12] = 4.4;
  arr[13] = 9.9;
  arr[14] = 15.4;

  ck_assert_int_eq(s21_matrix_creator(columns, rows, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}
START_TEST(test_m_transpose_6) {
  matrix_t matrx_1, result, check_m;
  int rows = 1, columns = 20;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }

  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_transpose(&matrx_1, &result), check);
  ck_assert_int_eq(s21_matrix_creator(columns, rows, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}
START_TEST(test_m_transpose_7) {
  matrix_t matrx_1, result;
  int rows = 1, columns = 1;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }

  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_transpose(&matrx_1, &result), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &matrx_1), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
}
START_TEST(test_m_transpose_8) {
  matrix_t matrx_1;
  int rows = 3, columns = 3;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  matrix_t *result = NULL;
  ck_assert_int_eq(s21_transpose(&matrx_1, result), check);
  s21_remove_matrix(&matrx_1);
}
// elevator compliments
START_TEST(test_m_compliments_1) {
  matrix_t matrx_1, result, check_m;
  int rows = 4, columns = 4;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  arr[rows * columns - 1] *= -1;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_calc_complements(&matrx_1, &result), check);

  arr[0] = 120;
  arr[1] = -240;
  arr[2] = 120;
  arr[3] = 0;

  arr[4] = -240;
  arr[5] = 480;
  arr[6] = -240;
  arr[7] = 0;

  arr[8] = 120;
  arr[9] = -240;
  arr[10] = 120;
  arr[11] = 0;

  arr[12] = 0;
  arr[13] = 0;
  arr[14] = 0;
  arr[15] = 0;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}
START_TEST(test_m_compliments_2) {
  matrix_t matrx_1, result;
  int rows = 4, columns = 4;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  arr[rows * columns - 1] = NAN;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_calc_complements(&matrx_1, &result), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_compliments_3) {
  matrix_t matrx_1, result;
  int rows = 4, columns = 4;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  arr[1] = INFINITY;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_calc_complements(&matrx_1, &result), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_compliments_4) {
  matrix_t matrx_1, result;
  int rows = 4, columns = 4;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  matrx_1.rows = 0;
  ck_assert_int_eq(s21_calc_complements(&matrx_1, &result), check);
  matrx_1.rows = rows;
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_compliments_5) {
  matrix_t matrx_1, result;
  int rows = 4, columns = 4;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  matrx_1.columns = -5;
  ck_assert_int_eq(s21_calc_complements(&matrx_1, &result), check);
  matrx_1.columns = columns;
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_compliments_6) {
  matrix_t matrx_1;
  matrix_t *result = NULL;
  int rows = 4, columns = 4;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_calc_complements(&matrx_1, result), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_compliments_7) {
  matrix_t matrx_1, result;
  int rows = 4, columns = 5;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 2;
  ck_assert_int_eq(s21_calc_complements(&matrx_1, &result), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_compliments_8) {
  matrix_t result;
  matrix_t *matrx_1 = NULL;
  int check = 1;
  ck_assert_int_eq(s21_calc_complements(matrx_1, &result), check);
}
START_TEST(test_m_compliments_9) {
  matrix_t matrx_1, result, check_m;
  int rows = 2, columns = 2;
  int check = 0;
  double arr[100];

  arr[0] = 1;
  arr[1] = 2;
  arr[2] = -4;
  arr[3] = 5;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_calc_complements(&matrx_1, &result), check);

  arr[0] = 5;
  arr[1] = 4;
  arr[2] = -2;
  arr[3] = 1;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}
START_TEST(test_m_compliments_10) {
  matrix_t matrx_1, result, check_m;
  int rows = 1, columns = 1;
  int check = 0;
  double arr[100];

  arr[0] = -50;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_calc_complements(&matrx_1, &result), check);

  arr[0] = 1;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}
// elevator inverse matrix
START_TEST(test_m_inverse_m_1) {
  matrix_t matrx_1, result, check_m;
  int rows = 2, columns = 2;
  int check = 0;
  double arr[100];

  arr[0] = 4;
  arr[1] = 7;
  arr[2] = 2;
  arr[3] = 6;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_inverse_matrix(&matrx_1, &result), check);
  arr[0] = 0.6;
  arr[1] = -0.7;
  arr[2] = -0.2;
  arr[3] = 0.4;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}
START_TEST(test_m_inverse_m_2) {
  matrix_t *matrx_1 = NULL;
  matrix_t result;
  int check = 1;
  ck_assert_int_eq(s21_inverse_matrix(matrx_1, &result), check);
}
START_TEST(test_m_inverse_m_3) {
  matrix_t matrx_1, result;
  int rows = 2, columns = 2;
  int check = 0;
  double arr[100];

  arr[0] = 4;
  arr[1] = 7;
  arr[2] = INFINITY;
  arr[3] = 6;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_inverse_matrix(&matrx_1, &result), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_inverse_m_4) {
  matrix_t matrx_1, result;
  int rows = 2, columns = 2;
  int check = 0;
  double arr[100];

  arr[0] = 4;
  arr[1] = 7;
  arr[2] = NAN;
  arr[3] = 6;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_inverse_matrix(&matrx_1, &result), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_inverse_m_5) {
  matrix_t matrx_1, result;
  int rows = 2, columns = 2;
  int check = 0;
  double arr[100];

  arr[0] = 4;
  arr[1] = 7;
  arr[2] = -INFINITY;
  arr[3] = 6;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_inverse_matrix(&matrx_1, &result), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_inverse_m_6) {
  matrix_t matrx_1, result;
  int rows = 2, columns = 2;
  int check = 0;
  double arr[100];

  arr[0] = 4;
  arr[1] = 7;
  arr[2] = -5;
  arr[3] = 6;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  matrx_1.rows = 0;
  check = 1;
  ck_assert_int_eq(s21_inverse_matrix(&matrx_1, &result), check);
  matrx_1.rows = rows;
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_inverse_m_7) {
  matrix_t matrx_1, result;
  int rows = 2, columns = 2;
  int check = 0;
  double arr[100];

  arr[0] = 4;
  arr[1] = 7;
  arr[2] = -5;
  arr[3] = 6;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  matrx_1.columns = -5;
  check = 1;
  ck_assert_int_eq(s21_inverse_matrix(&matrx_1, &result), check);
  matrx_1.columns = columns;
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_inverse_m_8) {
  matrix_t matrx_1, result;
  int rows = 2, columns = 3;
  int check = 0;
  double arr[100];

  arr[0] = 4;
  arr[1] = 7;
  arr[2] = 2;
  arr[3] = 6;
  arr[4] = 5;
  arr[5] = 1;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 2;
  ck_assert_int_eq(s21_inverse_matrix(&matrx_1, &result), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_inverse_m_9) {
  matrix_t matrx_1, result;
  int rows = 2, columns = 1;
  int check = 0;
  double arr[100];

  arr[0] = 4;
  arr[1] = 7;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 2;
  ck_assert_int_eq(s21_inverse_matrix(&matrx_1, &result), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_inverse_m_10) {
  matrix_t *result = NULL;
  matrix_t matrx_1;
  int rows = 2, columns = 2;
  int check = 0;
  double arr[100];

  arr[0] = 4;
  arr[1] = 7;
  arr[2] = 2;
  arr[3] = 6;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 1;
  ck_assert_int_eq(s21_inverse_matrix(&matrx_1, result), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_inverse_m_11) {
  matrix_t matrx_1, result;
  int rows = 4, columns = 4;
  int check = 0;
  double arr[100];

  for (int i = 0; i < rows * columns; i++) {
    arr[i] = i;
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 2;
  ck_assert_int_eq(s21_inverse_matrix(&matrx_1, &result), check);
  s21_remove_matrix(&matrx_1);
}
START_TEST(test_m_inverse_m_12) {
  matrix_t matrx_1, result, check_m;
  int rows = 4, columns = 4;
  int check = 0;
  double arr[100];

  arr[0] = -5;
  arr[1] = 1;
  arr[2] = 1;
  arr[3] = 1;

  arr[4] = 0;
  arr[5] = 0;
  arr[6] = 0;
  arr[7] = 1;

  arr[8] = 1;
  arr[9] = 1;
  arr[10] = -1;
  arr[11] = -1;

  arr[12] = 0;
  arr[13] = 1;
  arr[14] = 1;
  arr[15] = 0;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_inverse_matrix(&matrx_1, &result), check);

  arr[0] = -(double)1 / 5;
  arr[1] = (double)1 / 5;
  arr[2] = 0;
  arr[3] = (double)1 / 5;

  arr[4] = (double)1 / 10;
  arr[5] = (double)2 / 5;
  arr[6] = (double)1 / 2;
  arr[7] = (double)2 / 5;

  arr[8] = -(double)1 / 10;
  arr[9] = -(double)2 / 5;
  arr[10] = -(double)1 / 2;
  arr[11] = (double)3 / 5;

  arr[12] = 0;
  arr[13] = 1;
  arr[14] = 0;
  arr[15] = 0;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}
START_TEST(test_m_inverse_m_14) {
  matrix_t matrx_1, result, check_m;
  int rows = 1, columns = 1;
  int check = 0;
  double arr[100];

  arr[0] = -50;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_inverse_matrix(&matrx_1, &result), check);
  arr[0] = -(double)1 / 50;
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);
  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}
START_TEST(test_m_inverse_m_15) {
  matrix_t matrx_1, result;
  int rows = 3, columns = 5;
  int check = 0;
  double arr[100];

  arr[0] = 1;
  arr[1] = 2;
  arr[2] = 3;
  arr[3] = 3;
  arr[4] = 2;

  arr[5] = 5;
  arr[6] = 6;
  arr[7] = 7;
  arr[8] = 8;
  arr[9] = 9;

  arr[10] = 10;
  arr[11] = 12;
  arr[12] = 13;
  arr[13] = 13;
  arr[14] = 12;

  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  check = 2;
  ck_assert_int_eq(s21_inverse_matrix(&matrx_1, &result), check);
  s21_remove_matrix(&matrx_1);
}

START_TEST(test_m_inverse_m_16) {
  const int size = 2;
  matrix_t mtest = {0};
  matrix_t mresult = {0};
  int check = 0;
  double arr[100];

  arr[0] = 1;
  arr[1] = 1;
  arr[2] = 1;
  arr[3] = 1;

  ck_assert_int_eq(s21_matrix_creator(size, size, &mtest, arr), check);
  ck_assert_int_eq(s21_inverse_matrix(&mtest, &mresult), 2);
  s21_remove_matrix(&mresult);
  s21_remove_matrix(&mtest);
}

// Ошибка - матрица имеет нулевой детерминант
START_TEST(test_m_inverse_m_17) {
  matrix_t mtest = {0};
  matrix_t mresult = {0};
  int check = 0;
  double arr[100];

  arr[0] = 1;
  arr[1] = 2;
  arr[2] = 3;
  arr[3] = 2;
  arr[4] = 4;
  arr[5] = 6;
  arr[6] = 3;
  arr[7] = 6;
  arr[8] = 9;
  ck_assert_int_eq(s21_matrix_creator(3, 3, &mtest, arr), check);
  ck_assert_int_eq(s21_inverse_matrix(&mtest, &mresult), 2);
  s21_remove_matrix(&mresult);
  s21_remove_matrix(&mtest);
}

// Ошибка - переданы некорректные аргументы
START_TEST(test_m_inverse_m_18) {
  matrix_t mtest = {0};
  matrix_t mresult = {0};
  ck_assert_int_eq(s21_inverse_matrix(&mtest, &mresult), 1);
  s21_remove_matrix(&mresult);
  s21_remove_matrix(&mtest);
}

// Успешное вычисление обратной матрицы 2х2
START_TEST(test_m_inverse_m_19) {
  matrix_t mtest = {0};
  matrix_t mresult = {0};
  matrix_t mexpected = {0};
  int check = 0;
  double arr[100], arr1[100];

  arr[0] = 2;
  arr[1] = 3;
  arr[2] = 4;
  arr[3] = 5;
  arr1[0] = -2.5;
  arr1[1] = 1.5;
  arr1[2] = 2;
  arr1[3] = -1;
  ck_assert_int_eq(s21_matrix_creator(2, 2, &mtest, arr), check);
  ck_assert_int_eq(s21_matrix_creator(2, 2, &mexpected, arr1), check);

  ck_assert_int_eq(s21_inverse_matrix(&mtest, &mresult), 0);
  ck_assert_int_eq(s21_eq_matrix(&mresult, &mexpected), 1);
  s21_remove_matrix(&mexpected);
  s21_remove_matrix(&mresult);
  s21_remove_matrix(&mtest);
}

// Успешное вычисление обратной матрицы 3х3
START_TEST(test_m_inverse_m_20) {
  matrix_t mtest = {0};
  matrix_t mresult = {0};
  matrix_t mexpected = {0};
  int check = 0;
  double arr[100], arr1[100];
  arr[0] = 2.0;
  arr[1] = 5.0;
  arr[2] = 7.0;
  arr[3] = 6.0;
  arr[4] = 3.0;
  arr[5] = 4.0;
  arr[6] = 5.0;
  arr[7] = -2.0;
  arr[8] = -3.0;
  arr1[0] = 1.0;
  arr1[1] = -1.0;
  arr1[2] = 1.0;
  arr1[3] = -38.0;
  arr1[4] = 41.0;
  arr1[5] = -34.0;
  arr1[6] = 27.0;
  arr1[7] = -29.0;
  arr1[8] = 24.0;
  ck_assert_int_eq(s21_matrix_creator(3, 3, &mtest, arr), check);
  ck_assert_int_eq(s21_matrix_creator(3, 3, &mexpected, arr1), check);
  ck_assert_int_eq(s21_inverse_matrix(&mtest, &mresult), 0);
  ck_assert_int_eq(s21_eq_matrix(&mresult, &mexpected), 1);
  s21_remove_matrix(&mexpected);
  s21_remove_matrix(&mresult);
  s21_remove_matrix(&mtest);
}

START_TEST(test_m_complex_2) {
  matrix_t matrx_1, matrx_2, result, check_m;
  int rows = 5, columns = 5;
  int check = 0;
  double arr[100];

  arr[0] = 5;
  arr[1] = -1;
  arr[2] = -1;
  arr[3] = 1;
  arr[4] = 1;

  arr[5] = 0;
  arr[6] = 0;
  arr[7] = 1;
  arr[8] = 2;
  arr[9] = 2;

  arr[10] = -2;
  arr[11] = -2;
  arr[12] = 1;
  arr[13] = 1;
  arr[14] = 0;

  arr[15] = 0;
  arr[16] = 1;
  arr[17] = 0;
  arr[18] = -1;
  arr[19] = 2;

  arr[20] = 4;
  arr[21] = 4;
  arr[22] = -4;
  arr[23] = 0;
  arr[24] = -4;

  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_inverse_matrix(&matrx_1, &result), check);

  for (int i = 0, k = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++, k++) {
      if (i == j)
        arr[k] = 1;
      else
        arr[k] = 0;
    }
  }
  ck_assert_int_eq(s21_matrix_creator(rows, columns, &check_m, arr), check);
  ck_assert_int_eq(s21_mult_matrix(&matrx_1, &result, &matrx_2), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&matrx_2, &check_m), check);
  check = 0;
  s21_remove_matrix(&result);
  ck_assert_int_eq(s21_transpose(&matrx_2, &result), check);
  check = 1;
  ck_assert_int_eq(s21_eq_matrix(&result, &check_m), check);

  s21_remove_matrix(&matrx_1);
  s21_remove_matrix(&matrx_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_m);
}
START_TEST(test_m_complex_3) {
  matrix_t matrx_1, result;
  int rows = 5, columns = 5;
  int check = 0;
  double arr[100];
  double det = 0, det_check = -120, mult = 5;

  arr[0] = 5;
  arr[1] = -1;
  arr[2] = -1;
  arr[3] = 1;
  arr[4] = 1;

  arr[5] = 0;
  arr[6] = 0;
  arr[7] = 1;
  arr[8] = 2;
  arr[9] = 2;

  arr[10] = -2;
  arr[11] = -2;
  arr[12] = 1;
  arr[13] = 1;
  arr[14] = 0;

  arr[15] = 0;
  arr[16] = 1;
  arr[17] = 0;
  arr[18] = -1;
  arr[19] = 2;

  arr[20] = 4;
  arr[21] = 4;
  arr[22] = -4;
  arr[23] = 0;
  arr[24] = -4;

  ck_assert_int_eq(s21_matrix_creator(rows, columns, &matrx_1, arr), check);
  ck_assert_int_eq(s21_determinant(&matrx_1, &det), check);
  ck_assert_double_eq_tol(det, det_check, 0.00000009);
  ck_assert_int_eq(s21_mult_number(&matrx_1, mult, &result), check);
  ck_assert_int_eq(s21_determinant(&result, &det), check);
  det_check *= pow(5, 5);
  ck_assert_double_eq_tol(det, det_check, 0.00000009);
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrx_1);
}

START_TEST(test_extra) {
  matrix_t *matr_1 = NULL;
  matrix_t matr_2;
  s21_remove_matrix(matr_1);
  matr_2.matrix = NULL;
  s21_remove_matrix(&matr_2);
  double arr[5];
  arr[0] = 5;
  s21_matrix_array_fill(matr_1, arr);
}

void test_block_1(SRunner *sr) {
  Suite *s = suite_create("Test block #1");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);

  tcase_add_test(tc_core, test_m_legit_1_2);
  tcase_add_test(tc_core, test_m_legit_1_4);
  tcase_add_test(tc_core, test_m_legit_1_5);
  tcase_add_test(tc_core, test_m_legit_1_6);
  tcase_add_test(tc_core, test_m_legit_1_7);
  tcase_add_test(tc_core, test_m_legit_1_8);
  tcase_add_test(tc_core, test_m_lagit_2_1);

  tcase_add_test(tc_core, test_m_create_1);
  tcase_add_test(tc_core, test_m_create_2);
  tcase_add_test(tc_core, test_m_create_3);
  tcase_add_test(tc_core, test_m_create_4);

  tcase_add_test(tc_core, test_double_compare_1);
  tcase_add_test(tc_core, test_double_compare_2);

  tcase_add_test(tc_core, test_double_legit);

  tcase_add_test(tc_core, test_m_build_1);
  tcase_add_test(tc_core, test_m_build_2);
  tcase_add_test(tc_core, test_m_build_3);
  tcase_add_test(tc_core, test_m_build_4);
  tcase_add_test(tc_core, test_m_build_5);
  tcase_add_test(tc_core, test_m_build_6);

  tcase_add_test(tc_core, test_m_rebuild);

  tcase_add_test(tc_core, test_m_equality_1);
  tcase_add_test(tc_core, test_m_equality_2);
  tcase_add_test(tc_core, test_m_equality_3);

  tcase_add_test(tc_core, test_m_summ_1);
  tcase_add_test(tc_core, test_m_summ_2);
  tcase_add_test(tc_core, test_m_summ_3);
  tcase_add_test(tc_core, test_m_summ_4);
  tcase_add_test(tc_core, test_m_summ_5);
  tcase_add_test(tc_core, test_m_summ_6);
  tcase_add_test(tc_core, test_m_summ_7);
  tcase_add_test(tc_core, test_m_summ_8);
  tcase_add_test(tc_core, test_m_summ_9);
  tcase_add_test(tc_core, test_m_summ_10);

  tcase_add_test(tc_core, test_m_sub_1);
  tcase_add_test(tc_core, test_m_sub_2);
  tcase_add_test(tc_core, test_m_sub_3);
  tcase_add_test(tc_core, test_m_sub_4);
  tcase_add_test(tc_core, test_m_sub_5);
  tcase_add_test(tc_core, test_m_sub_6);
  tcase_add_test(tc_core, test_m_sub_7);
  tcase_add_test(tc_core, test_m_sub_8);
  tcase_add_test(tc_core, test_m_sub_9);
  tcase_add_test(tc_core, test_m_sub_10);

  tcase_add_test(tc_core, test_m_mult_num_1);
  tcase_add_test(tc_core, test_m_mult_num_2);
  tcase_add_test(tc_core, test_m_mult_num_3);
  tcase_add_test(tc_core, test_m_mult_num_4);
  tcase_add_test(tc_core, test_m_mult_num_5);
  tcase_add_test(tc_core, test_m_mult_num_6);
  tcase_add_test(tc_core, test_m_mult_num_7);
  tcase_add_test(tc_core, test_m_mult_num_8);
  tcase_add_test(tc_core, test_m_mult_num_9);
  tcase_add_test(tc_core, test_m_mult_num_10);
  tcase_add_test(tc_core, test_m_mult_num_11);

  tcase_add_test(tc_core, test_m_mult_m_1);
  tcase_add_test(tc_core, test_m_mult_m_2);
  tcase_add_test(tc_core, test_m_mult_m_3);
  tcase_add_test(tc_core, test_m_mult_m_4);
  tcase_add_test(tc_core, test_m_mult_m_5);
  tcase_add_test(tc_core, test_m_mult_m_6);
  tcase_add_test(tc_core, test_m_mult_m_7);
  tcase_add_test(tc_core, test_m_mult_m_8);
  tcase_add_test(tc_core, test_m_mult_m_9);
  tcase_add_test(tc_core, test_m_mult_m_10);
  tcase_add_test(tc_core, test_m_mult_m_11);
  tcase_add_test(tc_core, test_m_mult_m_12);

  srunner_add_suite(sr, s);
}

void test_block_2(SRunner *sr) {
  Suite *s = suite_create("Test block #2");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);

  tcase_add_test(tc_core, test_m_minor_maker_1_1);
  tcase_add_test(tc_core, test_m_minor_maker_1_2);
  tcase_add_test(tc_core, test_m_minor_maker_1_3);
  tcase_add_test(tc_core, test_m_minor_maker_1_4);

  tcase_add_test(tc_core, test_m_minor_maker_2_1);
  tcase_add_test(tc_core, test_m_minor_maker_2_2);
  tcase_add_test(tc_core, test_m_minor_maker_2_3);
  tcase_add_test(tc_core, test_m_minor_maker_2_4);

  tcase_add_test(tc_core, test_m_determinant_1_1);
  tcase_add_test(tc_core, test_m_determinant_1_2);
  tcase_add_test(tc_core, test_m_determinant_1_3);
  tcase_add_test(tc_core, test_m_determinant_1_4);
  tcase_add_test(tc_core, test_m_determinant_1_5);
  tcase_add_test(tc_core, test_m_determinant_1_6);

  tcase_add_test(tc_core, test_m_determinant_2_1);
  tcase_add_test(tc_core, test_m_determinant_2_2);
  tcase_add_test(tc_core, test_m_determinant_2_3);
  tcase_add_test(tc_core, test_m_determinant_2_4);
  tcase_add_test(tc_core, test_m_determinant_2_5);
  tcase_add_test(tc_core, test_m_determinant_2_6);
  tcase_add_test(tc_core, test_m_determinant_2_7);
  tcase_add_test(tc_core, test_m_determinant_2_8);
  tcase_add_test(tc_core, test_m_determinant_2_9);
  tcase_add_test(tc_core, test_m_determinant_2_10);

  tcase_add_test(tc_core, test_m_transpose_1);
  tcase_add_test(tc_core, test_m_transpose_2);
  tcase_add_test(tc_core, test_m_transpose_3);
  tcase_add_test(tc_core, test_m_transpose_4);
  tcase_add_test(tc_core, test_m_transpose_5);
  tcase_add_test(tc_core, test_m_transpose_6);
  tcase_add_test(tc_core, test_m_transpose_7);
  tcase_add_test(tc_core, test_m_transpose_8);

  tcase_add_test(tc_core, test_m_compliments_1);
  tcase_add_test(tc_core, test_m_compliments_2);
  tcase_add_test(tc_core, test_m_compliments_3);
  tcase_add_test(tc_core, test_m_compliments_4);
  tcase_add_test(tc_core, test_m_compliments_5);
  tcase_add_test(tc_core, test_m_compliments_6);
  tcase_add_test(tc_core, test_m_compliments_7);
  tcase_add_test(tc_core, test_m_compliments_8);
  tcase_add_test(tc_core, test_m_compliments_9);
  tcase_add_test(tc_core, test_m_compliments_10);

  tcase_add_test(tc_core, test_m_inverse_m_1);
  tcase_add_test(tc_core, test_m_inverse_m_2);
  tcase_add_test(tc_core, test_m_inverse_m_3);
  tcase_add_test(tc_core, test_m_inverse_m_4);
  tcase_add_test(tc_core, test_m_inverse_m_5);
  tcase_add_test(tc_core, test_m_inverse_m_6);
  tcase_add_test(tc_core, test_m_inverse_m_7);
  tcase_add_test(tc_core, test_m_inverse_m_8);
  tcase_add_test(tc_core, test_m_inverse_m_9);
  tcase_add_test(tc_core, test_m_inverse_m_10);
  tcase_add_test(tc_core, test_m_inverse_m_11);
  tcase_add_test(tc_core, test_m_inverse_m_12);
  tcase_add_test(tc_core, test_m_inverse_m_14);
  tcase_add_test(tc_core, test_m_inverse_m_15);
  tcase_add_test(tc_core, test_m_inverse_m_16);
  tcase_add_test(tc_core, test_m_inverse_m_17);
  tcase_add_test(tc_core, test_m_inverse_m_18);
  tcase_add_test(tc_core, test_m_inverse_m_19);
  tcase_add_test(tc_core, test_m_inverse_m_20);
  srunner_add_suite(sr, s);
}

void test_block_3(SRunner *sr) {
  Suite *s = suite_create("Test block #3");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);

  tcase_add_test(tc_core, test_m_complex_1);
  tcase_add_test(tc_core, test_m_complex_2);
  tcase_add_test(tc_core, test_m_complex_3);

  tcase_add_test(tc_core, test_extra);

  srunner_add_suite(sr, s);
}
// elevator  end
int main(void) {
  int number_failed;
  Suite *s = suite_create("Matrix tests");
  SRunner *sr = srunner_create(s);

  test_block_1(sr);
  test_block_2(sr);
  test_block_3(sr);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}