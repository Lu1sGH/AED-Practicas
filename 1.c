#include <stdio.h>
#include <stdlib.h>
#include <Time.h>

void crearA(int *******, int, int, int, int, int, int);
void llenarA(int ******, int, int, int, int, int, int);
void impA(int ******, int, int, int, int, int, int);
void liberarA(int *******, int, int, int, int, int, int);
int cambioV();

int main(){
    int A = 2, B = 2, C = 2, D = 2, E = 2, F = 2;
    int ******tensor = NULL;

    crearA(&tensor, A, B, C, D, E, F);
    llenarA(tensor, A, B, C, D, E, F);
    impA(tensor, A, B, C, D, E, F);
    liberarA(&tensor, A, B, C, D, E, F);

    return 0;
}

void crearA(int *******tensor, int A, int B, int C, int D, int E, int F){
    int g, h, i, j, k;
    *tensor = (int ******)malloc(A*sizeof(int *****));
    for(g = 0; g < A; g++){
        *(*tensor+g) = (int *****)malloc(B*sizeof(int ****));
        for(h = 0; h < B; h++){
            *(*(*tensor+g)+h) = (int ****)malloc(C*sizeof(int ***));
            for(i = 0; i < C; i++){
                *(*(*(*tensor+g)+h)+i) = (int ***)malloc(D*sizeof(int **));
                for(j = 0; j < D; j++){
                    *(*(*(*(*tensor+g)+h)+i)+j) = (int **)malloc(E*sizeof(int *));
                    for(k = 0; k < E; k++){
                        *(*(*(*(*(*tensor+g)+h)+i)+j)+k) = (int *)malloc(F*sizeof(int));
                    }
                }
            }
        }
    }
}

void llenarA(int ******tensor, int A, int B, int C, int D, int E, int F){
    int g = 0, h = 0, i = 0, j = 0, k = 0, l = 0;
    for(g = 0; g < A; g++)
        for(h = 0; h < B; h++)
            for(i = 0; i < C; i++)
                for(j = 0; j < D; j++)
                    for(k = 0; k < E; k++)
                        for(l = 0; l < F; l++)
                            *(*(*(*(*(*(tensor+g)+h)+i)+j)+k)+l) = cambioV();
}

void impA(int ******tensor, int A, int B, int C, int D, int E, int F){
    int g = 0, h = 0, i = 0, j = 0, k = 0, l = 0;
    for(g = 0; g < A; g++)
        for(h = 0; h < B; h++)
            for(i = 0; i < C; i++)
                for(j = 0; j < D; j++)
                    for(k = 0; k < E; k++)
                        for(l = 0; l < F; l++)
                            printf("TENSOR[%d][%d][%d][%d][%d][%d] = %d \n", g, h, i, j, k, l, *(*(*(*(*(*(tensor+g)+h)+i)+j)+k)+l));
}

void liberarA(int *******tensor, int A, int B, int C, int D, int E, int F){
    int g, h, i, j, k;
    for(g = 0; g < A; g++){
        for(h = 0; h < B; h++){
            for(i = 0; i < C; i++){
                for(j = 0; j < D; j++){
                    for(k = 0; k < E; k++){
                        free(*(*(*(*(*(*tensor+g)+h)+i)+j)+k));
                    }
                    free(*(*(*(*(*tensor+g)+h)+i)+j));
                }
                free(*(*(*(*tensor+g)+h)+i));
            }
            free(*(*(*tensor+g)+h));
        }
        free(*(*tensor+g));
    }
    free(*tensor);
    *tensor = NULL;
}

int cambioV(){
    srand(time(NULL));
    return rand()%2;
}

