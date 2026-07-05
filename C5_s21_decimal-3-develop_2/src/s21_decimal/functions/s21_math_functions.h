#ifndef S21_MATH_FUNC_H_
#define S21_MATH_FUNC_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../arithmetic/s21_arithmetic_operators.h"
#include "../comparison/s21_difference_operators.h"
#include "../conversion/s21_conversation.h"
#include "../helps/s21_helps.h"
#include "../s21_decimal_types.h"

int s21_floor(s21_decimal value, s21_decimal *result);

int s21_negate(s21_decimal value, s21_decimal *result);

int s21_round(s21_decimal value, s21_decimal *result);

int s21_truncate(s21_decimal value, s21_decimal *result);

typedef enum s21_functions {
  S21_FUNCTION_OK_STATUS = 0,
  S21_FUNCTION_ERROR_STATUS = 1
} s21_functions;

#endif  //  S21_MATH_FUNC_H_