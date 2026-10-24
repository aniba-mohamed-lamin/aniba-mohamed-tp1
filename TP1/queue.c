#include <stdio.h>
#include <stdlib.h>
     

typedef struct Node {
    int number;
    struct Node *next;
} Node;
typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;
void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}
int isEmpty(Queue *q) {
     return q->front == NULL;
}
void enqueue(Queue *q, int x) {
    Node *p = malloc(sizeof(Node));
    if (p == NULL)
        return;
    p->number = x;
    p->next = NULL;
    if (isEmpty(q)) {
        q->front = p;
        q->rear = p;
    } else {
        q->rear->next = p;
        q->rear = p;
    }
}
int dequeue(Queue *q) {
    if (isEmpty(q))
        return -1;
    Node *p = q->front;
    int x = p->number;
    q->front = q->front->next;
    if (q->front == NULL)
         q->rear = NULL;
    free(p);
    return x;
}
int peek(Queue *q) {
    if (isEmpty(q))
        return -1;

    return q->front->number;
}
void displayQueue(Queue *q) {
    Node *p = q->front;
    if (p == NULL) {
     printf("Queue is empty\n");
        return;
    }
    while (p != NULL) {
        printf("%d ", p->number);
        p = p->next;
    }
    printf("\n");
}
int main() {
    Queue q;
    int choice, x;
    initQueue(&q);
    do {
        printf("\n1 Add customer\n");
         printf("2 Serve customer\n");
         printf("3 Show first customer\n");
        printf("4 Display queue\n");
          printf("5 Exit\n");
        printf("Choice: ");
         scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter customer number: ");
            scanf("%d", &x);
            enqueue(&q, x);
            printf("Customer %d arrived and got a token\n", x);
        } else if (choice == 2) {
            if (!isEmpty(&q)) {
                x = dequeue(&q);
                printf("Customer %d is being served\n", x);
            } else {
                printf("Queue is empty\n");
            }
        } else if (choice == 3) {
            if (!isEmpty(&q))
                printf("First customer: %d\n", peek(&q));
            else
                printf("Queue is empty\n");
        } else if (choice == 4) {
            displayQueue(&q);
        }
    } while (choice != 5);
    while (!isEmpty(&q))
        dequeue(&q);
    return 0;
}