// #include <stdlib.h>

// #include "./../s21_decimal.h"
// #include "./test.h"

#include "./../s21_decimal.h"

#include "s21_decimal_test.h"

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = suite_create("s21_decimal");
  sr = srunner_create(s);

  srunner_add_suite(sr, s21_add_suite());
  srunner_add_suite(sr, s21_sub_suite());
  srunner_add_suite(sr, s21_mul_suite());
  srunner_add_suite(sr, s21_div_suite());
  srunner_add_suite(sr, s21_mod_suite());
  srunner_add_suite(sr, s21_is_less_suite());
  srunner_add_suite(sr, s21_is_less_or_equal_suite());
  srunner_add_suite(sr, s21_is_greater_suite());
  srunner_add_suite(sr, s21_is_greater_or_equal_suite());
  srunner_add_suite(sr, s21_is_equal_suite());
  srunner_add_suite(sr, s21_is_not_equal_suite());
  srunner_add_suite(sr, s21_from_int_to_decimal_suite());
  srunner_add_suite(sr, s21_from_float_to_decimal_suite());
  srunner_add_suite(sr, s21_from_decimal_to_int_suite());
  srunner_add_suite(sr, s21_from_decimal_to_float_suite());
  srunner_add_suite(sr, s21_floor_suite());
  srunner_add_suite(sr, s21_round_suite());
  srunner_add_suite(sr, s21_truncate_suite());
  srunner_add_suite(sr, s21_negate_suite());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
