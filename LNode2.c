#include <stdio.h>
#include <stdlib.h>

// 定义多项式的结点结构
struct Node {
    float coefficient; // 系数
    float exponent;    // 指数
    struct Node *next; // 指向下一个结点的指针
};

// 创建多项式
struct Node *createPolynomial() {
    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
    if (head == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    head->next = NULL; // 初始时链表为空

    int n;
    printf("输入多项式项数: ");
    scanf("%d", &n);

    struct Node *current = head;
    for (int i = 0; i < n; i++) {
        int coefficient, exponent;
        printf("依次输入 系数 and 指数  %d: ", i + 1);
        scanf("%d %d", &coefficient, &exponent);

        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        newNode->coefficient = coefficient;
        newNode->exponent = exponent;
        newNode->next = NULL;

        current->next = newNode;
        current = current->next;
    }
    return head;
}

// 输出多项式
void displayPolynomial(struct Node *head) {
    struct Node *current = head->next; // 跳过头结点
    if (current == NULL) {
        printf("多项式为空.\n");
        return;
    }

    printf("多项式为: ");
    while (current != NULL) {
        printf("%f,%f", current->coefficient, current->exponent);
        current = current->next;
        if (current != NULL) {
            printf(",");
        }
    }
    printf("\n");
}

// 多项式相加
struct Node *addPolynomials(struct Node *poly1, struct Node *poly2) {
    struct Node *result = (struct Node *)malloc(sizeof(struct Node));
    if (result == NULL) {
        printf(" failed.\n");
        exit(1);
    }
    result->next = NULL;

    struct Node *current1 = poly1->next;
    struct Node *current2 = poly2->next;
    struct Node *currentResult = result;

    while (current1 != NULL && current2 != NULL) {
        if (current1->exponent > current2->exponent) {
            currentResult->next = current1;
            current1 = current1->next;
        } else if (current1->exponent < current2->exponent) {
            currentResult->next = current2;
            current2 = current2->next;
        } else {
            // 指数相等，系数相加
            int sum = current1->coefficient + current2->coefficient;
            if (sum != 0) {
                struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
                if (newNode == NULL) {
                    printf(" failed.\n");
                    exit(1);
                }
                newNode->coefficient = sum;
                newNode->exponent = current1->exponent;
                newNode->next = NULL;
                currentResult->next = newNode;
                currentResult = currentResult->next;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    // 处理剩余的结点
    while (current1 != NULL) {
        currentResult->next = current1;
        current1 = current1->next;
        currentResult = currentResult->next;
    }
    while (current2 != NULL) {
        currentResult->next = current2;
        current2 = current2->next;
        currentResult = currentResult->next;
    }

    return result;
}

// 多项式相减
struct Node *subtractPolynomials(struct Node *poly1, struct Node *poly2) {
    struct Node *result = (struct Node *)malloc(sizeof(struct Node));
    if (result == NULL) {
        printf(" failed.\n");
        exit(1);
    }
    result->next = NULL;

    struct Node *current1 = poly1->next;
    struct Node *current2 = poly2->next;
    struct Node *currentResult = result;

    while (current1 != NULL && current2 != NULL) {
        if (current1->exponent > current2->exponent) {
            currentResult->next = current1;
            current1 = current1->next;
        } else if (current1->exponent < current2->exponent) {
            currentResult->next = current2;
            current2 = current2->next;
        } else {
            // 指数相等，系数相减
            int diff = current1->coefficient - current2->coefficient;
            if (diff != 0) {
                struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
                if (newNode == NULL) {
                    printf(" failed.\n");
                    exit(1);
                }
                newNode->coefficient = diff;
                newNode->exponent = current1->exponent;
                newNode->next = NULL;
                currentResult->next = newNode;
                currentResult = currentResult->next;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    // 处理剩余的结点
    while (current1 != NULL) {
        currentResult->next = current1;
        current1 = current1->next;
        currentResult = currentResult->next;
    }
    while (current2 != NULL) {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf(" failed.\n");
            exit(1);
        }
        newNode->coefficient = -current2->coefficient; // 对减数的系数取相反数
        newNode->exponent = current2->exponent;
        newNode->next = NULL;
        currentResult->next = newNode;
        currentResult = currentResult->next;
        current2 = current2->next;
    }

    return result;
}

// 求多项式的导数
struct Node *derivative(struct Node *poly) {
    struct Node *result = (struct Node *)malloc(sizeof(struct Node));
    if (result == NULL) {
        printf(" failed.\n");
        exit(1);
    }
    result->next = NULL;

    struct Node *current = poly->next;
    struct Node *currentResult = result;

    while (current != NULL) {
        // 求导数：系数乘以指数，指数减一
        if (current->exponent != 0) {
            struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
            if (newNode == NULL) {
                printf(" failed.\n");
                exit(1);
            }
            newNode->coefficient = current->coefficient * current->exponent;
            newNode->exponent = current->exponent - 1;
            newNode->next = NULL;
            currentResult->next = newNode;
            currentResult = currentResult->next;
        }
        current = current->next;
    }

    return result;
}

// 释放多项式链表的内存
void freePolynomial(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Node *poly1 = NULL;
    struct Node *poly2 = NULL;

    printf("Creating 多项式 1:\n");
    poly1 = createPolynomial();
    displayPolynomial(poly1);

    printf("\nCreating 多项式 2:\n");
    poly2 = createPolynomial();
    displayPolynomial(poly2);

    printf("\nAdding :\n");
    struct Node *sum = addPolynomials(poly1, poly2);
    displayPolynomial(sum);

    printf("\nSubtracting :\n");
    struct Node *difference = subtractPolynomials(poly1, poly2);
    displayPolynomial(difference);

    printf("\nDerivative  1:\n");
    struct Node *derivativePoly = derivative(poly1);
    displayPolynomial(derivativePoly);

    // 释放内存
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(sum);
    freePolynomial(difference);
    freePolynomial(derivativePoly);

    return 0;
}
