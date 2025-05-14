#include <stdio.h>
#include <stdint.h>

int main() {
    printf("Tamaños de tipos con stdint.h (en bytes):\n");
    printf("int8_t:   %zu bytes\n", sizeof(int8_t));
    printf("int16_t:  %zu bytes\n", sizeof(int16_t));
    printf("int32_t:  %zu bytes\n", sizeof(int32_t));
    printf("int64_t:  %zu bytes\n", sizeof(int64_t));
    printf("uint8_t:  %zu bytes\n", sizeof(uint8_t));
    printf("uint16_t: %zu bytes\n", sizeof(uint16_t));
    printf("uint32_t: %zu bytes\n", sizeof(uint32_t));
    printf("uint64_t: %zu bytes\n", sizeof(uint64_t));
    return 0;
}

