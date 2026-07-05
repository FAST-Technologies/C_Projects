#include "tests_s21_main.h"

#define GENERATE_TEST(test_name, str1, str2)            \
  START_TEST(test_name) {                               \
    s21_size_t result_custom = s21_strcspn(str1, str2); \
    s21_size_t result_original = strcspn(str1, str2);   \
    ck_assert_int_eq(result_custom, result_original);   \
  }                                                     \
  END_TEST

GENERATE_TEST(s21_strcspn_test_1, "", "abc")
GENERATE_TEST(s21_strcspn_test_2, "Hello", "")
GENERATE_TEST(s21_strcspn_test_3, "", "")
GENERATE_TEST(s21_strcspn_test_4, "abc", "abcdefghijklmnopqrstuvwxyz")
GENERATE_TEST(s21_strcspn_test_5, "Hello", "xyz")
GENERATE_TEST(s21_strcspn_test_6, "abcdef", "d")
GENERATE_TEST(s21_strcspn_test_7, "abcdef", "a")
GENERATE_TEST(s21_strcspn_test_8, "abcdef", "f")
GENERATE_TEST(s21_strcspn_test_9, "Hello",
              "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
GENERATE_TEST(s21_strcspn_test_10, "abcdef", "xyzzy")

Suite *s21_strcspn_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strcspn");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strcspn_test_1);
  tcase_add_test(tc_core, s21_strcspn_test_2);
  tcase_add_test(tc_core, s21_strcspn_test_3);
  tcase_add_test(tc_core, s21_strcspn_test_4);
  tcase_add_test(tc_core, s21_strcspn_test_5);
  tcase_add_test(tc_core, s21_strcspn_test_6);
  tcase_add_test(tc_core, s21_strcspn_test_7);
  tcase_add_test(tc_core, s21_strcspn_test_8);
  tcase_add_test(tc_core, s21_strcspn_test_9);
  tcase_add_test(tc_core, s21_strcspn_test_10);

  suite_add_tcase(s, tc_core);
  return s;
}
