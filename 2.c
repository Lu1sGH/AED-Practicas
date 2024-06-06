#include <stdio.h>
#include <stdlib.h>

void lanzar(int *, int, int, int*, int);
void hacerPliegues();
void pirueta(int);

int main(){

    return 0;
}

void lanzar(int *torre, int m, int n, int *fran, int M){
    if(m>n) return;
    int i,j,k;

    for(i=1, j=5; i <= 6; i++, j--){
        lanzar(torre, m+(i-1)*((n-m+1)/6), n-j*((n-m+1)/6), fran, M);
        hacerPliegues();
    }

    if(m==n){
        for(k = 0; k < M; k++) pirueta(torre[m]);
        fran[rand()%3] = torre[m];
    }
}

void hacerPliegues(){
    return;
}

void pirueta(int n){
    return;
}
