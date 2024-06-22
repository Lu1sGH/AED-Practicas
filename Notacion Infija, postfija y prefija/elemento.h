#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <stdio.h>
#include <stdlib.h>

#define VERDADERO 	1
#define FALSO		0

typedef struct elemento
{
	char dato;
}	t_elemento, *Elemento;

int crearElemento(Elemento *e);
int destruirElemento(Elemento *e);
int escribirDato(Elemento e, char dato);
int leerDato(Elemento e, char *dato);

// Elemento *= (struct elemento **)
// Elemento = (struct elemento *)
// t_elemento = (struct elemento)
// void *malloc(tamaño);

#endif

