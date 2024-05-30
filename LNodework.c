#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent a term in a polynomial
typedef struct Node {
    int coefficient;
    int exponent;
    struct Node *next;
} Node;

// Function to create a new node
Node* createNode(int coefficient, int exponent) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a term into a polynomial
void insertTerm(Node **head, int coefficient, int exponent) {
    Node *newNode = createNode(coefficient, exponent);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to display a polynomial
void displayPolynomial(Node *head) {
    Node *temp = head;
    printf("Polynomial: ");
    while (temp != NULL) {
        printf("%d,%d", temp->coefficient, temp->exponent);
        temp = temp->next;
        if (temp != NULL) {
            printf(",");
        }
    }
    printf("\n");
}

// Function to add two polynomials
Node* addPolynomials(Node *poly1, Node *poly2) {
    Node *result = NULL;
    while (poly1 != NULL || poly2 != NULL) {
        int coeff1 = (poly1 != NULL) ? poly1->coefficient : 0;
        int coeff2 = (poly2 != NULL) ? poly2->coefficient : 0;
        int exp1 = (poly1 != NULL) ? poly1->exponent : 0;
        int exp2 = (poly2 != NULL) ? poly2->exponent : 0;

        if (exp1 > exp2) {
            insertTerm(&result, coeff1, exp1);
            poly1 = poly1->next;
        } else if (exp1 < exp2) {
            insertTerm(&result, coeff2, exp2);
            poly2 = poly2->next;
        } else {
            insertTerm(&result, coeff1 + coeff2, exp1);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    return result;
}

// Function to subtract two polynomials
Node* subtractPolynomials(Node *poly1, Node *poly2) {
    Node *result = NULL;
    while (poly1 != NULL || poly2 != NULL) {
        int coeff1 = (poly1 != NULL) ? poly1->coefficient : 0;
        int coeff2 = (poly2 != NULL) ? poly2->coefficient : 0;
        int exp1 = (poly1 != NULL) ? poly1->exponent : 0;
        int exp2 = (poly2 != NULL) ? poly2->exponent : 0;

        if (exp1 > exp2) {
            insertTerm(&result, coeff1, exp1);
            poly1 = poly1->next;
        } else if (exp1 < exp2) {
            insertTerm(&result, -coeff2, exp2);
            poly2 = poly2->next;
        } else {
            insertTerm(&result, coeff1 - coeff2, exp1);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    return result;
}

// Function to differentiate a polynomial
Node* differentiatePolynomial(Node *poly) {
    Node *result = NULL;
    Node *temp = poly;
    while (temp->next != NULL) {
        insertTerm(&result, temp->coefficient * temp->exponent, temp->exponent - 1);
        temp = temp->next;
    }
    return result;
}

// Function to free memory allocated for a polynomial
void freePolynomial(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *poly1 = NULL, *poly2 = NULL, *result = NULL;
    int choice;

    do {
        printf("\n1. Create polynomial 1\n");
        printf("2. Create polynomial 2\n");
        printf("3. Display polynomial 1\n");
        printf("4. Display polynomial 2\n");
        printf("5. Add polynomials\n");
        printf("6. Subtract polynomials\n");
        printf("7. Differentiate polynomial 1\n");
        printf("8. Differentiate polynomial 2\n");
        printf("9. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                freePolynomial(poly1);
                poly1 = freePolynomial();
                break;
            case 2:
                freePolynomial(poly2);
                poly2 = freePolynomial();
                break;
            case 3:
                if (poly1 != NULL)
                    displayPolynomial(poly1);
                else
                    printf("Polynomial 1 is not created yet.\n");
                break;
            case 4:
                if (poly2 != NULL)
                    displayPolynomial(poly2);
                else
                    printf("Polynomial 2 is not created yet.\n");
                break;
            case 5:
                if (poly1 == NULL || poly2 == NULL) {
                    printf("Both polynomials must be created first.\n");
                } else {
                    result = addPolynomials(poly1, poly2);
                    displayPolynomial(result);
                    freePolynomial(result);
                }
                break;
            case 6:
                if (poly1 == NULL || poly2 == NULL) {
                    printf("Both polynomials must be created first.\n");
                } else {
                    result = subtractPolynomials(poly1, poly2);
                    displayPolynomial(result);
                    freePolynomial(result);
                }
                break;
            case 7:
                if (poly1 == NULL) {
                    printf("Polynomial 1 must be created first.\n");
                } else {
                    result = differentiatePolynomial(poly1);
                    displayPolynomial(result);
                    freePolynomial(result);
                }
                break;
            case 8:
                if (poly2 == NULL) {
                    printf("Polynomial 2 must be created first.\n");
                } else {
                    result = differentiatePolynomial(poly2);
                    displayPolynomial(result);
                    freePolynomial(result);
                }
                break;
            case 9:
                freePolynomial(poly1);
                freePolynomial(poly2);
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 9.\n");
        }
    } while (choice != 9);

    return 0;
}
