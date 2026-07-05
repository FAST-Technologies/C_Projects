#include "../s21_decimal_types.h"
#include "s21_helps.h"

int s21_or_bits(s21_decimal *value) {
  return value->bits[0] || value->bits[1] || value->bits[2];
}