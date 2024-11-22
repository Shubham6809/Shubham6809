#include<stdio.h>

struct process {
    int WT, AT, BT, TAT, PT;
};

int main() {
    struct process a[10];
    int n, temp[10], t = 0, count = 0, short_p;
    float total_WT = 0, total_TAT = 0, Avg_WT, Avg_TAT;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
     
    printf("Enter the arrival time, burst time, and priority of the processes (AT BT PT):\n");
    for(int i = 0; i < n; i++) {
        printf("Enter the arrival time of the process %d:\n",i+1);
        scanf("%d", &a[i].AT);
        printf("Enter the brust time of the process %d:\n",i+1);
        scanf("%d", &a[i].BT);
        printf("Enter the priority of the process %d:\n",i+1);
        scanf("%d", &a[i].PT);
        temp[i] = a[i].BT;  // Copying burst time for later use
    }

    a[9].PT = 10000;  // High priority value to ensure correct selection in the loop

    while(count != n) {
        short_p = 9;
        for(int i = 0; i < n; i++) {
            if(a[i].PT < a[short_p].PT && a[i].AT <= t && a[i].BT > 0) {
                short_p = i;
            }
        }

        a[short_p].BT--;
        t++;  // Move time forward

        // If a process is completed
        if(a[short_p].BT == 0) {
            count++;
            a[short_p].WT = t - a[short_p].AT - temp[short_p];
            a[short_p].TAT = t - a[short_p].AT;
            total_WT += a[short_p].WT;
            total_TAT += a[short_p].TAT;
        }
    }

    Avg_WT = total_WT / n;
    Avg_TAT = total_TAT / n;

    printf("ID  WT   TAT\n");
    for(int i = 0; i < n; i++) {
        printf("%d   %d   %d\n", i + 1, a[i].WT, a[i].TAT);
    }

    printf("Avg waiting time of the processes is %.2f\n", Avg_WT);
    printf("Avg turn around time of the processes is %.2f\n", Avg_TAT);

    return 0;
}
