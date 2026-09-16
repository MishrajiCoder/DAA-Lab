#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long comparisons = 0;

// Partition Function
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    int j, temp;

    for(j = low; j < high; j++)
    {
        comparisons++;

        if(arr[j] <= pivot)
        {
            i++;

            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Quick Sort Function
int quickSort(int arr[], int low, int high)
{
    int p;

    if(low < high)
    {
        p = partition(arr, low, high);

        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }

    return 0;
}

int main()
{
    FILE *fp1, *fp2;

    int arr[1000];
    int n = 0;
    int choice;
    int i;

    char inputFile[30];
    char outputFile[30];

    clock_t start, end;
    double time_taken;

    while(1)
    {
        printf("\n===== MAIN MENU (QUICK SORT) =====\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. EXIT\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                sprintf(inputFile,"inASCE.dat");
                sprintf(outputFile,"outQuickASCE.dat");
                break;

            case 2:
                sprintf(inputFile,"inDESC.dat");
                sprintf(outputFile,"outQuickDESC.dat");
                break;

            case 3:
                sprintf(inputFile,"Rad.dat");
                sprintf(outputFile,"outQuickRAD.dat");
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid Choice!\n");
                continue;
        }

        fp1 = fopen(inputFile,"r");

        if(fp1 == NULL)
        {
            printf("Cannot Open Input File.\n");
            continue;
        }

        n = 0;

        while(fscanf(fp1,"%d",&arr[n]) == 1)
            n++;

        fclose(fp1);

        printf("\nBefore Sorting:\n");

        for(i=0;i<n;i++)
            printf("%d ",arr[i]);

        comparisons = 0;

        start = clock();

        quickSort(arr,0,n-1);

        end = clock();

        time_taken = ((double)(end-start))/CLOCKS_PER_SEC;

        fp2 = fopen(outputFile,"w");

        for(i=0;i<n;i++)
            fprintf(fp2,"%d ",arr[i]);

        fclose(fp2);

        printf("\n\nAfter Sorting:\n");

        for(i=0;i<n;i++)
            printf("%d ",arr[i]);

        printf("\n\nNumber of Comparisons = %ld",comparisons);

        printf("\nExecution Time = %.9lf seconds",time_taken);

        printf("\n");
    }

    return 0;
}