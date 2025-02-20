#include "data_stat.h"

#include <math.h>
double max(double *data, int n) {
    double max_value = data[0];
    for (int i = 1; i < n; i++) {
        if (data[i] > max_value) {  // сравниваю значения
            max_value = data[i];    // присваиваю новое значение
        }
    }
    return max_value;
}
double min(double *data, int n) {
    double min_value = data[0];
    for (int j = 1; j < n; j++) {
        if (data[j] < min_value) {
            min_value = data[j];
        }
    }
    return min_value;
}
double mean(double *data, int n) {
    double result;
    int size = n;
    double sum = 0;
    for (int i = 0; i < n; i++) {
        if (data[i] != 0) {
            sum += data[i];
        }
    }
    result = sum / size;
    return result;
}
double variance(double *data, int n) {
    double sr = mean(data, n);
    int size = n;
    double res_var;
    double sumsr;
    for (int i = 0; i < n; i++) {
        sumsr += pow((data[i] - sr), 2);
        res_var = sumsr / size;
    }
    return res_var;
}
void sort(double *data, int n) {
    for (double *p = data; p - data < n - 1; p++) {
        for (double *p2 = p + 1; p2 - data < n; p2++) {
            if (*p > *p2) {
                int temp = *p;
                *p = *p2;
                *p2 = temp;
            }
        }
    }
}