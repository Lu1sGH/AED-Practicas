#include <stdio.h>
#include <stdlib.h>

void lanzar(int *, int, int, int*, int);
void hacerPliegues();
void pirueta(int);

int main(){
    int N = 6;
    int a[6] = {0};
    int b[3] = {0};
    lanzar(a, 0, N-1, b, 5);

    return 0;
}

void lanzar(int *torre, int m, int n, int *fran, int M){
    int i,j, par;
    
    if(m==n){
        for(j = 0; j < M; j++) pirueta(torre[m]);
        fran[rand()%3] = torre[m];
        return;
    }
    
    par = (n-m+1)/6;

    for(i=1; i <= 6; i++){
        lanzar(torre, m + (i-1)*par, m + i*par, fran, M);
        hacerPliegues();
    }
    
    
}

void hacerPliegues(){
    return;
}

void pirueta(int n){
    return;
}
