/*
    3. Implement a two dimensional array of integers using a) array of pointers b) pointer to pointer (with two
    malloc statements and again with one malloc statement, c) pointer to an array. Accept the value for the
    elements and print those.

    Name :- Anubhab Rakshit
    Class :- BCSE - II
    Roll number :- 002410501029
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int ch;
    printf("Enter your choice :- \n");
    scanf("%d",&ch); // enter your choice for particular method
    if (ch==1){ // method-1

    printf("Enter the number of rows :- \n");
    int r;  
    scanf("%d",&r); // value of row
    printf("Enter the number of columns :- \n");
    int c;
    scanf("%d",&c); //value of column

    
    int* arr[r]; // array of pointers
    for(int i=0;i<r;i++){
        arr[i]=(int*)malloc(c*sizeof(int)); // allocate memory for each row
    }
    printf("Enter your %d elements :- \n" , r*c);
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            scanf("%d",&arr[i][j]); // accept value for elements
        }
    }
    printf("\nYour %d elements are :- \n" , r*c);
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d ",arr[i][j]); // printing elements
        }
    }

   
    for(int i=0;i<r;i++){
        free(arr[i]); // free the allocated memory
    }
    }
    if (ch==2){ //method-2
    printf("Enter the number of rows :- \n");
    int r;
    scanf("%d",&r); //value of row
    printf("Enter the number of columns :- \n");
    int c;
    scanf("%d",&c); //value of column
    int** arr=malloc(r*sizeof(int*)); //pointer to pointer
    for(int i=0;i<r;i++){
        arr[i]=malloc(c*sizeof(int)); //allocating memory for c integers
    }
    printf("Enter your %d elements :- \n" , r*c);
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            scanf("%d",&arr[i][j]); //entering elements
        }
    }
    printf("\nYour %d elements are :- \n" , r*c);
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d ",arr[i][j]); //printing elements
        }
    }

    for(int i=0;i<r;i++){
        free (arr[i]); //free allocated memory for each row
    }
    free(arr); //free allocating memory of 2d array

    }
    if (ch==3){ //method-3
    printf("Enter the number of rows :- \n");
    int r;
    scanf("%d",&r);
    printf("Enter the number of columns :- \n");
    int c;
    scanf("%d",&c);

    int** arr=(int**)malloc(r*sizeof(int *)+r*c*sizeof(int));
    for(int i=0;i<r;i++){
        arr[i]=(int *)(arr+r+i*c);
    }
    printf("Enter your %d elements :- \n" , r*c);
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            scanf("%d",&arr[i][j]); //entering elements
            }
    }
    printf("\nYour %d elements are :- \n" , r*c);
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d ",arr[i][j]);//printing elements
        }
    }

    free(arr); //free allocated memory
    }

}