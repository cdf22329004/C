#include <stdio.h>
#include <stdlib.h>
// #define LIST_INIT_SIZE 100
// #define LISTINCREMENT 10
// typedef struct 
// {
//     int *elem;
//     int length;
//     int listsize;

//     /* data */
// }SqList;

typedef struct LNode
{
    int xdate;
    int zdate;
    struct LNode *next;
    /* data */
}LNode;

void creat_a()
{
    int i;
    int n;
    printf("该多项式a的项数为：");
    scanf("%d",&n);
    struct LNode a[n];
    printf("请依由低到高次输入各项系数指数，常数项为0次：");
    for ( i = 0; i < n; i++)
    {   
        printf("第%d项：",i);
        scanf("%d",&a[i].xdate);
        scanf("%d",&a[i].zdate);/* code */
    }
    printf("多项式a表示如下：%d",n);
    for ( i = 0; i < n; i++)
    {
        printf(" %d,%d",a[i].xdate,a[i].zdate);
       
    }
    
    
}
void creat_b()
{
    int i;int n;
    printf("该多项式b的项数为：");
    scanf("%d",&n);
    struct LNode b[n];
    printf("请依由高到低次输入各项系数指数：");
    for ( i = 0; i < n; i++)
    {   
        printf("第%d项：",i);
        scanf("%d",&b[i].xdate);
        scanf("%d",&b[i].zdate);/* code */
    }
    printf("多项式b表示如下：%d",n);
    for ( i = 0; i < n; i++)
    {
        printf(" %d,%d",b[i].xdate,b[i].zdate);
       
    }
    
}

void add()
{

}
int main()
{
    creat_a();
    creat_b();
    // printf("a:%d",a[]);

}



 
