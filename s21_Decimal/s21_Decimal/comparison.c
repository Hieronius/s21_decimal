#include "s21_decimal.h"

// Проверяем числа на идентичность
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 1;
  if (s21_getSign(value_1) == s21_getSign(value_2)) {
    s21_alignmentScale(&value_1, &value_2);
    for (int i = 95; i >= 0; i--) {
      if (s21_getBit(value_1, i) != s21_getBit(value_2, i)) {
        res = 0;
        break;
      }
    }
  } else if (!(s21_isNull(value_1) && s21_isNull(value_2))) {
    res = 0;
  }
  return res;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  int sign_a = s21_getSign(value_1), sign_b = s21_getSign(value_2);
  if (!(s21_isNull(value_1) && s21_isNull(value_2))) {
    if (sign_a != sign_b) {
      if (sign_a == 0) {
        res = 1;
      } else {
        res = 0;
      }
    } else {
      s21_alignmentScale(&value_1, &value_2);
      for (int i = 95; i >= 0; i--) {
        int bit_a = s21_getBit(value_1, i), bit_b = s21_getBit(value_2, i);
        if (bit_a != bit_b) {
          if (bit_a != 0) {
            res = (sign_a == 0) ? 1 : 0;
            break;
          } else {
            res = (sign_a == 0) ? 0 : 1;
            break;
          }
        }
      }
    }
  }
  return res;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_2, value_1);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}
