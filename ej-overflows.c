#include <stdio.h>
#include <limits.h>  // Para SHRT_MAX, SHRT_MIN, USHRT_MAX

int main() {
    // Parte con short con signo
    short s = SHRT_MAX;
    printf("short con signo:\n");
    printf("Valor inicial (SHRT_MAX): %d\n", s);
    s = s + 1;
    printf("Después de sumar 1: %d (overflow)\n", s);

    s = SHRT_MIN;
    printf("Valor mínimo (SHRT_MIN): %d\n", s);
    s = s - 1;
    printf("Después de restar 1: %d (underflow)\n", s);

    // Parte con unsigned short
    unsigned short us = USHRT_MAX;
    printf("\nunsigned short:\n");
    printf("Valor inicial (USHRT_MAX): %u\n", us);
    us = us + 1;
    printf("Después de sumar 1: %u (overflow - vuelve a 0)\n", us);

    us = 0;
    printf("Valor inicial: %u\n", us);
    us = us - 1;
    printf("Después de restar 1: %u (underflow - va a USHRT_MAX)\n", us);

    return 0;
}

