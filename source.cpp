/************************************************************************
*                                                                       *
*   Student Data Management System                                      *
*       -by                                                             *
*        Sujai Ram Prasath C and Avinash M                              *
*   [ver 0.1]                                                           *
*                                                                       *
*************************************************************************/


//-----------------------------------------------------------------------------------------------//

#ifndef _GLIBCXX_IOSTREAM
    #include <iostream>
#endif
#ifndef _GLIBCXX_FSTREAM
    #include <fstream>
#endif
#ifndef _GLIBCXX_CSTRING
    #include <cstring>
#endif
#ifndef _GLIBCXX_STRING
    #include <string>
#endif
#ifndef _GLIBCXX_CSTDLIB
    #include <cstdlib>
#endif
#ifndef _GLIBCXX_CTIME
    #include <ctime>
#endif
#ifndef _GLIBCXX_CCTYPE
    #include <cctype>
#endif
#ifndef _GLIBCXX_IOMANIP
    #include <iomanip>
#endif
#ifndef _GLIBCXX_CMATH
    #include <cmath>
#endif
#include <sys/dir.h>

//-----------------------------------------------------------------------------------------------//

using namespace std;

//-----------------------------------------------------------------------------------------------//

//#include "graphics_engine.h"
#ifndef CSRP_MISC_TOOLS
    #include "miscellaneous_tools.h"
#endif
#include "email.h"


//-----------------------------------------------------------------------------------------------//

#ifdef _WIN32
    #define clear_output_screen() system("cls")
#else
    #define clear_output_screen() system("clear")
#endif

//-----------------------------------------------------------------------------------------------//


ifstream marks_file,names_file,master_rec,test_data_file_in,cwf_file,split_marks_file;
string test_name,tmp,test_rec,t;
char ch;


//-----------------------------------------------------------------------------------------------//

bool open_File(int opt)
{
    string temp;

    NAME:
    cout<<"Enter the class name (cc-s-yyyy-yyyy) ( eg. 12-A-2016-2017 ) : ";
    cin>>t;
    cout<<"Verify if the data is correct or wrong...(C/W)? ";
    cin>>ch;
    if (ch=='W' or ch=='w')
        goto NAME;
    else if (ch=='C' or ch=='c')
        ;
    else    {
    cout<<"Something is wrong..."<<endl;
    goto NAME;
    }

    if (t.size()!=14)
    {
        cout<<"Not an acceptable class name"<<endl;
        goto NAME;
    }

    test_name=t;
    test_name.insert(0, "Data/");
    tmp=test_name;
    tmp.append(".names");
    names_file.open(tmp);


    if (opt==0)
    {
        NAME2:
        cout<<"Enter the date of the test (dd-mm-yyyy) ( eg. 31-08-2016 ) : ";
        cin>>temp;
        cout<<"Verify if the data is correct or wrong...(C/W)? ";
        cin>>ch;
        if (temp.length()!=10)
        {
            cout<<"Not an acceptable date format..."<<endl;
            goto NAME2;
        }
        if (ch=='W' or ch=='w')
            goto NAME2;
        else if (ch=='C' or ch=='c')
            ;
        else    {
        cout<<"Something is wrong..."<<endl;
        goto NAME2;
        }

        test_name.append("-");
        test_name.append(temp);

        marks_file.open(test_name);
        test_data_file_in.open(test_name+".data", ios::in);
        cwf_file.open(test_name+".cwf", ios::in);
        split_marks_file.open(test_name+".splm", ios::in);

        if(marks_file.is_open() and names_file.is_open() and test_data_file_in.is_open() and cwf_file.is_open() and split_marks_file.is_open())
            return true;
        else
            return false;
    }
    else if (opt==1)
    {
    test_rec=test_name+".record";
    master_rec.open(test_rec);

    if(names_file.is_open() and master_rec.is_open())
        return true;
    else
        return false;
    }
}

//-----------------------------------------------------------------------------------------------//

