//Write a menu driven program to sort list of array elemnts using Merge sort technique and calculate the execution time only to sort the elements. Count the number of comaprisons 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
long comparisons = 0;
// Merge Function
void merge(int arr[], int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = low;
    int temp[1000];
    while (i <= mid && j <= high){
        comparisons++;
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= high)
        temp[k++] = arr[j++];
    for (i = low; i <= high; i++)
        arr[i] = temp[i];
}
// Merge Sort
void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}
int main()
{
    FILE *fp1, *fp2;
    int arr[1000];
    int n = 0;
    int choice;
    char inputFile[30], outputFile[30];
    clock_t start, end;
    double time_taken;
    while (1)
    {
        printf("\n===== MAIN MENU (MERGE SORT) =====\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. EXIT\n");
        printf("Enter option: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                sprintf(inputFile,"inASCE.dat");
                sprintf(outputFile,"outMerge.dat");
                break;
            case 2:
                sprintf(inputFile,"inDESC.dat");
                sprintf(outputFile,"outMERGE_DESC.dat");
                break;
            case 3:
                sprintf(inputFile,"Rad.dat");
                sprintf(outputFile,"outMergeRad.dat");
                break;
            case 4:
                exit(0);
            default:
                printf("CHOOSE THE CORRECT OPTION\n");
                continue;
        }
        fp1 = fopen(inputFile,"r");
        if(fp1==NULL)
        {
            printf("Cannot open input file.\n");
            continue;
        }
        n = 0;
        while(fscanf(fp1,"%d",&arr[n])==1)
            n++;
        fclose(fp1);
        printf("\nBefore Sorting:\n");
        for(int i=0;i<n;i++)
            printf("%d ",arr[i]);
        comparisons = 0;
        start = clock();
        mergeSort(arr,0,n-1);
        end = clock();
        time_taken=((double)(end-start))/CLOCKS_PER_SEC;
        fp2=fopen(outputFile,"w");
        for(int i=0;i<n;i++)
            fprintf(fp2,"%d ",arr[i]);

        fclose(fp2);

        printf("\n\nAfter Sorting:\n");

        for(int i=0;i<n;i++)
            printf("%d ",arr[i]);

        printf("\n\nNumber of Comparisons = %ld",comparisons);
        printf("\nExecution Time = %.9lf seconds\n",time_taken);
    }
    return 0;
}