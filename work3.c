// *实验3 算数表达式求值
// 【问题描述】
// 表达式计算是实现程序设计语言的基本问题之一，也是栈应用的一个典型例子。设计一个程序，演示用算符优先法对算术表达式求值的过程。
// 【基本要求】
// 以字符序列的形式从终端输入语法正确的、不含变量的整数表达式。利用教科书表3.1给出的算符优先关系，实现对算数四则混合运算表达式的求值。
// 【测试数据】
// 教科书3-1的算术表达式3*(7-2)，以及以下表达式：
// 8;
// 1+2+3+4;
// 88–1*5;
// 1024/4*8;
// 1024/(4*8);
// (20+2)*(6/2);
// 3–3–3;
// 8/(9-9);
// 2*(6+2*(3+6*(6+6)));
// (((6+6)*6+3)*2+6)*2;
// 【实现提示】
// (1)设置运算符栈和运算数栈辅助分析算符优先关系。
// (2)可以参考教科书例3-1以熟悉在求值中运算符栈、运算数栈、输入字符和主要操作的变化过程。
// (3)在读入表达式的字符序列的同时，需要完成运算符和运算数（整数）的识别处理，以及相应的运算。
// (4)在程序的适当位置输出运算符栈、运算数栈、输入字符和主要操作的内容。
// */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT  50

// 定义字符栈的结构体，用于存放运算符
typedef struct {
    char* base;
    char* top;
    int stacksize;
} CharStack;
// 定义浮点栈的结构体，用于存放运算值
typedef struct {
    float* base;
    float* top;
    int stacksize;
} FloatStack;

// 初始化字符栈
void InitCharStack(CharStack *S) {
    S->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
    if (!S->base) {
        printf("内存分配失败\n");
        exit(1);
    }
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
}

// 初始化浮点数栈
void InitFloatStack(FloatStack *S) {
    S->base = (float *)malloc(STACK_INIT_SIZE * sizeof(float));
    if (!S->base) {
        printf("内存分配失败\n");
        exit(1);
    }
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
}

// 压入字符栈
void PushChar(CharStack *S, char c) {
    if (S->top - S->base >= S->stacksize) {
        S->base = (char *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(char));
        if (!S->base) {
            printf("内存扩展失败\n");
            exit(1);
        }
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *(S->top++) = c;
}

// 压入浮点数栈
void PushFloat(FloatStack *S, float f) {
    if (S->top - S->base >= S->stacksize) {
        S->base = (float *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(float));
        if (!S->base) {
            printf("内存扩展失败\n");
            exit(1);
        }
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *(S->top++) = f;
}

// 弹出字符栈
char PopChar(CharStack *S) {
    if (S->top == S->base) {
        printf("栈为空，无法弹出\n");
        return '\0';
    }
    return *(--S->top);
}

// 弹出浮点数栈
float PopFloat(FloatStack *S) {
    if (S->top == S->base) {
        printf("栈为空，无法弹出\n");
        return 0;
    }
    return *(--S->top);
}

// 获取字符栈顶元素
char GetTopChar(CharStack *S) {
    if (S->top == S->base) {
        printf("栈为空\n");
        return '\0';
    }
    return *(S->top - 1);
}

// 获取浮点数栈顶元素
float GetTopFloat(FloatStack *S) {
    if (S->top == S->base) {
        printf("栈为空\n");
        return 0;
    }
    return *(S->top - 1);
}

// 销毁字符栈
void DestroyCharStack(CharStack *S) {
    if (S->base) {
        free(S->base);
        S->base = NULL;
        S->top = NULL;
        S->stacksize = 0;
    }
}

// 销毁浮点数栈
void DestroyFloatStack(FloatStack *S) {
    if (S->base) {
        free(S->base);
        S->base = NULL;
        S->top = NULL;
        S->stacksize = 0;
    }
}

// 判断运算符优先级
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
        case ')':
            return 0;
        default:
            return -1;
    }
}

// 应用运算符
float applyOp(float a, float b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("Error: 分母不可为0.\n");
                exit(1);
            }
            return a / b;
        default:
            printf("Error: 运算符格式错误 %c.\n", op);
            exit(1);
    }
}

// 处理算术表达式
float evaluate(const char *expression) {
    CharStack operators;
    FloatStack operands;
    InitCharStack(&operators);
    InitFloatStack(&operands);

    for (int i = 0; expression[i] != '\0'; i++) {
        if (isspace(expression[i])) {
            continue;
        } else if (isdigit(expression[i])) {
            float val = 0;
            while (i < strlen(expression) && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            i--;
            PushFloat(&operands, val);
        } else if (expression[i] == '(') {
            PushChar(&operators, expression[i]);
        } else if (expression[i] == ')') {
            while (GetTopChar(&operators) != '(') {
                char op = PopChar(&operators);
                float val2 = PopFloat(&operands);
                float val1 = PopFloat(&operands);
                PushFloat(&operands, applyOp(val1, val2, op));
            }
            PopChar(&operators); // 弹出左括号
        } else {
            while (operators.top != operators.base && precedence(GetTopChar(&operators)) >= precedence(expression[i])) {
                char op = PopChar(&operators);
                float val2 = PopFloat(&operands);
                float val1 = PopFloat(&operands);
                PushFloat(&operands, applyOp(val1, val2, op));
            }
            PushChar(&operators, expression[i]);
        }
    }

    while (operators.top != operators.base) {
        char op = PopChar(&operators);
        float val2 = PopFloat(&operands);
        float val1 = PopFloat(&operands);
        PushFloat(&operands, applyOp(val1, val2, op));
    }

    float result = PopFloat(&operands);
    DestroyCharStack(&operators);
    DestroyFloatStack(&operands);
    return result;
}

int main() {
    for (int i = 0; i < 12; i++)
    {
        /* code */
    
    
    char expression[STACK_INIT_SIZE];    //定义一个用来承装算式的字符数组
    printf("请输入算式：");
    fgets(expression, STACK_INIT_SIZE, stdin);
    expression[strcspn(expression, "\n")] = '\0';

    float result = evaluate(expression);
    printf("结果是：%f\n", result);
      }
    return 0;
}
