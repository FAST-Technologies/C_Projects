#include "../comparison/s21_difference_operators.h"
#include "../functions/s21_math_functions.h"
#include "../helps/s21_helps.h"
#include "../s21_decimal_types.h"
#include "s21_arithmetic_operators.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic code_status = S21_ARITHMETIC_OK_STATUS;
  if (!result) {
    code_status = S21_ERROR_STATUS;
  } else if (!s21_correct_decimal(value_1) || !s21_correct_decimal(value_2)) {
    code_status = S21_ERROR_STATUS;
    *result = s21_decimal_get_inf();
  } else {
    int result_sign, mod_num = 0;
    ;
    s21_big_decimal big_value1, big_value2, result1,
        one_num = {{1, 0, 0, 0, 0, 0, 0, 0}};
    s21_big_decimal_to_null(&big_value1);
    s21_big_decimal_to_null(&big_value2);
    s21_big_decimal_to_null(&result1);
    s21_copy1(&big_value1, value_1);
    int scale1 = s21_get_scale_coeff(value_1);
    int scale2 = s21_get_scale_coeff(value_2);
    int sign1 = s21_decimal_get_sign(value_1);
    int sign2 = s21_decimal_get_sign(value_2);
    int scale = scale1 >= scale2 ? scale1 : scale2;

    s21_to_scale(value_1, scale, &big_value1);
    s21_to_scale(value_2, scale, &big_value2);

    if (sign1 == sign2) {
      result_sign = sign1;
    } else {
      if (s21_compare_greater(&big_value1, &big_value2) ||
          s21_compare_equal(&big_value1, &big_value2)) {
        s21_decimal_negate(&big_value2);
        result_sign = sign1;
      } else {
        s21_decimal_negate(&big_value1);
        result_sign = sign2;
      }
    }
    s21_decimal_set_sign(result, result_sign);
    s21_data_add(&big_value1, &big_value2, &result1);
    while ((scale && (s21_or_bits_big(&result1))) || scale > MAX_SCALE) {
      mod_num = s21_moding_by_10(&result1);
      s21_dividing_by_10(&result1, &result1);
      scale -= 1;
    }
    if (mod_num >= 5) {
      s21_data_add(&result1, &one_num, &result1);
    }
    if (!s21_or_bits_big(&result1)) {
      result_return(&result1, result, scale, result_sign);
    } else {
      code_status = 1 + result_sign;
    }
  }
  return code_status;
}
