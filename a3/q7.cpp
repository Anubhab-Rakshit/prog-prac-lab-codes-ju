/*
    Design a class TIME which stores hours,minute and second. The class should have the methods to support the followings:
    * User may give the time value in 24-hour format
    * User may give the time value in AM/PM format
    * Display the time in 24-hour format
    * Display the time in AM/PM format
    * User may like to add minute with a time value

Name:- Anubhab Rakshit
Class:- BCSE-II A1
Roll No:- 002410501029

*/

#include<iostream>
#include<string>

using namespace std;

class TIME{
    int second;
    private:

    void twenty_four(){

        cout << "Enter in the format (eg-12 34 56 AM   or   23 34 43)\n";
        int hr,min;

        string s;
        getline(cin,s);

        hr = (s[0]-'0')*10 + (s[1]-'0');
        min = (s[3]-'0')*10 + (s[4]-'0');
        second = (s[6]-'0')*10 + (s[7]-'0');
        if(s.length()>8){   
            if(s[9] == 'P' && hr<12){
                second += 12*3600;
            }

        }

        second += min*60 + 3600*(hr-1);
    }


    void output_twelve() {

        int temp = second;
        int p = (temp+3600)/(12*3600);
        p%=2;
        temp %= (12*3600);
        string last = (p?"PM":"AM");
        int hr = temp/3600;
        hr++;
        temp %= 3600;
        int min = temp /60;
// Forward declaration is necessary because Account and Withdraw reference each other.
        temp%=60;
        int sec = temp;
        cout << "Time :  " << hr << " " << min << " " << sec << " " << last << "\n";

    }

    void output_twenty4(){
        int temp = second;
        temp %= 24*3600;
        int hr,min,sec;
        hr = temp/3600;hr++;
        hr%=24;
        temp%=3600;
        min = temp/60;
        temp%=60;
        sec = temp;
        cout << "Time :  " << hr << " " << min << " " << sec << "\n";
    }

    public :
        void input(){
            twenty_four();
        }

        void output(){
            cout << "Enter 1 to display in 24hr format and 2 for 12hr format\n";
            int t;
            cin>>t;

        if(t==1) output_twenty4();
        else output_twelve();

        } 

    void edit(){

    int min;
    printf("Enter minute to add : ");
    cin>>min;
    second += 60*min;

    }

};





int main(){

    TIME time;
    printf("Enter the time \n");
    time.input();

    int t=1;

    while(1){

        cout << "Enter 1 to display and 2 to edit anything else\n";
        cin>>t;
        if(t==1) time.output();

        else if(t==2) time.edit();

        else return 0;

    }

}