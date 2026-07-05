#include "../s21_decimal_types.h"
#include "s21_helps.h"

s21_decimal s21_set_scale_coeff1(s21_decimal *decimal, int scaleCoeff) {
  for (int j = S21_START_INFO + START_SCALE_BIT;
       j < S21_START_INFO + END_SCALE_BIT; j++) {
    s21_set_bit(decimal, j, scaleCoeff & 1);
    scaleCoeff >>= 1;
  }
  return *decimal;
}