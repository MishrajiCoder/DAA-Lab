//write a program to find out the Longest Common Subsequence of two given strings. Calculate the length of the LCS. 

#include <stdio.h>
#include <string.h>
#define MAX 100

/* Find LCS and store it in result */
int findLCS(char a[], char b[], int m, int n, char result[]){
    int dp[MAX][MAX];
    int i, j;
    int index;

    /* Build LCS table */
    for (i = 0; i <= m; i++)
        dp[i][0] = 0;

    for (j = 0; j <= n; j++)
        dp[0][j] = 0;

    for (i = 1; i <= m; i++){
        for (j = 1; j <= n; j++){
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else if (dp[i - 1][j] >= dp[i][j - 1])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = dp[i][j - 1];
        }
    }

    /* Reconstruct LCS */
    index = dp[m][n];
    result[index] = '\0';
    i = m;
    j = n;
    while (i > 0 && j > 0){
        if (a[i - 1] == b[j - 1])
        {
            result[index - 1] = a[i - 1];
            i--;
            j--;
            index--;
        }

        else if (dp[i - 1][j] >= dp[i][j - 1])
            i--;
        else
            j--;
    }
    return dp[m][n];
}

int main(){
    char a[MAX], b[MAX], lcs[MAX];
    int m, n;
    int length;
    printf("Enter the first string into an array: ");
    scanf("%s", a);
    printf("Enter the second string into an array: ");
    scanf("%s", b);
    m = strlen(a);
    n = strlen(b);
    length = findLCS(a, b, m, n, lcs);
    printf("\nLCS: %s", lcs);
    printf("\nLCS Length: %d\n", length);
    return 0;
}