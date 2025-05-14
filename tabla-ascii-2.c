#include <stdio.h>
#include <ctype.h>
#include <limits.h>

// Convierte un byte a una cadena binaria
void byte_to_binary(unsigned char value, char *output) {
    for (int i = 7; i >= 0; i--) {
        output[7 - i] = (value & (1 << i)) ? '1' : '0';
    }
    output[8] = '\0';  // Null-terminator
}


int main() {
    char s[9];

    printf("Dec     Binary  Hex   Oct   Char\n");
    printf("--------------------------------\n");

    for (int i = 0; i <= UCHAR_MAX; i++) {
        if (isprint(i)) {
            byte_to_binary(i, s);
            printf("%3d  b%8s 0x%02X   0%03o   '%c'\n", i, s, i, i, i);
        }
    }

    return 0;
}

