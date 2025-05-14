# Ejercicio: Introducción a Strings en C

En C, un **string** no es un tipo de dato especial como en otros lenguajes. Se representa como un **arreglo de caracteres (`char`) finalizado por el carácter nulo** (`'\0'`), que indica dónde termina la cadena.

Esta característica implica que podemos **modificar los strings carácter por carácter**, y que es fundamental tener cuidado con el tamaño de los arreglos y el manejo de memoria.

---

## 🧪 Ejemplo: análisis de strings

Veamos el siguiente código, que muestra cómo se comportan los strings en C:

```c
#include <stdio.h>
#include <string.h>

int main() {
    printf("Ejemplos de strings.\n");
    char saludo[] = "Hola mundo!";
    char saludo_fijo[100] = "Hola mundo en un array de largo fijo.";
    printf("sizeof saludo:   %zu bytes\n", sizeof(saludo));
    printf("strlen saludo:   %zu bytes\n", strlen(saludo));
    printf("sizeof saludo_fijo:   %zu bytes\n", sizeof(saludo_fijo));
    printf("strlen saludo_fijo:   %zu bytes\n", strlen(saludo_fijo));
    printf("Modificacion de strings.\n");
    printf("saludo sin tocar: %s\n", saludo);
    saludo[0] = 'C';
    printf("saludo luego de cambiar la posicion 0 por una 'C': %s\n", saludo);
    saludo[1] = '\0';
    printf("saludo luego de cambiar la posicion 1 por el caracter nulo \\0: %s\n", saludo);
    printf("sizeof saludo:   %zu bytes\n", sizeof(saludo));
    printf("strlen saludo:   %zu bytes\n", strlen(saludo));
    return 0;
}
```

---

### 📌 ¿Qué se espera del alumno?

- **Ejecutar este código** y observar atentamente las salidas de `sizeof` y `strlen`.
- Notar cómo `sizeof` devuelve el tamaño total del arreglo (incluyendo `'\0'`), mientras que `strlen` devuelve la longitud **hasta** el primer `'\0'`.
- Ver cómo se puede **modificar** un string carácter por carácter.
- Entender cómo cambiar un carácter por `'\0'` **trunca visualmente** la cadena al imprimirla.

---

## ✍️ Parte 1: Escribir una función para invertir un string

Escriba una función que:

- Reciba un string como parámetro
- Invierta el contenido **in-place**, modificando el arreglo original

### 🧪 Ejemplo:

Entrada: `"Hola"` → Salida: `"aloH"`

### 🔧 Sugerencia de prototipo:

```c
void invertir(char texto[]);
```

#### ❓ ¿Por qué no se indica el tamaño del arreglo?

Cuando una función en C recibe un array (un string es un array de char) como argumento, lo que realmente recibe es una **referencia al primer elemento del arreglo**, es decir, un **puntero**. Por eso, la declaración `char texto[]` en una función es equivalente a `char* texto`, pero suele ser más clara para los estudiantes.

No es necesario (ni útil) declarar el tamaño del arreglo, ya que C **no transmite esa información automáticamente**. El tamaño se puede calcular dentro de la función (por ejemplo, usando `strlen`) si es un string válido terminado en `\0`.

En otros casos, se podría pasar el tamaño del array como otro argumento, como se requiere en las llamadas al sistema `read` y `write`, en donde `count` es el tamaño mínimo que debe tener `buf` para que todo funcione bien.

```c
ssize_t write(int fd, const void *buf, size_t count);
```

---

### 🧪 Prueba:

Después de definir la función, agregue el siguiente código en `main()` para probarla:

```c
char nombre[] = "Hola";
invertir(nombre);
printf("Nombre invertido: %s\n", nombre);
```

---

## ✂️ Parte 2: Separar la función en otro archivo

1. Cree un nuevo archivo llamado `invertir.c` que contenga **solo la función `invertir`**.
2. En el archivo original (`ejemplos-strings-1.c`), agregue el `#include` de su propio encabezado o simplemente declare la función con:

```c
void invertir(char texto[]);
```

---

## 🛠 Compilar múltiples archivos fuente

Para compilar ambos archivos juntos, use el siguiente comando en la terminal:

```bash
gcc ejemplos-strings-1.c invertir.c -o ejemplos-strings
```

Esto genera el ejecutable `ejemplos-strings`.

Ejecutá con:

```bash
./ejemplos-strings
```

---

## ✅ Objetivos pedagógicos

- Comprender qué es un string en C
- Diferenciar `sizeof` y `strlen`
- Manipular strings modificando directamente sus caracteres
- Dividir un programa en múltiples archivos fuente
- Compilar y vincular archivos separados para crear un ejecutable
