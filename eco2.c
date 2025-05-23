// version 2 de echo - usa punteros

#include <stdio.h>

int main(int argc, char *argv[]) {
    for (char **p = argv+1; *p != NULL; p++) {
        printf("%s", *p);
        if (*(p+1) != NULL) {
            putchar(' ');
        }
    }
    putchar('\n');
    return 0;
}
