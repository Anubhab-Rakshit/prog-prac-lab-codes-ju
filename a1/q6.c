/*
    Q6. Implement Q.5 using structure.
*/

/* 
Define a struct with(name and age) contained --> Enter the no of students --> Allocate memory for n number structs named Student --> Store the details --> Swap structs on 
comparison of ages (in ascending order) --> Print the data in ascending order 
*/

#include <stdlib.h>
#include <stdio.h>


typedef struct { // struct for storing data
    char name[100];
    int age;
}Student;

void swap_age(Student *arr,int n){ // function for swapping age
    for(int i=0;i<n-1;i++){ // Bubble sort
        for(int j=0;j<n-i-1;j++){
            if(arr[j].age>arr[j+1].age){ // comparing ages inside each struct (sorting in ascending order)
                Student temp=arr[j]; // swapping structs
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

void get(){ // entering details
    int n;
    printf("Enter the number of students: \n");
    scanf("%d", &n);
    Student* arr = (Student*)malloc(n * sizeof(Student)); // allocating memeory of n structs named Student
    for (int i = 0; i < n; i++) {
        printf("Enter the name and age of student %d: \n", i + 1);
        scanf("%s %d", arr[i].name, &arr[i].age);
        getchar();
    }

    swap_age(arr,n); // calling function for sorting ages 
    printf("Names in ascending order :- \n"); //printing names in ascending order
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", arr[i].name, arr[i].age); 
    }
}
int main(){ // main function
    get(); // calling function for getting details
}