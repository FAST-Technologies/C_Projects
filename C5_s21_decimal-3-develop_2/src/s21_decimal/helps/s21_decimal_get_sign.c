#include "../s21_decimal_types.h"
#include "s21_helps.h"

int s21_decimal_get_sign(s21_decimal decimal) {
  int res = !!(decimal.bits[3] & (1U << MAX_BLOCK_SHIFT));
  return res;
}