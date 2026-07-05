#include "../s21_decimal_types.h"
#include "s21_helps.h"

void s21_set_bit(s21_decimal* decimal, int ind, int bit) {
  int intnum = ind / S21_MAX_BLOCK_BITS;
  int bitnum = ind % S21_MAX_BLOCK_BITS;
  if (bit == 1) {
    decimal->bits[intnum] = decimal->bits[intnum] | (1U << bitnum);
  } else {
    decimal->bits[intnum] = decimal->bits[intnum] & (~(1U << bitnum));
  }
  return;
}