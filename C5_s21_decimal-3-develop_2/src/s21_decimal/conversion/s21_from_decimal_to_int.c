#include "../comparison/s21_difference_operators.h"
#include "../functions/s21_math_functions.h"
#include "../helps/s21_helps.h"
#include "s21_conversation.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_conversion_s conversed_code = S21_CONVERSION_OK_STATUS;
  *dst = 0;
  s21_decimal transform;
  s21_decimal_to_null(&transform);
  int data = 0;
  int sign = s21_decimal_get_sign(src);
  s21_truncate(src, &transform);
  if (s21_is_greater(transform, s21_get_max_int()) ==
      S21_COMPARISON_TRUE_STATUS) {
    conversed_code = S21_CONVERSATION_ERROR_STATUS;
  } else if (s21_is_less(transform, s21_get_min_int()) ==
             S21_COMPARISON_TRUE_STATUS) {
    conversed_code = S21_CONVERSATION_ERROR_STATUS;

  } else {
    data = transform.bits[0];

    if (sign == S21_NEGATIVE && *dst != S21_MIN_INT) {
      data = (-1) * data;
    } else if (*dst == S21_MIN_INT) {
      conversed_code = S21_CONVERSATION_ERROR_STATUS;
    }
  }

  *dst = data;
  return conversed_code;
}