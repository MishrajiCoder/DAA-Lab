//Write a program to find out the second smallest and second largest element stored in an array of n integers.
#include <stdio.h>
#include <limits.h>
int main()
{
    int n, i;
    int a[100];

    int smallest = INT_MAX;
    int secondSmallest = INT_MAX;

    int largest = INT_MIN;
    int secondLargest = INT_MIN;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    for (i = 0; i < n; i++)
    {
        // Finding smallest and second smallest
        if (a[i] < smallest)
        {
            secondSmallest = smallest;
            smallest = a[i];
        }
        else if (a[i] > smallest && a[i] < secondSmallest)
        {
            secondSmallest = a[i];
        }

        // Finding largest and second largest
        if (a[i] > largest)
        {
            secondLargest = largest;
            largest = a[i];
        }
        else if (a[i] < largest && a[i] > secondLargest)
        {
            secondLargest = a[i];
        }
    }

    if (secondSmallest == INT_MAX || secondLargest == INT_MIN)
    {
        printf("Second smallest or second largest element does not exist.\n");
    }
    else
    {
        printf("Second Smallest Element = %d\n", secondSmallest);
        printf("Second Largest Element = %d\n", secondLargest);
    }

    return 0;
}