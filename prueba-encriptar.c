#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void encriptar(char *s, const char *diccionario, int clave);
extern void desencriptar(char *s, const char *diccionario, int clave);

/* Diccionarios y frase predefinidos */
#define BIGDIC "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,-+"
#define MINDIC "abcdefghijklmnopqrstuvwxyz"
#define FRASE "La perfeccion se logra no cuando no hay nada mas que anadir, sino cuando no hay nada mas que quitar. Antoine de Saint-Exuperi"

typedef struct {
    char *s;
    char *dic;
    int clave;
} Test;

/* Compara strings y retorna "OK" o "ERROR" */
const char *verificar(const char *original, const char *encriptado, const char *desencriptado) {
    return (strcmp(original, desencriptado) == 0 && strcmp(original, encriptado) != 0) ? "OK" : "ERROR";
}

void correr_prueba(const char *s, const char *dic, int clave) {
    char *enc = strdup(s);
    encriptar(enc, dic, clave);
    char *desenc = strdup(enc);
    desencriptar(desenc, dic, clave);

    printf("\"%s\" \"%s\" %d\n", enc, dic, clave);
    printf("\"%s\" \"%s\" %d\n", desenc, dic, clave);
    printf("%s\n", verificar(s, enc, desenc));

    free(enc);
    free(desenc);
}

int main(int argc, char *argv[]) {
    if (argc == 4) {
        // Modo con argumentos
        char *s = argv[1];
        char *dic = argv[2];
        int clave = atoi(argv[3]);
        encriptar(s, dic, clave);
        printf("%s\n", s);
        return 0;
    }

    // Pruebas predefinidas
    Test tests[] = {
        {"abc", "abc", 0},
        {"abc", "abc", 1},
        {"abc", "abc", -1},
        {"abc", "abc", 2},
        {"abc", "abc", 3},
        {"ABC", "abcABC", 3},
        {"abc", "abcdef", 88888888},
        {"abc", BIGDIC, 3},
        {"abc", BIGDIC, 28392},
        {FRASE, BIGDIC, 0},
        {FRASE, BIGDIC, 209365},
        {FRASE, MINDIC, 4},
    };

    int n = sizeof(tests) / sizeof(Test);
    for (int i = 0; i < n; i++) {
        correr_prueba(tests[i].s, tests[i].dic, tests[i].clave);
    }

    return 0;
}

