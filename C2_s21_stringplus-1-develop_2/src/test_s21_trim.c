#include "tests_s21_main.h"

#define GENERATE_TEST(test_name, src, trim_chars, expectation) \
  START_TEST(test_name) {                                      \
    char *result_custom = s21_trim(src, trim_chars);           \
    ck_assert_str_eq(result_custom, expectation);              \
    free(result_custom);                                       \
  }                                                            \
  END_TEST

GENERATE_TEST(s21_trim_test_1, "123abc456xyz789", "123456789", "abc456xyz")
GENERATE_TEST(s21_trim_test_2, "*123xyz********c******c", "*1c", "23xyz")
GENERATE_TEST(s21_trim_test_3, "       LOL     ", S21_NULL, "LOL")
GENERATE_TEST(s21_trim_test_4, "123Maxim123", "123", "Maxim")
GENERATE_TEST(s21_trim_test_5, "LOL ", S21_NULL, "LOL")
GENERATE_TEST(s21_trim_test_6, "hello world", "hd", "ello worl")
GENERATE_TEST(s21_trim_test_7, "123", "123", "")
GENERATE_TEST(s21_trim_test_8, "---abc---xyz----", "-", "abc---xyz")
GENERATE_TEST(s21_trim_test_9, "\tHI!!!!\n\n", S21_NULL, "HI!!!!")
Suite *s21_trim_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_trim");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_trim_test_1);
  tcase_add_test(tc_core, s21_trim_test_2);
  tcase_add_test(tc_core, s21_trim_test_3);
  tcase_add_test(tc_core, s21_trim_test_4);
  tcase_add_test(tc_core, s21_trim_test_5);
  tcase_add_test(tc_core, s21_trim_test_6);
  tcase_add_test(tc_core, s21_trim_test_7);
  tcase_add_test(tc_core, s21_trim_test_8);
  tcase_add_test(tc_core, s21_trim_test_9);
  suite_add_tcase(s, tc_core);

  return s;
}
