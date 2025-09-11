/*
2. Write a function max(a,b) that will return the reference of larger value . Store the returned information to x
where x is a i) variable of type a or b ii) variable referring to type a or b . In both the cases modify 
x. Check also the values of a and b.

Name :- Anubhab Rakshit
Class :- BCSE - II
Roll Number :- 002410501029

*/

#include <iostream>

using namespace std;

int max(int a,int b){ //passing value
    if (a>b){
        return a;
    }
    else{
        return b;
    }
}

int& max_ref(int &a,int &b){ // passing reference
    if (a>b){
        return a;
    }
    else{
        return b;
    }
}
int main(){
    int a,b;
    cout<<"Enter your elements :- ";
    cin>>a>>b;
    int x=max(a,b);
    cout<<"Max of them x = "<<x<<endl;
    int &y=max_ref(a,b);
    cout<<"Max of them by reference type x = "<<y<<endl;
    return 0;
}