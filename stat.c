#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s archivo1 [archivo2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        struct stat info;

        if (stat(argv[i], &info) != 0) {
            perror(argv[i]);
            continue;
        }

        printf("Archivo: %s\n", argv[i]);
        printf("  Tamaño: %ld bytes\n", info.st_size);
        printf("  Tamaño preferido de bloque E/S: %ld bytes\n", info.st_blksize);
        printf("  Cantidad de bloques asignados: %ld (bloques de 512 bytes)\n", info.st_blocks);

        printf("  Inodo: %ld\n", info.st_ino);
        printf("  Número de enlaces: %ld\n", info.st_nlink);
        printf("  UID: %d   GID: %d\n", info.st_uid, info.st_gid);

        // Mostrar st_mode completo, tipo y permisos en octal
        printf("  st_mode: %06o\n", info.st_mode);
        printf("    Tipo de archivo (st_mode & S_IFMT): %06o\n", (info.st_mode & S_IFMT));
        printf("    Permisos (st_mode & 0777): %03o\n", (info.st_mode & 0777));

        // Timestamps como enteros + fecha
        printf("  Último acceso:           %ld (%s", info.st_atime, ctime(&info.st_atime));
        printf("  Última modificación:     %ld (%s", info.st_mtime, ctime(&info.st_mtime));
        printf("  Último cambio metadatos: %ld (%s", info.st_ctime, ctime(&info.st_ctime));

        printf("\n");
    }

    return 0;
}

