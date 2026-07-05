#ifndef S21_ARITHMETIC_H_
#define S21_ARITHMETIC_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./../s21_decimal_types.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_add_integer(s21_decimal value, int num, s21_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_modulo_by_integer(s21_decimal value, int integer);

int s21_divide_by_scale_of_10(s21_decimal value, int scale,
                              s21_decimal *result);

int s21_divide_by_number(s21_decimal value, int number, s21_decimal *result);

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

s21_decimal s21_abs(s21_decimal value_1);

int s21_add_number(s21_decimal value, int num, s21_decimal *result);

void s21_data_add(s21_big_decimal *temp_1, s21_big_decimal *temp_2,
                  s21_big_decimal *sub_res);

int s21_moding_by_10(s21_big_decimal *value);

void s21_dividing_by_10(s21_big_decimal *value, s21_big_decimal *result);

void s21_decimal_negate(s21_big_decimal *value);

int s21_compare_equal(s21_big_decimal *value1, s21_big_decimal *value2);

int s21_compare_greater(s21_big_decimal *value1, s21_big_decimal *value2);

int s21_multiply_by_number(s21_big_decimal *value, int size_1, int integer,
                           s21_big_decimal *result, int size_2);

int s21_multiply_to_10(s21_big_decimal *value);

void s21_to_scale(s21_decimal value, int scale, s21_big_decimal *result);

int s21_or_bits_big(s21_big_decimal *decl1);
int s21_or_signbits_big(s21_big_decimal *decl1);

int s21_abs_num(int a);

void s21_division_to_2(s21_big_decimal *value);

void s21_data_sub(s21_big_decimal *temp_1, s21_big_decimal *temp_2,
                  s21_big_decimal *sub_res);

void s21_pow_multiply(s21_big_decimal *value, int pow);

void result_return(s21_big_decimal *result1, s21_decimal *result,
                   int result_scale, int result_sign);

typedef enum s21_arithmetic {
  S21_ARITHMETIC_OK_STATUS = 0,
  S21_ARITHMETIC_BIGGER_STATUS = 1,
  S21_ARITHMETIC_SMALLER_STATUS = 2,
  S21_DIVISION_BY_ZERO_STATUS = 3,
  S21_ERROR_STATUS = 4
} s21_arithmetic;

#endif  //  S21_ARITHMETIC_H_