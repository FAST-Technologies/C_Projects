#include "../arithmetic/s21_arithmetic_operators.h"
#include "../helps/s21_helps.h"
#include "../s21_decimal_types.h"
#include "s21_math_functions.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_functions func_code = S21_FUNCTION_OK_STATUS;
  if (!result) {
    func_code = S21_FUNCTION_ERROR_STATUS;
  } else if (!s21_correct_decimal(value)) {
    func_code = S21_FUNCTION_ERROR_STATUS;
    *result = s21_decimal_get_inf();
  } else {
    *result = value;
    int scale = s21_get_scale_coeff(value);
    int sign = s21_decimal_get_sign(value);
    if (!scale) {
      s21_copy(result, value);
    }
    result->bits[3] &= SOMESIGN;
    s21_decimal val = *result;
    for (int i = 0; i < scale; i++) {
      s21_divide_by_number(val, 10, result);
      val = *result;
    }
    if (sign == S21_NEGATIVE) {
      s21_decimal_set_sign(result, S21_NEGATIVE);
    } else {
      s21_abs(*result);
    }
    func_code = S21_FUNCTION_OK_STATUS;
  }
  return func_code;
}