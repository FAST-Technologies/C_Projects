#include "tests_s21_main.h"

#define GENERATE_TEST(test_name, string, expect) \
  START_TEST(test_name) {                        \
    char *result_custom = s21_to_lower(string);  \
    ck_assert_str_eq(result_custom, expect);     \
    if (result_custom) free(result_custom);      \
  }                                              \
  END_TEST

GENERATE_TEST(s21_to_lower_test_1, "GOOD JOB", "good job")
GENERATE_TEST(s21_to_lower_test_2, "GoOdByE", "goodbye")
GENERATE_TEST(s21_to_lower_test_3, "", "")
GENERATE_TEST(s21_to_lower_test_4, "1=-384673^", "1=-384673^")
GENERATE_TEST(s21_to_lower_test_5, "A675FF537fdsD", "a675ff537fdsd")

Suite *s21_to_lower_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_to_lower");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_to_lower_test_1);
  tcase_add_test(tc_core, s21_to_lower_test_2);
  tcase_add_test(tc_core, s21_to_lower_test_3);
  tcase_add_test(tc_core, s21_to_lower_test_4);
  tcase_add_test(tc_core, s21_to_lower_test_5);
  suite_add_tcase(s, tc_core);

  return s;
}