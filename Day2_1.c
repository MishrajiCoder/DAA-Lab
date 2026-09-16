//WAP in C to convert the first 'n' deccimal numbers os a disc file to binary using recursion. Store the binary value in a seperate disc file 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Recursion Function
void decimalToBinary(int num, int binary[], int index){
    if (index < 0)
        return;
    binary[index] = num % 2;
    decimalToBinary(num / 2, binary, index - 1);
}
int main(int argc, char *argv[]){
    time_t start,end;
    start = clock();
    FILE *sourceFile, *destinationFile;
    int n, num;
    int binary[16];
    int i;
    if (argc != 4){
        printf("Usage: %s <n> <source_file> <destination_file>\n", argv[0]);
        return 1;
    }
    // Convert n from string to integer
    n = atoi(argv[1]);
    // Open source file
    sourceFile = fopen(argv[2], "r");
    if (sourceFile == NULL)
    {
        printf("Error opening source file.\n");
        return 1;
    }
    // File destination fetch
    destinationFile = fopen(argv[3], "w");
    if (destinationFile == NULL){
        printf("Error opening destination file.\n");
        fclose(sourceFile);
        return 1;
    }
    // Read first n decimal numbers
    for (i = 0; i < n; i++)
    {
        if (fscanf(sourceFile, "%d", &num) != 1)
            break;

        // Initialize binary array
        for (int j = 0; j < 16; j++){
            binary[j] = 0;
        }
        // Conversion of  decimal number to binary by rescursion
        decimalToBinary(num, binary, 15);
        // Store result in destination file
        fprintf(destinationFile,
                "The binary equivalent of %d is ", num);
        for (int j = 0; j < 16; j++){
            fprintf(destinationFile, "%d", binary[j]);
        }
        fprintf(destinationFile, "\n");
    }
    fclose(sourceFile);
    fclose(destinationFile);
    // Display contents of output file
    destinationFile = fopen(argv[3], "r");
    if (destinationFile == NULL){
        printf("Error opening output file.\n");
        return 1;
    }
    printf("Content of the first %d decimal and their equivalent binary numbers:\n\n", n);
    char ch;
    while ((ch = fgetc(destinationFile)) != EOF)
    {
        putchar(ch);
    }
    fclose(destinationFile);
    end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", cpu_time_used);
    return 0;
}
