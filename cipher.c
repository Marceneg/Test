#include <stdio.h>
#include <stdlib.h>

void read_file(char *file);
void write_file(char *file);
int main() {
    int n;
    char *file = malloc(25);
    int flag = 0;
    scanf("%d", &n);
    while (n != -1) {
        if (n == -1) {
            break;
        } else if (n == 1) {
            scanf("%s", file);
            read_file(file);
            flag = 1;
        } else if (n == 2) {
            if (flag == 1) {
                write_file(file);
            }
        } else {
            printf("n/a\n");
        }
        scanf("%d", &n);
    }
    free(file);
    return 0;
}
void read_file(char *file) {
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("n/a\n");
    } else {
        int ch;
        while ((ch = fgetc(fp)) != EOF) {
            printf("%c", ch);
        }
        printf("\n");
        fclose(fp);
    }
}
void write_file(char *file) {
    FILE *fp = fopen(file, "a");
    if (fp == NULL) {
        printf("n/a\n");
    } else {
        char w[256];
        scanf("%s", w);
        fputs("\n", fp);
        fputs(w, fp);
        fclose(fp);
    }
    read_file(file);
    printf("\n");
}