/*
8. Create a STACK class with operation for initialization , push and pop. Support for checking 
underflow and overflow condition are to be provided.

Name:- Anubhab Rakshit
Class:- BCSE-II A1
Roll No:- 002410501029
*/

#include <iostream>

#define MAX_SIZE 100

using namespace std;

class STACK{
    float data[MAX_SIZE];
    int cnt;
    public:
        void initialize(){
            cnt=-1;
            cout << "Stack initialized ";
        }
        int fullstack(){
            return (cnt==MAX_SIZE)? 1:0;
        }
        int emptystack(){
            return (cnt==-1)?1:0;
        }
        void push(){
            int f=fullstack();
            if(f==1){
                cout<<"Stack would overflow";
            }
            else{
                cout<<"Enter your value :- ";
                cin>>f;
                data[++cnt]=f;
            }

        }

        float pop(){
            int f=emptystack();
            if(f==1){
                cout<<"Stack is empty";
                return -1;
            }
            else{
                return data[cnt--];
            }
        }
        void display(){
            int f=emptystack();
            if(f==1){
                cout<<"Stack is empty ! Nothing to display" ;
                return;
            }
            for(int i=cnt;i>=0;i--){
                cout<<data[i]<<" ";
            }
        }

};

int main(){
    while(1){
        cout<<"\nMENU:- \n1.Initialize stack \n2.Push Items \n3.Pop Item \n4.Display \n5. Exit"<<endl;
        int ch;
        cout<<"Enter your choice :-";
        cin>>ch;
        STACK s;
        float x;
        switch(ch){
            case 1: s.initialize(); break;
            case 2: s.push(); break;
            case 3: 
                x=s.pop();
                if(x!=-1){
                    cout<<"Popped value :- "<<x<<endl;
                }
                break;
            case 4: s.display(); break;
            case 5: exit(0); break;
            default: cout<<"Invalid choice";
        }
    }
}