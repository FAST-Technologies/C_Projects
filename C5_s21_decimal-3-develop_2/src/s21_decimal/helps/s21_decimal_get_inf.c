#include "s21_helps.h"

s21_decimal s21_decimal_get_inf(void) {
  s21_decimal infinity = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
  return infinity;
}