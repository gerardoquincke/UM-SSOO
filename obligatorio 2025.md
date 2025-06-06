# Proyecto de Filesystem Simplificado

## Descripción General

Se propone a los estudiantes implementar un sistema de archivos simplificado, inspirado en conceptos tipo Unix. El objetivo es desarrollar, desde cero, una aplicación que permita crear y manipular una imagen de disco en memoria.

Este proyecto busca reforzar conceptos de sistemas de archivos, manejo de estructuras, acceso a bajo nivel y modularización del código en C.

### Organización de la entrega

La entrega del trabajo debe incluir:

* Un archivo fuente `.c` para **cada comando** implementado (`vfs-mkfs.c`, `vfs-ls.c`, `vfs-copy.c`, `vfs-rm.c`, `vfs-touch.c`, `vfs-cat.c`, etc.).
* Un archivo de encabezado común (`fs.h`) con todas las estructuras, constantes y prototipos utilizados.
* Un archivo `Makefile` que compile todos los comandos.
* Archivos de apoyo si los hubiera (por ejemplo: `util.c`, `bitmap.c`).
* El archivo `read_write_block.c`, que contiene funciones auxiliares obligatorias para acceder a los bloques del dispositivo.

La estructura del proyecto debe permitir compilar todos los comandos con un solo `make` y generar ejecutables separados para cada utilidad.

---

## Parámetros de Formato

* Tamaño de bloque: **1024 bytes fijo** (para simplificar el diseño y la implementación).
* Tamaño total de disco: hasta 64 MiB (en memoria, archivo plano).
* El primer bloque siempre contiene el **superbloque**.
* El segundo bloque en adelante contiene la **tabla de nodos-i**.
* Luego sigue el **bitmap de bloques**.
* Luego siguen los **bloques de datos**.
* El **nodo-i 0** corresponde al directorio raíz (único directorio), que debe contener las entradas especiales `.` y `..` desde su creación.

---

## Estructuras C Obligatorias

Se deben usar exactamente las siguientes estructuras (pueden agregarse campos auxiliares solo si son derivados):

### Constantes

```c
#define MAGIC_NUMBER 0x20250604
#define BLOCK_SIZE 1024
#define INODE_MODE_FILE 0x8000
#define INODE_MODE_DIR  0x4000
#define FILENAME_MAX_LEN 28
#define INDIRECT_BLOCK_PTRS (BLOCK_SIZE / sizeof(uint32_t))
```

### Superbloque

```c
struct superblock {
    uint32_t magic;
    uint32_t block_size;
    uint32_t total_blocks;
    uint32_t inode_count;
    uint32_t inode_start;
    uint32_t bitmap_start;
    uint32_t data_start;
};
```

### Nodo-i

```c
struct inode {
    uint16_t mode;
    uint16_t uid;
    uint16_t gid;
    uint32_t size;
    uint32_t blocks;
    uint32_t direct[7];
    uint32_t indirect;
    uint32_t atime;
    uint32_t mtime;
    uint32_t ctime;
    uint8_t reserved[6];
};
```

Las fechas están en formato **Unix timestamp**. Los campos `uid` y `gid` también siguen el formato estándar POSIX.

### Estructura de Indirección

```c
struct indirect_block {
    uint32_t blocks[INDIRECT_BLOCK_PTRS];
};
```

### Estructura de Directorio

```c
struct dir_entry {
    uint32_t inode;
    char name[FILENAME_MAX_LEN];
};
```

---

## Acceso a bloques

Todas las operaciones sobre bloques de datos deben realizarse mediante funciones auxiliares provistas por el docente:

```c
int read_block(const char *image_path, int block_number, void *buffer);
int write_block(const char *image_path, int block_number, const void *buffer);
int create_block_device(const char *image_path, int total_blocks, int block_size);
```

Estas funciones estarán implementadas en el archivo `read_write_block.c`.

### Implementación de funciones auxiliares (`read_write_block.c`)

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "vfs.h"

