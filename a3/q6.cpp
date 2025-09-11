/*
Define a structure student with roll and score as attributes and with two member functions to take input
and to show the data. Use the member functions to take data for a structure variable and to show. Write global 
function i) to modify score and ii) to show the data again

Name :- Anubhab Rakshit
Class :- BCSE-II
Roll Number :- 002410501029
*/

#include <iostream>

using namespace std;


typedef struct { //defining student struct
    int roll;
    float score;
    void input(){ // input data
        cin >> roll >> score;
    }
    void display(){ // display data
        cout<<"Data : Roll :- "<<roll<<" Score :- "<<score<<endl;
    }
}student;

void modify(student &s){ //modify student data
    int roll;
    float score;
    cout<<"Enter the modified student roll number and score";
    cin>>roll>>score;
    s.roll=roll; //re assigning the data
    s.score=score;
}
int main(){
    student s;
    cout<<"Enter roll and score :- ";
    s.input(); //calling for data input
    s.display(); //calling for display 
    int ch;
    cout<<"Do you want to modify score ? 0 for yes 1 for no ";
    cin>>ch;
    if(ch==0){
        modify(s); //calling for modify func
        s.display();
    }
    else{
        cout<<"Not modified!";
    }
}