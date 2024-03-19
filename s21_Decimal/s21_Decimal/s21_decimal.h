#include <stdio.h>
#define MINUS 0x80000000 // 10000000 00000000 00000000 00000000
#define SC 0x00ff0000 // 00000000 11111111 00000000 00000000 SCALE

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

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;

}