int read_block(const char *image_path, int block_number, void *buffer) {
    int fd = open(image_path, O_RDONLY);
    if (fd < 0) return -1;

    if (lseek(fd, block_number * BLOCK_SIZE, SEEK_SET) < 0) {
        close(fd);
        return -1;
    }

    if (read(fd, buffer, BLOCK_SIZE) != BLOCK_SIZE) {
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

int write_block(const char *image_path, int block_number, const void *buffer) {
    int fd = open(image_path, O_WRONLY);
    if (fd < 0) return -1;

    if (lseek(fd, block_number * BLOCK_SIZE, SEEK_SET) < 0) {
        close(fd);
        return -1;
    }

    if (write(fd, buffer, BLOCK_SIZE) != BLOCK_SIZE) {
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

int create_block_device(const char *image_path, int total_blocks, int block_size) {
    int fd = open(image_path, O_CREAT | O_EXCL | O_WRONLY, 0644);
    if (fd < 0) return -1;

    char zero[BLOCK_SIZE];
    memset(zero, 0, BLOCK_SIZE);

    for (int i = 0; i < total_blocks; i++) {
        if (write(fd, zero, block_size) != block_size) {
            close(fd);
            return -1;
        }
    }
    close(fd);
    return 0;
}
```

---

## Makefile

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
COMMON_SRCS = read_write_block.c bitmap.c util.c

TARGETS = vfs-mkfs vfs-ls vfs-copy vfs-rm vfs-touch vfs-cat vfs-info

all: $(TARGETS)

$(TARGETS): %: %.c $(COMMON_SRCS) fs.h
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS)
```

---

## Comandos del sistema

### `vfs-mkfs`

```bash
vfs-mkfs imagen cantidad_bloques cantidad_inodos
```

* El archivo `imagen` **no debe existir previamente**.
* Crea la imagen vacía, inicializando el superbloque, la tabla de nodos-i, el bitmap y el bloque del directorio raíz.
* El superbloque incluye el número mágico `MAGIC_NUMBER`.
* El bloque 0 es el superbloque.
* El bloque 1 comienza la tabla de nodos-i.


### `vfs-info`

```bash
vfs-info imagen
```

* Muestra información general del filesystem:

  * Contenido del superbloque (todos sus campos)
  * Cantidad de bloques libres y ocupados
  * Muestra el bitmap de bloques de forma textual, indicando con `.` los bloques libres y con `#` los bloques usados (en filas de 64 bloques, por ejemplo)

### `vfs-ls`

```bash
vfs-ls imagen
```

* Muestra una lista al estilo `ls -l`, ordenada alfabéticamente, incluyendo:

  * Nombre
  * Inodo
  * UID
  * GID
  * Tamaño
  * Cantidad de bloques
  * Tipo
  * Fecha de creación (formato legible)

### `vfs-copy`

```bash
vfs-copy imagen archivo_origen nombre_destino
```

* Copia un archivo del sistema anfitrión al filesystem.
* El nombre de destino debe cumplir las restricciones de nombres: letras, números, `.`, `_`, `-`.
* Si no hay espacio suficiente, debe abortar informando el error.

### `vfs-rm`

```bash
vfs-rm imagen archivo1 [archivo2...]
```

* Borra uno o más archivos.
* Solo se pueden borrar archivos regulares.

### `vfs-touch`

```bash
vfs-touch imagen archivo1 [archivo2...]
```

* Crea archivos vacíos.
* Si el nombre ya existe, debe rechazarlo.

### `vfs-cat`

```bash
vfs-cat imagen archivo1 [archivo2...]
```

* Muestra por salida estándar el contenido de uno o más archivos concatenados.

---

## Validaciones comunes

* Todos los comandos, excepto `mkfs`, requieren que la imagen exista y contenga el número mágico correcto.
* El sistema debe rechazar:

  * Nombres duplicados
  * Modos de archivo inválidos
  * Operaciones con inodos no asignados
  * Intentos de borrar o mostrar directorios como si fueran archivos
