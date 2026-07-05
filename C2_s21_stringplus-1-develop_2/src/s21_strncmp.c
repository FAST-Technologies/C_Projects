#include "s21_string.h"

// Сравнивает не более первых n байтов str1 и str2.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  // Оператор остановки цикла
  int stop = 0;
  while (n-- && !stop) {
    if (*str1 != *str2 || *str1 == '\0' || *str2 == '\0') {
      result = *str1 - *str2;
      stop = 1;
    } else {
      str1++;
      str2++;
    }
  }
  return result;
}