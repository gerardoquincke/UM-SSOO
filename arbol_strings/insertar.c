#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

Nodo *insertar(Nodo *raiz, char *dato) {
    if (raiz == NULL) {
        Nodo *nuevo = malloc(sizeof(Nodo));
        if (!nuevo) {
            perror("malloc");
            exit(1);
        }

        // strdup() haría esto en una sola línea: nuevo->dato = strdup(dato);
        // strdup() hace malloc seguido de strcpy
        nuevo->dato = malloc(strlen(dato) + 1);
        if (!nuevo->dato) {
            perror("malloc");
            exit(1);
        }
        strcpy(nuevo->dato, dato);

        nuevo->izq = nuevo->der = NULL;
        return nuevo;
    }

    if (strcmp(dato, raiz->dato) < 0) {
        raiz->izq = insertar(raiz->izq, dato);
    } else {
        raiz->der = insertar(raiz->der, dato);
    }

    return raiz;
}

