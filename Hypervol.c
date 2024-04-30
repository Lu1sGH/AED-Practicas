#include <stdio.h>
#include <stdlib.h>

void crearA(int *******, int, int, int, int, int, int);
void llenarA(int ******, int, int, int, int, int, int);
void impA(int ******, int, int, int, int, int, int);
void liberarA(int *******, int, int, int, int, int, int);

int main(){
    int m = 2, n = 2, o = 2, p = 2, q = 2, r = 2;
    int ******hyper = NULL;

    crearA(&hyper, m, n, o, p, q, r);
    llenarA(hyper, m, n, o, p, q, r);
    impA(hyper, m, n, o, p, q, r);
    liberarA(&hyper, m, n, o, p, q, r);

    return 0;
}

void crearA(int *******a, int m, int n, int o, int p, int q, int r){
    int g, h, i, j, k;
    *a = (int ******)malloc(m*sizeof(int *****));
    for(g = 0; g < m; g++){
        *(*a+g) = (int *****)malloc(n*sizeof(int ****));
        for(h = 0; h < n; h++){
            *(*(*a+g)+h) = (int ****)malloc(o*sizeof(int ***));
            for(i = 0; i < o; i++){
                *(*(*(*a+g)+h)+i) = (int ***)malloc(p*sizeof(int **));
                for(j = 0; j < p; j++){
                    *(*(*(*(*a+g)+h)+i)+j) = (int **)malloc(q*sizeof(int *));
                    for(k = 0; k < q; k++){
                        *(*(*(*(*(*a+g)+h)+i)+j)+k) = (int *)malloc(r*sizeof(int));
                    }
                }
            }
        }
    }
}

void llenarA(int ******a, int m, int n, int o, int p, int q, int r){
    int g = 0, h = 0, i = 0, j = 0, k = 0, l = 0;
    for(g = 0; g < m; g++)
        for(h = 0; h < n; h++)
            for(i = 0; i < o; i++)
                for(j = 0; j < p; j++)
                    for(k = 0; k < q; k++)
                        for(l = 0; l < r; l++)
                            *(*(*(*(*(*(a+g)+h)+i)+j)+k)+l) = g*h*i*j*k*l;
}

void impA(int ******a, int m, int n, int o, int p, int q, int r){
    int g = 0, h = 0, i = 0, j = 0, k = 0, l = 0;
    for(g = 0; g < m; g++)
        for(h = 0; h < n; h++)
            for(i = 0; i < o; i++)
                for(j = 0; j < p; j++)
                    for(k = 0; k < q; k++)
                        for(l = 0; l < r; l++)
                            printf("hyper[%d][%d][%d][%d][%d][%d] = %d \n", g, h, i, j, k, l, *(*(*(*(*(*(a+g)+h)+i)+j)+k)+l));
}

void liberarA(int *******a, int m, int n, int o, int p, int q, int r){
    int g, h, i, j, k;
    for(g = 0; g < m; g++){
        for(h = 0; h < n; h++){
            for(i = 0; i < o; i++){
                for(j = 0; j < p; j++){
                    for(k = 0; k < q; k++){
                        free(*(*(*(*(*(*a+g)+h)+i)+j)+k));
                    }
                    free(*(*(*(*(*a+g)+h)+i)+j));
                }
                free(*(*(*(*a+g)+h)+i));
            }
            free(*(*(*a+g)+h));
        }
        free(*(*a+g));
    }
    free(*a);
    *a = NULL;
}
