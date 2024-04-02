#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define S21_MINUS 0x80000000 // 10000000 00000000 00000000 00000000
#define S21_SCALE 0x00ff0000 // 00000000 11111111 00000000 00000111
#define S21_MAX_NUMBER 79228162514264337593543950335
#define S21_MIN_NUMBER -79228162514264337593543950335
#define S21_DEFAULT_NUMBER 0
#define S21_MAX_UINT 4294967295

// Decimal структура
typedef struct {
    unsigned int bits[4];
    // bits[3] (bits[2]  bits[1]  bits[0]) - mantissa
} s21_decimal;

// MARK: Арифметические операторы 
// Сложение +
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Вычитание -
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Умножение *
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Деление /
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
int getBit(s21_decimal value, int bit);
int getBitLast(s21_decimal value);
// Копируем содержимое из source в destination
s21_decimal* s21_copy(s21_decimal* destination, s21_decimal source);
s21_decimal* s21_reset(s21_decimal* value);
s21_decimal *setBit(s21_decimal *value, int pos, int bit);
int addBit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_getSign(s21_decimal value);
s21_decimal *s21_setSign(s21_decimal *value, int bit);
int s21_getScale(s21_decimal value);
s21_decimal *s21_setScale(s21_decimal *value, int scale);
s21_decimal *s21_decreaseScale(s21_decimal *value, int shift);
s21_decimal *s21_increaseScale(s21_decimal *value, int shift);
void s21_alignmentScale(s21_decimal *value_1, s21_decimal *value_2);
s21_decimal *s21_convert(s21_decimal *value);
int s21_isNull(s21_decimal value);
int s21_getFloatExp(float *value);
s21_decimal *s21_leftShift(s21_decimal *value, int shift);

