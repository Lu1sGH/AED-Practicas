#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *, int);
void merge(int *, int, int, int);

int main(){
    int i, j, N=10;

    int *a = (int *)malloc(N*sizeof(int));
    for(i=0, j=N; i<N; i++, j--){
        a[i] = j;
        printf("%d ", a[i]);
    } puts("");

    mergeSort(a, N);

    for(i=0; i<N; i++){
        printf("%d ", a[i]);
    } puts("");


    return 0;
}

void mergeSort(int *aviones, int N){
    int mitad = 0, av = 0, i = 0, j = 0, k = 1, taux = 0, n = N-1;

    for(av = 2; av < n; av *= 2){
        for(k = 0; av+k-1 < n; k += av){
            i = k;
            j = av+k-1;
            mitad = (i+j)/2;
            merge(aviones, i, mitad, j);
        }
        merge(aviones, k, n-1-taux, n);
        taux = n-k;
    }

    merge(aviones, 0, k-1, n);
}

void merge(int *a, int m, int mitad, int n) {
    int i, j, k, tam = n - m + 1;
    int *aux = (int *)malloc(tam * sizeof(int));
    if (aux == NULL) return;

    for (k = 0, i = m, j = mitad + 1; k < tam; k++) {
        if (i <= mitad && (j > n || a[i] <= a[j])) {
            aux[k] = a[i];
            i++;
        } else {
            aux[k] = a[j];
            j++;
        }
    }

    for (i = 0; i < tam; i++)
        a[m + i] = aux[i];

    free(aux);
}
