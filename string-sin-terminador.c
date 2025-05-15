#include <stdio.h>
#include <string.h>

int main() {
    char sin_terminador[] = { 'H', 'o', 'l', 'a' }; // Faltan '\0'
    char con_terminador[] = { 'C', 'h', 'a', 'u', '\0' }; // Correcto, pero confuso
    char correcto[] = "Bien"; // Igual al anterior, el compilador agrega el \0 final

    printf("Contenido de sin_terminador (NO uses esto en producción):\n");
    printf("printf del contenido: %s\n", sin_terminador);
    printf("sizeof: %zu\n", sizeof(sin_terminador));
    printf("strlen: %zu\n", strlen(sin_terminador));  // comportamiento indefinido

    printf("\nContenido de con_terminador:\n");
    printf("printf del contenido: %s\n", con_terminador);
    printf("sizeof: %zu\n", sizeof(con_terminador));
    printf("strlen: %zu\n", strlen(con_terminador));  // seguro

    printf("\nContenido de correcto:\n");
    printf("printf del contenido: %s\n", correcto);
    printf("sizeof: %zu\n", sizeof(correcto));
    printf("strlen: %zu\n", strlen(correcto));

    return 0;
}

