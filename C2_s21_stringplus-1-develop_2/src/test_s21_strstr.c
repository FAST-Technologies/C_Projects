#include "tests_s21_main.h"

#define GENERATE_TEST_1(test_name, haystack, needle)    \
  START_TEST(test_name) {                               \
    char *result_custom = s21_strstr(haystack, needle); \
    char *result_original = strstr(haystack, needle);   \
    ck_assert_str_eq(result_custom, result_original);   \
  }                                                     \
  END_TEST

#define GENERATE_TEST_2(test_name, haystack, needle)    \
  START_TEST(test_name) {                               \
    char *result_custom = s21_strstr(haystack, needle); \
    char *result_original = strstr(haystack, needle);   \
    ck_assert_ptr_eq(result_custom, result_original);   \
  }                                                     \
  END_TEST

GENERATE_TEST_1(s21_strstr_test_1, "Hello, world!", "")
GENERATE_TEST_1(s21_strstr_test_2, "Hello, world!", "world")
GENERATE_TEST_1(s21_strstr_test_3, "Hello", "Hello")
GENERATE_TEST_1(s21_strstr_test_4, "", "")
GENERATE_TEST_2(s21_strstr_test_5, "Hello", "hi")
GENERATE_TEST_2(s21_strstr_test_6, "Hi", "hello")

Suite *s21_strstr_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strstr");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strstr_test_1);
  tcase_add_test(tc_core, s21_strstr_test_2);
  tcase_add_test(tc_core, s21_strstr_test_3);
  tcase_add_test(tc_core, s21_strstr_test_4);
  tcase_add_test(tc_core, s21_strstr_test_5);
  tcase_add_test(tc_core, s21_strstr_test_6);
  suite_add_tcase(s, tc_core);

  return s;
}
