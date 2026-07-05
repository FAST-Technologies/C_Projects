#include "s21_string.h"

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2.
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *s1 = str1;
  s21_size_t length = 0;
  int found = 0;

  while (*s1 && !found) {
    const char *s2 = str2;
    while (*s2 && !found) {
      if (*s1 == *s2) {
        found = 1;
      }
      s2++;
    }
    if (!found) {
      s1++;
      length++;
    }
  }

  return length;
}