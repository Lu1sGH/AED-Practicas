#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "cola.h"
#include "elemento.h"

void add(Cola, Elemento *, int);
void addRR(Cola, Elemento *, int, int);
void addXPrioridad(Cola, Elemento *, int);
void remuv(Cola, Elemento *, int *);
void remuvRR(Cola, Elemento *, int *, int *);
void roundRobin(Cola, Elemento *);

int main(int argc, char *argv[])
{
	Cola c= NULL;
	Elemento e= NULL;
	int k=0; // x=0;
	int N= 0;
	int sw= FALSO;
	int ctr = 1;

	sw= crearCola(&c);

	if (sw==FALSO)
	  return 0;

    printf("¿Quiere preinicializar la cola? \n 1=Si \n 0= No \n");
    scanf("%d", &sw);

    if(sw){
        printf("Ingrese el numero de elementos que quiere que la cola contenga. \n");
        scanf("%d", &N);
        for (k=N; k>0; k--){
                add(c, &e, k);
                imprimirCola(c);
        }
    }

    //===================================
    (sw)?puts("¿Quiere agregar un elemento?"), scanf("%d", &ctr):puts("Agregue un elemento a la cola");
    while(ctr){
        puts("Escriba el elemento");
        scanf("%d", &k);
        addXPrioridad(c, &e, k);
        imprimirCola(c);
        puts("¿Quiere agregar otro elemento?");
        scanf("%d", &ctr);
    }
    //====================================

    printf("Presione cualquier tecla para continuar con el planificador Round Robin. \n \n");
    system("pause");

    roundRobin(c, &e);

	destruirCola(&c);

	return 0;
}

void add(Cola c, Elemento *e, int dato){
    crearElemento(e);
    escribirDato(*e, dato, 0);
    insertarElemento(c, *e);
}

void addRR(Cola c, Elemento *e, int dato, int act){
    crearElemento(e);
    escribirDato(*e, dato, act);
    insertarElemento(c, *e);
}

void addXPrioridad(Cola c, Elemento *e, int dato){
    crearElemento(e);
    escribirDato(*e, dato, 0);
    insertarElementoPorPrioridad(c, *e);
}

void remuv(Cola c, Elemento *e, int *dato){
    quitarElemento(c, e);
    leerDato(*e, dato);
    destruirElemento(e);
}

void remuvRR(Cola c, Elemento *e, int *dato, int *act){
    quitarElemento(c, e);
    leerDato(*e, dato);
    leerAct(*e, act);
    destruirElemento(e);
}

void roundRobin(Cola c, Elemento *e){
    int dato, act;
    while(c->longitud){
        imprimirCola(c);
        imprimirColaActividades(c);
        remuvRR(c, e, &dato, &act);
        printf("Actividad: %c \n -Delta T: %d seg \n", act, dato);
        if(dato > -1) Sleep(dato*1000);
        dato--;
        if(dato > 0){
            printf(" --A la actividad \"%c\" le restan %d seg. \n", act, dato);
            addRR(c, e, dato, act);
        }else{
            printf(" --La actividad \"%c\" fue finalizada \n", act);
        }
        puts("");
        puts("");
    }
    printf("Round Robin finalizado. \n");
}

/*
    N = c->longitud;
	for (k=0; k<N; k++){
	 		remuv(c, &e, &x);
	 		printf("%d\n", x);
	 		imprimirCola(c);
    }*/
