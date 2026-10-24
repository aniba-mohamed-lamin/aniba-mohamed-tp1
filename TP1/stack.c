#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
    char data;
    struct Node *next;
} Node;
typedef struct Stack {
    Node *top;
} Stack;
void initStack(Stack *s) {
    s->top = NULL;
}
int isEmpty(Stack *s) {
    return s->top == NULL;
}
void push(Stack *s, char x) {
    Node *p = malloc(sizeof(Node));
    if (p == NULL)
        return;
    p->data = x;
    p->next = s->top;
    s->top = p;
}
char pop(Stack *s) {
    if (isEmpty(s))
        return '\0';
    Node *p = s->top;
    char x = p->data;
    s->top = p->next;
    free(p);
    return x;
}
char peek(Stack *s) {
    if (isEmpty(s))
        return '\0';

    return s->top->data;
}
void display(Stack *s) {
    Node *p = s->top;
    if (p == NULL) {
        printf("Stack is empty\n");
        return;
    }
    while (p != NULL) {
        printf("%c ", p->data);
        p = p->next;
    }

    printf("\n");
}

int evaluate(char exp[]) {
    int stack[100];
    int top = -1;
    int i = 0;

    while (exp[i] != '\0') {
        if (exp[i] == ' ') {
            i++;
        } else if (exp[i] >= '0' && exp[i] <= '9') {
            int n = 0;

            while (exp[i] >= '0' && exp[i] <= '9') {
                n = n * 10 + exp[i] - '0';
                i++;
            }

            stack[++top] = n;
        } else {
            int b = stack[top--];
            int a = stack[top--];
            int r = 0;

            if (exp[i] == '+')
                r = a + b;
            else if (exp[i] == '-')
                r = a - b;
            else if (exp[i] == '*')
                r = a * b;
            else if (exp[i] == '/') {
                if (b == 0) {
                    printf("Division by zero\n");
                    return 0;
                }
                r = a / b;
            }

            stack[++top] = r;
            i++;
        }
    }
    return stack[top];
}

int main() {
    Stack s;
    int choice;
    char x;
    char exp[100];
    initStack(&s);
    do {
        printf("\n1 Push\n");
        printf("2 Pop\n");
        printf("3 Display\n");
        printf("4 Evaluate postfix\n");
        printf("5 Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter character: ");
            scanf(" %c", &x);
            push(&s, x);
        } else if (choice == 2) {
            if (!isEmpty(&s))
                printf("Element: %c\n", pop(&s));
            else
                printf("Stack is empty\n");
        } else if (choice == 3) {
            display(&s);
        } else if (choice == 4) {
            printf("Enter postfix expression: ");
            scanf(" %99[^\n]", exp);
            printf("Result = %d\n", evaluate(exp));
        }
    } while (choice != 5);
    while (!isEmpty(&s))
        pop(&s);
    return 0;
}