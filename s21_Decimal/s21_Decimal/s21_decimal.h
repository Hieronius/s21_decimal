#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define S21_MAX_UINT 4294967295

// Decimal структура
typedef struct {
    unsigned int bits[4];
    // bits[3] (bits[2]  bits[1]  bits[0]) - mantissa
} s21_decimal;

// Вспомогательный элемент для convertors
typedef union {
  int ui;
  float fl;
} fbits;

// MARK: Арифметические операторы 
// Сложение +
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Вычитание -
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Умножение *
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Деление /
// Вспомогательная функция
int s21_div1(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
             s21_decimal *tmp);
// Основная функция
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// MARK: - Операторы сравнения
// Меньше <
int s21_is_less(s21_decimal, s21_decimal);
// Меньше или равно <=
int s21_is_less_or_equal(s21_decimal, s21_decimal);
// Больше >
int s21_is_greater(s21_decimal, s21_decimal);
// Больше или равно >=
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
// Равно ==
int s21_is_equal(s21_decimal, s21_decimal);
// Не равно !=
int s21_is_not_equal(s21_decimal, s21_decimal);


// MARK: - Преобразователи
// Из int
int s21_from_int_to_decimal(int src, s21_decimal *dst);
// Из float
int s21_from_float_to_decimal(float src, s21_decimal *dst);
// В int
int s21_from_decimal_to_int(s21_decimal src, int *dst);
// В float
int s21_from_decimal_to_float(s21_decimal src, float *dst);
 
// MARK: - Другие функции
// Округляет указанное Decimal число до ближайшего целого числа в сторону отрицательной бесконечности.
int s21_floor(s21_decimal value, s21_decimal *result);
// Округляет Decimal до ближайшего целого числа.
int s21_round(s21_decimal value, s21_decimal *result);
// Возвращает целые цифры указанного Decimal числа; любые дробные цифры отбрасываются, включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result);
// Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result);

// MARK: - Дополнительные функции
int s21_getBit(s21_decimal value, int bit);
int s21_getBitLast(s21_decimal value);
s21_decimal *s21_setBit(s21_decimal *value, int pos, int bit);
int s21_addBit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Копируем содержимое из source в destination
s21_decimal* s21_copy(s21_decimal* destination, s21_decimal source);
// Обнулить содержимое
s21_decimal* s21_reset(s21_decimal* value);
// Получить знак
int s21_getSign(s21_decimal value);
// Установить знак
s21_decimal *s21_setSign(s21_decimal *value, int bit);

// Получить масштаб
int s21_getScale(s21_decimal value);
// Установить масштаб
s21_decimal *s21_setScale(s21_decimal *value, int scale);
// Уменьшить масштаб
s21_decimal *s21_decreaseScale(s21_decimal *value, int shift);
// Увеличить масштаб
s21_decimal *s21_increaseScale(s21_decimal *value, int shift);
// Направить масштаб
void s21_alignmentScale(s21_decimal *value_1, s21_decimal *value_2);

// Перевод значения
s21_decimal *s21_convert(s21_decimal *value);
// Является ли нилом
int s21_isNull(s21_decimal value);
int s21_getFloatExp(float *value);
// Сдвиг влева
s21_decimal *s21_leftShift(s21_decimal *value, int shift);
