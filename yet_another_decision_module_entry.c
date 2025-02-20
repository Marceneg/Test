#include <stdio.h>
#include <stdlib.h>

#include "decision.h"
int main() {
    double *data;
    int n;
    scanf("%d", &n);
    data = malloc(n * sizeof(double));
    if (make_decision(data, n))
        printf("YES");
    else
        printf("NO");
    free(data);
    return 0;
}
