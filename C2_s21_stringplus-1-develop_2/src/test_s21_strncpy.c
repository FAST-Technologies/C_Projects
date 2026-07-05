#include "tests_s21_main.h"

#define GENERATE_TEST(test_name, dest, src, n)       \
  START_TEST(test_name) {                            \
    char dest_custom[100] = {0};                     \
    char dest_original[100] = {0};                   \
    s21_strncpy(dest_custom, src, n);                \
    strncpy(dest_original, src, n);                  \
    ck_assert_mem_eq(dest_custom, dest_original, n); \
  }                                                  \
  END_TEST

GENERATE_TEST(s21_strncpy_test_1, "Hello, ", "World", 7)
GENERATE_TEST(s21_strncpy_test_2, "help", "mee", 4)
GENERATE_TEST(s21_strncpy_test_3, "qwert", "zxc", 7)

Suite *s21_strncpy_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strncpy");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strncpy_test_1);
  tcase_add_test(tc_core, s21_strncpy_test_2);
  tcase_add_test(tc_core, s21_strncpy_test_3);

  suite_add_tcase(s, tc_core);
  return s;
}