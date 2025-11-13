/*
Create an APPLICANT class with application id (auto generated as last id+1) , name and score. Support 
must be there to receive applicant data , show applicant details , and to find out number of applicants.

Name:- Anubhab Rakshit
Class:- BCSE-II A1
Roll No:- 002410501029
*/

#include<iostream>
#include<string>

using namespace std;
#define MAX 100
class APPLICANT{
    int app_id;
    string name;
    int score;

    public:
        static int counter;
        void add();
        void show();
        void count();
};

int APPLICANT::counter=0;
void APPLICANT::add(){
    cout<<"Enter name of the applicant :- ";
    cin>>name;
    cout<<"Enter your score :- ";
    cin>>score;
    app_id=counter;
    counter+=1;
}

void APPLICANT::show(){
    cout<<"Details of the applicant :- ";
    if (app_id > counter){
        cout<<"Applicant not found";
    }
    else{
        cout<<"Application id :- "<<app_id<<"\n"<<"Name :- "<<name<<"\n"<<"Score :- "<<score<<endl;
    }
}

void APPLICANT::count(){
    cout<<"No of applicants in system :- "<<counter<<endl;
}

int main(){
    cout<<"################ SYSTEM ################" <<endl;
    APPLICANT array[100];
    int count=0;
    int f=1;
    while(f){

        cout<<"\n MENU :- \n 1. Add Applicant \n 2. Show Applicant Details \n 3.Show Number of Applications \n 4. Exit"<<endl;
        int ch;
        cout<<"Enter your choice :- ";
        cin>>ch;
        switch(ch){
            case 1:
            count+=1;
            array[count-1].add();
            break;

            case 2:
            int details;
            cout<<"Enter the application id :- ";
            cin>>details;
            array[details].show();
            break;

            case 3:
            array[0].count();
            break;

            case 4:
            cout<<"Exiting System.....";
            f=0;
            break;

            default:
            cout<<"Invalid choice";
        }
    }
}