# Ejemplos de C para mostrar tipos y codificación ASCII

Este repositorio contiene pequeños programas en lenguaje C diseñados para uso en clase, mostrando conceptos básicos como:

- Tamaños de tipos (`char`, `int`, `short`, etc.)
- Uso de `stdint.h` para tipos con tamaño fijo
- Overflow y underflow en variables con y sin signo
- Representación de caracteres ASCII en distintos formatos
- Conversión manual a binario

## Archivos

| Archivo               | Descripción |
|-----------------------|-------------|
| `sizeof-basicos.c`    | Muestra los tamaños de los tipos estándar de C |
| `sizeof-stdint.c`     | Muestra tamaños de tipos de `<stdint.h>` como `int16_t` |
| `ej-overflows.c`      | Demuestra overflow con `short` y `unsigned short` |
| `multi_char_test.c`   | Prueba cómo se comporta el compilador con `'ñ'` |
| `tabla-ascii.c`       | Imprime la tabla ASCII de caracteres imprimibles |
| `tabla-ascii-2.c`     | Igual que anterior, pero incluye la representación binaria |

## Compilación

Usar `gcc`:

```bash
gcc archivo.c -o programa
./programa

