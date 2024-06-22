#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

int abrirArchivo(char **, int *);
int push(Pila, Elemento *, char);
int pop(Pila, Elemento *, char *);

int main(int argc, char *argv[]){
	Pila p= NULL;
	Elemento e= NULL;
	char y=0, elem = 0, *inf = NULL, *pos = NULL;
	int i = 0, j=0, k = 0, N= 0, ctr = 0;

    ctr = abrirArchivo(&inf, &N);
    pos = (char *) malloc(N*sizeof(char));

    if(!ctr || pos == NULL) return 0;
	crearPila(&p);

	for (k=0; k<N; k++){
        y = inf[k];
        printf("=== %c === \n", y);
        if(y == '{' || y == '[' || y == '(' || y == '<'
        || y == '+' || y == '-' || y == '*' || y == '/' || y == '^'){
            push(p, &e, y);
        }else if(y == '}' || y == ']' || y == ')' || y == '>'){
            ctr = 1;
            pop(p, &e, &elem);
            while(ctr){
                pos[i] = elem;
                i++;
                for(j = 0; j<i; j++) printf("%c ", pos[j]);
                puts("");
                pop(p, &e, &elem);
                (y-1 == elem || y-2 == elem)?(ctr=0):(ctr=1);
            }
        }else{
            pos[i] = y;
            i++;
        }
    }

	printf("\n");

    j = p->longitud;
    if(j != 0){
        for (k = 0; k < j; k++){
	 		pop(p, &e, &elem);
	 		pos[i] = elem;
            i++;
		}
    }

    for(j = 0; j<i; j++) printf("%c ", pos[j]);
    puts("");
    imprimirPila(p);

    free(pos);
	destruirPila(&p);
	return 0;
}

int abrirArchivo(char **a, int *n){
    if(*a!=NULL) free(*a);

    FILE *f = NULL;
    f = fopen("Infija.txt", "r");
    if(f == NULL) return 0;

    char c;
    while((c=fgetc(f))!=EOF){
        (*n)++;
    }
    rewind(f);

    *a = (char *)malloc((*n)*sizeof(char));
    for(int j=0; j<*n; j++)
        *(*a+j) = fgetc(f);

    return 1;
}

int push(Pila p, Elemento *e, char y){
    crearElemento(e);
    printf("%c\n", y);
    escribirDato(*e, y);
    insertarElemento(p, *e);
    imprimirPila(p);
    return 1;
}

int pop(Pila p, Elemento *e, char *dato){
    quitarElemento(p, e);
    leerDato(*e, dato);
    destruirElemento(e);
    printf("%c\n", *dato);
    imprimirPila(p);
    return 1;
}
