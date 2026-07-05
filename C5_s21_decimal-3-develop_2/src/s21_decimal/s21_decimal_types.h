#ifndef S21_DECIMAL_TYPES_H_
#define S21_DECIMAL_TYPES_H_
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define S21_decimal_size 4
#define S21_big_decimal_size 8

typedef struct s21_decimal {
  uint32_t bits[S21_decimal_size];
} s21_decimal;

typedef struct s21_big_decimal {
  uint32_t bits[S21_big_decimal_size];
} s21_big_decimal;

typedef union {
  uint32_t bits;
  float floatnum;
} float_bits;

#define S21_RESET_FLAG "\033[0m"
#define S21_RED_FLAG "\033[1;31m"
#define S21_YELLOW_FLAG "\033[1;33m"
#define S21_WHITE_FLAG "\033[1;37m"
#define S21_GREEN_FLAG "\033[1;32m"
#define S21_PURPLE_FLAG "\033[1;35m"
#define S21_CYAN_FLAG "\033[1;36m"

#define S21_START_LOW 0
#define S21_START_MID 32
#define S21_START_HIGHT 64
#define S21_START_INFO 96

#define S21_MAX_POWER 28

#define MIN_SCALE 0

#define MAX_SCALE 28

#define START_SCALE_BIT 16
#define END_SCALE_BIT 23

#define S21_FLOAT_ACCURACY 7

#define S21_STRUCT_BITS 3

#define S21_MAX_BITS 128

#define OLDER_BIT 0b10000000000000000000000000000000

#define OLDER_MANTISSA_BIT 0b10000000000000000000000

#define ALL_ONE 0b11111111111111111111111111111111

#define S21_MAX_BLOCK_BITS 32

#define MAX_BLOCK_SHIFT 31

#define S21_MAX_BLOCK_NUMBER 96

#define S21_MAX_DECIMAL powl(2.0, 96)
#define S21_MIN_DECIMAL -1 * S21_MAX_DECIMAL

#define S21_MMAX_DECIMAL 79228162514264337593543950335
#define S21_MMIN_DECIMAL -79228162514264337593543950335

#define S21_MIN_FLOAT -1.7976931348623e+308

#define S21_MAX_FLOAT 1.7976931348623e+308

#define S21_MIN_INT -2147483648

#define S21_MAX_INT 2147483647

#define S21_MIN_UINT 0

#define S21_MAX_UINT 4294967295

#define S21_MIN_LONG -9223372036854775808

#define S21_MAX_LONG 9223372036854775807

#define S21_MIN_ULONG 0

#define S21_MAX_ULONG 18446744073709551615

#define SOMESIGN 0x80000000

#define MAXBIT 0xFFFFFFFFULL

typedef enum Condition {
  S21_NULL,
  S21_NORMAL,
  S21_PLUS_INF,
  S21_MINUS_INF,
  S21_NAN,
  S21_DOP
} Condition;

typedef enum s21_decimal_sign {
  S21_POSITIVE = 0,
  S21_NEGATIVE = 1
} s21_decimal_sign;

#endif  // S21_DECIMAL_TYPES_H_