/*
3. Write a function that will have income and tax rate as arguments and will return tax amount. In case tax 
rate is not provided it will be automatically taken as 10%. Call it with and without taxes. 

Name :- Anubhab Rakshit
Class :- BCSE - II
Roll Number :- 002410501029

*/

#include <iostream>

using namespace std;
float calc(float income,float tax=10.0){ //function for calculating tax amount
    return (tax*income)/100.0;
}
int main(){
    float income;
    cout<<"Enter your income :- ";
    cin>>income;
    cout<<"Do you have a predefined tax rate 0=yes 1=no :- ";
    int ch;
    cin>>ch;
    float tax_amt;
    if(ch==0){
        cout<<"Enter your tax rate :- ";
        float rate;
        cin>>rate;
        tax_amt=calc(income,rate); //calling with custom tax rate
    }
    else{
        tax_amt=calc(income); //calling with default tax rate
    }

    cout<<"Calculated tax amt :- "<<tax_amt<<endl;
    return 0;
}