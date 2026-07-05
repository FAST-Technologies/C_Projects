#include "../s21_decimal_types.h"
#include "s21_helps.h"

int s21_get_scale_coeff(s21_decimal decimal) {
  int scale_coeff = 0;
  for (int j = S21_START_INFO + END_SCALE_BIT;
       j >= S21_START_INFO + START_SCALE_BIT; j--) {
    scale_coeff <<= 1;
    scale_coeff = scale_coeff | s21_get_bit(decimal, j);
  }
  return scale_coeff;
}