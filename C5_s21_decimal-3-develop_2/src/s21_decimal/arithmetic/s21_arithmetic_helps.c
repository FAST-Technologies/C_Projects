#include "../comparison/s21_difference_operators.h"
#include "../helps/s21_helps.h"
#include "./../s21_decimal_types.h"
#include "s21_arithmetic_operators.h"

void s21_data_add(s21_big_decimal *temp_1, s21_big_decimal *temp_2,
                  s21_big_decimal *sub_res) {
  unsigned long long temp = 0ull;
  for (int i = 0; i < S21_big_decimal_size; i++) {
    temp += (unsigned long long)temp_1->bits[i] +
            (unsigned long long)temp_2->bits[i];
    sub_res->bits[i] = (unsigned)temp;
    temp >>= S21_MAX_BLOCK_BITS;
  }
}

int s21_moding_by_10(s21_big_decimal *value) {
  unsigned long long temp = 0ull;
  unsigned mod = 0;
  for (int i = S21_big_decimal_size - 1; i >= 0; i--) {
    mod = (temp + value->bits[i]) % 10;
    temp = mod;
    temp = temp << S21_MAX_BLOCK_BITS;
  }
  return mod;
}

void s21_dividing_by_10(s21_big_decimal *value, s21_big_decimal *result) {
  unsigned long long temp = 0ull;
  for (int i = S21_big_decimal_size - 1; i >= 0; i--) {
    unsigned mod = (temp + value->bits[i]) % 10;
    unsigned long long div_buf = ((temp + value->bits[i]) / 10);
    result->bits[i] = (unsigned)div_buf;
    temp = mod;
    temp = temp << S21_MAX_BLOCK_BITS;
  }
}

void s21_decimal_negate(s21_big_decimal *value) {
  for (int i = 0; i < S21_big_decimal_size; i++)
    value->bits[i] = ~value->bits[i];
  unsigned long long temp = 1ull;
  for (int i = 0; i < S21_big_decimal_size; i++) {
    temp = temp + (unsigned long long)value->bits[i];
    value->bits[i] = (unsigned)temp;
    temp >>= S21_MAX_BLOCK_BITS;
  }
}

int s21_multiply_by_number(s21_big_decimal *value, int size_1, int integer,
                           s21_big_decimal *result, int size_2) {
  unsigned temp_arr[size_2];
  for (int i = 0; i < size_2; i++) {
    temp_arr[i] = 0;
  }
  for (int i = 0; i < size_1; i++) {
    temp_arr[i] = value->bits[i];
  }
  int status = 0;
  unsigned long long temp = 0ull;
  for (int i = 0; i < size_2; i++) {
    temp += (unsigned long long)(temp_arr[i]) * (unsigned long long)integer;
    temp_arr[i] = (unsigned)temp;
    temp = (temp >> S21_MAX_BLOCK_BITS);
  }
  for (int i = 0; i < size_2; i++) {
    result->bits[i] = temp_arr[i];
  }
  return status;
}

int s21_multiply_to_10(s21_big_decimal *value) {
  return s21_multiply_by_number(value, S21_big_decimal_size, 10, value,
                                S21_big_decimal_size);
}

void s21_to_scale(s21_decimal value, int scale, s21_big_decimal *result) {
  int newscale = s21_get_scale_coeff(value);
  s21_big_decimal_to_null(result);
  s21_copy1(result, value);
  for (int i = newscale; i < scale; i++) {
    s21_multiply_to_10(result);
  }
}

int s21_add_number(s21_decimal value, int num, s21_decimal *result) {
  int status = 0;
  unsigned long long temp = 0ull + num;
  for (int i = 0; i < S21_STRUCT_BITS; i++) {
    temp += value.bits[i];
    value.bits[i] = (unsigned)temp;
    temp >>= S21_MAX_BLOCK_BITS;
  }
  if (!temp) {
    s21_copy(result, value);
  } else {
    status = 1;
  }
  return status;
}

int s21_or_bits_big(s21_big_decimal *decl1) {
  return decl1->bits[3] || decl1->bits[4] || decl1->bits[5] || decl1->bits[6] ||
         decl1->bits[7];
}

