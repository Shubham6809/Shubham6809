#include <stdio.h>
#include <stdlib.h>

struct node {
    int arr[30];
    int f, r;
};

void enqueue(struct node* q, int val) {
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

    int n, totalBurstTime = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int AT[n], BT[n], CT[n], TAT[n], WT[n];
    int RBT[n], finished[n];
    
    // Input Arrival and Burst Times
    for (int i = 0; i < n; i++) {
        printf("Enter the Arrival Time of process %d: ", i + 1);
        scanf("%d", &AT[i]);
        printf("Enter the Burst Time of process %d: ", i + 1);
        scanf("%d", &BT[i]);
        
        RBT[i] = BT[i];  // Initialize Remaining Burst Time
        finished[i] = 0; // Process not finished
        totalBurstTime += BT[i];
    }

    int t = 0, minProcessIndex;
    int totalTimeExecuted = 0; // Tracks total time executed for all processes

    while (totalTimeExecuted < totalBurstTime) {
        int minBurstTime = 999;

        // Find the process with the smallest remaining burst time
        for (int j = 0; j < n; j++) {
            if (!finished[j] && AT[j] <= t && RBT[j] < minBurstTime) {
                minBurstTime = RBT[j];
                minProcessIndex = j;
            }
        }

        // If a process is ready to execute
        if (minBurstTime != 999) {
            enqueue(&q, minProcessIndex);
            RBT[minProcessIndex]--; // Execute one unit of burst time
            totalTimeExecuted++;
            t++;

            // If process is finished, set completion time
            if (RBT[minProcessIndex] == 0) {
                finished[minProcessIndex] = 1;
                CT[minProcessIndex] = t;
            }
        } else {
            t++; // No process was ready, increment time
        }
    }

    // Calculate Turnaround Time and Waiting Time
    for (int i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i]; // Calculate WT from TAT and original BT
    }

    // Print Burst Time, TAT, and WT for each process for debugging
    printf("\nProcess | Burst Time | TAT | WT\n");
    printf("---------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf(" P%d     | %d          | %d   | %d\n", i + 1, BT[i], TAT[i], WT[i]);
    }

    // Calculate and print average TAT and WT
    float totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        totalTAT += TAT[i];
        totalWT += WT[i];
    }

    printf("\nAverage Turnaround Time (TAT): %.2f", totalTAT / n);
    printf("\nAverage Waiting Time (WT): %.2f\n", totalWT / n);

    return 0;
}
