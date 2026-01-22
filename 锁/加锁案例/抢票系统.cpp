#include <iostream>
#include <pthread.h>
#include<unistd.h>
using namespace std;

#define NUM 1000
class Ticket
{
private:
    int num;
    pthread_mutex_t mtx;
public:
    Ticket(int n = NUM)
        : num(n)
    {
        pthread_mutex_init(&mtx,nullptr);
    }
    ~Ticket()
    {
        pthread_mutex_destroy(&mtx);
    }
public:
    bool GetTickets()
    {
        bool res=true;

        pthread_mutex_lock(&mtx);
        if(num>0)
        {
            usleep(1000);
            cout<<"鎴戞槸"<<pthread_self()<<",鎴戞姠绁ㄧ殑缂栧彿鏄?<<num<<endl;
            num--;
            printf("");//鏁呮剰璋冪敤锛屽鍔犵敤鎴锋€佺殑鍒囨崲
        }
        else
        {
            res=false;
        }
        pthread_mutex_unlock(&mtx);
        return res;
    }
};
void* thread_run(void* args)
{
    Ticket* t=(Ticket*)args;
    while(1)
    {
        if(!t->GetTickets())
        {
            cout<<"绁ㄨ鎶㈠畬浜?<<endl;
            break;
        }
    }
    return nullptr;
}
int main()
{
    Ticket* t =new Ticket();

    pthread_t tid[5];
    for(int i=0;i<5;i++)
    {
        pthread_create(&tid[i],nullptr,thread_run,(void*)t);//鍙傛暟涓嶆槸鐬庝紶鐨?
    }
    for(int i=0;i<5;i++)
    {
        pthread_join(tid[i],nullptr);//杩涜闃诲绛夊緟
    }
    return 0;
}