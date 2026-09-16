//Write a program to find the maximum profit nearest to but not exceeding the given knapsack capacity using the Fractional Knapsack algorithm.
#include <stdio.h>

struct ITEM
{
    int item_id;
    float item_profit;
    float item_weight;
    float ratio;
};

/* Function to swap two items */
int swap(struct ITEM *a, struct ITEM *b)
{
    struct ITEM temp;

    temp = *a;
    *a = *b;
    *b = temp;

    return 0;
}

/* Max Heapify based on profit/weight ratio */
int heapify(struct ITEM a[], int n, int i)
{
    int largest, left, right;

    largest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;

    if (left < n && a[left].ratio > a[largest].ratio)
        largest = left;

    if (right < n && a[right].ratio > a[largest].ratio)
        largest = right;

    if (largest != i)
    {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }

    return 0;
}

/* Heap Sort using Max Heap */
int heapSort(struct ITEM a[], int n)
{
    int i;

    /* Build Max Heap */
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    /* Heap Sort */
    for (i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
    }

    /* Reverse to obtain non-increasing order */
    for (i = 0; i < n / 2; i++)
        swap(&a[i], &a[n - i - 1]);

    return 0;
}

/* Fractional Knapsack */
int fractionalKnapsack(struct ITEM a[], int n, float capacity)
{
    int i;
    float fraction;
    float totalProfit = 0;

    printf("\nSelected Items:\n");
    printf("Item\tProfit\tWeight\tFraction\n");

    for (i = 0; i < n; i++)
    {
        if (capacity <= 0)
            fraction = 0;

        else if (a[i].item_weight <= capacity)
        {
            fraction = 1;

            capacity = capacity - a[i].item_weight;
            totalProfit = totalProfit + a[i].item_profit;
        }

        else
        {
            fraction = capacity / a[i].item_weight;

            totalProfit = totalProfit +
                          a[i].item_profit * fraction;

            capacity = 0;
        }

        printf("%d\t%.2f\t%.2f\t%.2f\n",
               a[i].item_id,
               a[i].item_profit,
               a[i].item_weight,
               fraction);
    }

    printf("\nMaximum Profit = %.2f\n", totalProfit);

    return 0;
}

int main()
{
    struct ITEM a[100];

    int n, i;
    float capacity;

    printf("Enter number of items: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        a[i].item_id = i + 1;

        printf("Enter profit and weight of item %d: ",
               i + 1);

        scanf("%f %f",
              &a[i].item_profit,
              &a[i].item_weight);

        a[i].ratio =
            a[i].item_profit / a[i].item_weight;
    }

    printf("Enter capacity of knapsack: ");
    scanf("%f", &capacity);

    /* Sort according to profit/weight ratio */
    heapSort(a, n);

    printf("\nItems in Non-Increasing Order of Profit/Weight:\n");

    printf("Item\tProfit\tWeight\tRatio\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               a[i].item_id,
               a[i].item_profit,
               a[i].item_weight,
               a[i].ratio);
    }

    /* Apply Fractional Knapsack */
    fractionalKnapsack(a, n, capacity);

    return 0;
}