#include "tests_s21_main.h"

#define GENERATE_TEST(test_name, str)                 \
  START_TEST(test_name) {                             \
    s21_size_t result_custom = s21_strlen(str);       \
    s21_size_t result_original = strlen(str);         \
    ck_assert_int_eq(result_custom, result_original); \
  }                                                   \
  END_TEST

GENERATE_TEST(s21_strlen_test_1, "Hello, World!")
GENERATE_TEST(s21_strlen_test_2, "a")
GENERATE_TEST(s21_strlen_test_3, "ab")
GENERATE_TEST(s21_strlen_test_4, "1234567890")
GENERATE_TEST(s21_strlen_test_5, "")
GENERATE_TEST(s21_strlen_test_6, " ")
GENERATE_TEST(s21_strlen_test_7, "\t")
GENERATE_TEST(s21_strlen_test_8, "\n")
GENERATE_TEST(s21_strlen_test_9, "Hello,\nWorld!")
GENERATE_TEST(s21_strlen_test_10, "Hello, \t\nWorld!")
GENERATE_TEST(s21_strlen_test_11, "Special chars: \a\b\f\n\r\t\v")
GENERATE_TEST(s21_strlen_test_12,
              "Long string with spaces and symbols !@#$%{}[]^&*()_+-/\\\"")

Suite *s21_strlen_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strlen");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strlen_test_1);
  tcase_add_test(tc_core, s21_strlen_test_2);
  tcase_add_test(tc_core, s21_strlen_test_3);
  tcase_add_test(tc_core, s21_strlen_test_4);
  tcase_add_test(tc_core, s21_strlen_test_5);
  tcase_add_test(tc_core, s21_strlen_test_6);
  tcase_add_test(tc_core, s21_strlen_test_7);
  tcase_add_test(tc_core, s21_strlen_test_8);
  tcase_add_test(tc_core, s21_strlen_test_9);
  tcase_add_test(tc_core, s21_strlen_test_10);
  tcase_add_test(tc_core, s21_strlen_test_11);
  tcase_add_test(tc_core, s21_strlen_test_12);
  suite_add_tcase(s, tc_core);

  return s;
}
