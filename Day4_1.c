#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    int id;
    char *name;
    int age, height, weight;
};

int swap(struct person *a, struct person *b)
{
    struct person t = *a;
    *a = *b;
    *b = t;
    return 0;
}

int readData(struct person **p, int *n)
{
    FILE *fp = fopen("person.dat", "r");
    char name[50];
    int i;

    if (fp == NULL)
        return 0;

    fscanf(fp, "%d", n);
    *p = malloc(*n * sizeof(struct person));

    for (i = 0; i < *n; i++)
    {
        fscanf(fp, "%d %s %d %d %d",
               &(*p)[i].id, name, &(*p)[i].age,
               &(*p)[i].height, &(*p)[i].weight);

        (*p)[i].name = malloc(strlen(name) + 1);
        strcpy((*p)[i].name, name);
    }

    fclose(fp);
    return 1;
}

int display(struct person a[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        printf("%d %s %d %d %d\n",
               a[i].id, a[i].name, a[i].age,
               a[i].height, a[i].weight);

    return 0;
}

int minHeap(struct person a[], int n)
{
    int i, l, r, s;

    for (i = n / 2 - 1; i >= 0; i--)
    {
        s = i;
        l = 2 * i + 1;
        r = 2 * i + 2;

        if (l < n && a[l].age < a[s].age)
            s = l;

        if (r < n && a[r].age < a[s].age)
            s = r;

        if (s != i)
        {
            swap(&a[i], &a[s]);
            i++;
        }
    }

    return 0;
}

int maxHeap(struct person a[], int n)
{
    int i, l, r, s;

    for (i = n / 2 - 1; i >= 0; i--)
    {
        s = i;
        l = 2 * i + 1;
        r = 2 * i + 2;

        if (l < n && a[l].weight > a[s].weight)
            s = l;

        if (r < n && a[r].weight > a[s].weight)
            s = r;

        if (s != i)
        {
            swap(&a[i], &a[s]);
            i++;
        }
    }

    return 0;
}

int main()
{
    struct person *p = NULL;
    int n = 0, ch;

    while (1)
    {
        printf("\n1.Read Data");
        printf("\n2.Min-Heap (Age)");
        printf("\n3.Max-Heap (Weight)");
        printf("\n4.Youngest Person Weight");
        printf("\n5.Exit");

        printf("\nEnter option: ");
        scanf("%d", &ch);

        if (ch == 1)
        {
            if (readData(&p, &n))
                display(p, n);
            else
                printf("File error\n");
        }

        else if (ch == 2)
        {
            if (p == NULL)
                printf("Read data first\n");
            else
            {
                minHeap(p, n);
                display(p, n);
            }
        }

        else if (ch == 3)
        {
            if (p == NULL)
                printf("Read data first\n");
            else
            {
                maxHeap(p, n);
                display(p, n);
            }
        }

        else if (ch == 4)
        {
            if (p == NULL)
                printf("Read data first\n");
            else
                printf("Weight = %.2f kg\n",
                       p[0].weight / 2.20462);
        }

        else if (ch == 5)
            break;

        else
            printf("Invalid option\n");
    }

    return 0;
}