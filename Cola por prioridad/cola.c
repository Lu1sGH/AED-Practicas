#ifndef COLA_C
#define COLA_C

#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

// Cola = (struct cola *)
// t_cola = (struct cola)

int crearCola(Cola *c)
{
	Cola q= NULL;

	q= (Cola) malloc(sizeof(t_cola));

	if (q==NULL)
	  return(FALSO);

	q->primero= NULL;
	q->ultimo= NULL;
	q->longitud= 0;

	*c= q;				// copia la direccion donde habita la cola q

	return(VERDADERO);
}


int insertarElemento(Cola c, Elemento e)
{
	Nodo n= NULL;
	int sw= FALSO;

	if (c==NULL)
	  return(FALSO);

	sw= crearNodo(&n);

	if (sw==VERDADERO)
		{
			sw= escribirElemento(n, e);
				// n->elem= e;
			if (sw==VERDADERO)
				{
					if (c->longitud==0){
					  c->primero= n;
					  actualizarUltimoEnlaceACircular(n, n);
					}else
					  conectarEnlaceACircular(c->ultimo, n, c->primero);

					c->ultimo= n;
					(c->longitud)++;

					return(VERDADERO);
				}
		}

	return(FALSO);
}

int quitarElemento(Cola c, Elemento *e)
{
	int sw= FALSO;
	Nodo siguiente= NULL;

	if (c==NULL)
	  return(FALSO);

	if (c->longitud==0)
	  return(FALSO);

	sw= leerElemento(c->primero, e);

	if (sw==VERDADERO)
		{
			sw= consultarEnlaceA(c->primero, &siguiente);
			if (sw==VERDADERO)
				{
					sw= desconectarEnlaceA(c->primero);
					if (sw==VERDADERO)
						{
							sw= destruirNodo(&(c->primero));
							if (sw==VERDADERO)
								{
									c->primero= siguiente;
									(c->longitud)--;

									if (c->longitud==0)
							  			{
							  				c->primero= NULL;
							  				c->ultimo= NULL;
							  				return(VERDADERO);
							  			}
                                    actualizarUltimoEnlaceACircular(siguiente, c->ultimo);
							  		return(VERDADERO);
							  	}
						}
				}
		}

	return(FALSO);
}

int consultarPrimero(Cola c, Elemento *e)
{
	int sw= FALSO;

	if (c==NULL)
	  return(FALSO);

	if (c->longitud==0 || c->primero==NULL)
	  return(FALSO);

	sw= leerElemento(c->primero, e);

	return(sw);
}

int consultarUltimo(Cola c, Elemento *e)
{
	int sw= FALSO;

	if (c==NULL)
	  return(FALSO);

	if (c->longitud==0 || c->ultimo==NULL)
	  return(FALSO);

	sw= leerElemento(c->ultimo, e);

	return(sw);
}

int destruirCola(Cola *q)
{
	Cola c= NULL;
	Nodo siguiente= NULL;
	int sw= FALSO;

	c= *q;				// extraccion de referencia externa

	if (c==NULL)
	  return(FALSO);

	while(c->primero!=NULL)
	{
		sw= consultarEnlaceA(c->primero, &siguiente);
		if (sw==FALSO)
		  return(FALSO);

		sw= desconectarEnlaceA(c->primero);
		if (sw==FALSO)
		  return(FALSO);

		sw= destruirNodo(&(c->primero));
		if (sw==FALSO)
		  return(FALSO);

		c->primero= siguiente;
		c->longitud--;
	}

	c->longitud= 0;
	c->primero= NULL;
	c->ultimo= NULL;

	free(c);	// liberacion de memoria cuando se libero previamente
				// el contenido de la cola de forma apropiada

	*q= NULL;

	return(VERDADERO);
}

int imprimirCola(Cola c)
{
	Nodo siguiente= NULL, nodo= NULL;
	Elemento e= NULL;
	int sw= FALSO;
	int dato= 0;

	if (c==NULL)
	  return(FALSO);

	printf("<");

	nodo= c->primero;

	while(nodo != NULL)
	{
		leerElemento(nodo, &e);
		leerDato(e, &dato);
		printf("%d", dato);

		sw= consultarEnlaceA(nodo, &siguiente);
		if (sw==FALSO)
		  return(FALSO);

        if(nodo != c->ultimo){
            nodo= siguiente;
            printf(", ");
        }else
            nodo = NULL;
	}
	printf(">\n");
	return(VERDADERO);
}

int insertarElementoPorPrioridad(Cola c, Elemento e)
{
	Nodo n= NULL;
	int sw= FALSO;
	int eInsertar, eCola;
	int i;

	if (c==NULL)
	  return(FALSO);

	sw= crearNodo(&n);

	if (sw==VERDADERO)
		{
			sw= escribirElemento(n, e);
			if (sw==VERDADERO)
				{
					if (c->longitud==0){
                        c->primero= n;
                        actualizarUltimoEnlaceACircular(n, n);
                        c->ultimo= n;
                        (c->longitud)++;
					}else{
					    Nodo aux = c->primero;
					    Nodo anteriorAux = c->ultimo;
                        leerDato(e, &eInsertar);
                        leerDato(aux->elem, &eCola);
                        for(i = 0; i<(c->longitud); i++){
                            if(eInsertar>eCola){
                                conectarEnlacePrioridad(aux, n, anteriorAux);
                                (c->longitud)++;
                                if(i==0){
                                    c->primero = n;
                                }
                                return(VERDADERO);
                            }
                            anteriorAux = aux;
                            aux = aux->enlaceA;
                            leerDato(aux->elem, &eCola);
                        }
                        conectarEnlaceACircular(c->ultimo, n, c->primero);
                        c->ultimo= n;
                        (c->longitud)++;
					}
					return(VERDADERO);
				}
		}

	return(FALSO);
}

int imprimirColaActividades(Cola c)
{
	Nodo siguiente= NULL, nodo= NULL;
	Elemento e= NULL;
	int sw= FALSO;
	int act= 0;

	if (c==NULL)
	  return(FALSO);

	printf("<");

	nodo= c->primero;

	while(nodo != NULL)
	{
		leerElemento(nodo, &e);
		leerAct(e, &act);
		printf("%c", act);

		sw= consultarEnlaceA(nodo, &siguiente);
		if (sw==FALSO)
		  return(FALSO);

        if(nodo != c->ultimo){
            nodo= siguiente;
            printf(", ");
        }else
            nodo = NULL;
	}
	printf(">\n");
	return(VERDADERO);
}

#endif

