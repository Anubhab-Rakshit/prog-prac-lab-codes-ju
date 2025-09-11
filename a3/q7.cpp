/* */

#include <iostream>
#include <string>
using namespace std;

class TIME{
    int hr,min,sec;
    char ch;
    public:
        void ent24(int h,int m,int s){
            hr=h;
            min=m;
            sec=s;
            ch=' ';
        } 
        void ent12(int h,int m,int s,char end){
            hr=h;
            min=m;
            sec=s;
            ch=end;
        }
        void display24(){
            string h=to_string(hr);
            string m=to_string(min);
            string s=to_string(sec);
            if (h.size() <= 1){
                h="0"+h;
            }
            if (m.size() <= 1){
                m="0"+m;
            }
            if (s.size() <= 1){
                s="0"+s;
            }

            cout<<"Time in 24hr format :- "<<h<<":"<<m<<":"<<s<<endl;
        }

        void dislay12(){
            int ref=0;
            if(hr>12){
                hr=hr%12;
                ref=1;
            }
            if(hr==12){
                ref=1;
            }
            string h=to_string(hr);
            string m=to_string(min);
            string s=to_string(sec);
            if (h.size() <= 1){
                h="0"+h;
            }
            if (m.size() <= 1){
                m="0"+m;
            }
            if (s.size() <= 1){
                s="0"+s;
            }
            
            if(ref==0){
                cout<<"Time in AM/PM format :- "<<h<<":"<<m<<":"<<s<<" AM"<<endl;
            }
            if(ref==1){
                cout<<"Time in AM/PM format :- "<<h<<":"<<m<<":"<<s<<" PM"<<endl;
            }

        }

        void add_time(int addmin){
            int sec_time=hr*3600+min*60+sec+addmin*60;
            int h_time=sec_time/3600;
            int m_time=(sec_time%3600)/60;
            int s_time=(sec_time%3600)%60;
            hr=h_time%24;
            min=m_time;
            sec=s_time;
        }
};
int main(){
    while(1){
        cout<<"MENU :- \n1. Enter time in 24hr format \n2.Enter time in 12hr format \n3.Display time in 24hr format \n4.Display time in AM/PM format \n5.Add time \nEnter your choice :- ";
        int ch;
        TIME time;
        int hr,min,sec;
        cin>>ch;
        switch(ch){
            case 1:
               
                cout<<"\nEnter your hours , min and seconds :- ";
                cin>>hr>>min>>sec;
                time.ent24(hr,min,sec);
                break;
            case 2:
                char ch;
                cout<<"\nEnter your hours , min and seconds :- ";
                cin>>hr>>min>>sec;
                cout<<"\nAM/PM (enter A for am and P for pm) :- ";
                cin>>ch;
                time.ent12(hr,min,sec,ch);
                break;
            case 3:
                time.display24();
                break;
            case 4:
                time.dislay12();
                break;
            case 5:
                cout<<"\nEnter time to add in minutes:- ";
                int add_min;
                cin>>add_min;
                time.add_time(add_min);
                break;
            default:
                cout<<"Invalid choice.. exiting system";
                exit(0);

        }
    }
}
