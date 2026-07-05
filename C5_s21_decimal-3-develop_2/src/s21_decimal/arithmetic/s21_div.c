#include "../comparison/s21_difference_operators.h"
#include "../helps/s21_helps.h"
#include "./../s21_decimal_types.h"
#include "s21_arithmetic_operators.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic code_status = S21_ARITHMETIC_OK_STATUS;
  if (!result) {
    code_status = S21_ERROR_STATUS;
    exit(-1);
  } else if (!s21_correct_decimal(value_1) || !s21_correct_decimal(value_2)) {
    code_status = S21_ERROR_STATUS;
    *result = s21_decimal_get_inf();
  } else {
    int scale1 = s21_get_scale_coeff(value_1);
    int scale2 = s21_get_scale_coeff(value_2);
    int result_scale = scale1 >= scale2 ? scale1 : scale2;
    int sign1 = s21_decimal_get_sign(value_1);
    int sign2 = s21_decimal_get_sign(value_2);
    int sign = (sign1 != sign2);
    if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
      code_status = S21_DIVISION_BY_ZERO_STATUS;
    } else {
      s21_big_decimal big_value1, big_value2, result1,
          one_num = {{1, 0, 0, 0, 0, 0, 0, 0}};
      s21_big_decimal_to_null(&big_value1);
      s21_big_decimal_to_null(&big_value2);
      s21_big_decimal_to_null(&result1);
      s21_copy1(&big_value1, value_1);
      s21_copy1(&big_value2, value_2);
      s21_to_scale(value_1, result_scale + 29, &big_value1);
      s21_to_scale(value_2, result_scale + 29, &big_value2);
      result_scale = -1;
      while (s21_compare_greater(&big_value1, &big_value2)) {
        s21_pow_multiply(&big_value2, 1);
        result_scale -= 1;
      }
      while (
          (s21_or_signbits_big(&big_value1) || s21_or_bits_big(&big_value1)) &&
          (s21_or_signbits_big(&big_value2) || s21_or_bits_big(&big_value2))) {
        s21_multiply_to_10(&result1);

        while (s21_compare_greater(&big_value1, &big_value2) ||
               s21_compare_equal(&big_value1, &big_value2)) {
          s21_data_sub(&big_value1, &big_value2, &big_value1);
          result1.bits[0] += 1;
        }
        s21_dividing_by_10(&big_value2, &big_value2);
        result_scale++;
      }
      int mod_num = 0;
      while ((s21_or_bits_big(&result1)) || result_scale > MAX_SCALE) {
        mod_num = s21_moding_by_10(&result1);
        s21_dividing_by_10(&result1, &result1);
        result_scale -= 1;
      }
      if (mod_num >= 5) {
        s21_data_add(&result1, &one_num, &result1);
      }
      if (!(s21_or_bits_big(&result1))) {
        result_return(&result1, result, result_scale, sign);
      } else {
        code_status = 1 + sign;
      }
    }
  }
  return code_status;
}