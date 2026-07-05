#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_sscanf.h"
#include "tests_s21_main.h"

// макрос для генерации тестов для строк
#define GENERATE_TEST_SSCANF_STRING(test_name, str, format, size)          \
  START_TEST(test_name) {                                                  \
    char *custom_var = malloc(size * sizeof(char));                        \
    char *original_var = malloc(size * sizeof(char));                      \
    int result_original, result_custom;                                    \
    if (original_var) result_original = sscanf(str, format, original_var); \
    if (custom_var) result_custom = s21_sscanf(str, format, custom_var);   \
    ck_assert_int_eq(result_custom, result_original);                      \
    ck_assert_str_eq(custom_var, original_var);                            \
    free(custom_var);                                                      \
    free(original_var);                                                    \
  }                                                                        \
  END_TEST

// макрос для генерации тестов для других типов данных
#define GENERATE_TEST_SSCANF(test_name, str, format, var_type)      \
  START_TEST(test_name) {                                           \
    var_type custom_var;                                            \
    var_type original_var;                                          \
    int result_original = sscanf(str, format, &original_var);       \
    int result_custom = s21_sscanf(str, format, &custom_var);       \
    ck_assert_int_eq(result_custom, result_original);               \
    ck_assert_mem_eq(&custom_var, &original_var, sizeof(var_type)); \
  }                                                                 \
  END_TEST

// макрос для генерации тестов для других типов данных
#define GENERATE_TEST_SSCANF_DOUBLE(test_name, str, format)   \
  START_TEST(test_name) {                                     \
    double custom_var;                                        \
    double original_var;                                      \
    int result_original = sscanf(str, format, &original_var); \
    int result_custom = s21_sscanf(str, format, &custom_var); \
    ck_assert_int_eq(result_custom, result_original);         \
    ck_assert_float_eq(custom_var, original_var);             \
  }                                                           \
  END_TEST

// макрос для генерации тестов для других типов данных
#define GENERATE_TEST_SSCANF_FLOAT(test_name, str, format)    \
  START_TEST(test_name) {                                     \
    float custom_var;                                         \
    float original_var;                                       \
    int result_original = sscanf(str, format, &original_var); \
    int result_custom = s21_sscanf(str, format, &custom_var); \
    ck_assert_int_eq(result_custom, result_original);         \
    ck_assert_float_eq(custom_var, original_var);             \
  }                                                           \
  END_TEST

// Генерация тестовых функций для строк
GENERATE_TEST_SSCANF_STRING(s21_sscanf_test_1, "Hello, World!", "%255s", 256)
GENERATE_TEST_SSCANF_STRING(s21_sscanf_test_3, "qwert", "%255s", 256)

// Генерация тестовых функций для других типов данных
GENERATE_TEST_SSCANF(s21_sscanf_test_2, "12345", "%d", int)
GENERATE_TEST_SSCANF(s21_sscanf_test_4, "12345", "%u", unsigned int)
GENERATE_TEST_SSCANF(s21_sscanf_test_5, "A", "%c", char)
// Генерация тестовых функций для float / double
GENERATE_TEST_SSCANF_DOUBLE(s21_sscanf_test_6, "1.23", "%lf")
GENERATE_TEST_SSCANF_FLOAT(s21_sscanf_test_7, "2.123456789", "%f")

GENERATE_TEST_SSCANF(s21_sscanf_test_8, "-100500", "%d", int)
GENERATE_TEST_SSCANF(s21_sscanf_test_9, "-100.500", "%f", float)
GENERATE_TEST_SSCANF_DOUBLE(s21_sscanf_test_10, "42.4200000000000001", "%lf")

