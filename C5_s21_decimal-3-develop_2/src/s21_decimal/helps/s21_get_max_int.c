#include "s21_helps.h"

s21_decimal s21_get_max_int(void) {
  s21_decimal max_int_constant = {{0x7FFFFFFF, 0x0, 0x0, 0x0}};
  return max_int_constant;
}