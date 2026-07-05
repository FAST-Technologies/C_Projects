#include "../s21_decimal_types.h"
#include "s21_helps.h"

int s21_correct_decimal(s21_decimal decimal) {
  int check_code = 1;
  int decim_scale_coeff = s21_get_scale_coeff(decimal);
  if (decim_scale_coeff > MIN_SCALE && decim_scale_coeff < MAX_SCALE) {
    check_code = 1;
  }
  for (int i = S21_START_INFO; i <= S21_START_INFO + 15; ++i) {
    int bitted;
    bitted = s21_get_bit(decimal, i);
    if (bitted == 1) {
      check_code = 0;
    }
  }
  for (int i = S21_START_INFO + 24; i <= S21_START_INFO + 30; ++i) {
    int bitted1 = s21_get_bit(decimal, i);
    if (bitted1 == 1) {
      check_code = 0;
    }
  }

  return check_code;
}