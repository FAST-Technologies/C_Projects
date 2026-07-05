#include "tests_s21_main.h"

#define GENERATE_TEST_STRPBRK(test_name, str1, str2, expected) \
  START_TEST(test_name) {                                      \
    char *result_custom = s21_strpbrk(str1, str2);             \
    const char *result_original = strpbrk(str1, str2);         \
    ck_assert_ptr_eq(result_custom, result_original);          \
  }                                                            \
  END_TEST

// Генерация тестовых функций
GENERATE_TEST_STRPBRK(s21_strpbrk_test_1, "hello world", "aeiou", "ello world")
GENERATE_TEST_STRPBRK(s21_strpbrk_test_2, "abcdefg", "xyz", S21_NULL)
GENERATE_TEST_STRPBRK(s21_strpbrk_test_3, "Hello, world!", " ,!", ", world!")
GENERATE_TEST_STRPBRK(s21_strpbrk_test_4, "test", "t", "test")
GENERATE_TEST_STRPBRK(s21_strpbrk_test_5, "", "a", S21_NULL)
GENERATE_TEST_STRPBRK(s21_strpbrk_test_6, "123456", "789", S21_NULL)
GENERATE_TEST_STRPBRK(s21_strpbrk_test_7, "abcdef", "f", "f")
GENERATE_TEST_STRPBRK(s21_strpbrk_test_8, "abcdef", "", S21_NULL)
GENERATE_TEST_STRPBRK(s21_strpbrk_test_9, "abcdef", "abcdef", "abcdef")
GENERATE_TEST_STRPBRK(s21_strpbrk_test_10, "abcdef", "ghijkl", S21_NULL)

Suite *s21_strpbrk_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strpbrk");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strpbrk_test_1);
  tcase_add_test(tc_core, s21_strpbrk_test_2);
  tcase_add_test(tc_core, s21_strpbrk_test_3);
  tcase_add_test(tc_core, s21_strpbrk_test_4);
  tcase_add_test(tc_core, s21_strpbrk_test_5);
  tcase_add_test(tc_core, s21_strpbrk_test_6);
  tcase_add_test(tc_core, s21_strpbrk_test_7);
  tcase_add_test(tc_core, s21_strpbrk_test_8);
  tcase_add_test(tc_core, s21_strpbrk_test_9);
  tcase_add_test(tc_core, s21_strpbrk_test_10);

  suite_add_tcase(s, tc_core);

  return s;
}