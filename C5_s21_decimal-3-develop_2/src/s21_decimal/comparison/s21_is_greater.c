#include "../helps/s21_helps.h"
#include "s21_difference_operators.h"

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  s21_comparison flag = S21_COMPARISON_FALSE_STATUS;
  int sign1 = s21_decimal_get_sign(num1);
  int sign2 = s21_decimal_get_sign(num2);
  if (sign1 == sign2) {
    int res_sign = sign1;
    int scale_normalize = s21_alignmentScale1(num1, num2);
    if (scale_normalize == S21_GREATER_STATUS) {
      if (res_sign == 1) {
        flag = S21_COMPARISON_FALSE_STATUS;
      } else {
        flag = S21_COMPARISON_TRUE_STATUS;
      }
    } else if (scale_normalize == S21_LESS_STATUS) {
      if (res_sign == 0) {
        flag = S21_COMPARISON_FALSE_STATUS;
      } else {
        flag = S21_COMPARISON_TRUE_STATUS;
      }
    } else if (scale_normalize == S21_EQUAL_STATUS) {
      flag = S21_COMPARISON_FALSE_STATUS;
    }
  } else {
    if (s21_is_zero(num1) && s21_is_zero(num2)) {
      flag = S21_COMPARISON_FALSE_STATUS;
    } else if (s21_is_equal(num1, num2)) {
      flag = S21_COMPARISON_FALSE_STATUS;
    } else if (sign1 == S21_POSITIVE && sign2 == S21_NEGATIVE) {
      flag = S21_COMPARISON_TRUE_STATUS;
    } else if (sign1 == S21_NEGATIVE && sign2 == S21_POSITIVE) {
      flag = S21_COMPARISON_FALSE_STATUS;
    }
  }
  return flag;
}