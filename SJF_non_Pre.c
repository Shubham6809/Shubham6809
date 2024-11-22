#include <stdio.h>
#include <stdlib.h>

struct node {
    int arr[10];
    int f, r;
};

void enqueue(struct node* q, int val) {
    if (q->r == 9) {
        printf("Queue is full\n");
        return;
    }
    if (q->f == -1) q->f = 0;
    q->arr[++q->r] = val;
}

int dequeue(struct node* q) {
    if (q->f == -1 || q->f > q->r) {
        return -1;
    }
    return q->arr[q->f++];
}

int main() {
    struct node q;
    q.f = q.r = -1;

    int n, count = 0;
    printf("Give the number of processes: ");
    scanf("%d", &n);

    int AT[n], BT[n], CT[n], TAT[n], WT[n],finished[n],running[n];
    for (int i = 0; i < n; i++) {
        printf("Give the Arrival time of process %d: ", i + 1);
        scanf("%d", &AT[i]);
        printf("Give the burst time of process %d: ", i + 1);
        scanf("%d", &BT[i]);
        finished[i] = 0;
        count += BT[i];
    }

    int t = 0, a,c, i = 0,min ;

    for(int k =0;k<n;k++)
    {
        min = 999;
        for (int j = 0; j < n; j++) {
            if (min > BT[j] && finished[j] !=1 && t>= AT[j]) {
                min = BT[j];
                c=j;
            }
        
        }
            t += BT[c];
                enqueue(&q, c);
                finished[c] =1;
        if(t == count)
        {
            break;
        }
    }
    
    t=0;
    while (1) {
        

        a = dequeue(&q);
        if (a != -1) {
            for (int counter = 0; counter < BT[a]; counter++) {
                t++;
            }
            printf("Process %d is completed at %d\n", a, t);
            CT[i] = t;
            TAT[a] = t - AT[a];
            WT[a] = TAT[a] - BT[a];
            running[i++] = a+1;
            finished[a] = 1;
        } else {
            t++;
        }

        if (count == t) {
            break;
        }
    }
    printf(" ");
    for (int i = 0; i < n; i++)
    {
        printf("-----");
    }
    
    printf("\n|");

    for (int i = 0; i < n; i++)
    {
        printf(" P%d |",running[i]);
    }

    printf("\n");
    printf(" ");
    for (int i = 0; i < n; i++)
    {
        printf("-----");
    }
    printf("\n0");
    for (int i = 0; i < n; i++)
    {
        printf("    %d",CT[i]);
    }
    return 0;
}
