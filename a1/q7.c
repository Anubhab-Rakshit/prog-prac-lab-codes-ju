/*
Maintain a list to store roll, name and score of students. As and when required student record may be
added or deleted. Also, the list has to be displayed. Design suitable functions for different operations. 

Name:- Anubhab Rakshit
Class :- BCSE-II
Roll Number :- 002410501029
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { // defining struct
    int roll;
    char name[41];
    int score;
}Student;

Student* students=NULL; //allocating a null Student* pointer to hold all values
int count=0; // number of values


void add(int roll,char *name,int score){ // add function

    students=(Student* )realloc(students,(count+1)*sizeof(Student)); // reallocating memory (increasing to hold 1 more student)
    students[count].roll=roll;
    strcpy(students[count].name,name);
    students[count].score=score;
    count+=1;

    printf("Record Added Successfully !!");
}

void delete(int roll){ //delete function
    int f=-1;
    for(int i=0;i<count;i++){
        if(students[i].roll==roll){ //data found
            f=i;
            break;
        }
    }
    if(f==-1) //data not found
    {
        printf("Student record not found \n");
        return;
    }
    for(int i=f;i<count-1;i++){ //shifting elements to delete the record
        students[i]=students[i+1];
    }
    count-=1; //decreasing student count by 1
    students=(Student*)realloc(students,count*sizeof(Student)); //reallocating memory for new number of students
    printf("\n Student Record Succesfully Deleted ! \n");
}

void display(){ //display function
    if (count==0){
        printf("No Records found"); //no records found
        return;
    }
    printf("\n All Records :- \n");
    for(int i=0;i<count;i++){
        printf(" Roll :- %d \n Name :- %s \n Score :- %d \n",students[i].roll,students[i].name,students[i].score);
    }
}

int main()
{
    int ch,roll,score;
    char name[41];
    while(1){
        printf("\nMenu:- \n 1. ADD \n 2. DELETE \n 3. PRINT \n 4. EXIT\n"); //menu
        printf("Enter your choice :-");
        scanf("%d",&ch);
        switch(ch){
            case 1: //add data 
                printf("Enter name :- ");
                getchar();
                scanf("%[^\n]s",name);
                printf("\nEnter Roll No :- ");
                scanf("%d",&roll);
                printf("\nEnter Score :- ");
                scanf("%d",&score);
                add(roll,name,score);
                break;
            case 2: //delete data
                printf("Enter roll to delete :- ");
                scanf("%d",&roll);
                delete(roll);
                break;
            case 3: //display data
                display();
                break;
            case 4: //exit system
                free(students);
                printf("Exiting system ...");
                exit(0);
            default:
                printf("Invalid choice ");
        }
    }
}