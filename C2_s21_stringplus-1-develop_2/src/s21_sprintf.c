#include "s21_string.h"

// основное тело функции
int s21_sprintf(char *str, const char *format, ...) {
  int result = 0;
  if (str == S21_NULL || format == S21_NULL) {
    result = -1;
  } else {
    str[0] = '\0';
    va_list args;
    va_start(args, format);
    result = s21_write_str(str, format, args);
    va_end(args);
  }
  return result;
}

// вывод полученнной строки на основе входных флагов/спецификаторов
int s21_write_str(char *str, const char *format, va_list args) {
  Modifiers m;
  const char *str_start = str;
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    } else {
      format++;
      m = s21_init_flags();
      format = s21_parse_flags(format, &m);
      format = s21_parse_width(format, &m, args);
      format = s21_parse_precision(format, &m, args);
      format = s21_parse_length(format, &m);

      m.specifier = *format;
      char buffer[BUFF_SIZE] = {'\0'};

      s21_use_modifier(buffer, args, &m);
      s21_apply_width_and_minus(buffer, &m);
      for (int i = 0; buffer[i] != '\0'; i++) {
        *str++ = buffer[i];
      }
    }
    format++;
  }
  *str = '\0';
  return str - str_start;
}

// инициализация флагов соответствующей функции
Modifiers s21_init_flags() {
  Modifiers m;
  m.plus = false;
  m.minus = false;
  m.space = false;
  m.zero = false;
  m.hash = false;
  m.precision = -1;
  m.width = 0;
  m.specifier = '\0';
  m.length = '\0';
  return m;
}

// парсинг флагов из консольной строки
const char *s21_parse_flags(const char *format, Modifiers *m) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '0' ||
         *format == '#') {
    if (*format == '-')
      m->minus = true;
    else if (*format == '+')
      m->plus = true;
    else if (*format == ' ')
      m->space = true;
    else if (*format == '0')
      m->zero = true;
    else if (*format == '#')
      m->hash = true;
    format++;
  }
  return format;
}

// парсинг размера ширины для текущего числа
const char *s21_parse_width(const char *format, Modifiers *m, va_list args) {
  if (*format == '*') {
    m->width = va_arg(args, int);
    if (m->width < 0) {
      m->minus = true;
      m->width = -m->width;
    }
    format++;
  } else if (*format >= '0' && *format <= '9') {
    m->width = 0;
    while (*format >= '0' && *format <= '9') {
      m->width = m->width * 10 + (*format - '0');
      format++;
    }
  }
  return format;
}

// парсинг точности для конкретного числа (bad)
const char *s21_parse_precision(const char *format, Modifiers *m,
                                va_list args) {
  if (*format == '.') {
    format++;
    if (*format == '*') {
      m->precision = va_arg(args, int);
      if (m->precision < 0) {
        m->precision = -1;
      }
      format++;
    } else {
      m->precision = 0;
      while (*format >= '0' && *format <= '9') {
        m->precision = m->precision * 10 + (*format - '0');
        format++;
      }
    }
  }
  return format;
}

// парсинг длины для соответствующего числа (bad)
const char *s21_parse_length(const char *format, Modifiers *m) {
  if (*format == 'h' || *format == 'l' || *format == 'L') {
    m->length = *format++;
  }
  return format;
}