void add_New_Class()
{
    int n;
    string class_name, mail_file_name;
    ofstream names_file,email_file;

    CLASS_NAME:
    cout<<"Enter class name ( cc-s-yyyy-yyyy ) ( eg. 12-A-2016-2017 ) : ";
    cin>>class_name;

    if (class_name.size()!=14)
    {
        cout<<"Not an acceptable class name"<<endl;
        goto CLASS_NAME;
    }

    class_name.insert(0, "Data/");
    mail_file_name=class_name;
    class_name.append(".names");
    mail_file_name.append(".mail_list");

    names_file.open(class_name);
    email_file.open(mail_file_name);

    E_POINT:
    cout<<"Enter the no of students : ";
    cin>>n;

    if (cin.fail())
    {
        cout<<"Invalid Input"<<endl;
        cin.clear();
        cin.ignore();
        goto E_POINT;
    }

    string names,email_Id;

    for(int i=0;i<n;i++)
    {
        ENTRY:
        cin.get();
        cout<<"Enter name of the student : ";
        getline(cin, names);
        cout<<"Enter email-id of the student : ";
        getline(cin,email_Id);
        CHECK:
        cout<<"Verify if the data is correct or wrong...(C/W)? ";
        cin>>ch;
        if (ch=='W' or ch=='w')
            goto ENTRY;
        else if (ch=='C' or ch=='c')
            goto ALL_OK;
        else
            goto CHECK;
        ALL_OK:
        names_file<<names<<endl;
        email_file<<email_Id<<endl;
    }

    names_file.close();
    email_file.close();

    cout<<"\nPress enter key to continue..."<<endl;
    cin.get();
    cin.get();
}

//-----------------------------------------------------------------------------------------------//

