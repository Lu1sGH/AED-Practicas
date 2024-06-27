
#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <stdio.h>
#include <stdlib.h>

#define VERDADERO 	1
#define FALSO		0

typedef struct elemento
{
    int actividad;
	int dato;
}	t_elemento, *Elemento;

int crearElemento(Elemento *e);
int destruirElemento(Elemento *e);
int escribirDato(Elemento e, int dato, int act);
int leerDato(Elemento e, int *dato);
int leerAct(Elemento e, int *act);

// Elemento *= (struct elemento **)
// Elemento = (struct elemento *)
// t_elemento = (struct elemento)
// void *malloc(tamaño);

#endif
