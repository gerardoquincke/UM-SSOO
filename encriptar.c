#include <string.h>
#include <stdio.h>

static
int
indice(const char *dic, char c) {
    // retorna índice de c en dic o -1 si c no está en dic
    // simil index de string.h pero retorna un indice en lugar de un puntero
    // podría haberse hecho un wrapper para index
    int i;

    for (i=0; dic[i] != '\0'; i++) {
        if (c == dic[i]) {
            return i;
        }
    }
    return -1;
}

static
int
desplazamiento(int clave, int tam_dicc)
{
    // genera un desplazamiento entre 1 y tam_dicc - 1,
    // en función de una clave y el largo de un diccionario
    return (unsigned) clave % (tam_dicc - 1) + 1;
}

// dado que encriptar y descencriptar tienen más del 90% del código idéntico,
// se hizo una función auxiliar que maneja ambos casos y recibe un cuarto argumento

static
char *
encriptar_desencriptar(char *s, const char *diccionario, int clave, int desencriptar)
{
    /*  encripta o desencripta inline el string s, dependiendo del último arg (0=encripta, !=0 desencripta)
        se usa un simple algoritmo de rotación de caracteres
        la clave determina el desplazamiento de la rotación (mínimo 1)
        los caracteres que se encriptan son los que pertenecen al "diccionario"
        El resto de caracteres se dejan como están.
    */
    int tam_dicc = strlen(diccionario);
    int j;
    char *cur;
    int despl;

    if (tam_dicc < 2) {
        return s;   // no se puede hacer nada si el diccionario tiene 0 o 1 bytes
    }

    despl = desplazamiento(clave, tam_dicc);

    if (desencriptar) {
        despl = tam_dicc - despl; // en la descencripción el desplazamiento es el complemento
    }

    for (cur=s; *cur != '\0'; cur++) {
        if ( (j = indice(diccionario, *cur)) >= 0) {
            *cur = diccionario[(j + despl) % tam_dicc];
        } 
    }
    return s;
}

void
encriptar(char *s, char *diccionario, int clave)
{
    /*  wrapper para encriptar_desencriptar, con el último argumento en 0
    */
    (void) encriptar_desencriptar(s, diccionario, clave, 0);
}

void
desencriptar(char *s, char *diccionario, int clave)
{
    /*  wrapper para encriptar_desencriptar, con el último argumento en 1
    */
    (void) encriptar_desencriptar(s, diccionario, clave, 1);
}
