#include<iostream>
#include<bits/stdc++.h>
#include<string.h>
#include<fstream>
#include<conio.h>
#include<time.h>
#include<dos.h>
#include<windows.h>
#include<MMSystem.h>
#include<string.h>
#include<stdlib.h>
#include <sstream>
#include<graphics.h>
using namespace std;
char g_ar[100];
int incyvalue;

time_t now;
struct tm *rn;

int i,p,n,hr,mins,tday,tmon,tyear, day[500],mon[500],year[500], rem_no=0, rem_x=0, tmp_hr, dmy=0;
int t_hr[1000],t_min[1000], format_hr[1000];
char s[500],s2,str[500][500], am_pm;
string text[500], tmp_text;

// global variables
class student
{
protected:
    char message[100];
    char time[50];
    char date[60];

public:
    void getdata();
    void showdata();
    friend void write();
};
int k=0;
fstream obj;
student st;
// Declaration of All non class functions
void viewall();
void mainmenu();
void deleteall();
void reminder();
void exit();




void write()
{
    //system("cls");

    //obj.open("mmm.txt",ios::app);
    //clrscr();

    //Author:Raju
    st.getdata();

    //mainmenu();
    //reminder();
    //obj.write((char*)&st,sizeof(st));//obj.close();
    //mainmenu();
}

void student :: getdata()
{
    clearviewport();
    system("cls");

    SYSTEMTIME t;
    GetLocalTime(&t);
    bool invalid_date = false;

    do
    {
        cout<<"Please enter a date >= today in format Day-month-year:"<<endl;
        outtextxy(215,25,"Please Enter A Date");
        line(50, 60+incyvalue , 550 , 60+incyvalue); line(50, 90+incyvalue , 550 , 90+incyvalue);
		line(50, 60+incyvalue , 50 , 90+incyvalue); line(550, 60+incyvalue , 550 , 90+incyvalue);
		outtextxy(215,50,"Format : Day - Month - Year");
        scanf("%d-%d-%d",&tday,&tmon,&tyear);
        sprintf(g_ar,"%d   ",tday);
        outtextxy(265+5,64,g_ar);
        sprintf(g_ar,"%d   ",tmon);
        outtextxy(300+10,64,g_ar);
        sprintf(g_ar,"%d",tyear);
        outtextxy(340+20,64,g_ar);
        invalid_date = false;
        _getch();
        if(tyear < t.wYear)
        {
            invalid_date = true;
        }
        else if(tyear == t.wYear)
        {
            if(tmon < t.wMonth)
            {
                invalid_date = true;
            }
            else if(tmon == t.wMonth)
            {
                if(tday<t.wDay)
                {
                    invalid_date = true;
                }
            }
        }
    }
    while(invalid_date);

rem_limit:
    cout<<endl<<endl<<"how many Reminder you want to add for that day?"<<endl;
    clearviewport();
    outtextxy(215,25,"How many number of Remainder you want to add");
     line(215, 60+incyvalue , 415 , 60+incyvalue); line(215, 90+incyvalue , 415 , 90+incyvalue);
		line(215, 60+incyvalue , 215 , 90+incyvalue); line(415, 60+incyvalue , 415 , 90+incyvalue);
    scanf("%d",&n);
    sprintf(g_ar,"%d   ",n);
    if(n>3)
    {
        printf("max 3 reminder per day.");
        goto rem_limit;
    }

    for(i=rem_no-rem_x; i<(n+rem_no-rem_x); i++)
    {
        day[i]=tday;
        mon[i]=tmon;
        year[i]=tyear;

        printf("\n\nReminder: %d\n",i+1);

chk_hour:
        printf("\nEnter hour:min\n");
        scanf("%d:%d",&hr,&mins);
        getchar();

        if(hr<0 || hr>12)
        {
            printf("Please use 12 hour format\n");
            goto chk_hour;
        }

        if(mins<0 || mins>=60)
        {
            printf("Minutes must be between 0 to 59\n");
            goto chk_hour;
        }

//        cout<<t.wHour<<" "<<t.wMinute<<" "<<t.wSecond<<endl;
//         if(hr>=rn->tm_hour) {
//            if(hr>rn->tm_hour) {
//
//            }
//            else if(mins>=rn->tm_min){
//                if(mins>rn->tm_min) {
//
//                }
//                else {
//                    printf("time must be greater than right now!");
//                    goto chk_hour;
//                }
//            }
//             else {
//                printf("time must be greater than right now!");
//                goto chk_hour;
//             }
//         }
//         else {
//            printf("time must be greater than right now!");
//            goto chk_hour;
//         }

chk_midnight_or_noon:
        printf("Please enter the time format AM or PM:\n");

        scanf("%c%c",&s[i], &s2);
        getchar();

        if((s[i]=='a'||s[i]=='A') && (s2=='m' || s2=='M'))
        {
            if(hr==12)
            {
                hr=hr-12;
            }
        }
        else if((s[i]=='p'|| s[i]=='P') && (s2=='m' || s2=='M'))
        {
            if(hr<12)
            {
                hr=hr+12;
            }
        }
        else
        {
            printf("\nInvalid time format.\n");
            goto chk_midnight_or_noon;
        }

        format_hr[i]=hr;
        t_hr[i]=hr;
        t_min[i]=mins;

        printf("Enter the event name to remind:\n");
        gets(str[i]);

        text[i]=str[i];
    }

    rem_no=(n+rem_no);
    n=rem_no-rem_x;
    dmy++;

    cout<<"\n\nReminder saved!"<<endl<<endl;

go_to_main_menu:
    cout<<"Press k for Main Menu"<<endl;
    char ch;
    cin>>ch;

    if(ch=='k' || ch == 'K')
    {
        mainmenu();
    }
    else
    {
        goto go_to_main_menu;
    }
}

