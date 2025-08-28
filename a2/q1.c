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

void display(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp==NULL) {

        printf("No file found!\n");
        return;
    }

    Student s;
    printf("\nDetails in file :- \n");
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (!s.deleted) {
            int total = 0;
            for (int i = 0; i < 5; i++) {
                total += s.marks[i];
            }
            printf("Name :- %s\n", s.name);
            printf("Roll :- %d\n", s.roll);
            printf("Total :- %d\n\n", total);
        }
    }

    fclose(fp);
}

void search(char *filename) {
    int roll,f=0;


    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("File doesn't exist!\n");
        return;
    }

    printf("Enter roll to search: ");
    scanf("%d", &roll);

    Student s;
    while(fread(&s, sizeof(Student), 1, fp)){

        if (s.roll==roll && !s.deleted) {

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

void edit(char *filename){

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

        if (s.roll == roll && !s.deleted) {
            f=1;
            printf("Enter new name :- ");
            getchar();
            scanf("%[^\n]s",s.name);
            
            printf("Enter new marks for all subjects :- ");

            for (int i=0;i<5;i++) 
            {
                scanf("%d", &s.marks[i]);
            }
            fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(&s,sizeof(Student),1,fp);
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

void logicalDelete(char *filename) {

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
            s.deleted = 1;
            fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(&s,sizeof(Student),1,fp);
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
void physicalDelete(char *filename) {

    FILE *fp = fopen(filename, "rb");

    FILE *temp = fopen("temp.dat", "wb");
    
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

    remove(filename);
    rename("temp.dat", filename);


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






