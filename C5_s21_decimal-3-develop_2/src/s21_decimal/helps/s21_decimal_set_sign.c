#include "../s21_decimal_types.h"
#include "s21_helps.h"

s21_decimal *s21_decimal_set_sign(s21_decimal *decimal, int sign) {
  decimal->bits[3] = (!sign) ? (decimal->bits[3] & ~(1U << MAX_BLOCK_SHIFT))

                             : (decimal->bits[3] | (1U << MAX_BLOCK_SHIFT));
  return decimal;
}