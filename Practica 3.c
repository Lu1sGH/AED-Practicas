#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int crearA(int **, int);
void destA(int **);
void impA(int **, int);
void llenarA(int **, int);
void quick(int **, int, int);
void swap(int **, int, int);
void merge(int **, int, int);
void recomb(int **, int, int, int);
void mergeIter(int **, int);

int main(){
    int *a, n = 16, maxI = n-1;

    crearA(&a, n);
    llenarA(&a, n);
    impA(&a, n);
    //quick(&a, 0, maxI);
    merge(&a, 0, maxI);
    mergeIter(&a, n);
    impA(&a, n);
    destA(&a);

    return 0;
}


int crearA(int **a, int m){
    int i;
    *a = (int *)malloc(m*sizeof(int));
    if(*a == NULL){
        puts("No se reservo la memoria");
        return 0;
    }
    return 1;
}

void impA(int **a, int m){
    int i;
    for(i = 0; i < m; i++)
            printf("%d ", *(*a+i));
    puts("\n");
}

void destA(int **a){
    free(*a);
    *a = NULL;
}

void llenarA(int **a, int m){
    srand(time(NULL));
    //int b[10] = {3, 2, 5, 0, 1, 8, 7, 6, 9, 4};
    for(int i = 0; i < m; i++)
        *((*a)+i) = rand()%11;
        //*((*a)+i) = b[i];
}

void quick(int **a, int m, int n){
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

void swap(int **a, int i, int j){
    int t;
    t = *(*a+i);
    *(*a+i) = *(*a+j);
    *(*a+j) = t;
}

void merge(int **a, int m, int n){
    if(m!=n){

        int mitad = m + (n-m)/2;

        merge(a, m, mitad);
        merge(a, mitad+1, n);

        recomb(a, m, mitad, n);

    }
}

void recomb(int **a, int m, int mitad, int n) {
    int i, j, k, tam = n - m + 1;
    int *aux = (int *)malloc(tam * sizeof(int));

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

void mergeIter(int **a, int n){
    int mitad, av, i, j, k;
    for(av = 2; av < n; av *= 2){
        for(k = 0; av+k-1 < n; k += av){
            i = k;
            j = av+k-1;
            mitad = (i+j)/2;
            recomb(a, i, mitad, j);
        }
    }
    if((av/2) < n)
        recomb(a, 0, av/2, n-1);
}
