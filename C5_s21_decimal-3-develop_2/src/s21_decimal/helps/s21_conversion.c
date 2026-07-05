#include "s21_helps.h"

s21_big_decimal s21_conversion(s21_decimal num) {
  s21_big_decimal number = {
      {num.bits[0], num.bits[1], num.bits[2], 0, 0, 0, 0, num.bits[3]}};
  return number;
}
