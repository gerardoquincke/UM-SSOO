#include <stdio.h>
#include <string.h>

int main() {
    char a[8] = "hola";
    char b[8] = "que";
    char c[8] = "tal";

    printf("Antes del overflow:\n");
    printf("a: %s  (direccion de memoria: %p)\n", a, a);
    printf("b: %s  (direccion de memoria: %p)\n", b, b);
    printf("c: %s  (direccion de memoria: %p)\n", c, c);

    // Simulamos un overflow en a
    // Simulamos overflow escribiendo más allá del final de 'a'
    printf("\nEscribiendo manualmente fuera del límite de 'a'...\n");

    a[0] = 'X';
    a[1] = 'Y';
    a[2] = 'Z';
    a[3] = '1';
    a[4] = '2';
    a[5] = '3';
    a[6] = '4';
    a[7] = '5';  // Última posición válida
    a[8] = '6';  // 🔥 Fuera de límite
    a[9] = '7';  // 🔥 Fuera de límite
    a[10] = '\0';

    printf("\nDespués del overflow:\n");
    printf("a: %s  (direccion de memoria: %p)\n", a, a);
    printf("b: %s  (direccion de memoria: %p)\n", b, b);
    printf("c: %s  (direccion de memoria: %p)\n", c, c);

    // Simulamos un overflow en b pero nos "olvidamos" del \0
    printf("\nEscribiendo manualmente fuera del límite de 'b'...\n");

    b[0] = 'a';
    b[1] = 'b';
    b[2] = 'c';
    b[3] = 'd';
    b[4] = 'e';

    printf("\nDespués del 2do overflow:\n");
    printf("a: %s  (direccion de memoria: %p)\n", a, a);
    printf("b: %s  (direccion de memoria: %p)\n", b, b);
    printf("c: %s  (direccion de memoria: %p)\n", c, c);

    return 0;
}

