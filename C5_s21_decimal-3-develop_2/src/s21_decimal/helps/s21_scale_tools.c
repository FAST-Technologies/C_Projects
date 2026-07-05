#include "../comparison/s21_difference_operators.h"
#include "../s21_decimal_types.h"
#include "s21_helps.h"

int s21_mantiss_normalize(uint32_t *newscale, int value) {
  uint64_t temporary = 0ULL;
  for (int i = 0; i < S21_STRUCT_BITS; i++) {
    temporary += (uint64_t)(newscale[i]) * (uint64_t)value;
    newscale[i] = (uint32_t)(temporary & MAXBIT);
    temporary = (temporary >> S21_MAX_BLOCK_BITS);
  }
  return temporary ? 1 : 0;
}

int s21_get_equal_scale(s21_decimal *value_1, s21_decimal *value_2) {
  s21_differ_status status = S21_EQUAL_STATUS;
  int scale1 = s21_get_scale_coeff(*value_1);
  int scale2 = s21_get_scale_coeff(*value_2);
  int result_scale;
  if (s21_max_flag(scale1, scale2)) {
    result_scale = scale1;
  } else {
    result_scale = scale2;
  }
  int newscale_1 = 0, newscale_2 = 0;
  for (int i = scale1; i < result_scale && !newscale_1; i++) {
    newscale_1 = s21_mantiss_normalize(value_1->bits, 10);
  }
  for (int i = scale2; i < result_scale && !newscale_2; i++) {
    newscale_2 = s21_mantiss_normalize(value_2->bits, 10);
  }

  if (s21_max_flag(newscale_1, newscale_2)) {
    status = S21_GREATER_STATUS;
  } else if (s21_max_flag(newscale_2, newscale_1)) {
    status = S21_LESS_STATUS;
  }

  return status;
}

int s21_alignmentScale1(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal temp1, temp2;
  s21_decimal_to_null(&temp1);
  s21_decimal_to_null(&temp2);
  s21_copy(&temp1, value_1);
  s21_copy(&temp2, value_2);
  s21_differ_status flag = s21_get_equal_scale(&temp1, &temp2);

  if (flag == S21_EQUAL_STATUS) flag = s21_comp(temp1, temp2);

  return flag;
}

int s21_comp(s21_decimal num1, s21_decimal num2) {
  s21_differ_status result = S21_EQUAL_STATUS;
  for (int i = S21_START_INFO - 1; i >= 0 && result == S21_EQUAL_STATUS; i--) {
    if (s21_get_bit(num1, i) == s21_get_bit(num2, i)) {
      continue;
    } else if (s21_max_flag(s21_get_bit(num1, i), s21_get_bit(num2, i))) {
      result = S21_GREATER_STATUS;
    } else if (s21_max_flag(s21_get_bit(num2, i), s21_get_bit(num1, i))) {
      result = S21_LESS_STATUS;
    }
  }
  return result;
}