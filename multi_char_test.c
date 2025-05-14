#include <stdio.h>

int main() {
    char c = 'ñ';  // Esto puede fallar
    printf("Letra: %c\n", c);
    return 0;
}

