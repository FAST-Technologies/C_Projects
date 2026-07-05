#include "s21_string.h"

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str.
void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *s = str;  // Переход памяти в unsigned char
  void *result = S21_NULL;       // Нулевой указатель
  const unsigned char symbol = c;  // Переход памяти в unsigned char
  // Итериеумся до того конца либо пока не встретим искомую память
  for (s21_size_t i = 0; i < n && result == S21_NULL; i++) {
    if (symbol == s[i]) {  // Проверка на искомое значение
      result = (char *)s + i;
      // Преоброзование типов для возможности изменения и сдвиг на i
    }
  }
  return result;
}