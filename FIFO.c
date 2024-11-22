#include<stdio.h>
#include<stdlib.h>

struct node
{
    int *arr;
    int f,r;
};


void print(struct node *q,int size)
{ 
    printf(" ");
    for (int i = 0; i < size; i++)
    {
        printf("----");
    }
    
    printf("\n|");

    for (int i = 0; i < size; i++)
    {
        printf(" %d |",q->arr[i]);
    }

    printf("\n");
    printf(" ");

    for (int i = 0; i < size; i++)
    {
        printf("----");
    }
    printf("\n");
    
}

void enqueue(struct node **q,int val)
{
    (*q)->arr[++(*q)->r] = val;
}

void FIFO(int ref[],struct node* q,int size,int req)
{
    for (int j = 0; j < size; j++)
    {
        q->arr[j] = -1;
    }
    int exist,hit = 0,fault = 0;
    for (int i = 0; i < req; i++)
    {
        if(q->r+1 == size)
        {
            q->r = -1;
        }
        exist = 0;
        // check if the page is already exist
        for (int j = 0; j < size; j++)
        {
            if(q->arr[j] == ref[i])
            {
                exist = 1;
                print(q,size);
                hit++;
            }
        }
        if(exist != 1)
        {
            enqueue(&q,ref[i]);
            print(q,size);
            fault++;
        }
        
        
    }
    printf("Page fault = %d\n",fault);
    printf("Page hit = %d",hit);
    
}
int main()
{
    int size;
    printf("Give the number of page frames:");
    scanf("%d",&size);
    int req;
    printf("Give the number of reference string elements present:");
    scanf("%d",&req);
    int ref[req];
    for (int i = 0; i < req; i++)
    {
        printf("Give element no. %d ",i+1);
        scanf("%d",&ref[i]);
    }
    
    struct node *q = (struct node *)malloc(sizeof(struct node));
    q->r = q->f = -1;
    q->arr = (int *)malloc(size * sizeof(int));


    FIFO(ref,q,size,req);
    
    return 0;
}