int s21_or_signbits_big(s21_big_decimal *decl1) {
  return decl1->bits[0] || decl1->bits[1] || decl1->bits[2];
}

int s21_compare_equal(s21_big_decimal *data1, s21_big_decimal *data2) {
  int flag = 1;
  for (int i = S21_big_decimal_size - 1; i >= 0; i--) {
    flag = flag && (data1->bits[i] == data2->bits[i]);
  }
  return flag;
}

int s21_compare_greater(s21_big_decimal *data1, s21_big_decimal *data2) {
  int result = 0;
  int flag = 0;
  for (int i = S21_big_decimal_size - 1; i >= 0; i--) {
    if (data1->bits[i] < data2->bits[i] && !flag) {
      flag = 1;
      result = 0;
    } else if (data1->bits[i] > data2->bits[i] && !flag) {
      flag = 1;
      result = 1;
    }
  }
  return result;
}

void s21_division_to_2(s21_big_decimal *value) {
  unsigned long long temp = 0ull;
  for (int i = S21_big_decimal_size - 1; i >= 0; i--) {
    unsigned mod = (temp + value->bits[i]) % 2;
    unsigned long long div_buf = ((temp + value->bits[i]) / 2);
    value->bits[i] = (unsigned)div_buf;
    temp = mod;
    temp = temp << S21_MAX_BLOCK_BITS;
  }
}

void s21_data_sub(s21_big_decimal *temp_1, s21_big_decimal *temp_2,
                  s21_big_decimal *sub_res) {
  unsigned long long temp = 0ull;
  s21_big_decimal inv;
  for (int i = 0; i < S21_big_decimal_size; i++) {
    inv.bits[i] = temp_2->bits[i];
  }
  s21_decimal_negate(&inv);
  for (int i = 0; i < S21_big_decimal_size; i++) {
    temp +=
        (unsigned long long)temp_1->bits[i] + (unsigned long long)inv.bits[i];
    sub_res->bits[i] = (unsigned)temp;
    temp >>= S21_MAX_BLOCK_BITS;
  }
}

void s21_pow_multiply(s21_big_decimal *value, int pow) {
  int xpo = pow;
  for (int i = xpo; i >= 8; i -= 8) {
    s21_multiply_by_number(value, S21_big_decimal_size, 100000000, value,
                           S21_big_decimal_size);
  }
  for (int i = xpo; i >= 4; i -= 4) {
    s21_multiply_by_number(value, S21_big_decimal_size, 10000, value,
                           S21_big_decimal_size);
  }
  for (int i = xpo; i >= 2; i -= 2) {
    s21_multiply_by_number(value, S21_big_decimal_size, 100, value,
                           S21_big_decimal_size);
  }
  for (int i = xpo; i >= 1; i -= 1) {
    s21_multiply_by_number(value, S21_big_decimal_size, 10, value,
                           S21_big_decimal_size);
  }
}

int s21_divide_by_number(s21_decimal value, int number, s21_decimal *result) {
  unsigned long long temp = 0ull;
  for (int i = (S21_STRUCT_BITS - 1); i >= 0; i--) {
    unsigned mod = (temp + value.bits[i]) % number;
    unsigned long long div_buf = (temp + value.bits[i]) / number;
    result->bits[i] = (unsigned)div_buf;
    temp = mod;
    temp = temp << S21_MAX_BLOCK_BITS;
  }
  return 0;
}

int s21_modulo_by_integer(s21_decimal value, int integer) {
  unsigned long long temp = 0ull;
  unsigned long long mod = 0;
  for (int i = (S21_STRUCT_BITS - 1); i >= 0; i--) {
    mod = (temp + value.bits[i]) % integer;
    temp = mod << S21_MAX_BLOCK_BITS;
  }
  return mod;
}

void result_return(s21_big_decimal *result1, s21_decimal *result,
                   int result_scale, int result_sign) {
  s21_classic_converse(result1, result);
  result->bits[3] = (unsigned int)result_sign << MAX_BLOCK_SHIFT;
  s21_set_scale_coeff1(result, result_scale);
}
