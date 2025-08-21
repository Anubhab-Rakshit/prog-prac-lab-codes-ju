/*
    5. Store name and age of number of persons (number provided at run time). Collect the data and display
    data in the ascending order of age. Implement without using structure. Write functions for memory
    allocation of the list, sorting and display of data.

    Name :- Anubhab Rakshit
    Class :- BCSE - II
    Roll number :- 002410501029

*/

/* Create datatype for saving names , ages  --> Enter details --> Pass to swap function for swapping ages (sorting in ascending order) and corresponding indexes(stored in an array) -> Print the names according to the indexes*/

#include <stdio.h>
#include <stdlib.h>



void swap_age(int *ages, char **names,int n,int *index){ // function for swaping ages 
    for(int i=0;i<n-1;i++) // Bubble sort
    {
        for(int j=0;j<n-i-1;j++){
            if(ages[j]>ages[j+1]){
                int temp = ages[j]; //swapping ages (sorting in ascending order)
                ages[j] = ages[j+1];
                ages[j+1] = temp;
                temp=index[j]; // swapping indexes (sorting in ascending order)
                index[j]=index[j+1];
                index[j+1]=temp;
            }
        }
    }

}

void print_names(int *index,int n,char** names){ // function for printing names
    printf("Names in ascending order of age :- \n");
    for(int i=0;i<n;i++){
        int in=index[i];
        printf("%s\n",names[in]); // ages and indexes got swapped , so automatically names would be printed in sorted index order
    }

}
void get(){ // function for entering details 
    int n;
    printf("Enter the number of persons :- \n");
    scanf("%d",&n);

    char** names=(char **)malloc(sizeof(char* )*n);
    int* ages=(int*)malloc(sizeof(int)*n);
    int *index =(int *)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        index[i]=i;
        names[i]=(char*)malloc(sizeof(char)*100);
        printf("Enter the name and age of person %d :- \n",i+1);
        scanf("%s %d",names[i],ages+i);
        getchar();
    }
    swap_age(ages,names,n,index);
    print_names(index,n,names);
}
int main(){ // main function
    get();
}