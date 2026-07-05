#include "../comparison/s21_difference_operators.h"
#include "../functions/s21_math_functions.h"
#include "../helps/s21_helps.h"
#include "./../s21_decimal_types.h"
#include "s21_arithmetic_operators.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic code_status = S21_ARITHMETIC_OK_STATUS;
  if (s21_is_zero(value_2)) {
    code_status = S21_DIVISION_BY_ZERO_STATUS;
    *result = s21_decimal_get_inf();
  } else if (!s21_correct_decimal(value_1) || !s21_correct_decimal(value_2)) {
    code_status = S21_ERROR_STATUS;
    *result = s21_decimal_get_inf();
  } else if (s21_is_equal(value_1, value_2)) {
    s21_decimal_to_null(result);
    code_status = S21_ARITHMETIC_OK_STATUS;
  } else {
    s21_decimal tmp_res = {{0, 0, 0, 0}};
    s21_decimal_to_null(result);
    int sign1 = s21_decimal_get_sign(value_1);
    int sign2 = s21_decimal_get_sign(value_2);
    if (sign1 == sign2) {
      s21_decimal_set_sign(&tmp_res, 0);
    } else {
      s21_decimal_set_sign(&tmp_res, 1);
    }
    code_status = s21_div(value_1, value_2, &tmp_res);
    if (!code_status) {
      s21_truncate(tmp_res, &tmp_res);
      s21_mul(tmp_res, value_2, &tmp_res);
      s21_sub(value_1, tmp_res, result);
    }
  }
  return code_status;
}
