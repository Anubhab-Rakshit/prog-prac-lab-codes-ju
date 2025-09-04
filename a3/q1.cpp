/* 
1. Write a function swap(a,b) to interchange the values of two variables . Do not use pointers .

Name :- Anubhab Rakshit
Class :- BCSE - II
Roll Number :- 002410501029

*/

#include <iostream>

using namespace std;

pair<int,int> swap(int a,int b){
    return {b,a};
}

int main(){
    int a,b;
    cout<<"Enter your value a and b :- ";
    cin>>a>>b;
    pair <int,int> x=swap(a,b);
    a=x.first;
    b=x.second;
    cout<<"a = "<< a << " b = " << b << endl;
    return 0;
}