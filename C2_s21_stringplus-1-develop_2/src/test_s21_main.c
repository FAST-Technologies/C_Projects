#include "tests_s21_main.h"

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = suite_create("s21_string");
  sr = srunner_create(s);

  srunner_add_suite(sr, s21_strlen_suite());
  srunner_add_suite(sr, s21_strcspn_suite());
  srunner_add_suite(sr, s21_memset_suite());
  srunner_add_suite(sr, s21_memcpy_suite());
  srunner_add_suite(sr, s21_strstr_suite());
  srunner_add_suite(sr, s21_insert_suite());
  srunner_add_suite(sr, s21_strtok_suite());
  srunner_add_suite(sr, s21_strncmp_suite());
  srunner_add_suite(sr, s21_strrchr_suite());
  srunner_add_suite(sr, s21_memchr_suite());
  srunner_add_suite(sr, s21_memcmp_suite());
  srunner_add_suite(sr, s21_strchr_suite());
  srunner_add_suite(sr, s21_strncpy_suite());
  srunner_add_suite(sr, s21_strpbrk_suite());
  srunner_add_suite(sr, s21_strncat_suite());
  srunner_add_suite(sr, s21_sprintf_suite());
  srunner_add_suite(sr, s21_trim_suite());
  srunner_add_suite(sr, s21_to_upper_suite());
  srunner_add_suite(sr, s21_to_lower_suite());
  srunner_add_suite(sr, s21_sscanf_suite());
  srunner_add_suite(sr, s21_strerror_suite());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}