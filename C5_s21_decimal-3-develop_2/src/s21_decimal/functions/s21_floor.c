#include "../arithmetic/s21_arithmetic_operators.h"
#include "../helps/s21_helps.h"
#include "../s21_decimal_types.h"
#include "s21_math_functions.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_functions func_code = S21_FUNCTION_OK_STATUS;
  if (!result) {
    func_code = S21_FUNCTION_ERROR_STATUS;
  } else if (!s21_correct_decimal(value)) {
    func_code = S21_FUNCTION_ERROR_STATUS;
    *result = s21_decimal_get_inf();
  } else {
    s21_decimal_to_null(result);
    int signe = s21_decimal_get_sign(value);
    int scale = s21_get_scale_coeff(value);
    if (value.bits[3] & SOMESIGN) {
      func_code = s21_truncate(value, result);
      if (s21_or_bits(&value) && scale) {
        s21_add_number(*result, 1, result);
      }
    } else {
      func_code = s21_truncate(value, result);
    }
    if (signe == S21_POSITIVE) {
      s21_decimal_set_sign(result, S21_POSITIVE);
    } else {
      s21_decimal_set_sign(result, S21_NEGATIVE);
    }
  }
  return func_code;
}