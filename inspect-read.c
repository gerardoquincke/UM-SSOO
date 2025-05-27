#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

#define NUM_BYTES 16

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s start_byte archivo\n", argv[0]);
        return 1;
    }

    // Validar y convertir el byte de inicio
    char *endptr;
    long start = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || start < 0) {
        fprintf(stderr, "Error: start_byte debe ser un entero >= 0.\n");
        return 1;
    }

    // Abrir el archivo
    int fd = open(argv[2], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Posicionar al byte de inicio
    if (lseek(fd, start, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    // Leer 16 bytes
    unsigned char buffer[NUM_BYTES];
    ssize_t bytes_leidos = read(fd, buffer, NUM_BYTES);
    if (bytes_leidos < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    close(fd);

    // Mostrar los bytes
    for (ssize_t i = 0; i < bytes_leidos; i++) {
        printf("Byte %2ld: 0x%02x", start + i, buffer[i]);
        if (isprint(buffer[i])) {
            printf(" '%c'\n", buffer[i]);
        } else {
            printf(" (no imprimible)\n");
        }
    }

    return 0;
}

