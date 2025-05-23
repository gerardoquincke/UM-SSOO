#include <stdlib.h>
#include "arbol.h"

void liberar_arbol(Nodo *raiz) {
    if (raiz == NULL)
        return;
    liberar_arbol(raiz->izq);
    liberar_arbol(raiz->der);
    free(raiz->dato);
    free(raiz);
}