void enter_Test_Marks()
{
    ofstream marks_file,correct_wrong_file,test_data_file,split_marks_file_out;
    ifstream names_file;
    string test_name, class_name, master_record, _class_name;
    int total_Questions,P,C,M;

    CLASS_NAME:
    cout<<"Enter the class name (cc-s-yyyy-yyyy) ( eg. 12-A-2016-2017 ) : ";
    cin>>class_name;

    if (class_name.size()!=14)
    {
        cout<<"Not an acceptable class name"<<endl;
        goto CLASS_NAME;
    }
    cout<<"Verify if the data is correct or wrong...(C/W)? ";
    cin>>ch;
    if (ch=='W' or ch=='w')
        goto CLASS_NAME;
    else if (ch=='C' or ch=='c')
        ;
    else    {
    cout<<"Something is wrong..."<<endl;
    goto CLASS_NAME;
    }

    _class_name=class_name;

    DATE:
    cout<<"Enter the date of the test (dd-mm-yyyy) ( eg. 31-08-2016 ) : ";
    cin>>test_name;
    if (test_name.length()!=10)
    {
    cout<<"Something is wrong..."<<endl;
    goto DATE;
    }
    cout<<"Verify if the data is correct or wrong...(C/W)? ";
    cin>>ch;
    if (ch=='W' or ch=='w')
        goto DATE;
    else if (ch=='C' or ch=='c')
        ;
    else    {
    cout<<"Something is wrong..."<<endl;
    goto DATE;
    }

    master_record="Data/"+class_name+".record";

    class_name.insert(0, "Data/");
    class_name.append(".names");

    names_file.open(class_name);

    if (names_file==NULL)
        cout<<"Cannot find the specified file..."<<endl;
    else    {
    ofstream test_names(master_record, ios::app);
    test_names<<test_name<<endl;
    test_names.close();

    test_name="Data/"+_class_name+"-"+test_name;

    marks_file.open(test_name, ios::out);
    correct_wrong_file.open(test_name+".cwf", ios::out);
    test_data_file.open(test_name+".data", ios::out);
    split_marks_file_out.open(test_name+".splm", ios::out);

    TOT_QUES:
    cout<<"\nEnter the total number of questions : ";
    cin>>total_Questions;

    if (cin.fail())
    {
        cout<<"Invalid Input"<<endl;
        cin.clear();
        cin.ignore();
        goto TOT_QUES;
    }

    test_data_file<<total_Questions<<endl;
    test_data_file<<total_Questions*4<<endl;

    TOT_PHY_QUES:
    cout<<"Enter the total number of physics questions : ";
    cin>>P;

    if (cin.fail())
    {
        cout<<"Invalid Input"<<endl;
        cin.clear();
        cin.ignore();
        goto TOT_PHY_QUES;
    }

    TOT_CHEM_QUES:
    cout<<"Enter the total number of chemistry questions : ";
    cin>>C;

    if (cin.fail())
    {
        cout<<"Invalid Input"<<endl;
        cin.clear();
        cin.ignore();
        goto TOT_CHEM_QUES;
    }

    TOT_MATHS_QUES:
    cout<<"Enter the total number of maths questions : ";
    cin>>M;

    if (cin.fail())
    {
        cout<<"Invalid Input"<<endl;
        cin.clear();
        cin.ignore();
        goto TOT_MATHS_QUES;
    }

    if (P+C+M!=total_Questions)
    {
        cout<<"ERROR : Sum of P,C,M marks not equal to total number of questions"<<endl;
        goto TOT_QUES;
    }

    test_data_file<<P<<endl<<C<<endl<<M<<endl;

    cout<<"\nEnter the data of the respective students"<<endl<<endl;

    while(names_file)
    {
        string names;
        int correct, wrong, mark, P_correct, C_correct, M_correct, P_wrong, C_wrong, M_wrong;
        getline(names_file,names);
        if (names.length()!=0)
        {
            ENTRY1:
            clear_output_screen();
            cout<<names<<endl;

            cout<<"Enter the number of correct in physics : ";
            cin>>P_correct;

            if (cin.fail())
            {
                cout<<"Invalid Input"<<endl;
                cin.clear();
                cin.ignore();
                goto ENTRY1;
            }

            cout<<"Enter the number of wrong in physics : ";
            cin>>P_wrong;

            if (cin.fail())
            {
                cout<<"Invalid Input"<<endl;
                cin.clear();
                cin.ignore();
                goto ENTRY1;
            }

            if (P_correct+P_wrong>P)
            {
                cout<<"ERROR : (Number of correct + Number of wrong) is greater than total number of physics questions..."<<endl;
                goto ENTRY1;
            }

            cout<<"Enter the number of correct in chemistry : ";
            cin>>C_correct;

            if (cin.fail())
            {
                cout<<"Invalid Input"<<endl;
                cin.clear();
                cin.ignore();
                goto ENTRY1;
            }

            cout<<"Enter the number of wrong in chemistry : ";
            cin>>C_wrong;

            if (cin.fail())
            {
                cout<<"Invalid Input"<<endl;
                cin.clear();
                cin.ignore();
                goto ENTRY1;
            }

            if (C_correct+C_wrong>C)
            {
                cout<<"ERROR : (Number of correct + Number of wrong) is greater than total number of physics questions..."<<endl;
                goto ENTRY1;
            }

            cout<<"Enter the number of correct in maths : ";
            cin>>M_correct;

            if (cin.fail())
            {
                cout<<"Invalid Input"<<endl;
                cin.clear();
                cin.ignore();
                goto ENTRY1;
            }

            cout<<"Enter the number of wrong in maths : ";
            cin>>M_wrong;

            if (cin.fail())
            {
                cout<<"Invalid Input"<<endl;
                cin.clear();
                cin.ignore();
                goto ENTRY1;
            }
            if (M_correct+M_wrong>M)
            {
                cout<<"ERROR : (Number of correct + Number of wrong) is greater than total number of physics questions..."<<endl;
                goto ENTRY1;
            }

            correct=P_correct+C_correct+M_correct;
            wrong=P_wrong+C_wrong+M_wrong;
            mark=(correct*4)-(wrong);
            if (mark>(total_Questions*4))
            {
                cout<<"ERROR : Calculated marks is greater than maximum marks..."<<endl;
                goto ENTRY1;
            }
            if (mark<(total_Questions*-1))
            {
                cout<<"ERROR : Calculated marks is less than minimum marks..."<<endl;
                goto ENTRY1;
            }
            if ((correct+wrong)>total_Questions)
            {
                cout<<"ERROR : (Number of correct + Number of wrong) is greater than total number of questions..."<<endl;
                goto ENTRY1;
            }
            cout<<"Marks scored : "<<mark<<endl<<endl;
            correct_wrong_file<<P_correct<<endl<<P_wrong<<endl<<C_correct<<endl<<C_wrong<<endl<<M_correct<<endl<<M_wrong<<endl<<correct<<endl<<wrong<<endl;
            split_marks_file_out<<P_correct*4-P_wrong<<endl<<C_correct*4-C_wrong<<endl<<M_correct*4-M_wrong<<endl;
            marks_file<<mark<<"\n";

            cout<<"Press enter key to continue...";
            cin.clear();
            cin.get();
            cin.get();
        }
    }
    marks_file.close();
    names_file.close();
    correct_wrong_file.close();
    test_data_file.close();
    split_marks_file_out.close();
    }
}

