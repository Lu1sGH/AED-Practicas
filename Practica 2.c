#include <stdio.h>
#include <stdlib.h>

int consTab(int ***, int);
void destTab(int ***, int);
void initTab(int ***, int);
void impTab(int ***, int);
void bloqCas(int ***, int);
void asigQ(int ***, int, int, int *, int *);
int verDisp(int ***, int, int, int);

int main(){
    int **a, n = 0, ctr, nComb=0, reinas = 0, flg;

    puts("PROBLEMA DE LAS N REINAS");
    puts("Ingrese el num de reinas para el que se quiere resolver el problema:");
    scanf(" %d", &n);
    printf("El problema se resolvera para %d reinas. \n", n);

    if(consTab(&a, n)){
        initTab(&a, n);
        system("pause");
        impTab(&a, n);

        printf("%cDesea bloquear casillas? \n 1=Si \n 0=No \n", 168);
        scanf(" %d", &flg);
        if(flg) bloqCas(&a, n);

        asigQ(&a, n, 0, &nComb, &reinas);
        impTab(&a, n);
        printf("Num. de combinaciones: %d.\n", nComb);
        destTab(&a, n);
    }else{
        printf("No se pudo reservar el suficiente espacio en memoria. \n");
    }


    return 0;
}

int consTab(int ***a, int n){
    *a = (int **)malloc(n*sizeof(int*));
    if(*a != NULL){
        for(int i = 0; i < n; i++){
            *(*a+i) = (int *)malloc(n*sizeof(int));
            if(*(*a+i) == NULL){
                destTab(a, i);
                return 0;
            }
        }
    }else{
        return 0;
    }

    return 1;
}

void destTab(int ***a, int n){
    for(int i = 0; i < n; i++){
        free(*(*a+i));
    }
    free(*a);
    *a = NULL;
}

void initTab(int ***t, int n){
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            *(*(*t+i)+j) = 0;
}

void impTab(int ***t, int n){
    int i, j, k;

    system("cls");

    printf("%c%c", 32, 32);
    for(k = 0; k < n; k++) printf("%c%c", 65+k, 32);
    printf("\n");

    for(i = 0; i < n; i++){
        printf("%d%c", i+1, 32);
        for(j = 0; j < n; j++){
            if(!(i%2)){
                if(j%2){
                    ((*(*(*t+i)+j))==3)?printf("%c%c", 158, 32):(((*(*(*t+i)+j))==2)?printf("%c%c", 232, 32):printf("%c%c", 176, 176));
                }else{
                    ((*(*(*t+i)+j))==3)?printf("%c%c", 158, 32):((*(*(*t+i)+j))==2)?printf("%c%c", 232, 32):printf("%c%c", 178, 178);
                }
            }else{
                if(!(j%2)){
                    ((*(*(*t+i)+j))==3)?printf("%c%c", 158, 32):((*(*(*t+i)+j))==2)?printf("%c%c", 232, 32):printf("%c%c", 176, 176);
                }else{
                    ((*(*(*t+i)+j))==3)?printf("%c%c", 158, 32):((*(*(*t+i)+j))==2)?printf("%c%c", 232, 32):printf("%c%c", 178, 178);
                }
            }
        }
        printf("\n");
    }

    //system("pause");
}

void bloqCas(int ***t, int n){
    int *a, i = 0, dim = 2*n, ctr = 1, k, tamT = n*n;
    char c;

    a = (int *)malloc(dim*sizeof(int));
    if(a==NULL){
        puts("No es posible bloquear casillas en este momento");
        return;
    }

    while(ctr && i<tamT){
        puts("Ingrese las coordenadas con el siguiente formato: A1");
        for(k=0; k<2; k++){
            scanf(" %c", &c);
            if(c>48  && c<58){
                *(a+i+k) = c-49;
            }else if(c>64 && c<65+n){
                *(a+i+k) = c-65;
            }else{
                printf("%c no es una opcion valida", c);
                k--;
            }
        }

        (*t)[a[i+1]][a[i]] = 3;
        i+=2;
        puts("¿Quiere bloquear mas casillas?\n1=Si\n0=No");
        scanf("%d",&ctr);
    }

    free(a);
    impTab(t, n);
    system("pause");
}

void asigQ(int ***t, int n, int niv, int *nComb, int *nReinas){
    int i;

    if((*nReinas < n) && (niv < n)){
        for(i = 0; i<n; i++){
            if(verDisp(t, n, niv, i)){
                (*t)[niv][i] = 2;
                (*nReinas)++;
                impTab(t, n);
                asigQ(t, n, niv+1, nComb, nReinas);
                impTab(t, n);
                (*t)[niv][i] = 0;
                (*nReinas)--;
            }
        }
    }else{
        (*nComb)++;
        //char c;
        //scanf(" %c", &c);
        return;
    }
    return;
}

int verDisp(int ***t, int n, int niv, int pos){
    int i, j;

    if((*t)[niv][pos]==3)
        return 0;

    for(i = 0; i<n; i++){
        if(((*t)[i][pos]==2) || ((*t)[niv][i]==2))
            return 0;
    }

    for(i = niv, j = pos; i >= 0 && j >= 0; i--, j--){
        if((*t)[i][j]==2)
            return 0;
    }

    for(i = niv, j = pos; i < n && j < n; i++, j++){
        if((*t)[i][j]==2)
            return 0;
    }

    for(i = niv, j = pos; i >= 0 && j < n; i--, j++){
        if((*t)[i][j]==2)
            return 0;
    }

    for(i = niv, j = pos; i < n && j >= 0; i++, j--){
        if((*t)[i][j]==2)
            return 0;
    }

    return 1;
}
