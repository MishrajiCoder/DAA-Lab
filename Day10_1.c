//WAP to implement randomized quicksort 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* Exchange two elements */
int exchange(int *p, int *q){
    int temp = *p;
    *p = *q;
    *q = temp;
    return 0;
}

/* Partition using a randomly selected pivot */
int partition(int a[], int low, int high){
    int pivot, i, j;
    i = low + rand() % (high - low + 1);
    exchange(&a[i], &a[high]);
    pivot = a[high];
    i = low - 1;
    for (j = low; j < high; j++){
        if (a[j] <= pivot){
            i++;
            exchange(&a[i], &a[j]);
        }
    }
    exchange(&a[i + 1], &a[high]);
    return i + 1;
}

/* Randomized Quick Sort */
int randomizedQuickSort(int a[], int low, int high){
    int p;
    if (low < high){
        p = partition(a, low, high);
        randomizedQuickSort(a, low, p - 1);
        randomizedQuickSort(a, p + 1, high);
    }
    return 0;
}

/* Display array elements */
int display(int a[], int n){
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}

int main(){
    int a[1000], n, i;
    srand(time(NULL));
    printf("Enter number of elements: ");
    scanf("%d", &n);
    if (n <= 0 || n > 1000){
        printf("Invalid array size.\n");
        return 0;
    }
    printf("Enter array elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    printf("Before sorting: ");
    display(a, n);
    randomizedQuickSort(a, 0, n - 1);
    printf("After sorting: ");
    display(a, n);
    return 0;
}