int clock(int a, int b, char str[])
{
    int j, loop=0;
    system("cls");

    while(loop!=1)
    {
        time(&now);

        rn=localtime(&now);

        if(a==rn->tm_hour & b==rn->tm_min)
        {
            tmp_text=text[0];

            for(p=0; p<n-1; p++)
            {
                format_hr[p]=format_hr[p+1];
                t_min[p]=t_min[p+1];
                text[p]=text[p+1];

                day[p]=day[p+1];
                mon[p]=mon[p+1];
                year[p]=year[p+1];

            }

            n=n-1;
            rem_x++;

            if(a>12)
            {
                a=a-12;
                am_pm='p';
            }
            else
            {
                am_pm='a';
            }

            printf("Right now your event is : %s\nTime - %d:%d%cm",tmp_text.c_str(),a,b,am_pm);

            for(j=0; j<2; j++)
            {
                Beep(500,900);
                Beep(700,800);
                Beep(500,900);

                Sleep(1000);
            }

            //mainmenu();

            loop=1;

            //getchar(); 30 09 2021

            system("cls");

            cout<<"\n\n\n   Press k to stop and goto Main Menu\n";

            if(_getch()=='k')
            {
                mainmenu();
            }
        }
        else
        {
            free(rn);
        }
    }
}

void sort_dmy_hr_mins()
{
    int tmd2=day[i];
    day[i]=day[p+1];
    day[p+1]=tmd2;

    int tmm=mon[i];
    mon[i]=mon[p+1];
    mon[p+1]=tmm;

    int tmy=year[i];
    year[i]=year[p+1];
    year[p+1]=tmy;

    int tmp=format_hr[i];
    format_hr[i]=format_hr[p+1];
    format_hr[p+1]=tmp;

    int tmp2=t_min[i];
    t_min[i]=t_min[p+1];
    t_min[p+1]=tmp2;

    string tmp3=text[i];
    text[i]=text[p+1];
    text[p+1]=tmp3;

    char tmp4=s[i];
    s[i]=s[p+1];
    s[p+1]=tmp4;
}

void sort_rems()
{
    // day month year check
    for(i=0; i<n; i++)
    {
        for(p=i; p<n-1; p++)
        {
            if( year[i]>year[p+1])
            {
                sort_dmy_hr_mins();
            }
            else if(year[i]==year[p+1])
            {
                if(mon[i]>mon[p+1])
                {
                    sort_dmy_hr_mins();
                }
                else if(mon[i]==mon[p+1])
                {
                    if(day[i]>day[p+1])
                    {
                        sort_dmy_hr_mins();
                    }
                }

            }
        }
    }

    // same day check
    for(i=0; i<n; i++)
    {
        for(p=i; p<n-1; p++)
        {
            if(year[i]==year[p+1] && mon[i]==mon[p+1] && day[i]==day[p+1])
            {
                if(s[i]=='p' && s[p+1]=='a')    //cout<<format_hr[i]<<"pm....am"<<format_hr[p+1]<<endl;
                {
                    int tmp=format_hr[i];
                    format_hr[i]=format_hr[p+1];
                    format_hr[p+1]=tmp;

                    // cout<<format_hr[i]<<"pm....am"<<format_hr[p+1]<<endl;

                    int tmp2=t_min[i];
                    t_min[i]=t_min[p+1];
                    t_min[p+1]=tmp2;

                    string tmp3=text[i];
                    text[i]=text[p+1];
                    text[p+1]=tmp3;


                    char tmp4=s[i];
                    s[i]=s[p+1];
                    s[p+1]=tmp4;
                }
            }
        }
    }

    // ends of am->pm
    for(i=0; i<n; i++)
    {
        for(p=i; p<n-1; p++)
        {
            if(year[i]==year[p+1] && mon[i]==mon[p+1] && day[i]==day[p+1])
            {
                if ((s[i]=='p' && s[p+1]=='p') || (s[i]=='a' && s[p+1]=='a') )
                {
                    if(format_hr[i]>format_hr[p+1])
                    {
                        int tmp=format_hr[i];
                        format_hr[i]=format_hr[p+1];
                        format_hr[p+1]=tmp;

                        int tmp2=t_min[i];
                        t_min[i]=t_min[p+1];
                        t_min[p+1]=tmp2;

                        string tmp3=text[i];
                        text[i]=text[p+1];
                        text[p+1]=tmp3;
                    }
                }
            }
        }
    }
//
    for(i=0; i<n; i++)
    {
        for(p=i; p<n-1; p++)
        {
            if(year[i]==year[p+1] && mon[i]==mon[p+1] && day[i]==day[p+1])
            {
                if ((s[i]=='p' && s[p+1]=='p') || (s[i]=='a' && s[p+1]=='a') )
                {
                    if(format_hr[i]==format_hr[p+1])
                    {
                        if(t_min[i]>t_min[p+1])
                        {
                            int tmp=t_min[i];
                            t_min[i]=t_min[p+1];
                            t_min[p+1]=tmp;

                            string tmp3=text[i];
                            text[i]=text[p+1];
                            text[p+1]=tmp3;
                        }
                    }
                }

            }
        }
    }

    //for(i=0;i<n;i++) cout<<format_hr[i]<<"hrs..\n";
}

