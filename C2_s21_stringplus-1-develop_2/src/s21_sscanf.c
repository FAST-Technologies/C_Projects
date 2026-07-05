#include "s21_sscanf.h"

#include <stdio.h>

#include "s21_string.h"

// Считывает форматированный ввод из строки
int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  int assigned_count = 0;
  va_start(args, format);
  int stop = 0;  // Если нужно остановить основной цикл обработки
  int eof_err = is_eof_err(str);

  while (*format && *str && !eof_err && !stop) {
    int next = 0;  // Если нужно переходить к следующей итерации
    if (is_skeep_simbol(*format)) {
      while (is_skeep_simbol(*str)) str++;
      format++;
    } else if (*format != '%') {
      if (*format != *str) {
        stop = 1;
      } else {
        format++;
        str++;
      }
    } else {
      format++;
      // Пропускаем %%
      s21_sscanf_check_double_percent(&format, &str, &next, &stop);
      if (!stop && !next) {
        ModifiersScanf m = s21_init_modifiers_scanf();
        format = s21_parse_sscanf_modifiers(format, &m);
        s21_sscanf_parse(&m, &stop, &assigned_count, &str, args);
      }
    }
  }
  va_end(args);
  return eof_err ? EOF : assigned_count;
}

// ИНициализация начальных значений модификаторов
ModifiersScanf s21_init_modifiers_scanf() {
  ModifiersScanf m;
  // Флаг подавления присваивания значения в переменную *
  m.suppress_assignment = false;
  // В задании указывается как n. %n. Используется для задания максимальной
  // ширины (количества символов), котрые должны быть прочитаны из строки для
  // текущего спецификатора в формате. Можно ограничить количество
  // символов, которые будут обработаны и назначены в переменную.
  m.width = 0;
  // Длина модификатора ('h', 'l', 'L'...)
  m.length = '\0';
  // Спецификатор формата ('d', 's', 'f'...)
  m.specifier = '\0';
  return m;
}

// Проверяет нужно ли пропустить символ не несущий нагрузки (пробелы, перенос
// строки ...)
int is_skeep_simbol(char c) {
  return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
          c == '\r');
}

// Проверка на ошибку конца строки
int is_eof_err(const char *src) {
  int err = 1;
  while (*src && err) {
    if (!is_skeep_simbol(*src)) {
      err = 0;
    }
    src++;
  }
  return err;
}

// Назначение модификатору значения по входному символу формата
const char *s21_parse_sscanf_modifiers(const char *format, ModifiersScanf *m) {
  if (*format == '*') {
    m->suppress_assignment = true;
    format++;
  }
  while (*format >= '0' && *format <= '9') {
    m->width = m->width * 10 + (*format - '0');
    format++;
  }
  if (*format == 'h' || *format == 'l' || *format == 'L') {
    m->length = *format++;
  }
  m->specifier = *format++;
  return format;
}

// Обработка целочисленных значений %d
int s21_parse_sscanf_int(const char **str, va_list args, ModifiersScanf *m) {
  int value = 0;
  int count = 0;
  int multiple = 1;

  while (is_skeep_simbol(**str)) (*str)++;

  if (**str == '-') {
    multiple = -1;
    (*str)++;
  }

  while (**str >= '0' && **str <= '9' && (!m->width || count < m->width)) {
    value = value * 10 + (**str - '0');
    (*str)++;
    count++;
  }

  if (!m->suppress_assignment) {
    if (m->length == 'h') {
      short *p = va_arg(args, short *);
      if (p != NULL) {
        *p = (short)(value * multiple);
      }
    } else if (m->length == 'l') {
      long *p = va_arg(args, long *);
      if (p != NULL) {
        *p = value * multiple;
      }
    } else {
      int *p = va_arg(args, int *);
      if (p != NULL) {
        *p = value * multiple;
      }
    }
  }

  return count > 0;
}

// Обработка строковых значений вида %s
int s21_parse_sscanf_string(const char **str, va_list args, ModifiersScanf *m) {
  char *buffer = va_arg(args, char *);
  int count = 0;

  while (is_skeep_simbol(**str)) (*str)++;

  while (**str && **str != ' ' && (!m->width || count < m->width)) {
    if (!m->suppress_assignment) {
      *buffer++ = **str;
    }
    (*str)++;
    count++;
  }

  if (!m->suppress_assignment) {
    *buffer = '\0';
  }

  return count > 0;
}

