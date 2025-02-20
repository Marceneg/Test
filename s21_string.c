#include "s21_string.h"

size_t s21_strlen(const char *str) {
    size_t size = 0;
    for (; *(str + size); size++);
    return size;
}
