#include "../s21_decimal_types.h"
#include "s21_helps.h"

void s21_print_decimal(s21_decimal decimal) {
  for (int i = S21_MAX_BITS - 1; i >= 0; i--) {
    printf("%d", s21_get_bit(decimal, i));
    if (i % S21_MAX_BLOCK_BITS == 0) printf(" ");
  }
  printf("\n");
}