START_TEST(EOF1) {
  char format[] = "%d";
  char str[] = "        ";

  int16_t res1 = s21_sscanf(str, format, 0);
  int16_t res2 = sscanf(str, format, 100);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(EOF2) {
  char format[] = "%d ";
  char str[] = "               ";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(str, format, &a1);
  int16_t res2 = sscanf(str, format, &a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(EOF3) {
  char format[] = "%d ";
  char str[] = "  ";
  int16_t a1 = 0;

  int16_t res1 = s21_sscanf(str, format, &a1);
  int16_t res2 = sscanf(str, format, &a1);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(c_not_correct) {
  char format[] = "%c %c %c %c";
  char str[] = "   a     b c d";
  int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);

  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(c_correct) {
  char format[] = "%c%c%c%c";
  char str[] = "abcd";
  int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);

  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(c_empty) {
  char format[] = "%c";
  char str[] = "";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(str, format, &a1);
  int16_t res2 = sscanf(str, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(c_spaces) {
  char format[] = "%c %c %c %c";
  char str[] = "A B C D";
  int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);

  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(c_spec_symbols) {
  char format[] = "%c %c %c %c";
  char str[] = "z ' ' /";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(c_star) {
  char format[] = "%c%*c%c%c";
  char str[] = "ABCD";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1);

  int16_t res2 = sscanf(str, format, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(c_stars) {
  char format[] = "%*c%*c%*c%c";
  char str[] = "abcd ";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(str, format, &a1);
  int16_t res2 = sscanf(str, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(c_width) {
  char format[] = "%1c %c %c %0c";
  char str[] = "z *'@";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(c_stars_and_spaces) {
  char format[] = "%*c%*c%*c%*c";
  char str[] = "   c ";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(str, format, &a1);
  int16_t res2 = sscanf(str, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(d_empty) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char format[] = "%d %d %d %d";
  const char str[] = "555 666 777 888";

  int32_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(d_correct) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char format[] = "%d %d %d %d";
  const char str[] = "555 666 777 888";

  int32_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(d_not_correct) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char format[] = " %d %d %d %d";
  const char str[] = "55.5 666 777 888";

  int32_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(d_h) {
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337 21 5008 3000";
  const char format[] = "%hd %hd %hd %hd";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(d_l) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337 21 5008 300004";
  const char format[] = "%ld %ld %ld %ld";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(d_l_w) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337 21 5008 300004";
  const char format[] = "%1ld %3ld %1ld %4ld";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(d_l_w2) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "100000000000000005";
  const char format[] = "%3ld%ld%1ld%5ld";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(d_l_stars) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  const char str[] = "1337123123 1 123412341234 1 999999 0";
  const char format[] = "%*d %ld %*d %ld %*d %ld";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(d_operators) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "11337 ++3 -5 ------4";
  const char format[] = "%ld %ld %ld %ld";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(d_zeros) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "-0 +0 +0 -0";
  const char format[] = "%2ld %1ld %1ld %1ld";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(i_empty) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char format[] = "%i %i %i %i";
  const char str[] = "555 666 777 888";

  int32_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(i_correct) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char format[] = "%i %i %i %i";
  const char str[] = "555 666 777 888";

  int32_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(i_not_correct) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char format[] = " %i %i %i %i";
  const char str[] = "1.0 666 777 888";

  int32_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(i_h) {
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337 21 5008 3000";
  const char format[] = "%hi %hi %hi %hi";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(i_l) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337 21 5008 300004";
  const char format[] = "%li %li %li %li";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(i_l_w) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337 21 5008 300004";
  const char format[] = "%1li %3li %1li %4li";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(i_l_w2) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "100000000000000005";
  const char format[] = "%3li%li%1li%5li";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(i_l_stars) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  const char str[] = "1337123123 1 123412341234 1 999999 0";
  const char format[] = "%*i %li %*i %li %*i %li";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(i_operators) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "11337 ++3 -5 ------4";
  const char format[] = "%li %li %li %li";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(i_zeros) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "-0 +0 +0 -0";
  const char format[] = "%2li %1li %1li %1li";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(i_symbols) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "  55555 f f f5555555 ddd   4    3    1 ";
  const char format[] = "%li %ld %ld %li";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(p_correct) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char str[] = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char format[] = "%p %p %p %p";

  int16_t res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(percent) {
  int32_t a1, a2;
  int32_t b1 = 80, b2 = 33;
  int32_t c1 = 55, c2 = 33;
  const char str[] = "12 % 13 % 14";
  const char format[] = "%d %% %d %% %d";
  int32_t res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int32_t res2 = sscanf(str, format, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(percent1) {
  int32_t a1, a2;
  int32_t b1 = 80, b2 = 33;
  int32_t c1 = 55, c2 = 33;
  const char str[] = "12%13%14";
  const char format[] = "%d%%%d%%%d";
  int32_t res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int32_t res2 = sscanf(str, format, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(percent2) {
  int32_t a1 = 1234, a2 = 33333;

  const char str[] = "%%%16";
  const char format[] = "%%%%%%%d";
  int32_t res1 = s21_sscanf(str, format, &a1);
  int32_t res2 = sscanf(str, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *s = suite_create("s21_sscanf");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_sscanf_test_1);
  tcase_add_test(tc_core, s21_sscanf_test_2);
  tcase_add_test(tc_core, s21_sscanf_test_3);
  tcase_add_test(tc_core, s21_sscanf_test_4);
  tcase_add_test(tc_core, s21_sscanf_test_5);
  tcase_add_test(tc_core, s21_sscanf_test_6);
  tcase_add_test(tc_core, s21_sscanf_test_7);
  tcase_add_test(tc_core, s21_sscanf_test_8);
  tcase_add_test(tc_core, s21_sscanf_test_9);
  tcase_add_test(tc_core, s21_sscanf_test_10);

  tcase_add_test(tc_core, EOF1);
  tcase_add_test(tc_core, EOF2);
  tcase_add_test(tc_core, EOF3);

  tcase_add_test(tc_core, c_not_correct);
  tcase_add_test(tc_core, c_correct);
  tcase_add_test(tc_core, c_empty);
  tcase_add_test(tc_core, c_spaces);
  tcase_add_test(tc_core, c_spec_symbols);
  tcase_add_test(tc_core, c_star);
  tcase_add_test(tc_core, c_stars);
  tcase_add_test(tc_core, c_width);
  tcase_add_test(tc_core, c_stars_and_spaces);

  tcase_add_test(tc_core, d_empty);
  tcase_add_test(tc_core, d_correct);
  tcase_add_test(tc_core, d_not_correct);
  tcase_add_test(tc_core, d_h);
  tcase_add_test(tc_core, d_l);
  tcase_add_test(tc_core, d_l_w);
  tcase_add_test(tc_core, d_l_w2);
  tcase_add_test(tc_core, d_l_stars);
  tcase_add_test(tc_core, d_operators);
  tcase_add_test(tc_core, d_zeros);

  tcase_add_test(tc_core, i_empty);
  tcase_add_test(tc_core, i_correct);
  tcase_add_test(tc_core, i_not_correct);
  tcase_add_test(tc_core, i_h);
  tcase_add_test(tc_core, i_l);
  tcase_add_test(tc_core, i_l_w);
  tcase_add_test(tc_core, i_l_w2);
  tcase_add_test(tc_core, i_l_stars);
  tcase_add_test(tc_core, i_operators);
  tcase_add_test(tc_core, i_zeros);
  tcase_add_test(tc_core, i_symbols);

  tcase_add_test(tc_core, p_correct);

  tcase_add_test(tc_core, percent);
  tcase_add_test(tc_core, percent1);
  tcase_add_test(tc_core, percent2);

  suite_add_tcase(s, tc_core);

  return s;
}
