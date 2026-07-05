#ifndef S21_STRING_H
#define S21_STRING_H
#include <stdlib.h>

#define S21_NULL ((void *)0)
typedef unsigned long s21_size_t;
#include "s21_sprintf.h"
#include "s21_sscanf.h"

s21_size_t s21_strlen(const char *str);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
void *s21_memset(void *str, int c, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
char *s21_strstr(const char *haystack, const char *needle);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
char *s21_strtok(char *str, const char *delim);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
char *s21_strrchr(const void *str, unsigned int c);
char *s21_strpbrk(const char *str1, const char *str2);
void *s21_trim(const char *src, const char *trim_chars);
int s21_sprintf(char *str, const char *format, ...);
void *s21_to_upper(const char *string);
void *s21_to_lower(const char *string);
int s21_sscanf(const char *str, const char *format, ...);
char *s21_strerror(int errnum);
#endif