#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>

#include "s21_string.h"
#define BUFF_SIZE 4096

typedef struct {
  bool minus;
  bool plus;
  bool space;
  bool zero;
  bool hash;
  int width;
  int precision;
  char specifier;
  char length;
} Modifiers;

int s21_write_str(char *str, const char *format, va_list args);
void s21_parse_char(char *buffer, va_list args);
void s21_parse_string(char *buffer, va_list args, Modifiers *m);
void s21_parse_unsigned(char *buffer, va_list args, Modifiers *m);
void s21_parse_float(char *buffer, va_list args, Modifiers *m);
void s21_parse_int(char *buffer, va_list args, Modifiers *m);
void s21_use_modifier(char *buffer, va_list args, Modifiers *m);
const char *s21_parse_flags(const char *format, Modifiers *m);
Modifiers s21_init_flags();
const char *s21_parse_width(const char *format, Modifiers *m, va_list args);
const char *s21_parse_precision(const char *format, Modifiers *m, va_list args);
const char *s21_parse_length(const char *format, Modifiers *m);
void s21_apply_width_and_minus(char *buffer, Modifiers *m);
void s21_reverse_str(char *str);
int s21_int_to_str(long long x, char *str, const s21_size_t base);
int s21_ftoa(long double number, char *buffer, int precision, Modifiers *m);
void s21_format_int_precision(char *temp, int precision, Modifiers *m);
void s21_format_flag_zero(char *src, int len, int negative, Modifiers *m);
int s21_uitoa(unsigned long long num, char *str, const s21_size_t base);
void s21_fparttoa(double fpart, char *res, int precision);
void s21_parse_octal(char *buffer, va_list args, Modifiers *m);
void s21_parse_hex(char *buffer, va_list args, Modifiers *m);
void s21_parse_e_scientific(char *buffer, va_list args, Modifiers *m);
int s21_fetoa(long double n, char *res, int precision, Modifiers *m);
void s21_fpartetoa(long double fpart, char *res, int precision, Modifiers *m,
                   int counter);
void s21_parse_pointer(char *buffer, va_list args);

#endif
