//WAP in C to find the GCD of two numbers using recursion. Read all pair of numbers from a file and store the result in sepearted file 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Recursive function to find GCD
int GCD(int a, int b){
    if (b == 0)
        return a;
    return GCD(b, a % b);
}
int main(int argc, char *argv[]){
    time_t start,end;
    start = clock();
    FILE *sourceFile, *destinationFile;
    int num1, num2, gcd;
    char ch;
    // Check command-line arguments
    if (argc != 3){
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }
    // Open source file for reading
    sourceFile = fopen(argv[1], "r");
    if (sourceFile == NULL){
        printf("Error opening source file.\n");
        return 1;
    }
    // Open destination file for writing
    destinationFile = fopen(argv[2], "w");
    if (destinationFile == NULL){
        printf("Error opening destination file.\n");
        fclose(sourceFile);
        return 1;
    }
    // Read all pairs of numbers from the source file
    while (fscanf(sourceFile, "%d %d", &num1, &num2) == 2){
        gcd = GCD(num1, num2);
        fprintf(destinationFile,"The GCD of %d and %d is %d\n",num1, num2, gcd);
    }
    fclose(sourceFile);
    fclose(destinationFile);
    // Display contents of the output file
    destinationFile = fopen(argv[2], "r");
    if (destinationFile == NULL){
        printf("Error opening output file.\n");
        return 1;
    }
    printf("Contents of the output file:\n\n");
    while ((ch = fgetc(destinationFile)) != EOF){
        putchar(ch);
    }
    end = clock();
    printf("Execution time: %f seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    fclose(destinationFile);
    return 0;
}