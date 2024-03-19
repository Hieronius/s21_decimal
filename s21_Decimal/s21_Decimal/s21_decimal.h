#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define MINUS 0x80000000 // 10000000 00000000 00000000 00000000
#define SCALE 0x00ff0000 // 00000000 11111111 00000000 00000000
#define MAX_NUMBER 79228162514264337593543950335
#define MIN_NUMBER -79228162514264337593543950335
#define DEFAULT_NUMBER 0

// Decimal структура
typedef struct {
  unsigned int bits[4];
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

// MARK: Операторы сравнения
// Меньше <
int s21_is_less(s21_decimal, s21_decimal);
//Меньше или равно <=
int s21_is_less_or_equal(s21_decimal, s21_decimal);
// Больше >
int s21_is_greater(s21_decimal, s21_decimal);
// Больше или равно >=
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
// Равно ==
int s21_is_equal(s21_decimal, s21_decimal);
// Не равно !=
int s21_is_not_equal(s21_decimal, s21_decimal);


// MARK: Преобразовали
// Из int
int s21_from_int_to_decimal(int src, s21_decimal *dst);
// Из float
int s21_from_float_to_decimal(float src, s21_decimal *dst);
// В int
int s21_from_decimal_to_int(s21_decimal src, int *dst);
// В float
int s21_from_decimal_to_float(s21_decimal src, float *dst);
 
// MARK: Другие функции
// Округляет указанное Decimal число до ближайшего целого числа в сторону отрицательной бесконечности.
int s21_floor(s21_decimal value, s21_decimal *result);
// Округляет Decimal до ближайшего целого числа.
int s21_round(s21_decimal value, s21_decimal *result);
// Возвращает целые цифры указанного Decimal числа; любые дробные цифры отбрасываются, включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result);
//Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result);

// MARK: Дополнительные функции
// Копируем содержимое из source в destination
s21_decimal* s21_copy(s21_decimal* destination, s21_decimal source);
s21_decimal* s21_reset(s21_decimal* value);
int s21_getSign(s21_decimal value);
s21_decimal *s21_setSign(s21_decimal *value, int bit);

/*
 
 Максимальные и минимальные значения INT32 и s21_decimal:

     INT_MIN = -2 147 483 648
     INT_MAX = 2 147 483 647

     UNSIGNED INT_MAX = 4 294 967 295


     DEC_MIN = - 79 228 162 514 264 337 593 543 950 335
     DEC_MAX = 79 228 162 514 264 337 593 543 950 335

     s21_decimal max 2^96
 
 ----------------------------------------------------------
 
 Базовые операции с битами:
 
 // Проверка бита
 bool isSetBit(int number, int index) {
    return (number & (1 << index) != 0;
 }
 
 // Установка бита в 1
 int setBit(int number, int index) {
    return number | (1 << index);
 }
 
 // Инверсия бита
 int inverseBit(int number, int index) {
    return number ^ (1 << index);
 }
 
 // Установка бита в 0
 int resetBit(int number, int index) {
    return number &~ (1 << index);
 }
 
 --------------------------------------------------------------
 
 if a1i + a2i + d == 0 => 0
 if a1i + a2i + d == 1 => 1
 if a1i + a2i + d == 2 => 0 AND 1 переносим в i + 1 = d
 if a1i + a2i + d == 3 => 1 AND 1 переносим в i + 1 = d
 
 I should take an official definition of Xor/Xon and other bitwise operators here
 
 first three elements of decimal data structure should store "mantissa" and the last of for instructions
 */
