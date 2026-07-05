#include "../s21_decimal_types.h"
#include "s21_helps.h"

s21_decimal* s21_copy(s21_decimal* dst, s21_decimal src) {
  for (int j = 0; j < (S21_STRUCT_BITS + 1); j += 1) {
    dst->bits[j] = src.bits[j];
  }
  return dst;
}

s21_big_decimal* s21_copy1(s21_big_decimal* dst, s21_decimal src) {
  for (int j = 0; j < (S21_STRUCT_BITS); j += 1) {
    dst->bits[j] = src.bits[j];
  }
  return dst;
}