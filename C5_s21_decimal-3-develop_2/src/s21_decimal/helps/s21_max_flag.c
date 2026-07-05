#include "s21_helps.h"

int s21_max_flag(int value_1, int value_2) {
  int flag = 0;
  if (value_1 > value_2) {
    flag = 1;
  }
  return flag;
}