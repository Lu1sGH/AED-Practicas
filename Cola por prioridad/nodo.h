#ifndef NODO_H
#define NODO_H

#include <stdio.h>
#include <stdlib.h>
#include "elemento.h"

typedef struct nodo
{
	struct nodo *enlaceA;			// *adelante
	Elemento elem;
	struct nodo *enlaceB;			// *atras
	// struct nodo *enlaceC;
	// struct nodo **enlaces; 	// arreglo a apuntadores
}t_nodo, *Nodo;

// Nodo = (struct nodo *)
// Nodo *= (struct nodo **)

int crearNodo(Nodo *n);
int destruirNodo(Nodo *n);
int escribirElemento(Nodo n, Elemento e);
int leerElemento(Nodo n, Elemento *e);

// conexion:
int conectarEnlaceA(Nodo n, Nodo eA);
int conectarEnlaceB(Nodo n, Nodo eB);

// consulta:
int consultarEnlaceA(Nodo n, Nodo *eA);
int consultarEnlaceB(Nodo n, Nodo *eB);

//desconexion:
int desconectarEnlaceA(Nodo n);
int desconectarEnlaceB(Nodo n);

//Cola circular
int conectarEnlaceACircular(Nodo n, Nodo eA, Nodo primero);
int actualizarUltimoEnlaceACircular(Nodo sig, Nodo ultimo);
//Por prioridad
int conectarEnlacePrioridad(Nodo a, Nodo b, Nodo c);

#endif

/*
// referencia a multiples nodos
typedef struct nodo
{
	struct nodo *enlaceA;
	struct nodo **coleccion;	// arreglo dinamico de nodos
	struct nodo *enlaceB;
	// struct nodo *enlaceC;
	// struct nodo **enlaces; 	// arreglo a apuntadores
}t_nodo, *Nodo;
*/




