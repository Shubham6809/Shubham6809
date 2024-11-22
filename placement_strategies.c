#include<stdio.h>

void firstFit(int process[],int n,int block[],int size_block)
{
    int counter,remaining;
    printf("process   process size   block   remaining_block_size\n");
    for (int i = 0; i < n; i++)
    {
        counter =0;
        for (int j = 0; j < size_block; j++)
        {
            if(process[i]<block[j])
            {
                remaining = block[j]-process[i];
                printf("%d        %d             %d      %d\n",i+1,process[i],block[j],remaining);
                block[j] = block[j]-process[i];
                break;
            }
            else
            {
                counter++;
            }
        }
        if(counter == size_block)
        {
            printf("%d        %d             not allocated\n",i+1,process[i]);
        }
        
    }
    
}

void nextFit(int process[],int n,int block[],int size_block)
{
    int counter,remaining;
    int pointer = 0;
    printf("process   process size   block   remaining_block_size\n");
    for (int i = 0; i < n; i++)
    {
        counter =pointer;
        for (int j = pointer; j < size_block; j++)
        {
            if(process[i]<=block[j])
            {
                remaining = block[j]-process[i];
                printf("%d          %d             %d      %d\n",i+1,process[i],block[j],remaining);
                block[j] = block[j]-process[i];
                pointer = j;
                if(pointer == size_block-1)
                {
                    pointer = 0;
                }
                break;
            }
            else
            {
                counter++;
            }
        }
        if(counter == size_block)
        {
            printf("%d          %d             not allocated\n",i+1,process[i]);
        }
        
    }
    
}

void bestFit(int process[],int n,int block[],int size_block)
{
    int counter,remaining,min,a;
    printf("process   process size   block   remaining_block_size\n");
    for (int i = 0; i < n; i++)
    {
        counter =0;
        min = 999;
        for (int j = 0; j < size_block; j++)
        {
            if(min > (block[j] - process[i] )&& (block[j] - process[i])>=0)
            {
                min = block[j] - process[i];
                a = j;
            }
            else
            {
                counter++;
            }
        }
        if(counter == size_block)
        {
            printf("%d        %d             not allocated\n",i+1,process[i]);
        }
        else
        {
            remaining = block[a]-process[i];
            printf("%d        %d             %d      %d\n",i+1,process[i],block[a],remaining);
            block[a] = block[a]-process[i];

        }
        
    }
    
}

void worstFit(int process[],int n,int block[],int size_block)
{
    int counter,remaining,max,a;
    printf("process   process size   block   remaining_block_size\n");
    for (int i = 0; i < n; i++)
    {
        counter =0;
        max = 0;
        for (int j = 0; j < size_block; j++)
        {
            if(max < (block[j] - process[i] ))
            {
                max = block[j] - process[i];
                a = j;
            }
            else
            {
                counter++;
            }
        }
        if(counter == size_block)
        {
            printf("%d        %d             not allocated\n",i+1,process[i]);
        }
        else
        {
            remaining = block[a]-process[i];
            printf("%d        %d             %d      %d\n",i+1,process[i],block[a],remaining);
            block[a] = block[a]-process[i];

        }
        
    }
    
}



int main()
{
    int size_block;
    printf("Give the number of the blocks which are vacant:");
    scanf("%d",&size_block);

    int block[size_block];
    printf("Give the block size for:\n");
    for (int i = 0; i < size_block; i++)
    {
        printf("Block %d:", i+1);
        scanf("%d",&block[i]);
    }

    int n;
    printf("Give the number of processes:");
    scanf("%d",&n);

    int process[n];
    printf("give the process size\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d:",i+1);
        scanf("%d",&process[i]);
    }
    
    //  firstFit(process,n,block,size_block);
    // nextFit(process,n,block,size_block);
    // bestFit(process,n,block,size_block);
    worstFit(process,n,block,size_block);
    
    return 0;
}