/*
5. Define functions f(int,int) and f(char,int). Call the functions with arguments of type (int,char),
(char,char) , (float,float) . Observe and analyze the outcome.

Name :- Anubhab Rakshit
Class :- BCSE-II
Roll Number :- 002410501029
*/

#include <iostream>

using namespace std;

void f(int a,int b){
    cout<<"Inside f(int,int) \n";
}
void f(char a,int b){
    cout<<"Inside f(char,int) \n";
}
int main(){
    cout<<"Passing (int,char) ";f(12,'c');
    cout<<"Passing (char,int) ";f('a',123);
    //cout<<"Passing (float,float)";f((float)12,(float)26.5);
    return 0;
}