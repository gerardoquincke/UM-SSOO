#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

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

    // Abrir archivo
    int fd = open(argv[2], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Obtener tamaño del archivo
    struct stat st;
    if (fstat(fd, &st) != 0) {
        perror("fstat");
        close(fd);
        return 1;
    }

    if (st.st_size == 0) {
        fprintf(stderr, "Error: el archivo está vacío, no se puede mapear.\n");
        close(fd);
        return 1;
    }

    if (start >= st.st_size) {
        fprintf(stderr, "Error: byte de inicio fuera del tamaño del archivo.\n");
        close(fd);
        return 1;
    }

    // Mapear archivo completo
    void *map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    // Leer desde la posición indicada
    unsigned char *ptr = (unsigned char *)map + start;
    size_t disponibles = st.st_size - start;
    size_t a_leer = disponibles < NUM_BYTES ? disponibles : NUM_BYTES;

    for (size_t i = 0; i < a_leer; i++) {
        printf("Byte %2ld: 0x%02x", start + i, ptr[i]);
        if (isprint(ptr[i])) {
            printf(" '%c'\n", ptr[i]);
        } else {
            printf(" (no imprimible)\n");
        }
    }

    munmap(map, st.st_size);
    close(fd);
    return 0;
}

