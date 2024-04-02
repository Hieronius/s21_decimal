#include "s21_decimal.h"

int main() {
    return 0;
}

// MARK: - Другие функции
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
    }
    return 0;
}

// Возвращает целые цифры указанного Decimal числа; любые дробные цифры отбрасываются, включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result) {
    s21_copy(s21_reset(result),
               s21_getScale(value) ? *s21_decreaseScale(&value, s21_getScale(value)) : value);
      return 0;
}

// Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result) {
    s21_copy(s21_reset(result),
             s21_getSign(value) ? *s21_setSign(&value, 0) : *s21_setSign(&value, 1));
    return 0;
}
