/*
    Q2. Implement a one dimensional array of integers where array size of the array will be provided during runtime . Accept the
    value for the elements and print those using pointers.
    
    Name :- Anubhab Rakshit
    Class :- BCSE - II
    Roll number :- 002410501029
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    int *arr; //array pointer
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    arr=(int *)malloc(sizeof(int)*n); // allocating memory for n integers
    printf("Enter the values of n :- \n");
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]); // entering n elements
    }

    printf("The elements in the array :- \n");
    for(int i=0;i<n;i++){
        printf("%d ", *(arr+i)); //printing elements of the array
    }
    return 0;
}