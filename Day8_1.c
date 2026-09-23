//Write a program to implement the matrix chain multiplication problem using M-table & S-table to find optimal parentthesization of a matrix-chai  product. Print the number of scalar multiplications required for the given input.

#include <stdio.h>
#define MAX 20

/* Print optimal parenthesization */
int printParenthesis(int s[MAX][MAX], int i, int j){
    if (i == j){
        printf("A%d", i);
        return 0;
    }
    printf("(");
    printParenthesis(s, i, s[i][j]);
    printParenthesis(s, s[i][j] + 1, j);
    printf(")");
    return 0;
}

/* Matrix Chain Multiplication */
int matrixChain(int p[], int n, long long m[MAX][MAX],
                int s[MAX][MAX]){
    int i, j, k, len;
    long long cost;

    /* Single matrix requires no multiplication */
    for (i = 1; i <= n; i++)
        m[i][i] = 0;

    /* Chain length */
    for (len = 2; len <= n; len++){
        for (i = 1; i <= n - len + 1; i++){
            j = i + len - 1;
            m[i][j] = -1;
            for (k = i; k < j; k++){
                cost = m[i][k] +
                       m[k + 1][j] +
                       (long long)p[i - 1] *
                       p[k] *
                       p[j];
                if (m[i][j] == -1 || cost < m[i][j]){
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
    return 0;
}

/* Display M Table */
int displayM(long long m[MAX][MAX], int n){
    int i, j;
    printf("\nM Table:\n");
    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++)
            printf("%lld\t", m[i][j]);
        printf("\n");
    }
    return 0;
}

/* Display S Table */
int displayS(int s[MAX][MAX], int n){
    int i, j;
    printf("\nS Table:\n");
    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++)
            printf("%d\t", s[i][j]);
        printf("\n");
    }
    return 0;
}

int main(){
    int p[MAX];
    long long m[MAX][MAX] = {0};
    int s[MAX][MAX] = {0};
    int n;
    int rows, cols;
    int i;
    printf("Enter number of matrices: ");
    scanf("%d", &n);
    if (n <= 0 || n >= MAX){
        printf("Invalid number of matrices.\n");
        return 0;
    }

    /* Read dimensions */
    for (i = 1; i <= n; i++){
        printf("Enter row and column size of A%d: ",i);
        scanf("%d %d", &rows, &cols);
        if (i > 1 && p[i - 1] != rows){
            printf("Matrix dimensions are not compatible.\n");
            return 0;
        }
        p[i - 1] = rows;
        p[i] = cols;
    }
    /* Calculate optimal multiplication cost */
    matrixChain(p, n, m, s);
    /* Display tables */
    displayM(m, n);
    displayS(s, n);
    printf("\nOptimal parenthesization: ");
    printParenthesis(s, 1, n);
    printf("\n\nMinimum scalar multiplications: %lld\n",
           m[1][n]);
    return 0;
}