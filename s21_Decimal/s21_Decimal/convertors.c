#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float* dst) {
  int res = 1;
  if (dst) {
    double tmp = 0;
    int exp = 0;
    for (int i = 0; i < 96; i++) {
      if ((src.bits[i / 32] & (1 << i % 32)) != 0) tmp += pow(2, i);
    }
    if ((exp = s21_getScale(src)) > 0) {
      for (int i = exp; i > 0; i--, tmp /= 10.0)
        ;
    }
    *dst = (float)tmp;
    if (s21_getSign(src)) {
      *dst *= -1;
    }
    res = 0;
  }
  return res;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 1;
  if (src.bits[1] == 0 && src.bits[2] == 0) {
    *dst = src.bits[0];
    if (s21_getSign(src)) {
      *dst *= -1;
    }
    *dst /= (int)pow(10, s21_getScale(src));
    res = 0;
  }
  return res;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int res = 1, exp = s21_getFloatExp(&src);
  if (dst && src != 0 && !isinf(src)) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    int sign = 0;
    if (src < 0) {
      src *= -1;
      sign = 1;
    }
    double tmp = (double)src;
    int scale = 0;
    while (scale < 28 && (int)tmp / (int)pow(2, 21) == 0) {
      tmp *= 10;
      scale++;
    }
    if (scale <= 28 && (exp > -94 && exp < 96)) {
      fbits mant;
      tmp = (float)tmp;
      for (; fmod(tmp, 10) == 0 && scale > 0; scale--, tmp /= 10) {
      }
      mant.fl = tmp;
      exp = s21_getFloatExp(&mant.fl);
      s21_setBit(dst, exp, 1);
      for (int i = exp - 1, j = 22; j >= 0; i--, j--) {
        if ((mant.ui & (1 << j)) != 0) {
          s21_setBit(dst, i, 1);
        }
      }
      s21_setSign(dst, sign);
      s21_setScale(dst, scale);
      res = 0;
    }
  }
  return res;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = 1;
  if (dst) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    if (src < 0) {
      s21_setSign(dst, 1);
      src *= -1;
    }
    dst->bits[0] = src;
    res = 0;
  }
  return res;
}
