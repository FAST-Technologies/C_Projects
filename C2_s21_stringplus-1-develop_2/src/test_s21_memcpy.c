#include "tests_s21_main.h"

#define GENERATE_MEMCPY_TEST(test_name, dest, src, n)        \
  START_TEST(test_name) {                                    \
    char dest_custom[100] = {0};                             \
    char dest_original[100] = {0};                           \
    strncpy(dest_custom, dest, sizeof(dest_custom) - 1);     \
    strncpy(dest_original, dest, sizeof(dest_original) - 1); \
    s21_memcpy(dest_custom, src, n);                         \
    memcpy(dest_original, src, n);                           \
    ck_assert_mem_eq(dest_custom, dest_original, n);         \
  }                                                          \
  END_TEST

GENERATE_MEMCPY_TEST(s21_memcpy_test_1, "Hello, s21-school-world!",
                     "Goodbye, World! Come tomorrow!", 24)
GENERATE_MEMCPY_TEST(s21_memcpy_test_2, "1234567890", "abcdefghij", 10)
GENERATE_MEMCPY_TEST(s21_memcpy_test_3, "abcdef", "123456", 6)
GENERATE_MEMCPY_TEST(s21_memcpy_test_4, "123", "abc", 3)
GENERATE_MEMCPY_TEST(s21_memcpy_test_5, "", "", 0)
GENERATE_MEMCPY_TEST(s21_memcpy_test_6, "Hello, World!", "Hello, World!", 5)
GENERATE_MEMCPY_TEST(s21_memcpy_test_7, "abcd", "efgh", 4)
GENERATE_MEMCPY_TEST(s21_memcpy_test_8, "1234567890", "abcdefghij", 0)

Suite *s21_memcpy_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_memcpy");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_memcpy_test_1);
  tcase_add_test(tc_core, s21_memcpy_test_2);
  tcase_add_test(tc_core, s21_memcpy_test_3);
  tcase_add_test(tc_core, s21_memcpy_test_4);
  tcase_add_test(tc_core, s21_memcpy_test_5);
  tcase_add_test(tc_core, s21_memcpy_test_6);
  tcase_add_test(tc_core, s21_memcpy_test_7);
  tcase_add_test(tc_core, s21_memcpy_test_8);
  suite_add_tcase(s, tc_core);
  return s;
}