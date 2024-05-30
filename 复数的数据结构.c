#include<stdio.h>
typedef struct {
    float realpart;
    float imagpart;
}Complex;

void asign(Complex* A,float real,float image);
void add(Complex* C,const Complex A,const Complex B);
void minus(Complex* C,const Complex A,const Complex B);
void multiply(Complex* C,const Complex A,const Complex B);
void divide(Complex*C,const Complex A,const Complex B);

void asign(Complex* A,float real,float image)
{
    A->realpart=real;
    A->imagpart=image;
}
void add(Complex* C,const Complex A,const Complex B)
{
    C->realpart=A.realpart+B.realpart;
    C->imagpart=A.imagpart+B.imagpart;
}
void minus(Complex* C,const Complex A,const Complex B)
{
    C->realpart=A.realpart-B.realpart;
    C->imagpart=A.imagpart-B.imagpart;
}
void multiply(Complex* C,const Complex A,const Complex B)
{
    C->realpart=A.realpart*B.realpart-A.imagpart*B.imagpart;
    C->imagpart=A.realpart*B.imagpart+A.imagpart*B.realpart;
}
void divide(Complex* C,const Complex A,const Complex B)
{
    C->realpart=(A.realpart*B.realpart+A.imagpart*B.imagpart)/(B.realpart*B.realpart+B.imagpart*B.imagpart);
    C->imagpart=(B.realpart*A.imagpart-A.realpart*B.imagpart)/(B.realpart*B.realpart+B.imagpart+B.imagpart);
}
int main()
{
    Complex A;
    Complex C;
    float real=1.1;
    float image=0.9;
    asign(&A,real,image);
    multiply(&C,A,A);
    printf("Realpart is %f\nImagpart is %f\n",A.realpart,A.imagpart);
    printf("C.Realpart=%f\nC.Imagpart=%f",C.realpart,C.imagpart);
}