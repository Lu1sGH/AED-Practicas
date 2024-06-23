#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

int abrirArchivo(char **, int *);
int push(Pila, Elemento *, char);
int pop(Pila, Elemento *, char *);
int datoTope(Pila, Elemento *, char *);
void inToPost(char *, char *, int *, int);
void inToPre(char *, char **, int *, int);

int main(int argc, char *argv[]){
	char *inf = NULL, *pos = NULL, *pre = NULL;
	int i = 0, N = 0, longPos = 0, longPre = 0, ctr = 0;

    ctr = abrirArchivo(&inf, &N);
    pos = (char *) malloc(N*sizeof(char));

    if(!ctr || pos == NULL) return 0;

    inToPost(inf, pos, &longPos, N);
    inToPre(inf, &pre, &longPre, N);

    printf(" Expresion infija: \n \t");
    for(i = 0; i<N; i++) printf("%c", inf[i]);
    printf("\n Expresion postfija: \n \t");
    for(i = 0; i<longPos; i++) printf("%c", pos[i]);
    printf("\n Expresion prefija: \n \t");
    for(i = 0; i<longPre; i++) printf("%c", pre[i]);
    puts("");

    free(pos);
    free(pre);
    free(inf);

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
    escribirDato(*e, y);
    insertarElemento(p, *e);
    return 1;
}

int pop(Pila p, Elemento *e, char *dato){
    quitarElemento(p, e);
    leerDato(*e, dato);
    destruirElemento(e);
    return 1;
}

int datoTope(Pila p, Elemento *e, char *elem){
    consultarTope(p, e);
    leerDato(*e, elem);
    return 1;
}

void inToPost(char *inf, char *pos, int *longPost, int N){
    Pila p= NULL;
	Elemento e= NULL;
	char y=0, elem = 0;
	int i = 0, j=0, k = 0, ctr = 0;

	crearPila(&p);

	for (k=0; k<N; k++){
        y = inf[k];
        if(y == '{' || y == '[' || y == '(' || y == '<'){
            push(p, &e, y);
        }else if(y == '+' || y == '-' || y == '*' || y == '/' || y == '^'){
            ctr = 1;
            datoTope(p, &e, &elem);
            while(ctr){
                if (((y == '+' || y == '-') && (elem == '*' || elem == '/' || elem == '^')) ||
                ((y == '*' || y == '/') && (elem == '^')) ||
                ((y == '+' || y == '-') && (elem == '+' || elem == '-')) ||
                ((y == '*' || y == '/') && (elem == '*' || elem == '/'))) {
                    pop(p, &e, &elem);
                    pos[i++] = elem;
                    if(p->longitud == 0){
                        ctr = 0;
                    }else{
                        datoTope(p, &e, &elem);
                    }
                }else{
                    ctr = 0;
                }
            }
            push(p, &e, y);
        }else if(y == '}' || y == ']' || y == ')' || y == '>'){
            ctr = 1;
            pop(p, &e, &elem);
            while(ctr){
                pos[i++] = elem;
                pop(p, &e, &elem);
                (y-1 == elem || y-2 == elem)?(ctr=0):(ctr=1);
            }
        }else{
            pos[i++] = y;
        }
    }

    j = p->longitud;
    if(j != 0){
        for (k = 0; k < j; k++){
	 		pop(p, &e, &elem);
	 		pos[i++] = elem;
		}
    }

	destruirPila(&p);
    *longPost = i;
}

void inToPre(char *inf, char **pref, int *longPre, int N){
    Pila p= NULL, pre = NULL;
	Elemento e= NULL;
	char y=0, elem = 0;
	int i = 0, j=0, k = 0, ctr = 0;

	crearPila(&p);
	crearPila(&pre);

	for (k=N-1; k>=0; k--){
        y = inf[k];
        if(y == '{' || y == '[' || y == '(' || y == '<'){
            ctr = 1;
            pop(p, &e, &elem);
            while(ctr){
                push(pre, &e, elem);
                pop(p, &e, &elem);
                (y+1 == elem || y+2 == elem)?(ctr=0):(ctr=1);
            }
        }else if(y == '+' || y == '-' || y == '*' || y == '/' || y == '^'){
            ctr = 1;
            datoTope(p, &e, &elem);
            while(ctr){
                if (((y == '+' || y == '-') && (elem == '*' || elem == '/' || elem == '^')) ||
                ((y == '*' || y == '/') && (elem == '^')) ||
                ((y == '+' || y == '-') && (elem == '+' || elem == '-')) ||
                ((y == '*' || y == '/') && (elem == '*' || elem == '/'))) {
                    pop(p, &e, &elem);
                    push(pre, &e, elem);
                    if(p->longitud == 0){
                        ctr = 0;
                    }else{
                        datoTope(p, &e, &elem);
                    }
                }else{
                    ctr = 0;
                }
            }
            push(p, &e, y);
        }else if(y == '}' || y == ']' || y == ')' || y == '>'){
            push(p, &e, y);
        }else{
            push(pre, &e, y);
        }
    }

    j = p->longitud;
    if(j != 0){
        for (k = 0; k < j; k++){
	 		pop(p, &e, &elem);
            push(pre, &e, elem);
		}
    }

    if(*pref != NULL) free(*pref);
    i = pre->longitud;
    *pref = (char *) malloc(i*sizeof(char));
    for(k = 0; k < i; k++){
        pop(pre, &e, &elem);
        (*pref)[k] = elem;
    }

	destruirPila(&p);
	destruirPila(&pre);
    *longPre = i;
}
