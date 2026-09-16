#include <stdio.h>

int main()
{
    FILE *fp;
    int arr[100];
    int n, i, j;
    int duplicateCount = 0;
    int isDuplicate;

    printf("Enter how many numbers you want to read from file: ");
    scanf("%d", &n);

    fp = fopen("numbers.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // Read numbers from the file
    for (i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &arr[i]);
    }

    fclose(fp);

    printf("The content of the array: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    // Count duplicate values
    for (i = 0; i < n; i++)
    {
        isDuplicate = 0;

        // Check if arr[i] appeared earlier
        for (j = 0; j < i; j++)
        {
            if (arr[i] == arr[j])
            {
                isDuplicate = 1;
                break;
            }
        }

        // Count only the first occurrence of each duplicate value
        if (isDuplicate == 0)
        {
            for (j = i + 1; j < n; j++)
            {
                if (arr[i] == arr[j])
                {
                    duplicateCount++;
                    break;
                }
            }
        }
    }

    printf("\nTotal number of duplicate values = %d\n", duplicateCount);

    return 0;
}