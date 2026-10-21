//we want to store a big binary counter in an array A. All the entries start at 0 and at each step we will be simply incrementing the counter. Let’s say our cost model is:
//whenever we increment the counter, we pay 1 for every bit we need to flip. Now we not only
//wish to increment a counter but also to reset it to 0 (i.e., make all bits in it 0). Counting the time
//to examine or modify a bit as θ(1) show how to implement a counter as an array of bits so that
//any sequence of n INCREMENT and RESET operations takes O(n) time on an initially zero
//counter. (Hint: Keep a pointer to the high-order 1.)

#include <stdio.h>
#define BITS 5
int main(){
    int counter[BITS] = {0};
    int cost = 0;
    int choice, i;
    printf("Initial Counter: ");
    for (i = 0; i < BITS; i++){
        printf("%d ", counter[i]);
    }
    printf("\n");
    while (1){
        printf("\n1. Increment");
        printf("\n2. Reset");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        if (choice == 1){
            i = BITS - 1;
            // Flip all trailing 1s to 0
            while (i >= 0 && counter[i] == 1){
                counter[i] = 0;
                cost++;
                i--;
            }
            // Flip the first 0 to 1
            if (i >= 0){
                counter[i] = 1;
                cost++;
            }
            else{
                printf("Counter overflow!\n");
            }
        }
        else if (choice == 2){
            // Reset all bits to 0
            for (i = 0; i < BITS; i++){
                if (counter[i] == 1){
                    counter[i] = 0;
                    cost++;
                }
            }
        }
        else if (choice == 3){
            break;
        }
        else{
            printf("Invalid choice!\n");
            continue;
        }
        printf("Counter: ");
        for (i = 0; i < BITS; i++){
            printf("%d ", counter[i]);
        }
        printf("\nCost of operation: %d", cost);
        printf("\n");
    }
    return 0;
}