#include "tests_s21_main.h"

#define GENERATE_TEST(test_name, str, symbol)                   \
  START_TEST(test_name) {                                       \
    void *result_custom = s21_strrchr(str, symbol);             \
    void *result_original = strrchr(str, symbol);               \
    if (result_custom == S21_NULL && result_original == NULL) { \
      ck_assert_ptr_eq(result_custom, S21_NULL);                \
      ck_assert_ptr_eq(result_custom, NULL);                    \
    } else {                                                    \
      ck_assert_ptr_eq(result_custom, result_original);         \
    }                                                           \
  }                                                             \
  END_TEST

GENERATE_TEST(s21_strrchr_test_1, "heehehhgehehe", 'g')
GENERATE_TEST(s21_strrchr_test_2, "hfghfghffg332412f", '3')
GENERATE_TEST(s21_strrchr_test_3, "", ' ')
GENERATE_TEST(s21_strrchr_test_4, "gfdgfd3", '6')
GENERATE_TEST(s21_strrchr_test_5, "Hello, friend!", '!')
GENERATE_TEST(s21_strrchr_test_6, "fd1sfsdfsdf", '3')
GENERATE_TEST(s21_strrchr_test_7, "Hi!!!!\n\n23", '\n')
GENERATE_TEST(s21_strrchr_test_8, "logl", '\0')

Suite *s21_strrchr_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strrchr");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strrchr_test_1);
  tcase_add_test(tc_core, s21_strrchr_test_2);
  tcase_add_test(tc_core, s21_strrchr_test_3);
  tcase_add_test(tc_core, s21_strrchr_test_4);
  tcase_add_test(tc_core, s21_strrchr_test_5);
  tcase_add_test(tc_core, s21_strrchr_test_6);
  tcase_add_test(tc_core, s21_strrchr_test_7);
  tcase_add_test(tc_core, s21_strrchr_test_8);

  suite_add_tcase(s, tc_core);
  return s;
}