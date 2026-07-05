#include "s21_string.h"

s21_size_t s21_trim_left_part(const char *src, const char *trim_chars);
s21_size_t s21_trim_right_part(const char *src, const char *trim_chars);

// Возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения набора заданных символов (trim_chars) из данной строки (src). В
// случае какой-либо ошибки следует вернуть значение NULL.
void *s21_trim(const char *src, const char *trim_chars) {  //
  char *result = S21_NULL;  // Выходная строка
  if (src) {  // Выполняем если изначальная строка не пустая
    if (trim_chars) {  // Если строка с символами для замены не пустая
      s21_size_t begin = s21_trim_left_part(
          src, trim_chars);  // Левый край выраждения с отрезанной частью
      s21_size_t ending = s21_trim_right_part(
          src, trim_chars);  // Правый край выраждения с отрезанной частью
      s21_size_t len_result = ending - begin + 1;  // Длина выходной строки

      result = (char *)malloc((len_result + 1) *
                              sizeof(char));  // Динамическое выделение памяти
      if (result) {  // Если выделние памяти успешно
        s21_size_t iterator_result = 0;  // Итератор для выходной строки
        for (s21_size_t i = begin; i < ending + 1; i++) {
          result[iterator_result] = src[i];
          iterator_result++;
        }
        result[len_result] = '\0';  // Добавляем нуль символ, чтобы избежать
                                    // неопределнное поведение
      }
    } else {  // В случае пустоты строчки с символами убираем всех пробелы,
              // переносы строки и знаки табуляции
      result = s21_trim(src, "\n\t ");
    }
  }
  return result;
}

s21_size_t s21_trim_left_part(const char *src, const char *trim_chars) {
  s21_size_t position = 0;  // Изначальная позиция
  int flag = 0;  // Флаг для выхода из внутреннего цикла
  int flag2 = 0;  // Флаг для выхода из внешнего цикла
  for (s21_size_t i = 0; i < s21_strlen(src) && flag2 == 0; i++) {
    position = i;  // Меняем позицию
    for (s21_size_t j = 0; j < s21_strlen(trim_chars) && flag == 0; j++) {
      if (src[i] == trim_chars[j]) {  // Если хотя бы один символ встретилс не
                                      // выходим из внешнего цикла
        flag = 1;
      }
    }
    if (flag == 0) {  // Если не нашли не одного выходим из внешнего цикла
      flag2 = 1;
    } else {  // В ином случае продолжаем
      flag = 0;
    }
  }
  return position;
}
s21_size_t s21_trim_right_part(const char *src, const char *trim_chars) {
  s21_size_t position = s21_strlen(src) - 1;  // Изначальная позиция
  int flag = 0;  // Флаг для выхода из внутреннего цикла
  int flag2 = 0;  // Флаг для выхода из внешнего цикла
  for (s21_size_t i = s21_strlen(src) - 1; i != 0 && flag2 == 0; i--) {
    position = i;  // Меняем позицию
    for (s21_size_t j = 0; j < s21_strlen(trim_chars) && flag == 0; j++) {
      if (src[i] == trim_chars[j]) {  // Если хотя бы один символ встретилс не
                                      // выходим из внешнего цикла
        flag = 1;
      }
    }
    if (flag == 0) {  // Если не нашли не одного выходим из внешнего цикла
      flag2 = 1;
    } else {  // В ином случае продолжаем
      flag = 0;
    }
  }
  return position;
}