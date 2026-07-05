#include "tests_s21_main.h"

#if defined(__APPLE__)
#define MAX_ERRLIST 107
#elif defined(__linux__)
#define MAX_ERRLIST 134
#endif

#define GENERATE_TEST_STRERROR(test_name)               \
  START_TEST(test_name) {                               \
    int errnum = 0;                                     \
    while (errnum < MAX_ERRLIST) {                      \
      char *result_custom = s21_strerror(errnum);       \
      char *result_original = strerror(errnum);         \
      ck_assert_str_eq(result_custom, result_original); \
      errnum++;                                         \
    }                                                   \
  }                                                     \
  END_TEST

GENERATE_TEST_STRERROR(s21_strerror_test_range);

Suite *s21_strerror_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strerror");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strerror_test_range);

  suite_add_tcase(s, tc_core);

  return s;
}