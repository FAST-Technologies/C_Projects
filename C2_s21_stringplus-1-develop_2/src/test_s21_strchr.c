#include "tests_s21_main.h"

#define GENERATE_TEST(test_name, str, c)              \
  START_TEST(test_name) {                             \
    char *result_custom = s21_strchr(str, c);         \
    char *result_original = strchr(str, c);           \
    ck_assert_ptr_eq(result_custom, result_original); \
  }                                                   \
  END_TEST

GENERATE_TEST(s21_strchr_test_1, "Hello, World!", 'e')
GENERATE_TEST(s21_strchr_test_2, "12345", '4')
GENERATE_TEST(s21_strchr_test_3, "qwert", 'b')
GENERATE_TEST(s21_strchr_test_4, "Hi!!!!!", '!')

Suite *s21_strchr_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strchr");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strchr_test_1);
  tcase_add_test(tc_core, s21_strchr_test_2);
  tcase_add_test(tc_core, s21_strchr_test_3);
  tcase_add_test(tc_core, s21_strchr_test_4);

  suite_add_tcase(s, tc_core);

  return s;
}