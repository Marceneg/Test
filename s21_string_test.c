#include "s21_string.h"

#include <stdio.h>

void s21_strlen_test();

int main() {
    s21_strlen_test();
    return 0;
}

void s21_strlen_test() {
    const char *str1 = "primer vvoda";
    const char *str2 = "marko_polo";
    const char *str3 = "123";
    if (s21_strlen(str1) == 13) {
        printf("%s %ld SUCCESS\n", str1, s21_strlen(str1));
    } else {
        printf("%s %ld FAIL\n", str1, s21_strlen(str1));
    }
    if (s21_strlen(str2) == 11) {
        printf("%s %ld SUCCESS\n", str2, s21_strlen(str2));
    } else {
        printf("%s %ld FAIL\n", str2, s21_strlen(str2));
    }
    if (s21_strlen(str3) == 3) {
        printf("%s %ld SUCCESS\n", str3, s21_strlen(str3));
    } else {
        printf("%s %ld FAIL\n", str3, s21_strlen(str3));
    }
}