#include "s21_helps.h"

s21_decimal s21_get_min_int(void) {
  s21_decimal min_int_constant = {{0x80000000, 0x0, 0x0, 0x80000000}};
  return min_int_constant;
}