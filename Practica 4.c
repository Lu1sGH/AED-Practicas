#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define VERDADERO		1
#define FALSO			0
#define CARTESIANO		1
#define POLAR			0

// TAD: tipo abstracto de datos numero complejo:

typedef struct complejo
{
	float real;
	float imaginario;
	float magnitud;
	float argumento;
}t_complejo, *Complejo;

// t_complejo = (struct complejo)
// Complejo =   (struct complejo *)
// Complejo *=  (struct complejo **)


// int *arr= (int *) malloc(N*sizeof(int));

// struct complejo *c= (struct complejo *) malloc(1*sizeof(struct complejo));

// Complejo c= (Complejo) malloc(sizeof(t_complejo));

// i= sqrt(-1);
// z= real + i imaginario;			z= x+iy;
// z= magnitud*exp(i*argumento);	z= r*exp(i*arg);

Complejo crearNumeroComplejo(float a, float b, int formato);
int crearNumeroComplejoReferencia(Complejo *z, float a, float b, int formato);
void imprimirNumeroComplejo(Complejo z, int formato);
int destruirNumeroComplejo(Complejo *z);

Complejo raiz(int, int);
void impRcs(int);

void crearA(Complejo ***, int, int);
void impA(Complejo **, int, int);
void freeA(Complejo ***, int, int);

int main(int argc, char *argv[])
{
    int n = 0;
    puts("Cuantas raices quiere obtener?");
    do{
        scanf("%d", &n);
        if(n==0)
            puts("El numero no puede ser 0.");
    }while(n==0);

    impRcs(n);

	return 0;
}

Complejo crearNumeroComplejo(float a, float b, int formato)
{
	Complejo z= NULL;	// declaracion de una variable de estructura

	// crear dinamicamente la estructura:
	z= (Complejo) malloc(sizeof(t_complejo));

	// verificacion de consistencia:
	if (z==NULL)
	  return(NULL);

	// asignacion de valores a los atributos segun formato:
	if (formato==CARTESIANO)
	  {
	  	// asignacion directa:
		z->real= a;				// x= a
		z->imaginario= b;		// y= b

		// conversion:
		z->magnitud= sqrt(a*a+b*b);		// r= sqrt(x^2+y^2)
		z->argumento= atan2(b,a);		// arg= atan(y/x)
	  }
	else
	  {
	  	z->magnitud= a;			// r= a
	  	z->argumento= b;		// arg= b

	  	z->real= a*cos(b);			// x= r*cos(arg);
	  	z->imaginario= a*sin(b);	// y= r*sin(arg);
	  }

	// regresar el valor:
	return(z);
}

int crearNumeroComplejoReferencia(Complejo *z, float a, float b, int formato)
{
	Complejo c= NULL;

	// creacion convencional:
	c= crearNumeroComplejo(a, b, formato);

	if (c==NULL)
	  {
	  	*z= NULL;
	  	return(FALSO);
	  }

	// acceder al contenido de la referencia:
	*z= c;

	return(VERDADERO);
}

void imprimirNumeroComplejo(Complejo z, int formato)
{
	if (z==NULL)
	  return;

	if (formato==CARTESIANO)
	  printf("%0.4f + i %0.4f\n", z->real, z->imaginario);
	else
	  printf("%0.4f e^(i %0.4f PI)\n", z->magnitud, z->argumento/M_PI);
}

int destruirNumeroComplejo(Complejo *z)
{
	if (*z==NULL)
	  return(FALSO);

	// liberar antes contenido de la estructura si es necesario

	free(*z);

	// asignacion del valor NULL al contenido del apuntador:
	*z= NULL;

	return(VERDADERO);
}

Complejo raiz(int k, int n){
    float r=0.0, a=0.0;

    Complejo z = NULL;

    crearNumeroComplejoReferencia(&z, 1.0, 0.0, CARTESIANO);
    if(z==NULL) return NULL;

    z->argumento = ((2*k)*M_PI)/n;

    r = z->magnitud;
    a = z->argumento;

    //CONVERSION
    z->real = r*cos(a);
    z->imaginario = r*sin(a);

    return z;
}

void impRcs(int n){
    Complejo *a1, **a2;

    a1 = (Complejo *)malloc(n*sizeof(Complejo));
    crearA(&a2, n, n);
    if(a1==NULL){puts("En este momento no se pueden imprimir las raices"); return;}

    int i, j;
    for(i = 0; i<n; i++){
        *(a1+i) = raiz(i, n);
    }

    for(i = 0; i<n; i++){
        printf("z[%d] = ", i);
        imprimirNumeroComplejo(a1[i], POLAR);
        printf("\n");
    }

    for(i = 0; i<n; i++){
        for(j = 0; j<n; j++){
            a2[i][j] = a1[(i+j)%n];
        }
    }

    impA(a2, n, n);

    for(i = 0; i<n; i++){
        destruirNumeroComplejo(a1+i);
    }
    free(a1);

    freeA(&a2, n, n);
}

void crearA(Complejo ***a, int m, int n){
    int i;
    *a = (Complejo **)malloc(m*sizeof(Complejo *));
    for(i = 0; i<m; i++){
        *(*a+i) = (Complejo *)malloc(n*sizeof(Complejo));
        if(*(*a+i) == NULL){
            for(int k; k<i; k++){
                free(*(*a+k));
            }
            free(*a);
            *a = NULL;
            return;
        }
    }
}

void impA(Complejo **a, int m, int n){
    int i, j;
    for(i = 0; i<m; i++){
        for(j = 0; j<n; j++){
            printf("Mult[%d][%d] = ", i, j);
            imprimirNumeroComplejo(a[i][j], POLAR);
        }
        printf("\n");
    }
}

void freeA(Complejo ***a, int m, int n){
    int i;
    for(i = 0; i<m; i++){
        free(*(*a+i));
    }
    free(*a);
    *a = NULL;
}
