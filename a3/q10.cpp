/*

    Q10. Design a STUDENT class to store roll, name, course, admission date and marks in 5 subjects. Provide methods corresponding to admission (marks are not available 
    then), receiving marks and preparing mark sheet. Support must be there to show the number of students who have taken admission.

    Name:- Anubhab Rakshit
    Class:- BCSE-II A1
    Roll No:- 002410501029
*/

#include<bits/stdc++.h>

using namespace std;

class STUDENT{
    string roll, name, course, admission_date;

    vector<int> marks;

    public :

        STUDENT(string r, string n, string c, string a){

            roll = r;
            name = n;
            course = c;
            admission_date = a;
            marks.assign(5,0);
        }
        void take_marks(){
            cout << "Enter marks : ";
            int temp;
            for(int i=0;i<5;i++) cin >> temp, marks[i] = temp;
        }
        void prepare(){

            cout << "Name : " << name << "\nRoll : " << roll << "\nCourse : " << course << "\nAdmission Date : " << admission_date << "\n";
            cout << "Marks : \n";

            for(int i=0;i<5;i++){

            cout << "\t\tsub-1 : " << marks[i] << "\n";

            }

        }

        string give_roll(){
            return roll;
        }

};





int fnd(string roll,vector<STUDENT> s,int p){
    for(int i=0;i<p;i++){
        if(s[i].give_roll()==roll){
            return i;
        }   
    }   

    return -1;

}


int main(){

    int p = 0;

    vector<STUDENT> s;
    string name,roll,course,admission_date;
    vector<int> marks(5);

    while(true){

        cout << "Enter :\n\t1 for admission\n\t2 to print marksheet\n\t3 to take the marks\n\tAnything else to exit\n";

        int t;
        cin >> t;
        if(t==1){

            cout << "Name : ";cin >> name;
            cout << "Roll : ";cin >> roll;
            cout << "Course : ";cin >> course;
            cout << "Admission-date : ";cin >> admission_date;

            STUDENT temp(roll,name,course,admission_date);

            s.push_back(temp);

            p++;
        } 
        else if(t==3){
            cout << "Enter the roll : ";
            cin >> roll;
            int k = fnd(roll,s,p);
            if(k==-1){
                cout << "No data !!\n";
            } 
            else {
                s[k].take_marks();  
            }

        } 
        else if(t==2){
            cout << "Enter the roll : ";
            cin >> roll;
            int k = fnd(roll,s,p);
            if(k==-1){
                cout << "No data !!\n";
            } 
            else {
                s[k].prepare();
            }

        } else return 0;

    }

}