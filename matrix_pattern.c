/* 
 * Find the number of pattern in below 
 * 3x3 matrix
 * 
 *        y\x | 0 1 2 
 *         ---+-------
 *          0 | 0 1 2
 *          1 | 3 4 5
 *          2 | 6 7 8
 *
 * example of patterns: 
 * 01, 10, 123, 321, 0751, 13754, 012345678
 */

#include <stdio.h>
#include <stdbool.h>

#define ND 9
int debug = 0;
int patterns = 0;
bool visited[ND] = { false };

struct node {
    int x;          /* x coordinate */
    int y;          /* y coordinate */
    int adj[ND];    /* adjacency list */
    int adj_num;    /* adjacency number */
};

struct node a[9] = { {0, 0, {-1}, 0}, {1, 0, {-1}, 0}, {2, 0, {-1}, 0},
                     {0, 1, {-1}, 0}, {1, 1, {-1}, 0}, {2, 1, {-1}, 0},
                     {0, 2, {-1}, 0}, {1 ,2, {-1}, 0}, {2, 2, {-1}, 0} };

int connect(struct node *n1, struct node *n2) 
{
    return ((abs(n1->x - n2->x) == 1) || 
            (abs(n1->y - n2->y) == 1)) ? 1 : 0;
}

/* create adjency list */
void adj_func(struct node *in) 
{
    int i, j, idx;
    struct node *n1, *n2;

    for (i = 0; i < ND; i++) {
        printf("%d: ", i);
        for (j = 0; j < ND; j++) {
            if (i == j) continue;
            n1 = &in[i];
            n2 = &in[j];
            if (connect(n1, n2) == 1) {
                printf("%d ", j);
                idx = n1->adj_num++;
                n1->adj[idx] = j;
            }     
        }
        printf("\n");
    }
}

void DFS(int i)
{
    struct node *n = &a[i];
    int j, idx;

    if (debug) printf(" %d+ ", i);

    visited[i] = true;
    for (j = 0; j < n->adj_num; j++) {
        idx = n->adj[j];
        if (!visited[idx]) {
            if (debug) printf("(%d->%d)", i, idx);
            patterns++;
            DFS(idx);
        }
    }
    visited[i] = false;

    if (debug) printf("%d-\n", i);
}

int main(void)
{
    int i;
    adj_func(a);
    for (i = 0; i < ND; i++) DFS(i);
    printf("number of patterns = %d\n", patterns);

    return 0;
}
