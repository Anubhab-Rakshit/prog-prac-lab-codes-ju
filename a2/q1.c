/*
Write a program to store student information in a file and to do the following operations. Information includes roll, name, and score in five subjects. Use may like to add record (check if roll number is unique), display all records showing roll, name and total score. User may search for the record against a roll.
User may edit the details in a record.User may delete record.Deletion may be logical (by some means indicate it is an invalid record and to be avoided in processing) and physical(file will not have the record ).

Name :- Anubhab Rakshit
Class :- BCSE - II
Roll Number :- 002410501029

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//defining student structure
typedef struct {
    int roll;
    char name[41];
    int marks[5];
    int deleted; // 0 = active, 1 = logically deleted
} Student;

//declaring all the functions for free access
/*
void add(char* filename);
void display(char* filename);
void search(char* filename);
void edit(char* filename);
void logicalDelete(char* filename);
void physicalDelete(char* filename);
bool isRollUnique(char* filename,int roll);

*/

bool isRollUnique(char* ,int );

void add(char *filename) {

    Student s;
    //opening file in append and binary mode
    FILE *fp = fopen(filename, "ab+");
    if(fp==NULL){
      printf("Error opening file!\n");
      return;
    }

    //input
    printf("Enter roll no :- ");
    scanf("%d",&s.roll);

    //checking for unique roll number
    if(!isRollUnique(filename,s.roll)){
      printf("Roll number already exists!\n");
      fclose(fp);
      return;
    }

    //input  name and marks
    printf("Enter name :- ");
    getchar();

    scanf("%[^\n]s",s.name);
   
    printf("Enter marks in 5 subjects :- \n");

    for (int i=0;i<5;i++) {
        scanf("%d", &s.marks[i]);
    }

    //setting variable active
    s.deleted = 0;
    fwrite(&s,sizeof(Student),1,fp);
    printf("Record added\n");

    fclose(fp);
}

void display(char *filename) { // display function
    FILE *fp = fopen(filename, "rb");
    if (fp==NULL) {

        printf("No file found!\n");
        return;
    }

    Student s;
    printf("\nDetails in file :- \n");
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (!s.deleted) { // not temporarily deleted 
            int total = 0;
            for (int i = 0; i < 5; i++) {
                total += s.marks[i]; // summation of marks
            }
            printf("Name :- %s\n", s.name);
            printf("Roll :- %d\n", s.roll);
            printf("Total :- %d\n\n", total);
        }
    }

    fclose(fp);
}

void search(char *filename) { // search function
    int roll,f=0;


    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("File doesn't exist!\n");
        return;
    }

    printf("Enter roll to search: ");
    scanf("%d", &roll);

    Student s;
    while(fread(&s, sizeof(Student), 1, fp)){ //reading till end of file

        if (s.roll==roll && !s.deleted) { //roll matched and not temporarily deleted

            printf("Record Found!\n  Roll :- %d\nName :- %s\nMarks :- ", s.roll, s.name);
            for (int i=0;i<5;i++){ 
                printf("%d ",s.marks[i]);
            }
            printf("\n");
            f=1;
            break;
        }
    }
  
    if (f==0) {
        printf("Record not found!\n");
    }

    fclose(fp);

}

void edit(char *filename){ //edit data in function

    int roll, f=0;
    FILE *fp = fopen(filename, "rb+");
    if (fp==NULL) {
        printf("File not found!\n");
        return;
    }


    printf("Enter roll to edit: ");
    
    scanf("%d", &roll);

    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {

        if (s.roll == roll && !s.deleted) { //data to be edited (found)
            f=1;
            printf("Enter new name :- ");
            getchar();
            scanf("%[^\n]s",s.name);
            
            printf("Enter new marks for all subjects :- ");

            for (int i=0;i<5;i++) 
            {
                scanf("%d", &s.marks[i]);
            }
            fseek(fp, -sizeof(Student), SEEK_CUR); // moving  cursor back with sizeof(Student)
            fwrite(&s,sizeof(Student),1,fp); // writing new data 
            printf("Record updated\n");
            break;
        }
    }

    if (f==0) 
    {   
        printf("Record not found!\n");
    }
    fclose(fp);
}

void logicalDelete(char *filename) { //logical deletion function (stays in file but is deleted)

    int roll, f= 0;
    FILE *fp = fopen(filename, "rb+");
    if (fp==NULL) {
        printf("File not found!\n");
        return;
    }


    printf("Enter roll to logically delete :- ");
    scanf("%d", &roll);


    Student s;
    while (fread(&s,sizeof(Student),1,fp)) {
        if (s.roll==roll && !s.deleted) {
            s.deleted = 1; // changing from 0 to 1 , here 0 is not logically deleted and 1 is logically deleted
            fseek(fp, -sizeof(Student), SEEK_CUR); // moving cursor back by 1 * sizeof(Student)
            fwrite(&s,sizeof(Student),1,fp); // writing new data
            printf("Record logically deleted\n");
            f=1;
            break;
        }
    }

    if(f==0)
    {
        printf("Record not found\n");
    }
    fclose(fp);
}
void physicalDelete(char *filename) { // physical deleting all data which are logically deleted

    FILE *fp = fopen(filename, "rb");

    FILE *temp = fopen("temp.dat", "wb"); // temporarily creating a new file
    
    if (fp==NULL||temp==NULL) {
        printf("Error \n");
        return;
    }
    //manually only storing elements that are not logically deleted
    Student s;
    while (fread(&s,sizeof(Student),1,fp)) {
        if(!s.deleted)
        { 
            fwrite(&s,sizeof(Student),1,temp);
        }
    }


    fclose(fp);
    fclose(temp);

    remove(filename); //removing original file
    rename("temp.dat", filename); //renaming temp file to original file


    printf("Physical deletion completed!\n");
}

bool isRollUnique(char* filename,int roll){

    FILE *fp = fopen(filename, "rb");
    if (fp==NULL)
    {
        return 1; // no file means unique
    }
    Student s;
    while (fread(&s,sizeof(Student),1,fp)) {
      if (s.roll==roll &&!s.deleted) {
            fclose(fp);
            return false;
        }
    }

    fclose(fp);
    return true;
}

int main(int argc,char *argv[]) {
    int ch;

    while (1) {
      //final menu for operations
      printf("\nMenu:\n");
        printf("1.Add Record\n");
        printf("2.Display Records\n");
        printf("3.Search by Roll\n");
        printf("4.Edit\n");
        printf("5.Logical Delete\n");
        printf("6.Physical Delete\n");
        printf("7.Exit\n");
        printf("Enter: ");
        scanf("%d", &ch);
        
        switch (ch) {
            case 1: 
                add(argv[1]); 

                break;
            case 2: 
                display(argv[1]); 
                break;
            case 3: 
                search(argv[1]);  
                break;
            case 4: 
                edit(argv[1]); 
                break;
            case 5: 
                logicalDelete(argv[1]); 
                break;
            case 6: 
                physicalDelete(argv[1]); 
                break;
            case 7: 
                exit(0);
            default: printf("Invalid choice!\n");

        }
    }
    return 0;
}






