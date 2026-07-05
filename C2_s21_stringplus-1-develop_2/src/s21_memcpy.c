#include "s21_string.h"

// Копирует n символов из src в dest.
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  // Преобразуем указатели на void в указатели на char для побайтового
  // копирования
  char *d = (char *)dest;
  const char *s = (const char *)src;

  // Копируем n байтов из src в dest
  for (s21_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }

  // указатель на dest
  return dest;
}