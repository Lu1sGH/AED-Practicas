#include <stdio.h>
#include <stdlib.h>

void quick(int *, int, int);
void swap(int *, int, int);
void quickI(int *, int);

int main(){
    int i, j, N=10;
    int *a = (int *)malloc(N*sizeof(int));
    for(i=0, j=N; i<N; i++, j--){
        a[i] = j;
        printf("%d ", a[i]);
    } puts("");

    //quick(a, 0, N-1);
    quickI(a, N);

    for(i=0; i<N; i++){
        printf("%d ", a[i]);
    } puts("");


    return 0;
}

void quick(int *a, int m, int n){
    if(m>=n) return;
    int piv, i, j;

    piv = n;
    j = m-1;

    for(i = m; i <= n; i++){
        if(a[i] <= a[piv]){
            j++;
            if(i>j){
                swap(a, i, j);
            }
        }
    }

    quick(a, m, j-1);
    quick(a, j+1, n);
}

void swap(int *a, int i, int j){
    int t;
    t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void quickI(int *a, int N){
    if(a==NULL) return;
    int *pivs=(int*)malloc(N*sizeof(int));
    int k=1, i=0, j=0, n=N-1, m=0, piv=0;
    pivs[0]=0; pivs[1]=n;
    while(k>=0){
        n=pivs[k--];
        m=pivs[k--];
        j=m-1;piv=n;
        for(i=m; i<=n; i++){
            if(a[i] <= a[piv]){
                j++;
                if(i>j) swap(a, i, j);
            }
        }
        if(j-1>m){
            pivs[++k] = m;
            pivs[++k] = j-1;
        }
        if(j+1<n){
            pivs[++k]=j+1;
            pivs[++k]=n;
        }
    }

    free(pivs);
}
