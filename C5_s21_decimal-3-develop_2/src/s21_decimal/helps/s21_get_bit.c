#include "../s21_decimal_types.h"
#include "s21_helps.h"

int s21_get_bit(s21_decimal decimal, int ind) {
  int intnum = ind / S21_MAX_BLOCK_BITS;
  int bitnum = ind % S21_MAX_BLOCK_BITS;
  return (decimal.bits[intnum] & (1U << bitnum)) >> bitnum;
}