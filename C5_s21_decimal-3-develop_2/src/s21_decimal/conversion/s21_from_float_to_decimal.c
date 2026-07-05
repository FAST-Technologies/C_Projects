#include <math.h>
#include <stdio.h>

#include "../helps/s21_helps.h"
#include "../s21_decimal_types.h"
#include "s21_conversation.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_conversion_s conversed_code = S21_CONVERSION_OK_STATUS;
  s21_decimal_to_null(dst);
  if (!dst) {
    conversed_code = S21_CONVERSATION_ERROR_STATUS;
  }
  if (isinf(src) || isnan(src)) {
    conversed_code = S21_CONVERSATION_ERROR_STATUS;
  } else {
    if (src != 0) {
      float_bits mantissa = {0};
      double temp = (double)fabs(src);
      int sign = (src < 0) ? 1 : 0;
      int scale = s21_get_expo_from_float(&src);
      int off;
      for (off = MIN_SCALE; off < MAX_SCALE && (int)temp / (int)pow(2, 21) == 0;
           off++) {
        temp *= 10;
      }
      temp = round(temp);
      if (off <= MAX_SCALE && (scale > -94 && scale < 96)) {
        temp = (float)temp;
        for (; fmod(temp, 10) == 0 && off > MIN_SCALE; off--) {
          temp /= 10;
        }
        mantissa.floatnum = temp;
        scale = s21_get_expo_from_float(&mantissa.floatnum);
        s21_set_bit(dst, scale, 1);
        for (int i = scale - 1, j = 22; j >= 0; i--, j--) {
          int float_shift = 1 << j;
          if (s21_and(mantissa.bits, float_shift) != 0) {
            s21_set_bit(dst, i, 1);
          }
          int c1 = (unsigned int)sign << (S21_MAX_BLOCK_BITS - 1);
          int c2 = off << START_SCALE_BIT;
          dst->bits[3] = s21_or(c1, c2);
        }
      }
    }
  }
  return conversed_code;
}
