CC=gcc
CFLAGS=-Wall -Wextra -std=c99

OBJS=main.o insertar.o imprimir.o liberar.o

all: arbol_strings

arbol_strings: $(OBJS)
	$(CC) $(CFLAGS) -o arbol_strings $(OBJS)

clean:
	rm -f *.o arbol_strings
