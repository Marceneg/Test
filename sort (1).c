#include <stdio.h>
#include <stdlib.h>

int input(int *a, int size);
void sort(int *a, int size);
void output(int *a, int size);

int main() {
    int size;
    scanf("%d", &size);
    int *data = calloc(size, sizeof(int));

    if (input(data, size) == 1) {
        sort(data, size);
        output(data, size);
    } else {
        printf("n/a");
    }
    free(data);
    return 0;
}

int input(int *a, int size) {
    int result = 1;
    int counter = 0;
    char ch;

    for (int *p = a; p - a < size - 1; p++) {
        if (scanf("%d%c", p, &ch) != 2 || ch == '\n') {  // проверка на ошибку
            result = 0;
            break;
        }
        counter += 1;
    }
    if (ch != '\n') {
        if (scanf("%d%c", &a[size - 1], &ch) != 2 || ch != '\n') {  // проверка на ввод лишнего
            result = 0;
        } else {
            counter += 1;
        }
    }
    return result;
}
void output(int *a, int size) {
    for (int *p = a; p - a < size - 1; p++) {
        printf("%d ", *p);
    }
    printf("%d", a[size - 1]);  // чтобы вывести без пробела
}

void sort(int *a, int size) {
    for (int *p = a; p - a < size; p++) {
        for (int *p2 = p + 1; p2 - a < size; p2++) {
            if (*p > *p2) {
                int temp = *p;
                *p = *p2;
                *p2 = temp;
            }
        }
    }
}