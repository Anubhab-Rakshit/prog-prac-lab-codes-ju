/*
    Q1. Write a program that will have an integer variable and a pointer (say p) pointing to it. Also have a pointer to pointer 
    pointing to p. Take the value for the integer variable and print it using p and pp.

    Name :- Anubhab Rakshit
    Class :- BCSE - II
    Roll number :- 002410501029
*/


/* Initialize pointer --> Initialize pointer to pointer --> Enter number --> do necessary steps --> print values*/
#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    int *p; //pointer
    int **pp;//pointer to pointer

    printf("Enter your number :- \n");
    scanf("%d",&n);

    p=&n; //address of variable
    pp=&p; // taking address of pointer
    printf("Value of n by pointer is %d\n",*p);
    printf("Value of n by pointer to pointer is %d\n",**pp);
    return 0;
}