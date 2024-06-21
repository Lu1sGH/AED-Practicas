#include <stdio.h>
#include <stdlib.h>
#include "cola.h"
#include "elemento.h"

int main(int argc, char *argv[])
{
	Cola c= NULL;
	Elemento e= NULL;
	int k=0, x=0;
	int N= 10;
	int sw= FALSO;
	int ctr = 1;

	sw= crearCola(&c);

	if (sw==FALSO)
	  return 0;

	for (k=N; k>0; k--)
	 	{
	 		crearElemento(&e);
	 		escribirDato(e, k*10);
			insertarElemento(c, e);
			imprimirCola(c);
		}

    //===================================
    puts("¿Quiere agregar un elemento?");
    scanf("%d", &ctr);
    while(ctr){
        puts("Escriba el elemento");
        scanf("%d", &k);
        crearElemento(&e);
        escribirDato(e, k);

        insertarElementoPorPrioridad(c, e);
        imprimirCola(c);
        N++;
        puts("¿Quiere agregar otro elemento?");
        scanf("%d", &ctr);
    }
    //====================================

	for (k=0; k<N; k++)
	 	{
	 		quitarElemento(c, &e);
	 		leerDato(e, &x);
	 		printf("%d\n", x);
	 		imprimirCola(c);
	 		destruirElemento(&e);
		}

	destruirCola(&c);

	return 0;
}
