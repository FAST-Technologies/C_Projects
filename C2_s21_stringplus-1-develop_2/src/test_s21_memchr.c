#include "tests_s21_main.h"

#define GENERATE_TEST(test_name, str, symbol, n)      \
  START_TEST(test_name) {                             \
    void *result_custom = s21_memchr(str, symbol, n); \
    void *result_original = memchr(str, symbol, n);   \
    ck_assert_ptr_eq(result_custom, result_original); \
  }                                                   \
  END_TEST

GENERATE_TEST(s21_memchr_test_1, "heehehhgehehe", 'g', 13)
GENERATE_TEST(s21_memchr_test_2, "hfghfghffg332412f", '3', 5)
GENERATE_TEST(s21_memchr_test_3, "", ' ', 0)
GENERATE_TEST(s21_memchr_test_4, "gfdgfd3", '6', 3)
GENERATE_TEST(s21_memchr_test_5, "Hello, friend!", '!', 100)
GENERATE_TEST(s21_memchr_test_6, "fdsfsdfsdf", '3', 3)
GENERATE_TEST(s21_memchr_test_7, "lol", '2', 2)
GENERATE_TEST(s21_memchr_test_8, "Hi!!!!\n\n23", '\n', 100)
GENERATE_TEST(s21_memchr_test_9, "logl", '\0', 5)

Suite *s21_memchr_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_memchr");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_memchr_test_1);
  tcase_add_test(tc_core, s21_memchr_test_2);
  tcase_add_test(tc_core, s21_memchr_test_3);
  tcase_add_test(tc_core, s21_memchr_test_4);
  tcase_add_test(tc_core, s21_memchr_test_5);
  tcase_add_test(tc_core, s21_memchr_test_6);
  tcase_add_test(tc_core, s21_memchr_test_7);
  tcase_add_test(tc_core, s21_memchr_test_8);
  tcase_add_test(tc_core, s21_memchr_test_9);

  suite_add_tcase(s, tc_core);
  return s;
}