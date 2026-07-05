#include "tests_s21_main.h"

#define GENERATE_TEST_1(test_name, str, delim, expected_tokens)  \
  START_TEST(test_name) {                                        \
    char input1[100];                                            \
    char input2[100];                                            \
    strncpy(input1, str, sizeof(input1) - 1);                    \
    strncpy(input2, str, sizeof(input2) - 1);                    \
    char *token_custom = s21_strtok(input1, delim);              \
    char *token_original = strtok(input2, delim);                \
    while (token_custom != S21_NULL && token_original != NULL) { \
      ck_assert_str_eq(token_custom, token_original);            \
      token_custom = s21_strtok(S21_NULL, delim);                \
      token_original = strtok(NULL, delim);                      \
    }                                                            \
    ck_assert_ptr_eq(token_custom, S21_NULL);                    \
    ck_assert_ptr_eq(token_original, NULL);                      \
  }                                                              \
  END_TEST

GENERATE_TEST_1(s21_strtok_test_1, "Hello, World! How are you?", " ,!?",
                "Hello World How are you")
GENERATE_TEST_1(s21_strtok_test_2, "a,b,c,d,e", ",", "a b c d e")
GENERATE_TEST_1(s21_strtok_test_3, "123-456-789", "-", "123 456 789")
GENERATE_TEST_1(s21_strtok_test_4, "abc:def:ghi", ":", "abc def ghi")
GENERATE_TEST_1(s21_strtok_test_5, "one two three", " ", "one two three")
GENERATE_TEST_1(s21_strtok_test_6, "   leading spaces", " ", "leading spaces")
GENERATE_TEST_1(s21_strtok_test_7, "trailing spaces   ", " ", "trailing spaces")
GENERATE_TEST_1(s21_strtok_test_8, "multiple   spaces", " ", "multiple spaces")
GENERATE_TEST_1(s21_strtok_test_9, "special!@#chars", "!@#", "special chars")
GENERATE_TEST_1(s21_strtok_test_10, "", " ", "")
GENERATE_TEST_1(s21_strtok_test_11, "singleword", " ", "singleword")
GENERATE_TEST_1(s21_strtok_test_12, " ", " ", "")
GENERATE_TEST_1(s21_strtok_test_13, " , ", ",", " ")
GENERATE_TEST_1(s21_strtok_test_14, "a,b,,c", ",", "a b c")
GENERATE_TEST_1(s21_strtok_test_15, "a,,b", ",", "a b")

Suite *s21_strtok_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strtok");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strtok_test_1);
  tcase_add_test(tc_core, s21_strtok_test_2);
  tcase_add_test(tc_core, s21_strtok_test_3);
  tcase_add_test(tc_core, s21_strtok_test_4);
  tcase_add_test(tc_core, s21_strtok_test_5);
  tcase_add_test(tc_core, s21_strtok_test_6);
  tcase_add_test(tc_core, s21_strtok_test_7);
  tcase_add_test(tc_core, s21_strtok_test_8);
  tcase_add_test(tc_core, s21_strtok_test_9);
  tcase_add_test(tc_core, s21_strtok_test_10);
  tcase_add_test(tc_core, s21_strtok_test_11);
  tcase_add_test(tc_core, s21_strtok_test_12);
  tcase_add_test(tc_core, s21_strtok_test_13);
  tcase_add_test(tc_core, s21_strtok_test_14);
  tcase_add_test(tc_core, s21_strtok_test_15);

  suite_add_tcase(s, tc_core);
  return s;
}
