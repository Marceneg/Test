#include <stdio.h>

int input(int *a, int size);
void sort(int *a, int size);
void output(int *a, int size);

int main() {
    int data[10], size = 10;

    if (input(data, size)) {
        sort(data, size);
        output(data, size);
    } else {
        printf("n/a");
    }

    return 0;
}

int input(int *a, int size) {
    int result = 1;
    char ch;
    int counter = 0;

    for (int *p = a; p - a < size - 1; p++) {
        if (scanf("%d%c", p, &ch) != 2 || ch == '\n') {
            result = 0;
            break;
        }
        counter += 1;
    }
    if (ch != '\n') {
        if (scanf("%d%c", &a[9], &ch) == 2 && ch == '\n') {
            counter += 1;
        }
    }
    if (counter == size) {
        return result;
    }
    return 0;
}

void output(int *a, int size) {
    for (int *p = a; p - a < size; p++) {
        printf("%d ", *p);
    }
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
