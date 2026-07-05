#include "s21_helps.h"

int s21_is_zero(s21_decimal decimal) {
  int flag = 0;
  if (!decimal.bits[0] && !decimal.bits[1] && !decimal.bits[2]) {
    flag = 1;
  }
  return flag;
}