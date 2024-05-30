#include<stdio.h>
typedef struct 
{
    float realpart;
    float imagepart;

}Complx;

void printA(Complx *A)
{printf("复数A=%f+i%f",A->realpart,A->imagepart);

}
void printB(Complx *B)
{
    printf("复数B=%f+i%f",B->realpart,B->imagepart);
}
void assign(Complx *A, float real, float image)
{
    printf("请输入实部");
    scanf("%f",&real);
    printf("请输入虚部");
    scanf("%f",&image);
    A->realpart=real;
    A->imagepart=image;
}

void add(Complx* C,  Complx A, Complx B)
{
    C->realpart=A.realpart+B.realpart;
    C->imagepart=A.imagepart+B.imagepart;

}
void dimi(Complx*A_B,Complx A,Complx B)
{
    A_B->realpart=A.realpart-B.realpart;
    A_B->imagepart=A.imagepart-B.imagepart;
}
void mutiply(Complx  *D,Complx A,Complx B)   //D为A*B的指针
{
    D->realpart=A.realpart*(B.realpart)-A.imagepart*(B.imagepart);
    D->imagepart=A.realpart*(B.imagepart)+A.imagepart*(B.realpart);
    
}
void GE(Complx *E,Complx A)             //E为A的共轭
{
    E->realpart=A.realpart;
    E->imagepart=(-1)*A.imagepart;
}
void divide(Complx *F,Complx A,Complx B) //F为A/B值的指针
{
    Complx *B_,D,U;                     //B_为B的共轭，D为B*B_；U为A*B_
    void GE(Complx *E,Complx A);
    void mutiply(Complx  *D,Complx A,Complx B);
    GE(B_,B);
    mutiply(&D,B,*B_);
    if (D.realpart==0&D.imagepart==0)
    {printf("\n0复数相除分母不可以为0,无意义，请重新输入！");
    };
    mutiply(&U,A,*B_);
    F->realpart=(U.realpart)/(D.realpart);
    F->imagepart=(U.imagepart)/(D.realpart);

}
void Getreal(Complx A)
{   
    printf("该复数A的实部为：%f",A.realpart);

}
void Getimage(Complx A)
{
    printf("该复数A的虚部为：%f",A.imagepart);
}

int main()
{
Complx A,B,B_,C,D,E,F,A_B;

printf("复数A:");
assign(&A,0,0);
printf("复数B:");
assign(&B,0,0);

printA(&A);
printf("\n");
printB(&B);
GE(&B_,B);
dimi(&A_B,A,B);
add(&C,A,B);
mutiply(&D,A,B);
divide(&F,A,B);

printf("\n");
printf("复数A、B的和C=%f+i%f",C.realpart,C.imagepart);
printf("\n");
printf("复数A、B的差A_B=%f+i%f",A_B.realpart,A_B.imagepart);
printf("\n");
printf("复数A、B的积为D=%f+i%f",D.realpart,D.imagepart);
printf("\n");
printf("复数A、B的商为F=%f+i%f",F.realpart,F.imagepart);
printf("\n");
printf("复数B的共轭B_=%f+i%f",B_.realpart,B_.imagepart);
printf("\n");
Getreal(A);
Getimage(A);

}
