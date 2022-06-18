
#include "inc/ATSS_Includes.h"

ATSS_DBData DBData_obj;
ATSS_Communication atss_communication_obj;
ATSS_MessageProcessor msg_processor_obj;

//template<typename T>
//T func(T a, T b)
//{
//    cout<<"\n"<<a<<" "<<b<<endl;
//    return a+b;
//}


//template<class X>
//class Test
//{
//private:
//    X a;
//public:
//    Test(X x):a(x)
//    {}
//    void print()
//    {
//        cout<<"\na="<<a<<endl;
//    }
//};

// struct node {
//     int data;
//     struct node* next;
// };

// void push(struct node** head,int data){
//     struct node* newnode = new node();
//     newnode->data = data;
//     newnode->next = *head;
//     *head  = newnode;
// }
// void print(struct node* head)
// {
//     struct node* temp = head;
//     do{
//         cout<<head->data<<" ";
//         head = head->next;
//     }
//     while(head->next!=temp);
// }
// // ________________________________________________________________________________________________________________________________________________________________________________________________
#include<bits/stdc++.h>
#include<map>
#include<string>
#include<pthread.h>

using namespace std;

struct mystruct{
    int a;
    char b;
    void logg(){
        std::cout<<"\na="<<a<<" b="<<b<<endl;
    }
};
struct mystruct2{
    string a;
    double b;
    void logg(){
        std::cout<<"\na="<<a<<" b="<<b<<endl;
    }
};
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

void print()
{
    cout<<"last fn called"<<endl;
}
///variadic template function
template<typename T, typename...Types>
void print(T v1,Types...var2)
{
    cout<<v1<<endl;
    print(var2...);
}

int main()
{
    print(1,2.2,"hello",'v');
    string k="1";
    mystruct m;

    m.a = 10;
    m.b = 'b';
    Mystruct<mystruct> abc;
    abc.setData(k,m);                  //abc.printData();
    //mystruct bcd = abc.getData(k);     //bcd.logg();

    mystruct2 m11;

    m11.a = "10";
    m11.b = 2.45456;
    Mystruct<mystruct2> bcd;
    bcd.setData(k,m11);

    k="2";mystruct m2;
    m2.a = 20;
    m2.b = 'c';
    abc.setData(k,m2);
    abc.printData();
    bcd.printData();
   // bcd = abc.getData(k);      bcd.logg();

    //        strcpy(k,"2"); mystruct m3;
    //        m3.a = 30;
    //        m3.b = 'd';
    //        //abc= new Mystruct<mystruct>(k,m3);
    //        abc.setData(k,m3);         abc.printData();
    //        bcd = abc.getData("2");      bcd.logg();
    //abc.deleteData(k);         //abc.printData();




    // struct node* head = nullptr;
    // push(&head,1);
    // push(&head,2);
    // print(head);

    //    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout); // use the rest of cout,cin as usual

    //    int n=1000;
    //    int array[n];
    //    for(int i=0;i<n;i++)
    //    {
    //        array[i]=i;
    //    }
    //    int k = 0;
    //    int x = 234;
    //    for (int b = n/2; b >= 1; b /= 2)
    //    {
    //        while (k+b < n && array[k+b] <= x)
    //        {
    //            k += b;
    //        }
    //    }
    //    if (array[k] == x)
    //    {
    //        cout<<x<<" found at index "<<k;
    //    }

    //    int array[]={-2,3,6,-1,4,-5};
    //    int best = 0, sum = 0;
    //    int n = sizeof(array)/sizeof(array[0]);
    //    for (int k = 0; k < n; k++)
    //    {
    //        sum = min(array[k],sum+array[k]);
    //        best = max(best,sum);
    //        cout<<"sum="<<sum<<"best="<<best<<endl;
    //    }
    //    cout << best << "\n";


    //    func(10,4);
    //    func('a','a');
    //    cout<<"\nsum="<<func(1.1,2.2);

    //    Test<int> tt(19);
    //    tt.print();
    //    Test<int> a(10);
    //    a.print();
}

