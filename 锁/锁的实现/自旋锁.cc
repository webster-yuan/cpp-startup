#include <iostream>
#include <pthread.h>
#include <thread>
//浣跨敤pthread搴撲腑鐨刾thread_spin_lock()鎺ュ彛灏佽涓€涓嚜鏃嬮攣绫?
class SpinLock
{
private:
    pthread_spinlock_t _lock;

public:
    SpinLock()
    {
        pthread_spin_init(&_lock, 0);
    }
    ~SpinLock()
    {
        pthread_spin_destroy(&_lock);
    }

public:
    void lock()
    {
        pthread_spin_lock(&_lock);//灏濊瘯鑾峰彇閿侊紝濡傛灉閿佸凡缁忚鍗犵敤锛屽垯浼氫竴鐩磋嚜鏃嬬瓑寰?
    }
    void unlock()
    {
        pthread_spin_unlock(&_lock);
    }
};
int main()
{
    SpinLock sl;
    std::thread t1([&]()
                   {
                       sl.lock();
                       //do things!!
                       std::cout<<"thread 1 acquired the lock!"<<std::endl;
                       sl.unlock(); });
    std::thread t2([&]() {
        sl.lock();
        //do thing!
        std::cout<<"thread 2 acquired the lock!"<<std::endl;
        sl.unlock();
    });
    t1.join();
    t2.join();
    return 0;
}