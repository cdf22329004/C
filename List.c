#include <stdio.h>
#define MAX 50
typedef struct 
{
   int date[MAX];
   int length; /* data */
}List;

void InitList(List *L)
{
    
    L->length=0;

}

int Insert(List *L,int idex,int element)
{
    if (idex<0||idex>L->length||L->length==MAX)
    {
        return 0;/* code */
    }
    for (int i= L->length-1;i>= idex-1; i--)
    {
        L->date[i+1]=L->date[i];/* code */
    };
    L->date[idex]=element;
    L->length++;
    return 1;
}

void printList(List *L)
{
    
    printf("List is :");
    for ( int i = 0; i <=L->length-1; i++)
    {
        printf("  %d",L->date[i]);/* code */
    };
    printf("\n");
    
}





int main()
{
    List L;
    InitList(&L);
    
    Insert(&L,0,4);
    Insert(&L,1,6);
    Insert(&L,2,8);
    printList(&L);


}
