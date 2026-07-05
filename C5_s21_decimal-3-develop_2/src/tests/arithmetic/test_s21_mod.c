#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../s21_decimal_test.h"

START_TEST(s21_mod_1) {
  s21_decimal src1, src2, res_mod;
  int a = 3;
  int b = 2;
  int res_origin = a % b;
  int res = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_2) {
  s21_decimal src1, src2, res_mod;
  int a = -98765;
  int b = 1234;
  int res_origin = a % b;
  int res = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_3) {
  s21_decimal src1, src2, res_mod;
  int a = 30198;
  int b = 20210;
  int res_origin = a % b;
  int res = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_4) {
  s21_decimal src1, src2, res_mod;
  int a = -98765;
  int b = -1234;
  int res_origin = a % b;
  int res = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_5) {
  s21_decimal src1, src2, res_mod;
  int a = 98765;
  int b = 127234;
  int res_origin = a % b;
  int res = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_6) {
  s21_decimal src1, src2, res_mod;
  int a = 342576;
  int b = 1542134;
  int res_origin = a % b;
  int res = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_7) {
  s21_decimal src1, src2, res_mod;
  int a = 12;
  int b = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int check = s21_mod(src1, src2, &res_mod);
  ck_assert_int_eq(check, 3);
}
END_TEST

START_TEST(s21_mod_8) {
  s21_decimal src1, src2, res_mod;
  int a = 12;
  float b = 0.0000;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  int check = s21_mod(src1, src2, &res_mod);
  ck_assert_int_eq(check, 3);
}
END_TEST

Suite *s21_mod_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_mod");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_mod_1);
  tcase_add_test(tc_core, s21_mod_2);
  tcase_add_test(tc_core, s21_mod_3);
  tcase_add_test(tc_core, s21_mod_4);
  tcase_add_test(tc_core, s21_mod_5);
  tcase_add_test(tc_core, s21_mod_6);
  tcase_add_test(tc_core, s21_mod_7);
  tcase_add_test(tc_core, s21_mod_8);

  suite_add_tcase(s, tc_core);

  return s;
}