#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int value;
    struct node *next;
};

struct queue {
    struct node *head;
    struct node *tail;
};

struct stack {
    struct node *top;
};

int dump(struct node *head)
{
    if (!head) return -1;
    
    struct node *current = head;
    printf("{");
    while (current) {
        printf(" %d", current->value);
        current = current->next;
    }
    printf("}\n");
    return 0;
}

int release(struct node *head)
{
    if (!head) return -1;

    struct node *current;
    while ((current = head) != NULL) {
        head = current->next;
        free(current);
    }
    return 0;
}

int push_queue(struct queue *q, int temp)
{
    if (!q) return -1;
    struct node *current = (struct node*)calloc(1, sizeof(struct node));
    if (!current) return -1;

    current->value = temp;
    current->next = NULL;
    
    if (!q->head) q->head = current;
    if (q->tail) q->tail->next = current;
    q->tail = current;
    return 0;
}

int pop_queue(struct queue *q)
{
    if (!q) return -1;
    
    struct node *head = q->head;
    if (!head) {
        printf("empty queue\n");
        return -1;
    }
    
    int temp = head->value;
    q->head = head->next;
    free(head);
    return temp;
}

int push_stack(struct stack *s, int temp)
{
    if (!s) return -1;
    
    struct node *current = (struct node*)calloc(1, sizeof(struct node));
    current->value = temp;
    current->next = s->top;
    s->top = current;
    return 0;
}

int pop_stack(struct stack *s)
{
    if (!s) return -1;
    
    struct node *head = s->top;
    if (!head) {
        printf("empty stack\n");
        return -1;
    }
    
    int temp = head->value;
    s->top = head->next;
    free(head);
    return temp;
}

int action(char *s)
{
    int now;
    printf("%s\n", s);
    return (scanf("%d", &now) != 1) ? -1 : now;
}

int push(void)
{
    printf("please input an integer:\n");
    int now;
    if (scanf("%d", &now) != 1) return -1;
    else return now;
}

int main(void)
{
    struct queue *q = (struct queue*)calloc(1, sizeof(struct queue));
    struct stack *s = (struct stack*)calloc(1, sizeof(struct stack));
    int now, test, temp;

    if ((now = action((char *)"please choose test item: [0|1] for [stack|queue]")) == -1) return -1;

    while ((test = action((char *)"please choose action item: [0|1|2] for [exit|push|pop]")) > 0) { 
        switch (now) {
            case 0: /* stack */
                switch (test) {
                    case 1: /* push */
                        if ((temp = push()) != -1) {
                            push_stack(s, temp);
                            dump(s->top);
                        }
                        break;
                    case 2: /* pop */
                        printf("pop()=%d\n", pop_stack(s));
                        dump(s->top);
                        break;
                    default:
                    break;
                };
                break;

            case 1: /* queue */
                switch (test) {
                    case 1: /* push */
                        if ((temp = push()) != -1) {
                            push_queue(q, temp);
                            dump(q->head);
                        }
                        break;
                    case 2: /* pop */
                        printf("pop()=%d\n", pop_queue(q));
                        dump(q->head);
                        break;
                    default:
                    break;
                };
                break;
          default:
                break;
        };
    };

    release(q->head);
    release(s->top);
    free(q);
    free(s);
    return 0;
}
