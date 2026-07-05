#include "../arithmetic/s21_arithmetic_operators.h"
#include "../s21_decimal_types.h"
#include "s21_helps.h"

s21_decimal s21_right_shift(s21_decimal dst, int value_shift,
                            s21_decimal result) {
  if (value_shift > 0) {
    for (int i = 0; i < S21_decimal_size; i++) result.bits[i] = dst.bits[i];
    result.bits[0] = ((result.bits[0] >> value_shift) & (~OLDER_BIT)) +
                     ((unsigned int)s21_get_bit_int(result.bits[1], 0) << 31);
    result.bits[1] = ((result.bits[1] >> value_shift) & (~OLDER_BIT)) +
                     ((unsigned int)s21_get_bit_int(result.bits[2], 0) << 31);
    result.bits[2] = ((result.bits[2] >> value_shift) & (~OLDER_BIT));
  } else if (value_shift < 0) {
    value_shift = s21_abs_num(value_shift);
    result = s21_left_shift(dst, value_shift, result);
  } else {
    result = dst;
  }
  return result;
}