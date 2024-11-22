#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n,m;
    printf("Give the number of processes:");
    scanf("%d",&n);
    printf("Give the number of resources:");
    scanf("%d",&m);

    int allocation[n][m],request[n][m],available[m], work[m],finish[n],count,check=0;

    for (int i = 0; i < n; i++)
    {
        finish[i] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("Give the resource allocation for process %d:",i+1);
            scanf("%d",&allocation[i][j]);
        }
        for (int j = 0; j < m; j++)
        {
            printf("Give the request of resources for process %d:",i+1);
            scanf("%d",&request[i][j]);
        }
        finish[i] = 0;
    }

    for (int j = 0; j < m; j++)
    {
        printf("Give the available resources of type %d:",j+1);
        scanf("%d",&available[j]);
        work[j] = available[j];
    }
    
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            count = 0;
            if(finish[j] == 0)
            {

                for (int k = 0; k < m; k++)
                {
                    if(work[k] >= request[j][k])
                    {
                        count++;
                    }
                }
                if(count == m)
                {
                    check++;
                    finish[j] = 1;
                    printf("Process %d is allocated with the resources:\n",j+1);
                    printf("Process %d is executing:\n",j+1);
                    printf("Process %d executed sucessfully:\n",j+1);
                    printf("Process %d is releasing its resources:\n",j+1);
                    for (int l = 0; l < m; l++)
                    {
                        
                        work[l] = work[l] + allocation[j][l];
                        printf("available resources of type %d are %d\n",l+1,work[l]);
                    }
                    printf("------------------------------------------------------------------------");
                    
                }
            
            }
        }
        if(check == n)
        {
            printf("The system is not in deadlock all processes executed sucessfully:\n");
            exit(0);
        }
        
    }
    printf("system is in deadlock:\n");
    
    
    return 0;
}