#include "../helps/s21_helps.h"
#include "../s21_decimal_types.h"

int s21_abs_num(int a) {
  int binar_shift = (unsigned int)a >> MAX_BLOCK_SHIFT;
  int val_with_shift = a + binar_shift;
  int exit_value = val_with_shift ^ binar_shift;
  return exit_value;
}