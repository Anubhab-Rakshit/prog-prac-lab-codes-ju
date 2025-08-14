/*
    Q6. Implement Q.5 using structure.
*/

#include <stdlib.h>
#include <stdio.h>


typedef struct {
    char name[100];
    int age;
}Student;

void swap_age(Student *arr,int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j].age>arr[j+1].age){
                Student temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

void get(){
    int n;
    printf("Enter the number of students: \n");
    scanf("%d", &n);
    Student* arr = (Student*)malloc(n * sizeof(Student));
    for (int i = 0; i < n; i++) {
        printf("Enter the name and age of student %d: \n", i + 1);
        scanf("%s %d", arr[i].name, &arr[i].age);
        getchar();
    }

    swap_age(arr,n);
    printf("Names in ascending order :- \n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", arr[i].name, arr[i].age);
    }
}
int main(){
    get();
}