#include "tests_s21_main.h"

#define GENERATE_TEST(test_name, str, sym, lenght)            \
  START_TEST(test_name) {                                     \
    char result_custom[50] = {0};                             \
    char result_original[50] = {0};                           \
    strcpy(result_original, str);                             \
    strcpy(result_custom, str);                               \
    memset(result_original, sym, lenght);                     \
    s21_memset(result_custom, sym, lenght);                   \
    ck_assert_mem_eq(result_custom, result_original, lenght); \
  }                                                           \
  END_TEST

GENERATE_TEST(memset_test_1, "", '1', 5)
GENERATE_TEST(memset_test_2, "Hello", '2', 10)
GENERATE_TEST(memset_test_3, "Hello", '3', 3)
GENERATE_TEST(memset_test_4, "Hello", '4', (size_t)0)

Suite *s21_memset_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_memset");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, memset_test_1);
  tcase_add_test(tc_core, memset_test_2);
  tcase_add_test(tc_core, memset_test_3);
  tcase_add_test(tc_core, memset_test_4);
  suite_add_tcase(s, tc_core);
  return s;
}