// Иcпользование соответствующего модификатора
void s21_use_modifier(char *buffer, va_list args, Modifiers *m) {
  switch (m->specifier) {
    case 'c':
      s21_parse_char(buffer, args);
      break;
    case 's':
      s21_parse_string(buffer, args, m);
      break;
    case 'd':
      s21_parse_int(buffer, args, m);
      break;
    case 'u':
      s21_parse_unsigned(buffer, args, m);
      break;
    case 'f':
      s21_parse_float(buffer, args, m);
      break;
    case 'o':
      s21_parse_octal(buffer, args, m);
      break;
    case 'p':
      s21_parse_pointer(buffer, args);
      break;
    case 'x':
    case 'X':
      s21_parse_hex(buffer, args, m);
      break;
    case 'E':
    case 'e':
      s21_parse_e_scientific(buffer, args, m);
      break;
    case '%':
      buffer[0] = '%';
      break;
  }
}
// применение ширины и  выравнивание по левому краю
void s21_apply_width_and_minus(char *buffer, Modifiers *m) {
  int len = s21_strlen(buffer);
  if (m->width > len) {
    if (m->minus) {
      for (int i = len; i < m->width; i++) {
        buffer[i] = ' ';
      }
    } else {
      for (int i = m->width - 1; i >= m->width - len; i--) {
        buffer[i] = buffer[i - (m->width - len)];
      }
      for (int i = 0; i < m->width - len; i++) {
        buffer[i] = ' ';
      }
    }
  }
}
// парсим символ
void s21_parse_char(char *buffer, va_list args) {
  char c = (char)va_arg(args, int);
  *buffer++ = c;
}
// парсим строку
void s21_parse_string(char *buffer, va_list args, Modifiers *m) {
  const char *s = va_arg(args, const char *);
  int precision = (m->precision >= 0) ? m->precision : (int)s21_strlen(s);
  if (precision != 0) {
    while (*s && precision > 0) {
      *buffer++ = *s++;
      precision--;
    }
  }
  *buffer = '\0';
}
// парсим целые числа
void s21_parse_int(char *buffer, va_list args, Modifiers *m) {
  long long value;
  if (m->length == 'l') {
    value = va_arg(args, long);
  } else if (m->length == 'h') {
    value = (short)va_arg(args, int);
  } else {
    value = va_arg(args, int);
  }
  char temp[BUFF_SIZE] = {'\0'};
  int index = 0;
  if (value >= 0) {
    if (m->plus) {
      buffer[index++] = '+';
    } else if (m->space) {
      buffer[index++] = ' ';
    }
  }
  int precision = (m->precision > 0) ? m->precision : 0;
  if (precision != 0 || value != 0) {
    s21_int_to_str(value, temp, 10);
  }
  if (m->precision < 0) {
    if (value == 0) {
      temp[0] = '0';
    }
  }
  s21_format_int_precision(temp, precision, m);

  s21_strncpy((index == 0) ? buffer : buffer + index, temp, s21_strlen(temp));
}
// перевод целых чисел в строку, а также перевод систем счисления
int s21_int_to_str(long long x, char *str, s21_size_t base) {
  int i = 0;
  char tmp[BUFF_SIZE] = {'\0'};
  int ix = BUFF_SIZE - 2;
  long long y = x;  // для фиксации отрицательных чисел
  y = (y < 0) ? -y : y;

  if (y == 0) {
    tmp[ix] = '0';
  }
  // буфера происходит с конца, чтобы не делать потом разворот
  while (y > 0) {
    ix--;
    tmp[ix] = "0123456789abcdef"[y % base];
    y /= base;
  }
  for (int j = 0; tmp[ix]; ix++, j++) {
    if (x < 0 && j == 0) {
      str[j++] = '-';
      i++;
    }
    i++;
    str[j] = tmp[ix];
  }

  return i;
}
// применение точности  для всех спецификаторов кроме с плавающей точкой. Для %f
// применение только флага 0. функционал значительнее шире изначальной задумки
void s21_format_int_precision(char *temp, int precision, Modifiers *m) {
  int len = s21_strlen(temp);
  char buf[BUFF_SIZE] = {'\0'};
  int index = 0;  // нужен для сдвига указателей
  int negative = 0;
  // применение # для %x или %X
  if ((m->specifier == 'x' || m->specifier == 'X') && m->hash &&
      !(len == 1 && temp[0] == '0')) {
    buf[index++] = '0';
    buf[index++] = (m->specifier == 'x') ? 'x' : 'X';
  }
  // вставка '-' для отрицательных чисел.
  if (temp[0] == '-') {
    buf[0] = temp[0];
    index++;
    negative = 1;
    temp++;
    len--;
  }
  // !!! Вероятнее всего тут будут и флаги e/g
  if (m->specifier == 'f') {
    s21_format_flag_zero(buf, len, negative, m);
  } else {
    if (m->zero && m->precision < 0) {
      s21_format_flag_zero(buf + index, len + index, negative, m);
    }
    // применение точности ко всем кроме float
    if (precision > len && !m->zero) {
      for (int i = 0; i < precision - len; i++) {
        buf[index++] = '0';
      }
    }
  }

  s21_strncat(buf, temp, len);
  s21_strncpy(temp - negative, buf, s21_strlen(buf));
}
// форматирование под ноль , заполнение буфера нулями
void s21_format_flag_zero(char *src, int len, int negative, Modifiers *m) {
  if (m->zero) {
    if (m->width > len) {
      if (negative) {
        src++;
        len++;
      }
      if (m->plus || m->space) {
        len++;
      }
      for (int i = 0; i < m->width - len; i++) {
        *src++ = '0';
      }
    }
  }
}
// парсинг безнаковых
void s21_parse_unsigned(char *buffer, va_list args, Modifiers *m) {
  unsigned long long value;
  if (m->length == 'l') {
    value = va_arg(args, unsigned long);
  } else if (m->length == 'h') {
    value = (unsigned short)va_arg(args, unsigned int);
  } else {
    value = va_arg(args, unsigned int);
  }
  char temp[BUFF_SIZE] = {'\0'};
  s21_uitoa(value, temp, 10);
  int precision = (m->precision > 0) ? m->precision : 0;

  s21_format_int_precision(temp, precision, m);

  s21_strncpy(buffer, temp, s21_strlen(temp));
}
// безнаковые в строку, смысл почти такой же как у int_to_str()
int s21_uitoa(unsigned long long num, char *str, const s21_size_t base) {
  char tmp[BUFF_SIZE] = {'\0'};
  s21_size_t ix = BUFF_SIZE - 1;
  int i = 0;
  if (num == 0) {
    tmp[ix] = '0';
    ix--;
  }

  for (; num && ix; --ix, num /= base) {
    tmp[ix] = "0123456789abcdef"[num % base];
  }
  for (int j = 0; ix < BUFF_SIZE - 1; ix++, j++) {
    str[j] = tmp[ix + 1];
    i++;
  }
  return i;
}

