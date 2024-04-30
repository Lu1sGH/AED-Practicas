#include <stdio.h>
#include <stdlib.h>
#include <Time.h>

int crearA(char **, int);
void impA(char **, int);
void destA(char **);
void llenarA(FILE *, char **, int);
void swap(char **, int, int);
void selection(char **, int);
void insertion(char **, int);
void bubble(char **, int);
void rFile(char *[], FILE **, int *);

int main(int argc, char *argv[]){
    char *a;
    int i, ctr = 0;
    FILE *f;

    rFile(argv, &f, &i);
    i--;
    if(i>=3000){
        printf("El archivo tiene %d caracteres. \n", i);
        ctr = crearA(&a, i);
    }else{
        printf("El programa no puede ser ejecutado si el archivo no tiene al menos de 3000 caracteres.\n Caracteres actuales: %d \n", i);
    }

    if(ctr){
        llenarA(f, &a, i);
        impA(&a, i);
        //bubble(&a, i);
        //selection(&a, i);
        insertion(&a, i);
        impA(&a, i);
        destA(&a);
    }

    return 0;
}

void rFile(char **argv, FILE **a, int *n){
    if(argv[1]==NULL)
        *a = fopen("TEXTO.txt", "r");
    else
        *a = fopen(argv[1], "r");

    char c;
    while((c=fgetc(*a))!=EOF){
        (*n)++;
    }
    rewind(*a);
}

void llenarA(FILE *f, char **a, int m){
    for(int j=0; j<m; j++)
        *(*a+j) = fgetc(f);
}

int crearA(char **a, int m){
    int i;
    *a = (char *)malloc(m*sizeof(char));
    if(*a == NULL){
        puts("No se reservo la memoria");
        return 0;
    }
    return 1;
}

void impA(char **a, int m){
    int i;
    for(i = 0; i < m; i++)
        //if(((*(*a+i))!=10) && ((*(*a+i))!=32))
            printf("%c", *(*a+i));
    puts("\n");
}

void destA(char **a){
    free(*a);
    *a = NULL;
}

void swap(char **a, int i, int j){
    char t;
    t = *(*a+i);
    *(*a+i) = *(*a+j);
    *(*a+j) = t;
}

void selection(char **a, int m){
    int i, j, piv;
    for(i = 0; i < m; i++){
        piv = i;
        for(j = i; j < m; j++){
            if(*(*a+piv) > *(*a+j)){
               piv = j;
            }
        }
        swap(a, i, piv);
    }
}

void insertion(char **a, int m){
    int i, j;
    char t;
    for(i = 1; i < m; i++){
        t = *(*a+i);
        for(j = i; j > 0 && t<*(*a+j-1); j--){
            *(*a+j) = *(*a+j-1);
        }
        *(*a+j) = t;
    }
}

void bubble(char **a, int m){
    int i, j;
    for(i = 1; i < m; i++){
        for(j = 0; j < m-i; j++){
            if(*(*a+j) > *(*a+j+1)){
               swap(a, j, j+1);
            }
        }
    }
}