void reminder()
{
    sort_rems();

    SYSTEMTIME t;
    GetLocalTime(&t);

    for(i=0; i<n; i++)
    {
        if(tyear==t.wYear && tmon==t.wMonth && tday==t.wDay )
        {
            clock(format_hr[i],t_min[i],str[i]);

//            for(p=0;p<n;p++){
//                t_hr[p]=t_hr[p+1];
//                t_min[p]=t_min[p+1];
//                str[p][p]=str[p][p+1];
//            }
        }
        else
        {
            printf("\nYou have no nReminder today");
            break;
        }
    }


    cout<<"\n\nPress k to goto Main Menu\n";

    if(_getch()=='k')
    {
        mainmenu();
    }

    //mainmenu();
}

void exit()
{
    system("cls");

    Sleep(3000);
    exit(0);
}

void viewall()
{
    system("cls");

//	printf("befor sort\n");
//	for(i=0;i<n;i++){
//        if(format_hr[i]>12) {
//            tmp_hr=format_hr[i]-12;
//        } else {
//            tmp_hr=format_hr[i];
//        }
//
//        cout<<"index : hr["<<i<<"]:"<<"mins["<<i<<"]"<<endl;;
//        cout<<"time : "<<tmp_hr<<":"<<t_min[i]<<s[i]<<"m"<<endl;
//        cout<<"date : "<<day<<"-"<<mon<<"-"<<year<<endl; cout<<"\n\n";
//    }
//	printf("befor sort\n");

    sort_rems();

    cout<<"Saved Reminders...\n\n";
    for(i=0; i<n; i++)
    {
        if(format_hr[i]>12)
        {
            tmp_hr=format_hr[i]-12;
        }
        else if(format_hr[i]==0)
        {
            tmp_hr=12;
        }
        else
        {
            tmp_hr=format_hr[i];
        }

        cout<<"Reminder "<<i+1<<": "<<text[i]<<endl;;
        cout<<"Time : "<<tmp_hr<<":"<<t_min[i]<<s[i]<<"m"<<endl;
        cout<<"Date : "<<day[i]<<"-"<<mon[i]<<"-"<<year[i]<<endl;
        cout<<"\n\n";
    }

    cout<<"\n\n\nPress k for Main Menu\n";

    if(_getch()=='k')
    {
        mainmenu();
    }
    else
    {
        viewall();
    }
}

void deleteall()
{
    system("cls");

    cout<<"If you want to delete All Reminders (y/n): ";

    if(_getch()=='y')
    {
        n=0;
        rem_no=0;
        rem_x=0;

        cout<<"\n\nALL Reminders have been deleted!!!"<<endl;

        Sleep(2000);

        mainmenu();
    }
    else if(_getch()=='n')
    {
        mainmenu();
    }
    else
    {
        deleteall();
    }
}



