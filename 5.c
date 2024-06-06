#include <stdio.h>
void onda(int, int, int);
int objeto();
int seAtenuo(int);

int main(){

    onda(2, 5, 0);

    return 0;
}

void onda(int L, int M, int p){
    if(p>=M || objeto() || seAtenuo(p)) return;
    int i;
    for(i=0; i<L; i++){
        onda(L, M, p+1);
    }
}

int objeto(){
    return 0;
}

int seAtenuo(int p){
    return 0;
}
