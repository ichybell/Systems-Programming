// A simple C program to practice using the malloc() function for memory allocation

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) 
{
    int n, i,sum, *ptr;
    float mean, SD = 0.0;
    printf("Welcome to the integer program. We will calculate the standard deviation and sum of your intger input. Please input number of intgers to be used\n> ");
    scanf("%d", &n);
    ptr = (int *) malloc(n *sizeof(int)); // Allocating memory 

    // Deal with memory error
    if(ptr == NULL) {
        printf("Error with memory allocation!");
        exit(0);
    }
    printf("Enter your integers.\n");
    for(i = 0; i < n; ++i) {
        printf("> ");
        scanf("%d", ptr + i);
        sum += *(ptr + i);
    }
    mean = sum / 10;

    printf("\nYour integers are:\n");
    for(i = 0; i < n; ++i) {
        printf("%d\n", *(ptr + i));
        SD += pow(*(ptr + i) - mean, 2);
    }
    SD = sqrt(SD / 10);
    printf("Sum of given integers = %d\n", sum);
    printf("Standard deviation of given integers is = %f", SD);
    return 0;
}
