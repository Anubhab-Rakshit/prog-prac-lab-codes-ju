/*
Write a function void f(int) that prints "inside f(int)" . Call the function with actual argument of type
i) int , ii) char iii) float and iv) double. Add one more function f(float) that prints "inside f(float)" .
Repeat the calls again and observe the outcomes.

Name :- Anubhab Rakshit
Class :- BSCE - II
Roll Number :- 002410501029

*/

#include <iostream>
using namespace std;

void f(int a){
    cout<<" inside f(int) \n";
}

void f(float a){
    cout<<" inside f(float)\n";
}
int main(){
    cout <<"int : ";f(12);
    cout <<"char : ";f((char)'a');
    cout <<"float : ";f((float)8);
   
}