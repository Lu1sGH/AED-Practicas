#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int crearA(char **, int);
void destA(char **);
void impA(char **, int);
void llenarA(FILE *, char **, int);
void quick(char **, int, int);
void swap(char **, int, int);
void merge(char **, int, int);
void recomb(char **, int, int, int);
void mergeIter(char **, int);
void rFile(char *[], FILE **, int *);

int main(int argc, char **argv){
    int n, maxI, ctr = 0;
    char *a;
    FILE *file;

    rFile(argv, &file, &n);
    maxI = n-1;

    if(n >= 3000 || 1){
        printf("El archivo tiene %d caracteres. \n", n);
        ctr = crearA(&a, n);
    }else{
        printf("El programa no puede ser ejecutado si el archivo no tiene al menos de 3000 caracteres.\n Caracteres actuales: %d \n", n);
    }

    if(ctr){
        llenarA(file, &a, n);
        impA(&a, n);
        //quick(&a, 0, maxI);
        //merge(&a, 0, maxI);
        mergeIter(&a, n);
        impA(&a, n);
        destA(&a);
    }

    return 0;
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
    for(i = 0; i < m; i++){
        //if(((*(*a+i))!=10) && ((*(*a+i))!=32))
        printf("%c", *(*a+i));
    }
    puts("\n");
}

void destA(char **a){
    free(*a);
    *a = NULL;
}

void llenarA(FILE *f, char **a, int m){
    for(int j=0; j<m; j++)
        *(*a+j) = fgetc(f);
}

void quick(char **a, int m, int n){
    if((n >= 0) && (m <= n)){
        int piv, i, j;

        piv = n;
        j = m-1;

        for(i = m; i <= n; i++){
            if(*((*a)+i) <= *((*a)+piv)){
                j++;
                if(i>j){
                    swap(a, i, j);
                }
            }
        }

        quick(a, m, j-1);
        quick(a, j+1, n);

    }
}

void swap(char **a, int i, int j){
    char t;
    t = *(*a+i);
    *(*a+i) = *(*a+j);
    *(*a+j) = t;
}

void merge(char **a, int m, int n){
    if(m!=n){

        int mitad = m + (n-m)/2;

        merge(a, m, mitad);
        merge(a, mitad+1, n);

        recomb(a, m, mitad, n);

    }
}

void recomb(char **a, int m, int mitad, int n) {
    int i, j, k, tam = n - m + 1;
    char *aux = (char *)malloc(tam * sizeof(char));

    if (aux != NULL) {
        for (k = 0, i = m, j = mitad + 1; k < tam; k++) {
            if (i <= mitad && (j > n || (*a)[i] <= (*a)[j])) {
                aux[k] = (*a)[i];
                i++;
            } else {
                aux[k] = (*a)[j];
                j++;
            }
        }

        for (i = 0; i < tam; i++)
            (*a)[m + i] = aux[i];

        free(aux);
    } else {
        puts("HA OCURRIDO UN ERROR AL ASIGNAR MEMORIA CON MALLOC");
    }
}

void mergeIter(char **a, int n){
    int mitad = 0, av = 0, i = 0, j = 0, k=1, taux = 0;

    for(av = 2; av < n; av *= 2){
        for(k = 0; av+k-1 < n; k += av){
            i = k;
            j = av+k-1;
            mitad =(i+j)/2;
            recomb(a, i, mitad, j);
        }
        recomb(a, k, n-2-taux, n-1); //toma la mitad de acuerdo al tamaño de la ultima combinacion
        taux = n-1-k; // calcula el tamaño de la combinacion realizada
    }

    recomb(a, 0, k-1, n-1);
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
