#include "../helps/s21_helps.h"
#include "./../s21_decimal_types.h"
#include "s21_arithmetic_operators.h"

s21_decimal s21_abs(s21_decimal value_1) {
  int sign = s21_decimal_get_sign(value_1);
  s21_decimal_set_sign(&value_1, !sign);

  return value_1;
}
