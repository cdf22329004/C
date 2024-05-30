#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

#include <float.h>
#define MAXSTRLEN 255
//串的定长循序表示
typedef struct 
{
    char ch[MAXSTRLEN+1];
    int length;

    /* data */
}SString;

//串的堆分配存储方式
typedef struct{
   char *ch;
   int length;

}HString;

//串的块链存储表示
#define CHUNKSIZE 80
typedef struct chunk
{
    char Ch[CHUNKSIZE];
    struct chunk *next;
  
    /* data */
}Chunk;
typedef struct 
{
    Chunk *head,*tail;
    int curlen;
    /* data */
}LString;


Status Concat(SString &T,SString S1,SString S2)
{
    if (S1[0]+S2[0]<=MAXSTRLEN)
    {
     T[1..S1[0]] = S1[1..S1[0]];
     T[S1[0]+1..S1[0]+S2[0]] = S2[1..S2[0]];
     T[0] =S1[0] +S2[0];
     uncut = TRUE;

    }
    else if (S1[0]<MAXSTRLEN)
    {
        T[1..S1[0]] = S1[1..S1[0]];
        T[S1[0]+1..S1[0]+S2[0]] = S2[1..S2[0]];
        T[0] = MAXSTRLEN;
        uncut = FALSE;

            }
else {
    T[0..MAXSTRLEN] = S1[0..MAMAXSTRLEN];
    uncut= FALSE;

}
return uncut;
}
