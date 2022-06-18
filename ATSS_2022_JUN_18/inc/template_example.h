#ifndef TEMPLATE_EXAMPLE_H
#define TEMPLATE_EXAMPLE_H
#include"inc/ATSS_Includes.h"
static pthread_mutex_t map_lock1                = PTHREAD_MUTEX_INITIALIZER;

/// using structure as template parameter
template<class T>
class Mystruct
{
    std::multimap<string,T>map1;
public:
    bool setData(string key, T data)
    {
        bool flag = false;
        pthread_mutex_lock(&map_lock1);
        auto it = map1.insert(std::pair<string,T>(key,data));
        pthread_mutex_unlock(&map_lock1);
        cout<<"\nelement added = "<<it->first<<endl;
        return flag;
    }
    T getData(string key){
        T val; memset(&val,0,sizeof(0));
        auto it = map1.find(key);
        if(it!=map1.end())
        {
            cout<<"\nelement="<<it->first;
            return it->second;
        }
        return val;
    }
    bool deleteData(string key){
        bool flag = false;
        int count = map1.erase(key);
        cout<<"\nelements erased="<<count<<endl;
        return flag;
    }
    void printData(){
        for(auto i=map1.begin();i!=map1.end();i++)
        {
            cout<<"key:"<<i->first<<" val: a="<<i->second.a<<" b="<<i->second.b<<endl;
        }
    }
};
class template_example
{
public:
    template_example();
};

#endif // TEMPLATE_EXAMPLE_H
