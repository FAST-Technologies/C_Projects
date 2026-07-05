#include "s21_string.h"

// Возвращает копию строки (str), преобразованной в нижний регистр. В случае
// какой-либо ошибки следует вернуть значение NULL.
void *s21_to_lower(const char *string) {
  char *result = S21_NULL;
  // проверяем строку на неравенство нулю
  if (string != S21_NULL) {
    // находим длину полученной строки
    s21_size_t length = s21_strlen(string);
    // создаем строку с размером, равным длине строки length
    result = (char *)malloc(sizeof(char) * (length + 1));
    // проверяем исходную строку
    for (s21_size_t i = 0; i <= length; i++) {
      // если встретили высокий регистр, меняем буквы на низкий регистр, иначе
      // оставляем первоначальный вариант
      if (string[i] >= 'A' && string[i] <= 'Z') {
        result[i] = (string[i] - 'A') + 'a';
      } else {
        result[i] = string[i];
      }
    }
    result[length] = '\0';
  }
  return result;
}