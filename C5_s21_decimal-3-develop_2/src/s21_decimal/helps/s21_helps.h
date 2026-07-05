#ifndef S21_HELPS_FUNC_H_
#define S21_HELPS_FUNC_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./../s21_decimal_types.h"

int s21_get_bit(s21_decimal decimal, int ind);

void s21_set_bit(s21_decimal *decimal, int ind, int bit);

int s21_correct_decimal(s21_decimal decimal);

int s21_get_bit_int(int value, int ind);

int s21_get_scale_coeff(s21_decimal decimal);

int s21_mantiss_normalize(uint32_t *newscale, int value);

int s21_get_equal_scale(s21_decimal *value_1, s21_decimal *value_2);

int s21_alignmentScale1(s21_decimal value_1, s21_decimal value_2);

int s21_decimal_get_sign(s21_decimal decimal);

s21_decimal *s21_decimal_set_sign(s21_decimal *decimal, int sign);

s21_decimal s21_left_shift(s21_decimal dst, int value_shift,
                           s21_decimal result);

s21_decimal s21_right_shift(s21_decimal dst, int value_shift,
                            s21_decimal result);

s21_decimal s21_get_max_int(void);

s21_decimal s21_get_min_int(void);

s21_decimal s21_decimal_get_inf(void);

int s21_is_zero(s21_decimal decimal);

int s21_and(int vaue_1, int value_2);

int s21_or(int value_1, int value_2);

s21_decimal s21_decimal_to_null(s21_decimal *decimal);
s21_decimal s21_set_scale_coeff1(s21_decimal *decimal, int scaleCoeff);
s21_big_decimal s21_big_decimal_to_null(s21_big_decimal *big_decimal);

int can_be_align_to_coeff(s21_decimal *decimal, int align_coeff);

s21_big_decimal s21_conversion(s21_decimal num);

s21_decimal s21_classic_converse(s21_big_decimal *num, s21_decimal *result);

s21_decimal *s21_copy(s21_decimal *dst, s21_decimal src);
s21_big_decimal *s21_copy1(s21_big_decimal *dst, s21_decimal src);

void s21_print_decimal(s21_decimal decimal);

int s21_max_flag(int value_1, int value_2);

int s21_get_expo_from_float(float *decimal);

int s21_or_bits(s21_decimal *value);

int s21_comp(s21_decimal num1, s21_decimal num2);

#endif  // S21_HELPS_FUNC_H_