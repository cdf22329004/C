// 实验4 病毒感染检测问题
// 【问题描述】
// 医学研究者最近发现了某些新病毒，通过对这些病毒的分析，得知它们的DNA序列都是环状的。现在研究者已收集了大量的病毒DNA和人的DNA数据，想快速检测出这些人是否感染了相应的病毒。为了方便研究，研究者将人的DNA和病毒DNA均表示成由一些字母组成的字符串序列，然后检测某种病毒DNA序列是否在患者的DNA序列中出现过，如果出现过，则此人感染了该病毒，否则没有感染。例如，假设病毒的DNA序列为baa，患者1的DNA序列为aaabbba，则感染；患者2的DNA序列为babbba，则未感染。（注意，本例中人的DNA序列是线性的，而病毒的DNA序列是环状的。）
// 【基本要求】
// 输入要求：多组数据，每组数据有1行，为序列A和B，A对应病毒的DNA序列，B对应人的DNA序列。A和B都为“0”时输入结束。
// 输出要求：对于每组数据输出1行，若患者感染了病毒输出“YES”，否则输出“NO”。
// 【测试数据】
// 输入样例：
// abbab abbabaab
// baa cacdvcabacsd
// abc def
// ……
// 0 0
// 输出样例：
// YES
// YES
// NO
// ……
// （其他测试数据请自行设计，总数据量不少于10。）
// 【实现提示】
// (1)使用字符串的顺序存储表示方法。
// (2)可使用BF算法或KMP算法实现字符串的模式匹配过程。
//  



// #include <cstdio>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define MAX 200


typedef struct 
{
    int len;
    char ch[MAX];
    /* data */
}SString;



void Concat(SString *T,SString *S1,SString *S2)
{
    T->len=S1->len+S2->len;
    if (T->len<=MAX)
    {
        
        for (int i = 0; i <S1->len ; i++)  //复制S1
        {
            T->ch[i]=S1->ch[i];
            /* code */
        }
        for (int i = S1->len; i < T->len; i++)//复制S2
        {
            T->ch[i]=S2->ch[i-S1->len];
            /* code */
        }
     
         printf("串联接成功！");
        printf("连接后的串为：");
        printf("%s\n",T->ch);
        /* code */
    }
    else if (S1->len<MAX&&T->len>MAX)
     {
        T->len=S1->len;
        for (int i = 0; i < S1->len; i++)
        {
            T->ch[i]=S1->ch[i];
            /* code */
        }
    }
    else
    {
        T->len=MAX;
        for (int i = 0; i < MAX; i++)
        {
            T->ch[i]=S1->ch[i];
            /* code */
        }
        
    }
    T->ch[T->len]='\0';

}

void SubString(SString Sub,SString S,int pos,int lent)
{
    if (pos<1||pos>S.len||lent<0||lent>S.len-pos+1)
     printf("ERRROR!");
    else
    {
        Sub.len=lent;
        for (int i = 0; i < pos+lent; i++)
        {
            Sub.ch[i]=S.ch[i];           /* code */
        }
        printf("Sub SUCCESS!");       
    }
}

void AssignStr(SString *T,char* chars)
{
    T->len=strlen(chars);
    // printf("字符串长度为：%d\n",T->len);
    if (T->len<MAX)
    {
      for (int i = 0; i < T->len+1; i++)
    {T->ch[i]=chars[i];} 
    printf("字符串赋予成功！\n");   
    }
    else printf("字符串过大！无法初始化！");
    
    // printf("字符串为：%s\n",T->ch);
}

void CopyStr(SString T,SString S)
{
    if(S.len>0&&S.len<MAX&&T.len==0)
    {
        for (int i = 0; i < S.len+1; i++)
        {    T.ch[i]=S.ch[i];}       
    }
    else printf("ERROR!");
}

int EmptyStr(SString S)
{
    if(S.len==0)
    return 1;
    else return -1;

}
void ShowStr(SString *S)
{
    printf("字符串的长度为:%d\n",S->len);
    printf("%s\n",S->ch);
        
    
}

int main()
{
    SString  S,S1,S2;
    char* char1=(char *)malloc(MAX*sizeof(char));
    char* char2=(char *)malloc(MAX*sizeof(char));
    if(!char1||!char2){exit(0);}
    printf("请输入char1：");
    fgets(char1,sizeof(char1),stdin);
    char1[strcspn(char1,"\n")]=0;
    printf("请输入char2：");
    fgets(char2,sizeof(char2),stdin);
    char2[strcspn(char2,"\n")]=0;
    AssignStr(&S1,char1);
    AssignStr(&S2,char2);
    
    Concat(&S,&S1,&S2);
    
    ShowStr(&S1);ShowStr(&S2); ShowStr(&S);
    free(char1);free(char2);

    return 0;




    

}