//-----------------------------------------------------------------------------------------------//

void single_test_marks()
{
    string names,marks,correct,wrong,P_correct,P_wrong,C_correct,C_wrong,M_correct,M_wrong;

    if (open_File(0))
    {
    cout<<"The marks of all students in the test...."<<endl;
    cout.setf(ios::left);
    cout<<setw(32)<<"Names"<<setw(17)<<"Physics Correct"<<setw(15)<<"Physics Wrong"<<setw(19)<<"Chemistry Correct"<<setw(17)<<"Chemistry Wrong"<<setw(15)<<"Maths Correct"<<setw(13)<<"Maths Wrong"<<setw(9)<<"Correct"<<setw(7)<<"Wrong"<<setw(7)<<"Marks"<<endl;
    while(getline(names_file,names))
    {
        getline(marks_file,marks);
        getline(cwf_file,P_correct);
        getline(cwf_file,P_wrong);
        getline(cwf_file,C_correct);
        getline(cwf_file,C_wrong);
        getline(cwf_file,M_correct);
        getline(cwf_file,M_wrong);
        getline(cwf_file,correct);
        getline(cwf_file,wrong);
        cout<<setw(32)<<names<<setw(17)<<P_correct<<setw(15)<<P_wrong<<setw(19)<<C_correct<<setw(17)<<C_wrong<<setw(15)<<M_correct<<setw(13)<<M_wrong<<setw(9)<<correct<<setw(7)<<wrong<<setw(7)<<marks<<endl;
    }
    marks_file.close();
    names_file.close();
    cwf_file.close();
    test_data_file_in.close();
    }
    else
        cout<<"Cannot find specified file..."<<endl;

    cout<<"Press enter key to continue...";
    cin.ignore();
    cin.ignore();
}

//-----------------------------------------------------------------------------------------------//

void all_test_marks()
{
string names_of_tests, name, mark;

if (open_File(1))
{
    clear_output_screen();
    int n=0,z=0;

    cout.setf(ios::left);
    cout<<setw(32)<<"NAMES";

    while(getline(master_rec,names_of_tests))
    {
        if (names_of_tests.length()!=0)
        {
            cout<<setw(16)<<names_of_tests;
        }
    }

    master_rec.close();

    while(getline(names_file,name))
    {
    n+=1;
    master_rec.open(test_rec);
    if (name.length()!=0)
    {
        cout<<"\n"<<setw(32)<<name;
        while(getline(master_rec,names_of_tests))
        {
        z=0;
        if (names_of_tests.length()!=0)
        {
        names_of_tests="Data/"+t+"-"+names_of_tests;

        marks_file.open(names_of_tests);

        while (getline(marks_file,mark))
        {
            z+=1;
            if (n==z)
                cout<<setw(16)<<mark;
        }

        marks_file.close();
        }
        }
    }
    master_rec.close();
    }
names_file.close();
cwf_file.close();
test_data_file_in.close();
}
else
    cout<<"Cannot find specified file...";
cout<<endl<<endl;
cout<<"\nPress enter key to continue..."<<endl;
cin.ignore();
cin.ignore();
}

