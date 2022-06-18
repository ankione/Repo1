#ifndef USER_DEFINED_H
#define USER_DEFINED_HA
#include"inc/ATSS_Includes.h"

struct mystruct{
    int a;
    char b;
    void log(){
        std::cout<<"\na="<<a<<" b="<<b<<endl;
    }
};
struct mystruct2{
    string a;
    double b;
    void log(){
        std::cout<<"\na="<<a<<" b="<<b<<endl;
    }
};

#endif // USER_DEFINED_H
