/*
Consider an array that stores roll, name, and score of number of students. Develop a function to sort the
array. User of sort() will develop the comparison function for sorting on roll/score and ascending or
descending order and reuse the same sort() function. 

Name :- Anubhab Rakshit
Class :- BCSE-II
Roll Number :- 002410501029
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int roll;
    char name[100];
    int score;
} Student;

//sorting
void sort(Student *arr, int n, bool(*fp)(Student, Student)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i+1; j < n; j++) {
            if (fp(arr[i], arr[j])) {
                Student temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// all possibilities 
// Roll ascending
bool rollAsc(Student a, Student b) {
    return a.roll > b.roll;
}
// Roll descending
bool rollDesc(Student a, Student b) {
    return b.roll > a.roll;
}
// Score ascending
bool scoreAsc(Student a, Student b) {
    return a.score > b.score;
}
// Score descending
bool scoreDesc(Student a, Student b) {
    return b.score > a.score;
}

// Display
void display(Student *arr,int n) {

    printf("\nStudent Records\n");

    for (int i = 0;i<n;i++) {

        printf("Roll: %d, Name: %s, Score: %d\n",arr[i].roll, arr[i].name, arr[i].score);
    }
}

int main() {
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);

    Student *arr=(Student*)malloc(n*sizeof(Student));
    // Input
    for (int i = 0; i < n; i++) {
        printf("Enter roll: ");
        scanf("%d", &arr[i].roll);
        printf("Enter name: ");
        getchar();
        scanf("%[^\n]s", arr[i].name);
        printf("Enter score: ");
        scanf("%d", &arr[i].score);
    }
    while(1){
    int ch;
    printf("\nSort by :- \n1. Roll-Ascending \n2. Roll-Descending \n3. Score-Ascending \n4. Score-Descending\n");
    scanf("%d", &ch);
    //menu
    switch (ch){
        case 1: 
            sort(arr,n,rollAsc);
            break;
        case 2: 
            sort(arr,n,rollDesc);
            break;
        case 3: 
            sort(arr,n,scoreAsc);
            break;
        case 4: 
            sort(arr,n,scoreDesc);
            break;
        default:
            printf("Invalid choice\n");
            free(arr);
            exit(0);
        }

    display(arr, n);
    }
    //clearing up memory
    free(arr);
    return 0;
}