//-----------------------------------------------------------------------------------------------//


void send_Mail()
{
if (open_File(0)==true)
{
cout<<endl<<endl;
char username[50];
char password[50];
char to[50];

ifstream username_File("Data/username_File");
username_File.getline(username,50);
username_File.close();

ifstream password_File("Data/password_File");
password_File.getline(password,50);
password_File.close();


char out_of[4];
test_data_file_in.getline(out_of,4);
test_data_file_in.getline(out_of,4);

string tag(".names");
string mail_file=tmp;
int z=mail_file.find(tag);
mail_file.replace(z, tag.size(), ".mail_list");

ifstream mail_List(mail_file, ios::in);

while (mail_List)   {
    mail_List.getline(to,50);

    if (strlen(to)!=0)
    {
        char marks[4];
        marks_file.getline(marks,4);

        char P_marks[4];
        split_marks_file.getline(P_marks,4);

        char C_marks[4];
        split_marks_file.getline(C_marks,4);

        char M_marks[4];
        split_marks_file.getline(M_marks,4);

        char P_correct[3];
        cwf_file.getline(P_correct,3);

        char P_wrong[3];
        cwf_file.getline(P_wrong,3);

        char C_correct[3];
        cwf_file.getline(C_correct,3);

        char C_wrong[3];
        cwf_file.getline(C_wrong,3);

        char M_correct[3];
        cwf_file.getline(M_correct,3);

        char M_wrong[3];
        cwf_file.getline(M_wrong,3);

        char correct[3];
        cwf_file.getline(correct,3);

        char wrong[3];
        cwf_file.getline(wrong,3);

        char name[50];
        names_file.getline(name,50);

        char CRLF[]="\r\n";
        char bar[]="\t\t|";
        char sub[]="Subject: EVPS Entrance Class Test Results\r\n";
        char begin[]="***********************************BEGIN***********************************\r\n\r\n";
        char full_dash[]="-------------------------------------------------------------------------\r\n";
        char full_star[]="            *********************************************\r\n";
        char header_line[]="|   -----   |  Physics  |   Chemistry   |     Maths     |   Total       |\r\n";
        char reference[]="            *                REFERENCE                  *\r\n            *********************************************\r\n            *   Marks added for correct answer : +4     *\r\n            *   Marks reduced fot wrong answer : -1     *\r\n            *********************************************\r\n\r\n";
        char marks_scored[]="\r\nMarks Scored = ";
        char slash[]="/";
        char _correct[]="|  Correct  |";
        char _wrong[]="|   Wrong   |";
        char _marks[]="|   Marks   |";
        char _tot[]="            *     TOTAL MARKS SECURED = ";
        char end[]="******************************END OF REPORT********************************\r\n";

        char data[strlen(sub)+strlen(begin)+strlen(name)+strlen(CRLF)+strlen(CRLF)+strlen(full_dash)+strlen(header_line)+strlen(full_dash)+strlen(_correct)+strlen(P_correct)+strlen(bar)+strlen(C_correct)+strlen(bar)+strlen(M_correct)+strlen(bar)+strlen(correct)+strlen(CRLF)+strlen(full_dash)+strlen(_wrong)+strlen(P_wrong)+strlen(bar)+strlen(C_wrong)+strlen(bar)+strlen(M_wrong)+strlen(bar)+strlen(wrong)+strlen(bar)+strlen(CRLF)+strlen(full_dash)+strlen(_marks)+strlen(P_marks)+strlen(bar)+strlen(C_marks)+strlen(bar)+strlen(M_marks)+strlen(bar)+strlen(CRLF)+strlen(full_dash)+strlen(CRLF)+strlen(full_star)+strlen(_tot)+strlen(marks)+strlen(slash)+strlen(out_of)+strlen(CRLF)+strlen(full_star)+strlen(CRLF)+strlen(full_star)+strlen(reference)+strlen(end)+1];
        int i;

        for (i=0;i<strlen(sub);i++)
            data[i]=sub[i];


        for (int j=0;j<strlen(begin);j++,i++)
            data[i]=begin[j];


        for (int j=0;j<strlen(name);j++,i++)
            data[i]=name[j];
        for (int j=0;j<strlen(CRLF);j++,i++)
            data[i]=CRLF[j];
        for (int j=0;j<strlen(CRLF);j++,i++)
            data[i]=CRLF[j];


        for (int j=0;j<strlen(full_dash);j++,i++)
            data[i]=full_dash[j];
        for (int j=0;j<strlen(header_line);j++,i++)
            data[i]=header_line[j];


        for (int j=0;j<strlen(full_dash);j++,i++)
            data[i]=full_dash[j];
        for (int j=0;j<strlen(_correct);j++,i++)
            data[i]=_correct[j];
        for (int j=0;j<strlen(P_correct);j++,i++)
            data[i]=P_correct[j];
        for (int j=0;j<strlen(bar);j++,i++)
            data[i]=bar[j];
        for (int j=0;j<strlen(C_correct);j++,i++)
            data[i]=C_correct[j];
        for (int j=0;j<strlen(bar);j++,i++)
            data[i]=bar[j];
        for (int j=0;j<strlen(M_correct);j++,i++)
            data[i]=M_correct[j];
        for (int j=0;j<strlen(bar);j++,i++)
            data[i]=bar[j];
        for (int j=0;j<strlen(correct);j++,i++)
            data[i]=correct[j];
        for (int j=0;j<strlen(bar);j++,i++)
            data[i]=bar[j];
        for (int j=0;j<strlen(CRLF);j++,i++)
            data[i]=CRLF[j];


        for (int j=0;j<strlen(full_dash);j++,i++)
            data[i]=full_dash[j];
        for (int j=0;j<strlen(_wrong);j++,i++)
            data[i]=_wrong[j];
        for (int j=0;j<strlen(P_wrong);j++,i++)
            data[i]=P_wrong[j];
        for (int j=0;j<strlen(bar);j++,i++)
            data[i]=bar[j];
        for (int j=0;j<strlen(C_wrong);j++,i++)
            data[i]=C_wrong[j];
        for (int j=0;j<strlen(bar);j++,i++)
            data[i]=bar[j];
        for (int j=0;j<strlen(M_wrong);j++,i++)
            data[i]=M_wrong[j];
        for (int j=0;j<strlen(bar);j++,i++)
            data[i]=bar[j];
        for (int j=0;j<strlen(wrong);j++,i++)
            data[i]=wrong[j];
        for (int j=0;j<strlen(bar);j++,i++)
            data[i]=bar[j];
        for (int j=0;j<strlen(CRLF);j++,i++)
            data[i]=CRLF[j];


        for (int j=0;j<strlen(full_dash);j++,i++)
            data[i]=full_dash[j];
        for (int j=0;j<strlen(_marks);j++,i++)
            data[i]=_marks[j];
        for (int j=0;j<strlen(P_marks);j++,i++)
            data[i]=P_marks[j];
        for (int j=0;j<strlen(bar);j++,i++)
            data[i]=bar[j];
        for (int j=0;j<strlen(C_marks);j++,i++)
            data[i]=C_marks[j];
        for (int j=0;j<strlen(bar);j++,i++)
            data[i]=bar[j];
        for (int j=0;j<strlen(M_marks);j++,i++)
            data[i]=M_marks[j];
        for (int j=0;j<strlen(bar);j++,i++)
            data[i]=bar[j];
        for (int j=0;j<strlen(marks);j++,i++)
            data[i]=marks[j];
        for (int j=0;j<strlen(bar);j++,i++)
            data[i]=bar[j];
        for (int j=0;j<strlen(CRLF);j++,i++)
            data[i]=CRLF[j];


        for (int j=0;j<strlen(full_dash);j++,i++)
            data[i]=full_dash[j];
        for (int j=0;j<strlen(CRLF);j++,i++)
            data[i]=CRLF[j];


        for (int j=0;j<strlen(full_star);j++,i++)
            data[i]=full_star[j];
        for (int j=0;j<strlen(_tot);j++,i++)
            data[i]=_tot[j];
        for (int j=0;j<strlen(marks);j++,i++)
            data[i]=marks[j];
        for (int j=0;j<strlen(slash);j++,i++)
            data[i]=slash[j];
        for (int j=0;j<strlen(out_of);j++,i++)
            data[i]=out_of[j];
        for (int j=0;j<strlen(CRLF);j++,i++)
            data[i]=CRLF[j];
        for (int j=0;j<strlen(full_star);j++,i++)
            data[i]=full_star[j];
        for (int j=0;j<strlen(CRLF);j++,i++)
            data[i]=CRLF[j];


        for (int j=0;j<strlen(full_star);j++,i++)
            data[i]=full_star[j];
        for (int j=0;j<strlen(reference);j++,i++)
            data[i]=reference[j];
        for (int j=0;j<strlen(end);j++,i++)
            data[i]=end[j];


        cout<<"Sending e-mail to "<<to<<"..."<<endl<<"Please Wait..."<<endl;

        if(send_Mail_Gmail_cURL_Engine(username, to, username, password, data)==0)
            cout<<"Mail sent to "<<to<<endl;
    }
}
mail_List.close();
marks_file.close();
cwf_file.close();
split_marks_file.close();
names_file.close();
test_data_file_in.close();
}
else
{
cout<<endl<<endl;
cout<<"Cannot find specified file...";
}
cout<<"\nPress enter key to continue..."<<endl;
cin.get();
cin.get();
}

