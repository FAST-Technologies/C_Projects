#include "s21_string.h"

// Проверяет, является ли символ разделителем
int is_delimiter(char c, const char *delim) {
  int found = 0;
  for (int i = 0; delim[i] != '\0' && !found; i++) {
    if (c == delim[i]) {
      found = 1;
    }
  }
  return found;
}

// Пропускает начальные разделители
char *skip_leading_delimiters(char *str, const char *delim) {
  while (*str != '\0' && is_delimiter(*str, delim)) {
    str++;
  }
  return str;
}

// Находит конец текущего токена
char *find_token_end(char *str, const char *delim) {
  while (*str != '\0' && !is_delimiter(*str, delim)) {
    str++;
  }
  return str;
}

// Основная функция s21_strtok для разделения строки на токены
// Разбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim) {
  static char *last = S21_NULL;
  // Если передана новая строка, начинаем с начала
  if (str != S21_NULL) {
    last = str;
  } else if (last == S21_NULL) {
    // Проверка входных значений, поэтому можно return
    return S21_NULL;
  } else {
    // Иначе продолжаем с последней позиции
    str = last;
  }
  // Пропускаем начальные разделители
  str = skip_leading_delimiters(str, delim);
  // Если достигнут конец строки, завершаемся с S21_NULL
  if (*str == '\0') {
    last = S21_NULL;
    str = S21_NULL;
  } else {
    // Находим конец текущего токена
    char *token_end = find_token_end(str, delim);
    // Если достигнут конец строки, обновляем last и возвращаем токен
    if (*token_end == '\0') {
      last = S21_NULL;
    } else {
      // Иначе заменяем разделитель на \0 и обновляем last
      *token_end = '\0';
      last = token_end + 1;
    }
  }
  // Возвращаем начало текущего токена
  return str;
}