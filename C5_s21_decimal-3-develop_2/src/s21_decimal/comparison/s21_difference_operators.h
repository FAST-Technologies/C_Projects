#ifndef S21_COMPARISON_H_
#define S21_COMPARISON_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../arithmetic/s21_arithmetic_operators.h"
#include "./../s21_decimal_types.h"

int s21_is_equal(s21_decimal, s21_decimal);

int s21_is_greater_or_equal(s21_decimal, s21_decimal);

int s21_is_greater(s21_decimal, s21_decimal);

int s21_is_less_or_equal(s21_decimal, s21_decimal);

int s21_is_less(s21_decimal, s21_decimal);

int s21_is_not_equal(s21_decimal, s21_decimal);

typedef enum s21_comparison {
  S21_COMPARISON_FALSE_STATUS = 0,
  S21_COMPARISON_TRUE_STATUS = 1
} s21_comparison;

typedef enum s21_differ_status {
  S21_EQUAL_STATUS = 0,
  S21_GREATER_STATUS = 1,
  S21_LESS_STATUS = -1
} s21_differ_status;

#endif  //  S21_COMPARISON_H_