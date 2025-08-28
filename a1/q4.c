/*
    Q4. Implement the programs in Q.2 and 3 breaking it into functions for i) getting the dimensions from user,
        ii) dynamic memory allocation, iii) accepting the values and iv) printing the values.

    Name :- Anubhab Rakshit
    Class :- BCSE - II
    Roll number :- 002410501029

*/

#include <stdio.h>
#include <stdlib.h>

int q2_dim(){ // function for dimension of 1d array
    printf("Enter the dimension for the 1d array :- \n");
    int num;
    scanf("%d", &num);
    return num;
}

void q2_alloc(int *arr,int n){ // function for allocating memory to 1d array
    arr = (int *)malloc(n * sizeof(int));
    printf("Enter the elements :- \n");
    for(int i=0;i<n;i++){
        scanf("%d",arr+i);
    }
    printf("Your elements :- \n");
    for(int i=0;i<n;i++){
        printf("%d ",*(arr+i));
    }
    printf("\n");
}


void get(int **arr,int r,int c){ // function for entering elements into 2d array
    printf("Enter your %d elements :- \n" , r*c);
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            scanf("%d",&arr[i][j]);
            }
    }

}

void print(int **arr,int r,int c){ // function for printing elements of 2d array
    printf("\nYour %d elements are :- \n" , r*c);
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }

}

void methoda(){ // method of array of pointers (2d array)
    printf("Enter the number of rows :- \n");
    int r;
    scanf("%d",&r);
    printf("Enter the number of columns :- \n");
    int c;
    scanf("%d",&c);

    int* arr[r];
    for(int i=0;i<r;i++){
        arr[i]=(int*)malloc(c*sizeof(int));
    }
    get(arr,r,c);
    print(arr,r,c);
    for(int i=0;i<r;i++){
        free(arr[i]);
    }
}

void methodb_two(){ // method for double malloc (2d array)
    printf("Enter the number of rows :- \n");
    int r;
    scanf("%d",&r);
    printf("Enter the number of columns :- \n");
    int c;
    scanf("%d",&c);
    int** arr=malloc(r*sizeof(int*));
    for(int i=0;i<r;i++){
        arr[i]=malloc(c*sizeof(int));
    }
    get(arr,r,c);
    print(arr,r,c);
    for(int i=0;i<r;i++){
        free (arr[i]);
    }
    free(arr);

}

void methodb_single(){ // method for single malloc (1d array)
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
    get(arr,r,c);
    print(arr,r,c);
    free(arr);
}

void methodc(){ // method of pointer to an array

    printf("Enter the number of rows :- \n"); 
        int r;
        scanf("%d",&r);
        printf("Enter the number of columns :- \n");
        int c;
        scanf("%d",&c);
        int (*arr)[c]; // pointer to an array
        arr=malloc(sizeof(int *)*c); // allocating memory
        get(arr,r,c);
        print(arr,r,c);
        free (arr); //free allocated memory

}


int main(){
    int ch;
    printf("Enter your choice :- \n"); 
    scanf("%d",&ch); // Choice for switch case
    switch(ch){
        case 1:
        methoda();
        break;
        case 2:
        methodb_two();
        break;
        case 3:
        methodb_single();
        break;
        case 4:
        methodc();
        break;
        case 5:
        printf("For Question 2 \n");
        int n=q2_dim(); // getting dimension
        int *arr;
        q2_alloc(arr,n); // allocating memory and print elements
        break;
        default:
        printf("Invalid choice\n");
    }
}


