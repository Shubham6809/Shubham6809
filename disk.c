#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int disk_size;

int FCFS(int arr[], int size,int head)
{
    printf("\n\nmovement | seek time\n");
    int movement = 0;
    for (int i = 0; i < size; i++)
    {
        movement += abs(arr[i] - head);
        printf("%d-%d    | %d\n",head,arr[i],movement);
        head = arr[i];
    }
    printf("\n\n\n");
    return movement;
}

int SSTF(int arr[],int size,int head,int finished[])
{
     int movement = 0,a;
    printf("\n\nmovement | seek time\n");
    for (int i = 0; i < size; i++)
    {
        int min =999;
        for (int j = 0; j < size; j++)
        {
            if(min > abs(arr[j]-head) && finished[j] == 0)
            {
                min = abs(arr[j]-head);
                a =j;
            }
        }
        
        movement += abs(arr[a] - head);
         printf("%d-%d    | %d\n",head,arr[i],movement);
        head = arr[a];
        finished[a] = 1;
        arr[a] = 999;
    }
    printf("\n\n\n");
    return movement;
}

void SCAN(int arr[],int size,int head)
{
     int right[size],left[size],left_count = 0,right_count = 0,seek = 0;
    printf("\n\nmovement | seek time\n");
     right[right_count++] = disk_size -1;

     for (int i = 0; i < size; i++)
     {
        if(arr[i]<head)
        {
            left[left_count++] = arr[i];
        }
        else
        {
            right[right_count++] = arr[i];
        }
     }

     for (int i = 0; i < right_count; i++)
     {
        for (int j = i+1; j < right_count; j++)
        {
            if(right[i]>right[j])
            {
                int swap = right[j];
                right[j] = right[i];
                right[i] = swap;
            }
        }
        
     }
     for (int i = 0; i < left_count; i++)
     {
        for (int j = i+1; j < left_count; j++)
        {
            if(left[i]>left[j])
            {
                int swap = left[j];
                left[j] = left[i];
                left[i] = swap;
            }
        }
        
     }

    int i;
    for (i = 0; i < right_count; i++)
     {
        seek += abs(right[i]-head);
         printf("%d-%d    | %d\n",head,arr[i],seek);
        head = right[i];
     }
    for (int j = left_count-1; j >= 0 ; j--)
     {
        seek += abs(left[j]-head);
         printf("%d-%d    | %d\n",head,arr[i],seek);
        head = left[j];
     }
    printf("\n\n\n");
     printf("Total seek time: %d by SCAN\n",seek);

}

void CSCAN(int arr[],int size,int head)
{
    printf("\n\nmovement | seek time\n");
     int right[size],left[size],left_count = 0,right_count = 0,seek = 0;

     right[right_count++] = disk_size -1;
     left[left_count++] = 0;

     for (int i = 0; i < size; i++)
     {
        if(arr[i]<head)
        {
            left[left_count++] = arr[i];
        }
        else
        {
            right[right_count++] = arr[i];
        }
     }

     for (int i = 0; i < right_count; i++)
     {
        for (int j = i+1; j < right_count; j++)
        {
            if(right[i]>right[j])
            {
                int swap = right[j];
                right[j] = right[i];
                right[i] = swap;
            }
        }
        
     }
     for (int i = 0; i < left_count; i++)
     {
        for (int j = i+1; j < left_count; j++)
        {
            if(left[i]>left[j])
            {
                int swap = left[j];
                left[j] = left[i];
                left[i] = swap;
            }
        }
        
     }

    int i;
    for (i = 0; i < right_count; i++)
     {
        seek += abs(right[i]-head);
         printf("%d-%d    | %d\n",head,arr[i],seek);
        head = right[i];
     }
     
    

    for (int j = 0; j < left_count ; j++)
     {
        seek += abs(left[j]-head);
         printf("%d-%d    | %d\n",head,arr[i],seek);
        head = left[j];
     }
    printf("\n\n\n");
     printf("Total seek time:  %d by CSCAN \n",seek);

}

int main()
{
    printf("Give the disk size:");
    scanf("%d",&disk_size);
    int size,head;
    printf("How many traks positions are there:");
    scanf("%d",&size);
    int arr[size],finished[size];
    for (int i = 0; i < size; i++)
    {
        printf("Give the track no %d:",i+1);
        scanf("%d",&arr[i]);
        finished[i] = 0;
    }
    printf("Give initial head position:");
    scanf("%d",&head);
    SCAN(arr,size,head);
    CSCAN(arr,size,head);
    int movement;
    movement  = FCFS(arr,size,head);
    printf("seek time is:%d\nby FCFS\n",movement);
    movement  = SSTF(arr,size,head,finished);
    printf("seek time is:%d\nby SSTF\n",movement);
    return 0;
}