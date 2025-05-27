#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void listar_directorio(const char *dir) {
    DIR *d = opendir(dir);
    if (d == NULL) {
        perror(dir);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        // Ignorar "." y ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Mostrar inodo y nombre con prefijo de directorio
        printf("%lu %s/%s\n", (unsigned long)entry->d_ino, dir, entry->d_name);
    }

    closedir(d);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        listar_directorio(".");
    } else {
        for (int i = 1; i < argc; i++) {
            listar_directorio(argv[i]);
        }
    }
    return 0;
}

