#include "data_io.h"

#include <stdio.h>
#include <stdlib.h>

void input(double *data, int n) {
    int counter = 0;
    char ch;

    for (int i = 0; i < n - 1; i++) {
        if (scanf("%lf%c", &data[i], &ch) != 2 || ch == '\n') {  // проверка на ошибку
            break;
        }
        counter += 1;
    }
    if (ch != '\n') {
        if (scanf("%lf%c", &data[n - 1], &ch) != 2 || ch != '\n') {  // проверка на ввод лишнего
        } else {
            counter += 1;
        }
    }
}
void output(double *data, int n) {
    for (int i = 0; i < n - 1; i++) {
        printf("%.2lf ", data[i]);
    }
    printf("%.2lf", data[n - 1]);  // чтобы вывести без пробела
}
