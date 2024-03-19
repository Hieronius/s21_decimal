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
int s21_round(s21_decimal value, s21_decimal *result);


// Возвращает целые цифры указанного Decimal числа; любые дробные цифры отбрасываются, включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result);


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
