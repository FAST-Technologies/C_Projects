#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include <stdarg.h>
#include <stdbool.h>

typedef struct {
  // Следует ли подавлять присваивание. Если suppress_assignment = true, то
  // значение будет прочитано, но не присвоено в переменную. Например, для %*d,
  // прочитает целое число, но не присваивать его в переменную.
  bool suppress_assignment;
  // максимальное количество символов. Например %5s - читает 5 символов,
  // отсальное отбрасывает
  int width;
  // длина для типизации данных: l, h. %ld - long, lf - double
  char length;
  // тип данных - d,f,s,c
  char specifier;

} ModifiersScanf;

// Считывает форматированный ввод из строки
int s21_sscanf(const char *str, const char *format, ...);
// Назначение модификатору значения по входному символу формата
const char *s21_parse_sscanf_modifiers(const char *format, ModifiersScanf *m);
// ИНициализация начальных значений модификаторов
ModifiersScanf s21_init_modifiers_scanf();
// Обработка целочисленных значений %d
int s21_parse_sscanf_int(const char **str, va_list args, ModifiersScanf *m);
// Обработка строковых значений вида %s
int s21_parse_sscanf_string(const char **str, va_list args, ModifiersScanf *m);
// Обработка одиночных символов вида %c
int s21_parse_sscanf_char(const char **str, va_list args, ModifiersScanf *m);
// Обработка беззнаковых чисел %u
int s21_parse_sscanf_unsigned(const char **str, va_list args,
                              ModifiersScanf *m);
// Обработка чисел с плавающей точкой %f %lf
int s21_parse_sscanf_float(const char **str, va_list args, ModifiersScanf *m);
// Обработка модификаторов %p для отображения адресов указателей
int s21_parse_sscanf_pointer(const char **str, va_list args, ModifiersScanf *m);
// Проверяет нужно ли пропустить символ не несущий нагрузки (пробелы, перенос
// строки ...)
int is_skeep_simbol(char c);
// Основной процесс парсинга строки по спецификаторам
void s21_sscanf_parse(ModifiersScanf *m, int *stop, int *assigned_count,
                      const char **str, va_list args);
// Проверяем %% в формате и строке для пропуска двойных процентов
void s21_sscanf_check_double_percent(const char **format, const char **str,
                                     int *next, int *stop);
// Проверка на ошибку конца строки
int is_eof_err(const char *src);

#endif