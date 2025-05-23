#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

#define MAX_LINEA 1024

int main(int argc, char *argv[]) {
    Nodo *raiz = NULL;
    char linea[MAX_LINEA];

    if (argc == 1) {
        while (fgets(linea, sizeof(linea), stdin)) {
            raiz = insertar(raiz, linea);
        }
    } else {
        for (int i = 1; i < argc; i++) {
            FILE *f = fopen(argv[i], "r");
            if (!f) {
                perror(argv[i]);
                continue;
            }
            while (fgets(linea, sizeof(linea), f)) {
                raiz = insertar(raiz, linea);
            }
            fclose(f);
        }
    }

    imprimir_ordenado(raiz);
    liberar_arbol(raiz);
    return 0;
}