// парсинг дробных чисел

void s21_parse_float(char *buffer, va_list args, Modifiers *m) {
  long double value;
  char temp1[BUFF_SIZE] = {'\0'};
  if (m->length == 'L') {
    value = va_arg(args, long double);
  } else {
    value = va_arg(args, double);
  }
  if (value >= 0) {
    int index = 0;
    if (m->plus) {
      buffer[index++] = '+';

    } else if (m->space) {
      buffer[index++] = ' ';
    }
  }
  int precision = (m->precision >= 0) ? m->precision : 6;
  s21_ftoa(value, temp1, precision, m);
  s21_format_int_precision(temp1, precision, m);
  s21_strncat(buffer, temp1, s21_strlen(temp1));
}
// float to asci .
int s21_ftoa(long double n, char *res, int precision, Modifiers *m) {
  int negative = 0;
  int index = 0;
  if (n < 0) {
    negative = 1;
    n = -n;
  }
  if (negative) {
    res[0] = '-';
    index++;
  }
  // целая часть отдельно , дробная отдельно
  long long ipart = (long long)n;
  double fpart = n - (double)ipart;
  // манипуляция для правильного округления
  double rounding_factor = 0.5 / pow(10, precision);
  fpart += rounding_factor;
  int i = s21_int_to_str(ipart, res + index, 10);  // получаем длину целой части
  if (precision > 0 || m->hash) {
    res[i + index] = '.';
  }
  s21_fparttoa(fpart, res, precision);
  return s21_strlen(res);
}
// дробную часть в строку
void s21_fparttoa(double fpart, char *res, int precision) {
  char buffer[BUFF_SIZE] = {'\0'};
  if (precision > 0) {
    int prec = precision;
    int i = 0;
    while (prec--) {
      fpart *= 10;
      int tmp = (int)fpart;
      if (tmp > 9) {
        tmp %= 10;
      }
      buffer[i++] = '0' + tmp;
    }
  }

  s21_strncat(res, buffer, s21_strlen(buffer));
}

// парсинг числа в 8-ной системе
void s21_parse_octal(char *buffer, va_list args, Modifiers *m) {
  long long value;
  if (m->length == 'l') {
    value = va_arg(args, long);
  } else if (m->length == 'h') {
    value = (unsigned short)va_arg(args, unsigned int);
  } else {
    value = va_arg(args, unsigned int);
  }
  char temp[BUFF_SIZE] = {'\0'};
  int index = 0;
  if (value > 0 && m->hash) {
    temp[index++] = '0';
  }
  s21_int_to_str(value, temp + index, 8);
  int precision = (m->precision > 0) ? m->precision : 0;

  s21_format_int_precision(temp, precision, m);

  s21_strncpy(buffer, temp, s21_strlen(temp));
}

// парсинг числа в 16-ой системе
void s21_parse_hex(char *buffer, va_list args, Modifiers *m) {
  unsigned long long value;
  if (m->length == 'l') {
    value = va_arg(args, unsigned long);
  } else if (m->length == 'h') {
    value = (unsigned short)va_arg(args, unsigned int);
  } else {
    value = va_arg(args, unsigned int);
  }
  char temp[BUFF_SIZE] = {'\0'};

  s21_uitoa(value, temp, 16);
  // изменения регистра для %X
  if (m->specifier == 'X') {
    for (int i = 0; temp[i] != '\0'; i++) {
      if (temp[i] >= 'a' && temp[i] <= 'f') {
        temp[i] = temp[i] - 'a' + 'A';
      }
    }
  }

  int precision = (m->precision > 0) ? m->precision : 0;
  s21_format_int_precision(temp, precision, m);
  s21_strncpy(buffer, temp, s21_strlen(temp));
}

