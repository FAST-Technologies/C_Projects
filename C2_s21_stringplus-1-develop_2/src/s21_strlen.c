#include "s21_string.h"

// Вычисляет длину строки str, не включая завершающий нулевой символ.
s21_size_t s21_strlen(const char *str) {
  const char *s = str;
  while (*s) {
    s++;
  }
  return s - str;
}