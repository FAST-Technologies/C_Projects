#include "../arithmetic/s21_arithmetic_operators.h"
#include "../helps/s21_helps.h"
#include "../s21_decimal_types.h"
#include "s21_difference_operators.h"

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  return !(s21_is_greater_or_equal(num1, num2));
}
