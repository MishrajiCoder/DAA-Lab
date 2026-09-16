#include <stdio.h>

int main()
{
    FILE *fp;
    int arr[100];
    int n, i, j;
    int count, maxCount = 0;
    int mostRepeating;

    printf("Enter how many numbers you want to read from file: ");
    scanf("%d", &n);

    fp = fopen("numbers.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // Reading integers from the disk file
    for (i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &arr[i]);
    }

    fclose(fp);

    printf("\nThe content of the array: ");

    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    // Finding the most repeating element
    for (i = 0; i < n; i++)
    {
        count = 1;

        for (j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
            }
        }

        if (count > maxCount)
        {
            maxCount = count;
            mostRepeating = arr[i];
        }
    }

    printf("\nThe most repeating element in the array = %d", mostRepeating);

    return 0;
}