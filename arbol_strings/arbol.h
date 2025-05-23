#ifndef ARBOL_H
#define ARBOL_H

typedef struct nodo {
    char *dato;
    struct nodo *izq;
    struct nodo *der;
} Nodo;

Nodo *insertar(Nodo *raiz, char *dato);
void imprimir_ordenado(Nodo *raiz);
void liberar_arbol(Nodo *raiz);

#endif
