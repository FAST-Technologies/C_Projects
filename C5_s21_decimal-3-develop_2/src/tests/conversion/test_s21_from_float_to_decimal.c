#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../s21_decimal_test.h"

START_TEST(s21_from_float_to_decimal_2) {
  s21_decimal val;
  float a = 1.00001F;
  int err_check = s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(err_check, 0);
  ck_assert_int_eq(val.bits[0], 0b11000011010100001);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 5 << 16);
}
END_TEST

START_TEST(s21_from_float_to_decimal_3) {
  s21_decimal val;
  float a = 1.0F / 0.0F;
  int err_check = s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(err_check, 1);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_4) {
  s21_decimal val;
  float a = NAN;
  int err_check = s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(err_check, 1);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

Suite *s21_from_float_to_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_from_float_to_decimal");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_from_float_to_decimal_2);
  tcase_add_test(tc_core, s21_from_float_to_decimal_3);
  tcase_add_test(tc_core, s21_from_float_to_decimal_4);
  suite_add_tcase(s, tc_core);

  return s;
}