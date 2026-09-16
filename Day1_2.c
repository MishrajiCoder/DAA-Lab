#include <stdio.h>

int main()
{
    int n, i;
    int arr[100], prefixSum[100];

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    printf("Enter the elements of the array:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // First element of prefix sum array
    prefixSum[0] = arr[0];

    // Calculate remaining prefix sums
    for (i = 1; i < n; i++)
    {
        prefixSum[i] = prefixSum[i - 1] + arr[i];
    }

    printf("Prefix Sum Array:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", prefixSum[i]);
    }

    return 0;
}