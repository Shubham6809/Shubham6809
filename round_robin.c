#include<stdio.h>

struct node {
    int arr[50];
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

    int n,quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int AT[n], BT[n], CT[n], TAT[n], WT[n],RCT[100];
    int RBT[n], finished[n],running[100];

    for (int i = 0; i < n; i++) {
        printf("Enter the Arrival Time of process %d: ", i + 1);
        scanf("%d", &AT[i]);
        printf("Enter the Burst Time of process %d: ", i + 1);
        scanf("%d", &BT[i]);
        RBT[i] = BT[i]; 
        finished[i] = 0;
    }

    printf("Give the time quantum:");
    scanf("%d",&quantum);
    int t=0,element,condition =1,a =0;
    while(condition)
    {
        for (int i = 0; i < n; i++)
        {
            if(AT[i] == t && finished[i] == 0)
            {
                enqueue(&q,i);
                condition = 0;
                break;
            }
        }t++;

    }
    t--;
    while(1)
    {
    
        
      
        element = dequeue(&q);
        if(element != -1)
        {
            running[a] = element;
            for (int k = 0; k < quantum; k++)
            {
                 
                RBT[element]--;
                t++;
                for (int i = 0; i < n; i++)
                {
                    if(AT[i] == t && finished[i] == 0)
                    {
                        enqueue(&q,i);
                    }
                } 
            
                if(RBT[element] == 0)
                {
                    break;
                }
            }
            if(RBT[element] == 0)
                {
                    finished[element] = 1;
                    CT[element] = t;
                }
                else
                {
                    enqueue(&q,element);
                }
            
           
            
           
            RCT[a++] = t;
            printf("Time: %d, Process: P%d, Remaining Burst: %d\n", t, element, RBT[element]);

            
            
        }
        else
        {
            break;
        }

    }

    for (int i = 0; i < n; i++)
    {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
    }


    printf("process | AT | BT | TAT | WT |\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d        | %d  | %d  | %d   | %d  |\n",i,AT[i],BT[i],TAT[i],WT[i]);
    }
    
     printf(" ");
    for (int i = 0; i < a; i++)
    {
        printf("-----");
    }
    
    printf("\n|");

    for (int i = 0; i < a; i++)
    {
        printf(" P%d |",running[i]);
    }

    printf("\n");
    printf(" ");
    for (int i = 0; i < a; i++)
    {
        printf("-----");
    }
    printf("\n0");
    for (int i = 0; i < a; i++)
    {
        if(RCT[i]>9)
        {
            printf("   %d",RCT[i]);
        }
        else
        {
            printf("    %d",RCT[i]);
        }
    }
     
    printf("\n");
    printf("\n");
    printf("\n");
     int TT=0,W=0;
    for (int i = 0; i < n; i++)
    {
        TT += TAT[i];
        printf("\n%d",TAT[i]);
    }
    float avgTAT =(float) TT/n;
    printf("\nAVERAGE TAT is:%f\n",avgTAT);
    for (int i = 0; i < n; i++)
    {
        printf("\n%d",WT[i]);
        W += WT[i];
    }
    float avgWT =(float) W/n;
    printf(" AVERAGE WT is:%f\n",avgWT);



    return 0;
}