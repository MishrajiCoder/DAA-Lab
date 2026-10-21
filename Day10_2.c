//We represent integers as the sum of Fibonacci numbers. In other words, instead of an array of bits, we keep an array of fits, where the ith least significant fit indicates whether the sum includes the ith Fibonacci number Fi.

#include <stdio.h>
#include <string.h>
#define MAX 100
int fibonacci(int n){
    int f[MAX];
    int i;
    f[1] = 1;
    f[2] = 2;
    for (i = 3; i <= n; i++)
        f[i] = f[i - 1] + f[i - 2];
    return f[n];
}

/* Convert fitstring to integer */
int fitToDecimal(char fit[]){
    int n = strlen(fit);
    int i, num = 0;
    int f[MAX];
    f[1] = 1;
    f[2] = 2;
    for (i = 3; i <= n; i++)
        f[i] = f[i - 1] + f[i - 2];
    for (i = 0; i < n; i++){
        if (fit[n - 1 - i] == '1')
            num += f[i + 1];
    }
    return num;
}

/* Convert integer to fitstring */
int decimalToFit(int num, char fit[]){
    int f[MAX], n = 1, i;
    int started = 0, j = 0;
    f[1] = 1;
    f[2] = 2;
    n = 2;
    while (f[n] <= num && n < MAX - 1){
        n++;
        f[n] = f[n - 1] + f[n - 2];
    }
    if (num == 0){
        fit[0] = '0';
        fit[1] = '\0';
        return 0;
    }
    for (i = n - 1; i >= 1; i--){
        if (f[i] <= num){
            fit[j++] = '1';
            num -= f[i];
            started = 1;
        }
        else if (started){
            fit[j++] = '0';
        }
    }
    fit[j] = '\0';
    return 0;
}

int main(){
    char fit[MAX], result[MAX];
    int num, choice;
    printf("Enter fitstring: ");
    scanf("%99s", fit);
    num = fitToDecimal(fit);
    printf("\n1. Increment");
    printf("\n2. Decrement");
    printf("\nEnter choice: ");
    scanf("%d", &choice);
    if (choice == 1)
        num++;
    else if (choice == 2 && num > 0)
        num--;
    else{
        printf("Invalid choice or cannot decrement zero.\n");
        return 0;
    }
    decimalToFit(num, result);
    printf("Resulting fitstring: %s\n", result);
    printf("Resulting integer: %d\n", num);
    return 0;
}