#include "../s21_decimal_types.h"
#include "s21_helps.h"

s21_decimal s21_decimal_to_null(s21_decimal *decimal) {
  for (int i = 0; i < S21_decimal_size; i++) {
    decimal->bits[i] = 0;
  }
  return *decimal;
}