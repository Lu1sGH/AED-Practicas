#include <stdio.h>
#include <stdlib.h>
#include <Time.h>
#include "lista.h"

void merge(Lista, int, int);
void recomb(Lista, int, int, int);

int main(int argc, char *argv[])
{
	Lista l= NULL;
	Elemento e= NULL;
	int k=0, x=0;
	int N= 0;

    srand(time(NULL));
	int sw = crearLista(&l);
	if(!sw) return -10;

	printf("¿Cuantos elementos quiere que se generen en la lista? \n");
	scanf("%d", &N);
	printf("¿Quiere que los elementos se generen: (0) de forma descendente o (1) aleatoriamente? \n");
	scanf("%d", &sw);

	for (k=0, x=N; k<N; k++, x--){
	 		crearElemento(&e);
	 		(sw)?escribirDato(e, rand()%N):escribirDato(e, x);
			insertarElementoPosicionVariante(l, e, k);
			imprimirLista(l);
    }

    puts("LISTA DESORDENADA");
    imprimirLista(l);

    merge(l, 0, (l->longitud)-1);

    puts("LISTA ORDENADA");
    imprimirLista(l);

	destruirLista(&l);
	return 0;
}

void merge(Lista l, int m, int n){
    if(m!=n){

        int mitad = m + (n-m)/2;

        merge(l, m, mitad);
        merge(l, mitad+1, n);

        recomb(l, m, mitad, n);

    }
}

void recomb(Lista l, int m, int mitad, int n) {
    int sw, i, j, k, tam = n - m + 1, dato1, dato2;
    Elemento e;
    Lista aux;
    sw = crearLista(&aux);

    if (!sw){ puts("HA OCURRIDO UN ERROR AL CREAR LA LISTA AUXILIAR"); return;}

    for (k = 0, i = m, j = mitad + 1; k < tam; k++) {
        consultarElementoPosicion(l, &e, i);
        leerDato(e, &dato1); //*a[i]
        consultarElementoPosicion(l, &e, j);
        leerDato(e, &dato2); //*a[j]
        if (i <= mitad && (j > n || dato1 <= dato2)) {
            crearElemento(&e);
            escribirDato(e, dato1);
            insertarElementoPosicionVariante(aux, e, k);
            i++;
        } else {
            crearElemento(&e);
            escribirDato(e, dato2);
            insertarElementoPosicionVariante(aux, e, k);
            j++;
        }
    }
    puts("====LLEGADA=====");
    imprimirLista(l);
    imprimirLista(aux);
    puts("====SALIDA======");

    for (i = 0; i < tam; i++){
        quitarElementoPosicion(l, &e, m+i);
        destruirElemento(&e);
        quitarElementoPosicion(aux, &e, 0);
        insertarElementoPosicionVariante(l, e, m+i);
    }

    imprimirLista(l);

    destruirLista(&aux);
}