// парсим адрес указателя
void s21_parse_pointer(char *buffer, va_list args) {
  void *ptr = va_arg(args, void *);
  unsigned long long address = (unsigned long long)ptr;
  if (ptr != S21_NULL) {
    int index = 0;
    buffer[index++] = '0';
    buffer[index++] = 'x';
    s21_uitoa(address, buffer + index, 16);
  } else {
    s21_strncpy(buffer, "(nil)", 5);
  }
}
// парсинг числа в научной нотации (флаги е и Е)
void s21_parse_e_scientific(char *buffer, va_list args, Modifiers *m) {
  long double value;
  char temp2[BUFF_SIZE] = {'\0'};
  if (m->length == 'L') {
    value = va_arg(args, long double);
  } else {
    value = va_arg(args, double);
  }
  if (value >= 0) {
    int index = 0;
    if (m->plus) {
      buffer[index++] = '+';

    } else if (m->space) {
      buffer[index++] = ' ';
    }
  }
  int precision =
      (m->precision > 0) ? m->precision : (m->precision == 0 ? 0 : 6);
  s21_fetoa(value, temp2, precision, m);
  s21_format_int_precision(temp2, precision, m);
  s21_strncat(buffer, temp2, s21_strlen(temp2));
}
// exponent float/double exponent to ascii
int s21_fetoa(long double n, char *res, int precision, Modifiers *m) {
  int negative = 0;
  int index = 0;
  int counter = 0;
  if (n < 0) {
    negative = 1;
    n = -n;
  }
  if (negative) {
    res[0] = '-';
    index++;
  }
  long double kpart = n;
  long double newipart = kpart;
  long long ipart;
  long double fpart;
  if (kpart >= 10) {
    while (newipart >= 10) {
      newipart /= 10;
      counter += 1;
    }
  } else if (kpart < 1) {
    while (newipart < 1) {
      newipart = newipart * 10;
      counter -= 1;
    }
  } else {
    counter = 0;
  }
  ipart = (long long)newipart;
  fpart = newipart - (long double)ipart;
  // манипуляция для правильного округления
  if (precision != 0) {
    double rounding_factor = 0.5 / pow(10, precision);
    fpart += rounding_factor;
  } else {
    fpart = 0;
  }
  int i = s21_int_to_str(ipart, res + index, 10);  // получаем длину целой части
  // рассмотреть для E(есть точка) / .E(нет точка)
  if (precision > 0 || m->hash) {
    res[i + index] = '.';
  }
  s21_fpartetoa(fpart, res, precision, m, counter);
  return s21_strlen(res);
}

// перевод дробной части в строку с условием спецификатора Е/е
void s21_fpartetoa(long double fpart, char *res, int precision, Modifiers *m,
                   int counter) {
  char buffer[BUFF_SIZE] = {'\0'};
  char buffer1[BUFF_SIZE] = {'\0'};

  if (precision >= 0) {
    long int prec = precision;
    int i = 0, j = 0, newcc = 0;
    while (prec--) {
      fpart *= 10;
      long int tmp = (long int)fpart;
      if (tmp > 9) {
        tmp %= 10;
      }
      buffer[i++] += '0' + tmp;
    }
    // нужен перевод в строку
    if (m->specifier == 'E') {
      buffer[i++] = 'E';
    } else if (m->specifier == 'e') {
      buffer[i++] = 'e';
    }
    if (counter == 0) {
      buffer[i++] = '+';
      buffer[i++] = '0';
      buffer[i++] = '0';
    } else if (counter > 0 && counter <= 9) {
      buffer[i++] = '+';
      buffer[i++] = '0';
    } else if (counter >= 10) {
      buffer[i++] = '+';
    } else if (counter <= 0 && counter >= -9) {
      counter = -counter;
      buffer[i++] = '-';
      buffer[i++] = '0';
    } else if (counter <= -10) {
      counter = -counter;
      buffer[i++] = '-';
    }
    while (counter > 0) {
      int newc;
      newc = counter % 10;
      buffer1[j++] += (newc + '0');
      newcc++;
      counter /= 10;
    }
    for (j = newcc - 1; j >= 0; j--) {
      buffer[i++] = buffer1[j];
    }
  }
  s21_strncat(res, buffer, s21_strlen(buffer));
}