// Обработка одиночных символов вида %c
int s21_parse_sscanf_char(const char **str, va_list args, ModifiersScanf *m) {
  if (!m->suppress_assignment) {
    char *buffer = va_arg(args, char *);
    *buffer = **str;
  }
  (*str)++;

  return 1;
}

// Обработка беззнаковых чисел %u
int s21_parse_sscanf_unsigned(const char **str, va_list args,
                              ModifiersScanf *m) {
  unsigned int value = 0;
  int count = 0;

  while (is_skeep_simbol(**str)) (*str)++;

  while (**str >= '0' && **str <= '9' && (!m->width || count < m->width)) {
    value = value * 10 + (**str - '0');
    (*str)++;
    count++;
  }

  if (!m->suppress_assignment) {
    unsigned int *p = va_arg(args, unsigned int *);
    *p = value;
  }

  return count > 0;
}

// Обработка чисел с плавающей точкой %f %lf
int s21_parse_sscanf_float(const char **str, va_list args, ModifiersScanf *m) {
  double value = 0.0;
  int count = 0;
  float factor = 0.1;
  bool is_fraction = false;
  float multiple = 1.0;

  while (is_skeep_simbol(**str)) (*str)++;

  if (**str == '-') {
    multiple = -1.0;
    (*str)++;
  }

  while ((**str >= '0' && **str <= '9') || **str == '.') {
    if (**str == '.') {
      is_fraction = true;
    } else {
      if (is_fraction) {
        value += (**str - '0') * factor;
        factor *= 0.1;
      } else {
        value = (value * 10) + (**str - '0');
      }
    }
    (*str)++;
    count++;
  }

  if (!m->suppress_assignment) {
    if (m->length == 'l') {
      double *p = va_arg(args, double *);
      *p = value * multiple;
    } else {
      float *p = va_arg(args, float *);
      *p = value * multiple;
    }
  }

  return count > 0;
}

// Обработка модификаторов %p для отображения адресов указателей
int s21_parse_sscanf_pointer(const char **str, va_list args,
                             ModifiersScanf *m) {
  unsigned long long value = 0;
  int count = 0;

  while (is_skeep_simbol(**str)) (*str)++;

  if (**str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X')) {
    *str += 2;
  }

  while ((**str >= '0' && **str <= '9') || (**str >= 'a' && **str <= 'f') ||
         (**str >= 'A' && **str <= 'F')) {
    value = value * 16;
    if (**str >= '0' && **str <= '9') {
      value += **str - '0';
    } else if (**str >= 'a' && **str <= 'f') {
      value += **str - 'a' + 10;
    } else if (**str >= 'A' && **str <= 'F') {
      value += **str - 'A' + 10;
    }
    (*str)++;
    count++;
  }

  if (!m->suppress_assignment) {
    void **p = va_arg(args, void **);
    if (p != NULL) {
      *p = (unsigned long long *)value;
    }
  }

  return count > 0;
}

// Основной процесс парсинга строки по спецификаторам
void s21_sscanf_parse(ModifiersScanf *m, int *stop, int *assigned_count,
                      const char **str, va_list args) {
  int res = 0;

  switch ((*m).specifier) {
    case 'd':
    case 'i':
      res = s21_parse_sscanf_int(str, args, m);
      break;
    case 's':
      res = s21_parse_sscanf_string(str, args, m);
      break;
    case 'c':
      res = s21_parse_sscanf_char(str, args, m);
      break;
    case 'u':
      res = s21_parse_sscanf_unsigned(str, args, m);
      break;
    case 'f':
      res = s21_parse_sscanf_float(str, args, m);
      break;
    case 'p':
      res = s21_parse_sscanf_pointer(str, args, m);
      break;
    default:
      res = 0;
      break;
  }
  if (res > 0 && !(*m).suppress_assignment) {
    *assigned_count = *assigned_count + 1;
  }
  if (res == 0) {
    *stop = 1;
  }
}

// Проверяем %% в формате и строке для пропуска двойных процентов
void s21_sscanf_check_double_percent(const char **format, const char **str,
                                     int *next, int *stop) {
  if (**format == '%') {
    if (**str == '%') {
      *format = *format + 1;
      *str = *str + 1;
      *next = 1;
    } else {
      *stop = 1;
    }
  }
}
