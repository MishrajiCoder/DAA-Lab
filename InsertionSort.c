#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long comparisons = 0;

// Insertion Sort Function
int insertionSort(int arr[], int n)
{
    int i, j, key;

    for(i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while(j >= 0)
        {
            comparisons++;

            if(arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            else
            {
                break;
            }
        }

        arr[j + 1] = key;
    }

    return 0;
}

int main()
{
    FILE *fp1, *fp2;

    int arr[1000];
    int n = 0;
    int choice, i;

    char inputFile[30];
    char outputFile[30];

    clock_t start, end;
    double time_taken;

    while(1)
    {
        printf("\n===== MAIN MENU (INSERTION SORT) =====\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. EXIT\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                sprintf(inputFile, "inASCE.dat");
                sprintf(outputFile, "outInsertASCE.dat");
                break;

            case 2:
                sprintf(inputFile, "inDESC.dat");
                sprintf(outputFile, "outInsertDESC.dat");
                break;

            case 3:
                sprintf(inputFile, "Rad.dat");
                sprintf(outputFile, "outInsertRAD.dat");
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid Choice!\n");
                continue;
        }

        fp1 = fopen(inputFile, "r");

        if(fp1 == NULL)
        {
            printf("Cannot Open Input File.\n");
            continue;
        }

        n = 0;

        while(fscanf(fp1, "%d", &arr[n]) == 1)
            n++;

        fclose(fp1);

        printf("\nBefore Sorting:\n");

        for(i = 0; i < n; i++)
            printf("%d ", arr[i]);

        comparisons = 0;

        start = clock();

        insertionSort(arr, n);

        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        fp2 = fopen(outputFile, "w");

        for(i = 0; i < n; i++)
            fprintf(fp2, "%d ", arr[i]);

        fclose(fp2);

        printf("\n\nAfter Sorting:\n");

        for(i = 0; i < n; i++)
            printf("%d ", arr[i]);

        printf("\n\nNumber of Comparisons = %ld", comparisons);

        printf("\nExecution Time = %.9lf seconds\n", time_taken);
    }

    return 0;
}