#include "../arithmetic/s21_arithmetic_operators.h"
#include "../helps/s21_helps.h"
#include "../s21_decimal_types.h"
#include "s21_math_functions.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_functions func_code = S21_FUNCTION_OK_STATUS;
  if (!result) {
    func_code = S21_FUNCTION_ERROR_STATUS;
  } else if (!s21_correct_decimal(value)) {
    func_code = S21_FUNCTION_ERROR_STATUS;
    *result = s21_decimal_get_inf();
  } else {
    s21_decimal_to_null(result);
    int sign = s21_decimal_get_sign(value);
    int scale = s21_get_scale_coeff(value);
    s21_copy(result, value);
    if (scale) {
      result->bits[3] = s21_and(value.bits[3], SOMESIGN);
      for (int j = scale; j > 1; j--) {
        s21_divide_by_number(*result, 10, result);
      }
      int mod = s21_modulo_by_integer(*result, 10);
      int flag = (mod >= 5) ? 1 : 0;
      int status = s21_truncate(value, result);
      if (flag && !status) {
        s21_add_number(*result, 1, result);
      }
    }
    if (sign == S21_POSITIVE) {
      s21_decimal_set_sign(result, S21_POSITIVE);
    } else {
      s21_decimal_set_sign(result, S21_NEGATIVE);
    }
    func_code = S21_FUNCTION_OK_STATUS;
  }
  return func_code;
}