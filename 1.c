#include <stdio.h>

int main(){

    int a=1, b=1, c=2, d=3, e=4, f=5;
    int *x, *y, *z;
    int **u, **v, **w;

    x=&f; y=&e; z=&d;
    a *= *z;
    b += *y-42;
    c -= 13*(*x);
    u = &x; y = *u; *y = 3*f;
    v = &y; w = &z; u = w; w = v; v = &x;
    **u = a+1; **v = b+2; **w = c+3;
    printf("(%x) a=%d \n(%x) b=%d \n(%x) c=%d \n(%x) d=%d \n(%x) e=%d \n(%x) f=%d \n", &a, a, &b, b, &c, c, &d, d, &e, e, &f, f);
    printf("(%x) x=%x \n(%x) y=%x  \n(%x) z=%x \n", &x, x, &y, y, &z, z);
    printf("u=%x v=%x w=%x \n", u, v, w);
    return 0;
}

