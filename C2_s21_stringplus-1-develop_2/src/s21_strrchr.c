#include "s21_string.h"

// Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
char *s21_strrchr(const void *str, unsigned int c) {
  const unsigned char *s = str;  // Переход памяти в unsigned char
  char *result = S21_NULL;       // Нулевой указатель
  unsigned symbol = c;           // Переход памяти в unsigned char
  // Итериеумся до того конца либо пока не встретим искомую память
  for (int i = (int)s21_strlen(str); i > -1 && result == S21_NULL; i--) {
    if (symbol == s[i]) {  // Проверка на искомое значение
      result = (char *)s + i;
      // Преоброзование типов для возможности изменения и сдвиг на i
    }
  }
  return result;
}