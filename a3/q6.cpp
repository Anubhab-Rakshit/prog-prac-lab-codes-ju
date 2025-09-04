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


typedef struct {
    int roll;
    float score;
    void input(){
        cin >> roll >> score;
    }
    void display(){
        cout<<"Data : Roll :- "<<roll<<" Score :- "<<score<<endl;
    }
}student;

void modify(student s){
    
}
int main(){
    student s;
    cout<<"Enter roll and score :- ";
    s.input();
    s.display();
    int ch;
    cout<<"Do you want to modify score ? 0 for yes 1 for no ";
    if(ch==0){
        modify(s);
    }
    else{
        cout<<"Not modified!";
    }
}