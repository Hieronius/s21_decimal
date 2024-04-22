#include "s21_decimal.h"

// Логический сдвиг влево
int s21_getBit(s21_decimal value, int bit) {
  return !!(value.bits[bit / 32] & (1u << (bit % 32)));
}

int s21_getBitLast(s21_decimal value) {
  int bitLast = 95;
  for (; (bitLast >= 0) && (!s21_getBit(value, bitLast));) bitLast -= 1;
  return bitLast;
}

// Установка бита
s21_decimal *s21_setBit(s21_decimal *value, int pos, int bit) {
  if (pos / 32 < 4 && bit)
    value->bits[pos / 32] |= (1u << (pos % 32));
  else if (pos / 32 < 4 && !bit)
    value->bits[pos / 32] &= ~(1u << (pos % 32));
  return value;
}

// Добавить бит
int s21_addBit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int fres = 0, exp = 0;
  for (int i = 0; i < 96; i += 1) {
    int bitValue_1 = s21_getBit(value_1, i), bitValue_2 = s21_getBit(value_2, i);
    if (!bitValue_1 && !bitValue_2)
      exp ? s21_setBit(result, i, (exp = 0) + 1) : s21_setBit(result, i, 0);
    else if (bitValue_1 != bitValue_2)
      exp ? s21_setBit(result, i, (exp = 1) - 1) : s21_setBit(result, i, 1);
    else
      exp ? s21_setBit(result, i, (exp = 1)) : s21_setBit(result, i, (exp = 1) - 1);
    if (i == 95 && exp == 1 && !s21_getBit(value_1, 97) && !s21_getBit(value_2, 97))
      fres = 1;
  }
  return fres;
}

// Копировать из source в destination
s21_decimal* s21_copy(s21_decimal* destination, s21_decimal source) {
  for (int i = 0; i < 4; i += 1) destination->bits[i] = source.bits[i];
  return destination;
}

// Обнулить байты
s21_decimal* s21_reset(s21_decimal* value) {
  for (int i = 0; i < 4; i += 1) value->bits[i] = 0;
  return value;
}

// Получить знак
int s21_getSign(s21_decimal value) {
  int result = !!(value.bits[3] & (1u << 31));
  return result;
}

// Установить знак
s21_decimal *s21_setSign(s21_decimal *value, int bit) {
  value->bits[3] =
      (bit) ? (value->bits[3] | (1u << 31)) : (value->bits[3] & ~(1u << 31));
  return value;
}

// Получить масштаб
int s21_getScale(s21_decimal value) {
  int result = (char)(value.bits[3] >> 16);
  return result;
}

// Установить масштаб
s21_decimal *s21_setScale(s21_decimal *value, int scale) {
  if (scale >= 0 && scale <= 28) {
    int sign = s21_getSign(*value);
    value->bits[3] &= ~(0xFF << 16);
    value->bits[3] |= scale << 16;
    sign ? s21_setSign(value, 1) : value;
  }
  return value;
}

// Увеличить масштаб
s21_decimal *s21_increaseScale(s21_decimal *value, int shift) {
  if (s21_getScale(*value) + shift < 29) {
    s21_setScale(value, s21_getScale(*value) + shift);
    s21_decimal auxValue_1 = *value, auxValue_2 = *value;
    if (s21_addBit(*s21_leftShift(&auxValue_1, 1), *s21_leftShift(&auxValue_2, 3), value))
      s21_setBit(value, 96, 1);
  }
  return value;
}

// Уменьшить масштаб
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

// Выровнять масштаб
void s21_alignmentScale(s21_decimal *value_1, s21_decimal *value_2) {
  if (s21_getScale(*value_1) != s21_getScale(*value_2)) {
    if (s21_getScale(*value_1) < s21_getScale(*value_2)) {
      s21_alignmentScale(value_2, value_1);
    } else {
      int scaleLow = s21_getScale(*value_2), scaleHigh = s21_getScale(*value_1);
      for (; (scaleHigh - scaleLow) && !s21_getBit(*value_2, 96); scaleLow += 1)
        s21_increaseScale(value_2, 1);
      for (; scaleHigh - scaleLow; scaleHigh -= 1) {
        s21_decreaseScale(value_1, scaleHigh - scaleLow);
        s21_setScale(value_1, scaleLow);
      }
    }
  }
}

// Конвертировать число
s21_decimal *s21_convert(s21_decimal *value) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal add = {{1, 0, 0, 0}};
  for (int x = 0; x < 3; x += 1) value->bits[x] = ~value->bits[x];
  s21_addBit(*value, add, &result);
  for (int x = 0; x < 3; x += 1) value->bits[x] = result.bits[x];
  s21_setBit(value, 97, 1);
  return value;
}

// Проверка числа на соответствие Null
int s21_isNull(s21_decimal value) {
  return !value.bits[0] && !value.bits[1] && !value.bits[2];
}


int s21_getFloatExp(float *value) {
  return ((*((int *)value) & ~(1u << 31)) >> 23) - 127;
}

// Логические сдвиг влева
s21_decimal *s21_leftShift(s21_decimal *value, int shift) {
  if (!(s21_getBitLast(*value) + shift > 95)) {
    for (int y = 0; y < shift; y += 1) {
      int bitTransfer_1 = s21_getBit(*value, 31);
      int bitTransfer_2 = s21_getBit(*value, 63);
      for (int x = 0; x < 3; x += 1) value->bits[x] <<= 1;
      if (bitTransfer_1) s21_setBit(value, 32, 1);
      if (bitTransfer_2) s21_setBit(value, 64, 1);
    }
  }
  return value;
}
