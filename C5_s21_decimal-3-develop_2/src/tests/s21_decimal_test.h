#ifndef S21_DECIMAL_TEST_H_
#define S21_DECIMAL_TEST_H_

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./../s21_decimal.h"

#define EPS (10e3)

#define OK_ARITHMETIC_TEST 0
#define BIG_ARITHMETIC_TEST 1
#define SMALL_ARITHMETIC_TEST 2
#define ZERO_DIVISION_ARITHMETIC_TEST 3

#define FALSE_COMPARISON_TEST 0
#define TRUE_COMPARISON_TEST 1

#define OK_CONVERSION_TEST 0
#define ERROR_CONVERSION_TEST 1

#define OK_FUNCTION_TEST 0
#define ERROR_FUNCTION_TEST 1

#define S21_TEST_OK 1
#define S21_TEST_FAIL 0

Suite *s21_add_suite(void);
Suite *s21_sub_suite(void);
Suite *s21_mul_suite(void);
Suite *s21_div_suite(void);
Suite *s21_mod_suite(void);
Suite *s21_is_less_suite(void);
Suite *s21_is_less_or_equal_suite(void);
Suite *s21_is_greater_suite(void);
Suite *s21_is_greater_or_equal_suite(void);
Suite *s21_is_equal_suite(void);
Suite *s21_is_not_equal_suite(void);
Suite *s21_from_int_to_decimal_suite(void);
Suite *s21_from_float_to_decimal_suite(void);
Suite *s21_from_decimal_to_int_suite(void);
Suite *s21_from_decimal_to_float_suite(void);
Suite *s21_floor_suite(void);
Suite *s21_round_suite(void);
Suite *s21_truncate_suite(void);
Suite *s21_negate_suite(void);

#endif  // S21_DECIMAL_TEST_H_