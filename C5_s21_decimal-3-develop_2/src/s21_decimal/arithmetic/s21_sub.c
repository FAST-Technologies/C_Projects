#include "../comparison/s21_difference_operators.h"
#include "../functions/s21_math_functions.h"
#include "../helps/s21_helps.h"
#include "./../s21_decimal_types.h"
#include "s21_arithmetic_operators.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic code_status = S21_ARITHMETIC_OK_STATUS;
  if (!s21_correct_decimal(value_1) || !s21_correct_decimal(value_2)) {
    code_status = S21_ERROR_STATUS;
  } else {
    s21_negate(value_2, &value_2);
    code_status = s21_add(value_1, value_2, result);
  }
  return code_status;
}