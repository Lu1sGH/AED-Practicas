#include <stdio.h>
#include <stdlib.h>

void lanzar(int *, int, int, int*, int);
void hacerPliegues();
void pirueta(int);

int main(){
  
    int a[7] = {1, 2, 3, 4, 5, 6, 7};
    int b[3] = {0};
    lanzar(a, 0, 6, b, 5);

    return 0;
}

void lanzar(int *torre, int m, int n, int *fran, int M){
    if(m>n) return;
    int i,j, par;
    
    par = (n-m+1)/6;

    for(i=1; i <= 6; i++){
        lanzar(torre, m+(i-1)*par+1, m+(i)*par, fran, M);
        hacerPliegues();
    }
    
    if(m==n){
        for(j = 0; j < M; j++) pirueta(torre[m]);
        fran[rand()%3] = torre[m];
    }
}

void hacerPliegues(){
    return;
}

void pirueta(int n){
    return;
}