//-----------------------------------------------------------------------------------------------//


void modify_student_data()
{
}


//-----------------------------------------------------------------------------------------------//


int main(int argc, char* argv[])
{
DIR *d;
d=opendir("Data");
if (d==NULL)
    mkdir("Data");
closedir(d);

{
ifstream temp;

temp.open("Data/username_File");
if (!temp.is_open())
{
    string username;
    clear_output_screen();
    cout<<"Student Data Management System"<<endl;
    cout<<"\t-by Sujai Ram Prasath C and Avinash M"<<endl;
    cout<<"ver 0.1"<<endl;
    cout<<endl<<"Username file is missing..."<<endl;
    cout<<"Enter the username : ";
    getline(cin,username);
    ofstream tmp("Data/username_File");
    tmp<<username;
    tmp.close();
}
temp.close();

temp.open("Data/password_File");
if (!temp.is_open())
{
    string password;
    clear_output_screen();
    cout<<"Student Data Management System"<<endl;
    cout<<"\t-by Sujai Ram Prasath C and Avinash M"<<endl;
    cout<<"ver 0.1"<<endl;
    cout<<endl<<"Password file is missing..."<<endl;
    cout<<"Enter the password : ";
    getline(cin,password);
    ofstream tmp("Data/password_File");
    tmp<<password;
    tmp.close();
}
temp.close();
}

START:
int choice;
do
{
    clear_output_screen();
    cout<<"Student Data Management System"<<endl;
    cout<<"\t-by Sujai Ram Prasath C and Avinash M"<<endl;
    cout<<"ver 0.1"<<endl;
    cout<<"MENU\n\t1.ADD NEW CLASS\n\t2.ENTER TEST MARKS\n\t3.VIEW SINGLE TEST MARKS\n\t4.VIEW ALL TEST MARKS\n\t5.SEND MAIL\n\t6.EXIT";
    cout<<"\nEnter the choice ( 1 to 6 ) : ";

    cin>>choice;

    if (cin.fail())
    {
        cout<<"Invalid Input"<<endl;
        cin.clear();
        cin.ignore();
        goto START;
    }

    cout<<endl;

    switch(choice)
    {
    case 1:
        add_New_Class();
        break;

    case 2:
        enter_Test_Marks();
        break;

    case 3:
        single_test_marks();
        break;

    case 4:
        all_test_marks();
        break;

    case 5:
        send_Mail();
        break;

    case 6:
        exit(0);

    case 7:
        modify_student_data();
        break;

    default:
        cout<<"Enter the right choice"<<endl;
        break;
    }
}while(choice!=6);

return 0;
}

//-----------------------------------------------------------------------------------------------//
