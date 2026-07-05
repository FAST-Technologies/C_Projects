#include "s21_string.h"

// Сравнивает первые n байтов str1 и str2.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1 = str1;  // Переход памяти в unsigned char
  const unsigned char *s2 = str2;  // Переход памяти в unsigned char
  int result = 0;                  // Выходное значение
  // Итериеумся до того конца либо пока не встретим отлиный байт
  for (s21_size_t i = 0; i < n && result == 0; i++) {
    if (s1[i] != s2[i]) {  // Проверка отличаются ли байты
      result = s1[i] - s2[i];  // Разница в значениях байтов, интерпретируемых,
                               // как unsigned char
    }
  }
  return result;
}