#include <stdio.h>

int main() {
    printf("Tamaños de tipos básicos en C (en bytes):\n");
    printf("char:   %zu bytes\n", sizeof(char));
    printf("short:  %zu bytes\n", sizeof(short));
    printf("int:    %zu bytes\n", sizeof(int));
    printf("long:   %zu bytes\n", sizeof(long));
    printf("float:  %zu bytes\n", sizeof(float));
    printf("double: %zu bytes\n", sizeof(double));
    return 0;
}

