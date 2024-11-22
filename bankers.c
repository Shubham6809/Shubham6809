#include<stdio.h>
 
int main()
{
    int m,n;
    printf("Give the number of processes present:");
    scanf("%d",&m);
    printf("how many types of resources are there:");
    scanf("%d",&n);
    
    int allocation[m][n];
    int need[m][n];
    int available[n];
    int Rneed[m][n];
    int max[n];
    int safe[m];

    //give the total  resources   the system have
    printf("give the total  resources the system have\n");
    for(int i=0;i<n;i++)
    {
        printf("Number of resources of type %d:",i+1);
        scanf("%d",&max[i]);
    }

    //allocating resources
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("how much resources of type %d is allocated to the process %d:",j+1,i+1);
            scanf("%d",&allocation[i][j]);
        }
    }

    //finding total available resources after allocating resources
    int temp[n];
    for(int i=0;i<n;i++)
    {
        temp[i]=0;
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            temp[i]+=allocation[j][i];
        }
        available[i]=max[i]-temp[i];
    }

    //finding the needed resources
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("how much resources of type %d is needed to the process %d for execution:",j+1,i+1);
            scanf("%d",&need[i][j]);
        }
    }

    //finding the remaining need
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
           Rneed[i][j]=need[i][j]-allocation[i][j];
        }
    }

   int count = 0;
    int counter = 0; 
    int finish[m];
    int z=0;
    for (int i = 0; i < m; i++) {
        finish[i] = 0; // Initialize all processes as not finished
    }

    // Using Banker's Algorithm
    for (int k = 0; k < m; k++) {
        for (int i = 0; i < m; i++) {
            if (finish[i] == 0) { // If process i is not finished
                count = 0; // Reset count for each process
                for (int j = 0; j < n; j++) {
                    if (available[j] >= Rneed[i][j]) { 
                        count++;
                    }
                }
                if (count == n) {
                    for (int j = 0; j < n; j++) {
                        available[j] += allocation[i][j]; // Release the resources
                    }
                    finish[i] = 1; // Mark process as finished
                    safe[z] = i;
                    z++;
                    
                    counter++; 
                }
            }
        }
    }

    if(counter==m)
    {
        printf("No Deadlock exist");
        printf("Safe sequence is:\n");
       for (int i = 0; i < m; i++)
       {
            printf("%d-",safe[i]);
       }
        
    }
    else{
        printf("Deadlock exist");
    }
    return 0;
}