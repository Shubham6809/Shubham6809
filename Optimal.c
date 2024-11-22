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
void enqueue2(struct node **q,int val,int index)
{
    (*q)->arr[index] = val;
}

void optimal(int ref[],struct node* q,int size,int req)
{
    for (int j = 0; j < size; j++)
    {
        q->arr[j] = -1;
    }

    int exist,hit = 0,fault = 0,dist = 0,max,unuse;
    for (int i = 0; i < req; i++)
    {
        exist = 0;
        for (int j = 0; j < size; j++)
        {
            if(ref[i] == q->arr[j])
            {
                exist = 1;
                print(q,size);
                hit++;
                break;
            }
        }
        
         
            
        if(!exist)
        {
            if(q->r < size-1)
            {
                enqueue(&q,ref[i]);
                print(q,size);
                fault++;
            }
            else
            {

                max = 0;
                for (int j = 0; j < size; j++)
                {
                    dist = 0;
                    for (int k = i; k < req; k++)
                    {
                        if(q->arr[j] == ref[k] && dist > max)
                        {
                            max = dist;
                            unuse = j;
                            break;
                        }
                        if(q->arr[j] == ref[k])
                        {
                            break;
                        }
                        if(k+1 == req)
                        {
                            unuse = j;
                            max = 999;
                            goto here;
                        }
                        dist++;
                    }
                }

                here:
                enqueue2(&q,ref[i],unuse);
                fault++;
                print(q,size);
            }

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


    optimal(ref,q,size,req);
    
    return 0;
}