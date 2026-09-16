#include <stdio.h>
#include <stdlib.h>

struct SYMBOL
{
    char alphabet;
    int frequency;
    struct SYMBOL *left;
    struct SYMBOL *right;
};

/* Swap two nodes in priority queue */
int swap(struct SYMBOL **a, struct SYMBOL **b)
{
    struct SYMBOL *temp;

    temp = *a;
    *a = *b;
    *b = temp;

    return 0;
}

/* Min-Heapify based on frequency */
int heapify(struct SYMBOL *heap[], int n, int i)
{
    int smallest, left, right;

    smallest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;

    if (left < n &&
        heap[left]->frequency < heap[smallest]->frequency)
        smallest = left;

    if (right < n &&
        heap[right]->frequency < heap[smallest]->frequency)
        smallest = right;

    if (smallest != i)
    {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, n, smallest);
    }

    return 0;
}

/* Insert a node into Min-Priority Queue */
int insert(struct SYMBOL *heap[], int *n, struct SYMBOL *node)
{
    int i, parent;

    i = *n;
    heap[i] = node;
    (*n)++;

    while (i > 0)
    {
        parent = (i - 1) / 2;

        if (heap[parent]->frequency <= heap[i]->frequency)
            break;

        swap(&heap[parent], &heap[i]);

        i = parent;
    }

    return 0;
}

/* Delete minimum frequency node */
struct SYMBOL *deleteMin(struct SYMBOL *heap[], int *n)
{
    struct SYMBOL *temp;

    if (*n == 0)
        return NULL;

    temp = heap[0];

    heap[0] = heap[*n - 1];
    (*n)--;

    if (*n > 0)
        heapify(heap, *n, 0);

    return temp;
}

/* Create Huffman Tree */
struct SYMBOL *createHuffman(struct SYMBOL *heap[], int n)
{
    struct SYMBOL *left;
    struct SYMBOL *right;
    struct SYMBOL *parent;

    while (n > 1)
    {
        left = deleteMin(heap, &n);
        right = deleteMin(heap, &n);

        parent = (struct SYMBOL *)
                 malloc(sizeof(struct SYMBOL));

        parent->alphabet = '-';
        parent->frequency =
            left->frequency + right->frequency;

        parent->left = left;
        parent->right = right;

        insert(heap, &n, parent);
    }

    return heap[0];
}

/* In-order traversal */
int inorder(struct SYMBOL *root)
{
    if (root != NULL)
    {
        inorder(root->left);

        if (root->alphabet != '-')
            printf("%c ", root->alphabet);

        inorder(root->right);
    }

    return 0;
}

int main()
{
    struct SYMBOL *heap[100];
    struct SYMBOL *root;

    int n, i;
    char ch;
    int freq;

    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    printf("Enter the alphabets:\n");

    for (i = 0; i < n; i++)
    {
        scanf(" %c", &ch);

        heap[i] = (struct SYMBOL *)
                  malloc(sizeof(struct SYMBOL));

        heap[i]->alphabet = ch;
        heap[i]->left = NULL;
        heap[i]->right = NULL;
    }

    printf("Enter its frequencies:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &freq);
        heap[i]->frequency = freq;
    }

    /* Build initial Min-Heap */
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(heap, n, i);

    root = createHuffman(heap, n);

    printf("\nIn-order traversal of the tree (Huffman): ");

    inorder(root);

    return 0;
}