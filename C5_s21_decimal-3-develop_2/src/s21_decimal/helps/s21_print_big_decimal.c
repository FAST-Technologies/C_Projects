#include "../s21_decimal_types.h"
#include "s21_helps.h"

s21_decimal s21_classic_converse(s21_big_decimal *num, s21_decimal *result) {
  for (int i = 0; i < 3; i++) {
    result->bits[i] = num->bits[i];
  }
  return *result;
}