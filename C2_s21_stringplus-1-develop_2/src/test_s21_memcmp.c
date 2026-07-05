#include "tests_s21_main.h"

#define GENERATE_TEST(test_name, str1, str2, n)            \
  START_TEST(test_name) {                                  \
    int result_custom = s21_memcmp(str1, str2, n);         \
    int result_original = memcmp(str1, str2, n);           \
    if (result_custom > 0 && result_original > 0) {        \
      ck_assert_int_gt(result_custom, 0);                  \
      ck_assert_int_gt(result_original, 0);                \
    } else if (result_custom < 0 && result_original < 0) { \
      ck_assert_int_lt(result_custom, 0);                  \
      ck_assert_int_lt(result_original, 0);                \
    } else {                                               \
      ck_assert_int_eq(result_custom, result_original);    \
    }                                                      \
  }
END_TEST
int test = 82;
GENERATE_TEST(s21_memcmp_test_1, "abc", "ab", 2)
GENERATE_TEST(s21_memcmp_test_2, "gdgfdgdfg", "Hello", 5)
GENERATE_TEST(s21_memcmp_test_3, "hehehhehe", "213", 3)
GENERATE_TEST(s21_memcmp_test_4, "Hi", "Hi", 2)
GENERATE_TEST(s21_memcmp_test_5, "Hi44", "Higf", 3)
GENERATE_TEST(s21_memcmp_test_6, "R", &test, 1)
GENERATE_TEST(s21_memcmp_test_7, "Hifdfgh", "Hifdhghg", 2)
GENERATE_TEST(s21_memcmp_test_8, "fdsssssssssssssssdfsdfsdfds",
              "bmnwsl;kjfqwouhfsdlngvbskhgsldjnfjlsdf", 15)
GENERATE_TEST(s21_memcmp_test_9, "dd", "dd", 0)
GENERATE_TEST(s21_memcmp_test_10, "fsd", "fds", 1)
GENERATE_TEST(s21_memcmp_test_11, "fsdfsdf", "2222", 5)
GENERATE_TEST(s21_memcmp_test_12, "nhgnghngh", "3232345", 7)

Suite *s21_memcmp_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_memcmp");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_memcmp_test_1);
  tcase_add_test(tc_core, s21_memcmp_test_2);
  tcase_add_test(tc_core, s21_memcmp_test_3);
  tcase_add_test(tc_core, s21_memcmp_test_4);
  tcase_add_test(tc_core, s21_memcmp_test_5);
  tcase_add_test(tc_core, s21_memcmp_test_6);
  tcase_add_test(tc_core, s21_memcmp_test_7);
  tcase_add_test(tc_core, s21_memcmp_test_8);
  tcase_add_test(tc_core, s21_memcmp_test_9);
  tcase_add_test(tc_core, s21_memcmp_test_10);
  tcase_add_test(tc_core, s21_memcmp_test_11);
  tcase_add_test(tc_core, s21_memcmp_test_12);

  suite_add_tcase(s, tc_core);

  return s;
}
