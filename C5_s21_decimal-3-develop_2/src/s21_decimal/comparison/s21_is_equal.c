#include "../helps/s21_helps.h"
#include "../s21_decimal_types.h"
#include "s21_difference_operators.h"

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  s21_comparison flag = S21_COMPARISON_FALSE_STATUS;
  int sign1 = s21_decimal_get_sign(num1);
  int sign2 = s21_decimal_get_sign(num2);
  int is_same_sign = (sign1 == sign2);

  int scale_normalize = s21_alignmentScale1(num1, num2);
  if (s21_is_zero(num1) && s21_is_zero(num2)) {
    flag = S21_COMPARISON_TRUE_STATUS;
  } else if (!is_same_sign) {
    flag = S21_COMPARISON_FALSE_STATUS;
  } else if (!scale_normalize) {
    flag = S21_COMPARISON_TRUE_STATUS;
  } else {
    flag = S21_COMPARISON_FALSE_STATUS;
  }

  return flag;
}
