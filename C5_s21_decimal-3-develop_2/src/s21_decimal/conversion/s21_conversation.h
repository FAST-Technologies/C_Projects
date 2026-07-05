#ifndef S21_CONVERSATION_H_
#define S21_CONVERSATION_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../comparison/s21_difference_operators.h"
#include "../helps/s21_helps.h"
#include "../s21_decimal_types.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_from_decimal_to_int(s21_decimal src, int *dst);

int s21_from_float_to_decimal(float src, s21_decimal *dst);

int s21_from_int_to_decimal(int src, s21_decimal *dst);

typedef enum s21_conversion_s {
  S21_CONVERSION_OK_STATUS = 0,
  S21_CONVERSATION_ERROR_STATUS = 1
} s21_conversion_s;

#endif  //  S21_CONVERSATION_H_