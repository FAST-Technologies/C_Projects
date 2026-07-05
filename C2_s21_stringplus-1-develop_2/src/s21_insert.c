#include "s21_string.h"

// Возвращает новую строку, в которой указанная строка (str) вставлена в
// указанную позицию (start_index) в данной строке (src). В случае какой-либо
// ошибки следует вернуть значение NULL.
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = S21_NULL;
  s21_size_t len_src, len_str, len_new;
  len_str = (str == S21_NULL) ? 0 : s21_strlen(str);
  len_src = (src == S21_NULL) ? 0 : s21_strlen(src);
  len_new = len_src + len_str;
  // проверка индекса на допустимость
  if (start_index <= len_src) {
    res = (char *)calloc(len_new + 1, sizeof(char));
  }
  if (res) {
    for (size_t i = 0; i < len_new; i++) {
      if (i < start_index) {
        res[i] = src[i];  // копируем до стартового индекса
      } else if (i < len_str + start_index) {
        res[i] = str[i - start_index];  // копируем str
      } else {
        res[i] = src[i - len_str];  // копируем оставшиеся символы.
      }
    }
  }

  return res;
}
