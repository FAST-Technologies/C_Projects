#include "tests_s21_main.h"

#define GENERATE_TEST(test_name, str1, str2, n)       \
  START_TEST(test_name) {                             \
    int result_custom = s21_strncmp(str1, str2, n);   \
    int result_original = strncmp(str1, str2, n);     \
    ck_assert_int_eq(result_custom, result_original); \
  }                                                   \
  END_TEST

GENERATE_TEST(s21_strncmp_test_1, "Hello, World!", "Hello, World!", 5)
GENERATE_TEST(s21_strncmp_test_2, "a", "a", 1)
GENERATE_TEST(s21_strncmp_test_3, "ab", "ab", 2)

Suite *s21_strncmp_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strncmp");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strncmp_test_1);
  tcase_add_test(tc_core, s21_strncmp_test_2);
  tcase_add_test(tc_core, s21_strncmp_test_3);

  suite_add_tcase(s, tc_core);
  return s;
}