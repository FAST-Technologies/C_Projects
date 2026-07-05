#include "../helps/s21_helps.h"
#include "s21_math_functions.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_functions func_code = S21_FUNCTION_OK_STATUS;
  if (!s21_correct_decimal(value)) {
    func_code = S21_FUNCTION_ERROR_STATUS;
  }
  s21_copy(result, value);
  if (!s21_decimal_get_sign(value)) {
    s21_decimal_set_sign(result, S21_NEGATIVE);
    if (!s21_correct_decimal(value)) func_code = S21_FUNCTION_ERROR_STATUS;
  } else {
    s21_decimal_set_sign(result, S21_POSITIVE);
    if (!s21_correct_decimal(value)) func_code = S21_FUNCTION_ERROR_STATUS;
  }
  return func_code;
}