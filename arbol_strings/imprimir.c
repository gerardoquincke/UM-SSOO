#include <stdio.h>
#include "arbol.h"

void imprimir_ordenado(Nodo *raiz) {
    if (raiz == NULL)
        return;
    imprimir_ordenado(raiz->izq);
    fputs(raiz->dato, stdout);
    imprimir_ordenado(raiz->der);
}
