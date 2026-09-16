#include <stdio.h>

// Function to exchange two numbers
void EXCHANGE(int *p, int *q)
{
    int temp;
    temp = *p;
    *p = *q;
    *q = temp;
}

// Function to rotate first p2 elements to the right by 1 position
void ROTATE_RIGHT(int *p1, int p2)
{
    int i;

    for (i = p2 - 1; i > 0; i--)
    {
        EXCHANGE(&p1[i], &p1[i - 1]);
    }
}

int main()
{
    int A[100];
    int N, p2, i;

    printf("Enter the size of array: ");
    scanf("%d", &N);

    printf("Enter the elements of the array:\n");

    for (i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }

    printf("Enter the number of elements to rotate: ");
    scanf("%d", &p2);

    printf("\nBefore ROTATE: ");

    for (i = 0; i < N; i++)
    {
        printf("%d ", A[i]);
    }

    ROTATE_RIGHT(A, p2);

    printf("\nAfter ROTATE: ");

    for (i = 0; i < N; i++)
    {
        printf("%d ", A[i]);
    }

    return 0;
}