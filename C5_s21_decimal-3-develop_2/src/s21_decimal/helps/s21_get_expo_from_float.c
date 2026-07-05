#include "../s21_decimal_types.h"
#include "s21_helps.h"

int s21_get_expo_from_float(float *decimal) {
  return ((*((unsigned int *)decimal) & ~(1u << 31)) >> 23) - 127;
}