int login()
{
logfun:
    system("CLS");
    int incyvalue=0;
    outtextxy(215,125,"log in");
    line(50, 180+incyvalue, 550, 180+incyvalue);
    line(50, 210+incyvalue, 550, 210+incyvalue);
    line(50, 180+incyvalue, 50, 210+incyvalue);
    line(550, 180+incyvalue, 550, 210+incyvalue);

    outtextxy(80,184,"user name");
    line(50, 240+incyvalue, 550, 240+incyvalue);
    line(50, 270+incyvalue, 550, 270+incyvalue);
    line(50, 240+incyvalue, 50, 270+incyvalue);
    line(550, 240+incyvalue, 550, 270+incyvalue);

    outtextxy(80,244,"password");

    int ch;
    char username[100];
    char password[100] = "";
    string u1="user";
    string p1="pass";
    printf("\n  =======================  LOGIN FORM  =======================\n  ");
    printf(" \n                       ENTER USERNAME:-");
    cin>>username;
    sprintf(g_ar,"%s",username);
    outtextxy(180,184,g_ar);
    printf(" \n                       ENTER PASSWORD:-");
    ch=0;
    char input;
    for(int i = 0; i < 4; i++)
    {
        //cin >> input;
        input = _getch();
        cout << "*";

        password[i] = input;


    }
    sprintf(g_ar,"%s",password);
    outtextxy(180,244,g_ar);
    _getch();
    if(username==u1 && password==p1)
    {
        printf("  \n\n\n       WELCOME TO OUR SYSTEM !! YOUR LOGIN IS SUCCESSFUL");
        printf("\n\n\n\t\t\t\tPress any key to continue...");
        _getch();
        return 1;
    }
    else
    {
        cout<<endl<<"wrong password,try again"<<endl;
        _getch();
        goto logfun;
    }
}



void mainmenu()
{
    system("cls");
    clearviewport();

    //reminder();

    cout<<"\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Main Menu \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n";
    cout<<"\t\t 1. Set Reminder\n\t\t 2. View All Reminders\n\t\t 3. Delete All Reminders\n\t\t 4. Exit\n\t\t 5. Activate Reminder\n\n";
    cout<<"\t\t Please select from the above: ";

    outtextxy(215,25,"Main Menu");
    line(50, 60+incyvalue, 550, 60+incyvalue);
    line(50, 90+incyvalue, 550, 90+incyvalue);
    line(50, 60+incyvalue, 50, 90+incyvalue);
    line(550, 60+incyvalue, 550, 90+incyvalue);

    outtextxy(80,64,"1.Set Reminder:");


    line(50, 120+incyvalue, 550, 120+incyvalue);
    line(50, 150+incyvalue, 550, 150+incyvalue);
    line(50, 120+incyvalue, 50, 150+incyvalue);
    line(550, 120+incyvalue, 550, 150+incyvalue);
    outtextxy(80,124,"2.View All Reminder:");

    line(50, 180+incyvalue, 550, 180+incyvalue);
    line(50, 210+incyvalue, 550, 210+incyvalue);
    line(50, 180+incyvalue, 50, 210+incyvalue);
    line(550, 180+incyvalue, 550, 210+incyvalue);

    outtextxy(80,184,"3.Delete All Reminder:");

    line(50, 240+incyvalue, 550, 240+incyvalue);
    line(50, 270+incyvalue, 550, 270+incyvalue);
    line(50, 240+incyvalue, 50, 270+incyvalue);
    line(550, 240+incyvalue, 550, 270+incyvalue);

    outtextxy(80,244,"4.Exit:");
    line(50, 300+incyvalue, 550, 300+incyvalue);
    line(50, 330+incyvalue, 550, 330+incyvalue);
    line(50, 300+incyvalue, 50, 330+incyvalue);
    line(550, 300+incyvalue, 550, 330+incyvalue);

    outtextxy(80,304,"5.Active Reminder: ");

    char ch;
    cin>>ch;

    switch(ch)
    {
    case '1':
        write();
        break;
    case '2':
        viewall();
        break;
    case '3':
        deleteall();
        break;
    case '4':
        exit();
        break;
    case '5':
        reminder();
        break;
    default :
        mainmenu();
        break;
    }
}

int main()
{
    system("CLS");
    printf("\t\t==================================================\n");
    printf("\t\t|                                                |\n");
    printf("\t\t|      -----------------------------------       |\n");
    printf("\t\t|             Personal_Task_Tracker              |\n");
    printf("\t\t|      -----------------------------------       |\n");
    printf("\t\t|                                                |\n");
    printf("\t\t|                                                |\n");
    printf("\t\t|                                                |\n");
    printf("\t\t|              BROUGHT TO YOU BY                 |\n");
    printf("\t\t|         |  Rimon Hasan ,    CE-19014 |         |\n");
    printf("\t\t|         |  Jahid Hasan Raju,CE-19017 |         |\n");
    printf("\t\t|         |  Md Rahij Mia ,   CE-19019 |         |\n");
    printf("\t\t==================================================\n\n\n");
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
    system("color B");
    printf(" \n Press any key to continue:");

    _getch();
    system("CLS");
    login();
    system("CLS");
    mainmenu();
}
