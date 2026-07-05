#include "../helps/s21_helps.h"
#include "../s21_decimal_types.h"
#include "s21_conversation.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_conversion_s conversed_code = S21_CONVERSION_OK_STATUS;
  if (!dst) {
    conversed_code = S21_CONVERSATION_ERROR_STATUS;
  } else {
    s21_decimal_to_null(dst);
    int decim_sign;
    if (src < 0) {
      decim_sign = S21_NEGATIVE;
      src = (-1) * src;
    } else {
      decim_sign = S21_POSITIVE;
    }
    dst->bits[0] = src;
    s21_decimal_set_sign(dst, decim_sign);
    conversed_code = S21_CONVERSION_OK_STATUS;
  }
  return conversed_code;
}