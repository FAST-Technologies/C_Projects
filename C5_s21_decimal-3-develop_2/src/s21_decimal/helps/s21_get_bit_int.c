#include "s21_helps.h"

int s21_get_bit_int(int value, int ind) { return (value & (1 << ind)) != 0; }
