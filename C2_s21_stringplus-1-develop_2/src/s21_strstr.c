#include "s21_string.h"

// Находит первое вхождение всей строки needle (не включая завершающий нулевой
// символ), которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  if (!*needle) {
    result = (char *)
        haystack;  // если needle пустая возвращаем указатель на начало haystack
  } else {
    const char *n = needle;
    for (const char *h = haystack; *h != '\0' && *n != '\0'; h++) {
      // ищем первое вхождение
      if (*h == *needle) {
        const char *h_tmp = h;
        n = needle;
        // проверка остальных символов needle
        while (*h_tmp && *n && (*h_tmp == *n)) {
          h_tmp++;
          n++;
        }
        // устанавливаем result если вся подстрока найдена
        if (*n == '\0') {
          result = (char *)h;
        }
      }
    }
  }
  return result;
}