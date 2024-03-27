#include "s21_decimal.h"

int main() {
    return 0;
}

// MARK: Другие функции
// Округляет указанное Decimal число до ближайшего целого числа в сторону отрицательной бесконечности.
int s21_floor(s21_decimal value, s21_decimal *result) {
      if (!s21_truncate(value, s21_reset(result)) && s21_getSign(value) &&
          !s21_is_equal(*result, value))
        s21_sub(*result, ((s21_decimal){{1, 0, 0, 0}}), result);
      return 0;
}
// Округляет Decimal до ближайшего целого числа.
int s21_round(s21_decimal value, s21_decimal *result) {
    if (!s21_truncate(value, result) && !s21_is_equal(value, *result)) {
        if (s21_getSign(value)) {
            s21_sub(value, ((s21_decimal){{5, 0, 0, 65536}}), &value);
        } else {
          s21_add(value, ((s21_decimal){{5, 0, 0, 65536}}), &value);
        s21_truncate(value, result);
      }
      return 0;
}


// Возвращает целые цифры указанного Decimal числа; любые дробные цифры отбрасываются, включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result) {
    s21_copy(s21_reset(result),
               s21_getScale(value) ? *s21_decreaseScale(&value, s21_getScale(value)) : value);
      return 0;
}


//Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result) {
    s21_copy(s21_reset(result),
             s21_getSign(value) ? *s21_setSign(&value, 0) : *s21_setSign(&value, 1));
    return 0;
}

s21_decimal* s21_copy(s21_decimal* destination, s21_decimal source) {
  for (int i = 0; i < 4; i += 1) destination->bits[i] = source.bits[i];
  return destination;
}

s21_decimal* s21_reset(s21_decimal* value) {
  for (int i = 0; i < 4; i += 1) value->bits[i] = 0;
  return value;
}

int s21_getSign(s21_decimal value) {
  int result = !!(value.bits[3] & (1u << 31));
  return result;
}

s21_decimal *s21_setSign(s21_decimal *value, int bit) {
  value->bits[3] =
      (bit) ? (value->bits[3] | (1u << 31)) : (value->bits[3] & ~(1u << 31));
  return value;
}

// decimal number = 563
// 1 000 000 000 - precision
// .00000000 - scale
int s21_getScale(s21_decimal value) {
  int result = (char)(value.bits[3] >> 16);
  return result;
}

s21_decimal *s21_decreaseScale(s21_decimal *value, int shift) {
  for (int y = 0; y < shift; y += 1) {
    unsigned long long overflow = value->bits[2];
    for (int x = 2; x >= 0; x -= 1) {
      value->bits[x] = overflow / 10;
      overflow =
          (overflow % 10) * (S21_MAX_UINT + 1) + value->bits[x ? x - 1 : x];
    }
  }
  s21_setScale(value, (s21_getScale(*value) - shift));
  return value;
}

s21_decimal *s21_setScale(s21_decimal *value, int scale) {
  if (scale >= 0 && scale <= 28) {
    int sign = s21_getSign(*value);
    value->bits[3] &= ~(0xFF << 16);
    value->bits[3] |= scale << 16;
    sign ? s21_setSign(value, 1) : value;
  }
  return value;
}
