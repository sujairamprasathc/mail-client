#ifndef CSRP_MISC_TOOLS
#define CSRP_MISC_TOOLS 1

#ifndef _MATH_H
    #include <math.h>
#endif
#ifndef _STRING_H
    #include <string.h>
#endif

#ifdef __cplusplus
    #ifndef _GLIBCXX_STRING
        #include <string>
    #endif
#endif

//Convert int to char
void itoa(int a, char *b[], int c)
{
/*
    No returning... Directly modify the array pointed to...
    Eg. of modifications...
        1) 0 - 00000....c times
        2) 5 - 00000....c-1 times...5
        3) 152 - 00000....c-3 times....152
*/
c--;

for (int i=c,d=0;i>0;i--,d++)
{
    int x=(a/(pow(10,i)));
    a=a%(int)pow(10,i);
    *b[d]=x+48;
}

*b[c]=(a%10)+48;

}


#ifdef __cplusplus  /*Strings only available on C++*/

//Convert int to string
string itos(int to_convert)
{
/*
    Returns a string containing the given number
    in the form of strings...
*/
int no_of_digits=0;

for (int i=0;(int)(to_convert/pow(10,i))!=0;i++)
{
if (to_convert/pow(10,i)==0)
    break;
else
    no_of_digits++;
}

string temp;
no_of_digits--;

for (int i=no_of_digits;i>0;i--)
{
    char tmp;
    int x=(to_convert/(pow(10,i)));
    to_convert=to_convert%(int)pow(10,i);
    tmp=x+48;
    temp.append(&tmp);
}

char z=(to_convert%10)+48;
temp.append(&z);

return temp;
}

#endif  /*__cplusplus*/


//Create a new folder
int mkdir(const char* __NAME__)
{
/*
    Creates a directory with the given NAME

    Only Windows and Linux are supported

    Warning : The function depends on the shell used,
              and may not work in all cases...
*/
#ifdef _WIN32
    char call[3+strlen(__NAME__)]={'m','d',' '};
    strcat(call,__NAME__);
    if (system(call)==0)
        return 0;
    else
        return -1;
#elif __linux__
    char call[6+strlen(__NAME__)]={'m','k','d','i','r',' '};
    strcat(call,__NAME__);
    if (system(call)==0)
        return 0;
    else
        return -1;
#endif
}

#endif  /*CSRP_MISC_TOOLS*/
