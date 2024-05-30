#include <stdio.h>
#include <stdlib.h>

// 定义多项式的项
typedef struct Node {
    float coef;   // 系数
    float expo;   // 指数
    struct Node *next;
} Node;

// 初始化多项式
Node* initPoly() {
    Node *head = (Node *)malloc(sizeof(Node));
    head->next = NULL;
    return head;
}

// 插入多项式的项
void insertPoly(Node *head, float coef, float expo) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->coef = coef;
    newNode->expo = expo;
    newNode->next = NULL;

    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// 输出多项式
void printPoly(Node *head) {
    Node *temp = head->next;
    int count = 0;
    while (temp != NULL) {
        printf("%.2fx^%.2f", temp->coef, temp->expo);
        temp = temp->next;
        if (temp != NULL) {
            printf(" + ");
        }
        count++;
    }
    printf("\nTotal number of terms: %d\n", count);
}

// 多项式相加
Node* addPoly(Node *poly1, Node *poly2) {
    Node *result = initPoly();
    Node *temp1 = poly1->next;
    Node *temp2 = poly2->next;

    while (temp1 && temp2) {
        if (temp1->expo > temp2->expo) {
            insertPoly(result, temp1->coef, temp1->expo);
            temp1 = temp1->next;
        } else if (temp1->expo < temp2->expo) {
            insertPoly(result, temp2->coef, temp2->expo);
            temp2 = temp2->next;
        } else {
            insertPoly(result, temp1->coef + temp2->coef, temp1->expo);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    while (temp1) {
        insertPoly(result, temp1->coef, temp1->expo);
        temp1 = temp1->next;
    }

    while (temp2) {
        insertPoly(result, temp2->coef, temp2->expo);
        temp2 = temp2->next;
    }

    return result;
}

// 多项式相减
Node* subtractPoly(Node *poly1, Node *poly2) {
    Node *result = initPoly();
    Node *temp1 = poly1->next;
    Node *temp2 = poly2->next;

    while (temp1 && temp2) {
        if (temp1->expo > temp2->expo) {
            insertPoly(result, temp1->coef, temp1->expo);
            temp1 = temp1->next;
        } else if (temp1->expo < temp2->expo) {
            insertPoly(result, -temp2->coef, temp2->expo);
            temp2 = temp2->next;
        } else {
            insertPoly(result, temp1->coef - temp2->coef, temp1->expo);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    while (temp1) {
        insertPoly(result, temp1->coef, temp1->expo);
        temp1 = temp1->next;
    }

    while (temp2) {
        insertPoly(result, -temp2->coef, temp2->expo);
        temp2 = temp2->next;
    }

    return result;
}

// 求多项式的导数
Node* differentiatePoly(Node *poly) {
    Node *result = initPoly();
    Node *temp = poly->next;

    while (temp) {
        if (temp->expo != 0) {
            insertPoly(result, temp->coef * temp->expo, temp->expo - 1);
        }
        temp = temp->next;
    }

    return result;
}

// 主函数
int main() {
    int terms;
    float coef, expo;
    
    printf("Enter the number of terms for Polynomial 1: ");
    scanf("%d", &terms);
    Node *poly1 = initPoly();
    printf("Enter the coefficients and exponents for Polynomial 1:\n");
    for (int i = 0; i < terms; ++i) {
        printf("Coefficient %d: ", i + 1);
        scanf("%f", &coef);
        printf("Exponent %d: ", i + 1);
        scanf("%f", &expo);
        insertPoly(poly1, coef, expo);
    }

    printf("\nEnter the number of terms for Polynomial 2: ");
    scanf("%d", &terms);
    Node *poly2 = initPoly();
    printf("Enter the coefficients and exponents for Polynomial 2:\n");
    for (int i = 0; i < terms; ++i) {
        printf("Coefficient %d: ", i + 1);
        scanf("%f", &coef);
        printf("Exponent %d: ", i + 1);
        scanf("%f", &expo);
        insertPoly(poly2, coef, expo);
    }

    printf("\nPolynomia 1: ");
    printPoly(poly1);

    printf("Polynomial 2: ");
    printPoly(poly2);

    Node *sum = addPoly(poly1, poly2);
    printf("Sum of  1 and 2: ");
    printPoly(sum);

    Node *difference = subtractPoly(poly1, poly2);
    printf("Difference of  1 and 2: ");
    printPoly(difference);

    Node *derivative = differentiatePoly(poly1);
    printf("Derivative of  1: ");
    printPoly(derivative);

    return 0;
}
