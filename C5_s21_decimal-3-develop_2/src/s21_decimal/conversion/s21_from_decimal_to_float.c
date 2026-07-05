#include <math.h>

#include "../comparison/s21_difference_operators.h"
#include "../helps/s21_helps.h"
#include "../s21_decimal_types.h"
#include "s21_conversation.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  s21_conversion_s conversed_code = S21_CONVERSION_OK_STATUS;
  if (!s21_correct_decimal(src)) {
    conversed_code = S21_CONVERSATION_ERROR_STATUS;
    *dst = 0;
  } else if (!dst) {
    conversed_code = S21_CONVERSATION_ERROR_STATUS;
  } else if (s21_is_zero(src)) {
    int src_sign = s21_decimal_get_sign(src);
    if (src_sign == S21_POSITIVE) {
      *dst = 0.0;
    }
    conversed_code = S21_CONVERSION_OK_STATUS;
  } else {
    *dst = 0;
    double tcp = 0.0;
    int scale = s21_get_scale_coeff(src);
    int sign = s21_decimal_get_sign(src);
    for (int k = 0; k < S21_START_INFO; k++) {
      if (s21_get_bit(src, k) != S21_START_LOW) {
        tcp += pow(2.0, k);
      }
    }
    double paweer = pow(10, scale);
    tcp /= paweer;
    if (sign == S21_POSITIVE) {
    } else {
      tcp *= (-1) * 1.0;
    }
    *dst = (float)tcp;
  }
  return conversed_code;
}