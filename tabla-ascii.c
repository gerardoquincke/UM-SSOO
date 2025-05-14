#include <stdio.h>
#include <ctype.h>
#include <limits.h>

int main() {
    printf("Dec    Hex   Oct   Char\n");
    printf("-----------------------\n");

    for (int i = 0; i <= UCHAR_MAX; i++) {
        if (isprint(i)) {
            printf("%3d  0x%02X   0%03o   '%c'\n", i, i, i, i);
        }
    }

    return 0;
}

