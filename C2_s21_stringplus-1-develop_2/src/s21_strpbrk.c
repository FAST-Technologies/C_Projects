#include "s21_string.h"

// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = S21_NULL;

  while (*str1) {
    const char *s2 = str2;
    while (*s2 && res == S21_NULL) {
      if (*str1 == *s2) {
        res = (char *)str1;
      }
      s2++;
    }
    str1++;
  }
  return res;
}