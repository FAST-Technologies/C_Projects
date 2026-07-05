#include "../s21_decimal_types.h"
#include "s21_helps.h"

s21_big_decimal s21_big_decimal_to_null(s21_big_decimal *big_decimal) {
  for (int j = 0; j < S21_big_decimal_size; j++) {
    big_decimal->bits[j] = 0;
  }
  return *big_decimal;
}