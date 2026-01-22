#pragma once
#include <queue>
#include <mutex>
#include "Task.hpp"
namespace ns_thread_pool
{
    const int g_num = 5;
    template <class T>
    class ThreadPool
    {
    private:
        int _num;
        std::queue<T> task_queue_;
        pthread_mutex_t mtx_;
        pthread_cond_t cond_;

        static ThreadPool<T>* ins;

    private:
        ThreadPool(int num = g_num)
            : _num(num)
        {
            pthread_mutex_init(&mtx_, nullptr);
            pthread_cond_init(&cond_, nullptr);
        }
        ThreadPool(const ThreadPool<T>& tp) = delete;
        ThreadPool<T>& operator=(const ThreadPool<T>& tp) = delete;

        ~ThreadPool()
        {
            pthread_mutex_destroy(&mtx_);
            pthread_cond_destroy(&cond_);
        }

    public:
        static ThreadPool<T>* GetInstance()
        {
            static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
            // 如果是第一次来的,就获取锁.省得浪费了获取锁的时间之后发现还不是第一个来的,白竞争了
            if (ins == nullptr)
            {
                pthread_mutex_lock(&lock);
                if (ins == nullptr)
                {
                    ins = new ThreadPool<T>();
                    ins->InitThreadPool();
                    std::cout << "首次加载对象" << std::endl;
                }
                pthread_mutex_unlock(&lock);
            }
            return ins;
        }

    public:
        void Lock()
        {
            pthread_mutex_lock(&mtx_);
        }
        void UnLock()
        {
            pthread_mutex_unlock(&mtx_);
        }
        void Wait()
        {
            pthread_cond_wait(&cond_, &mtx_);
        }
        void WakeUp()
        {
            pthread_cond_signal(&cond_);
        }
        bool IsEmpty()
        {
            return task_queue_.empty();
        }

    public:
        static void* Rountine(void* args) // 传过来的是单个线程信息,线程调用类内成员,得声明为static
        {
            pthread_detach(pthread_self());
            ThreadPool<T>* tp = (ThreadPool<T> *)args;

            while (true)
            {
                tp->Lock();
                while (tp->IsEmpty())
                {
                    tp->Wait();
                }
                T t;
                tp->PopTask(&t);
                tp->UnLock();

                t.Run();
            }
        }
        void InitThreadPool()
        {
            pthread_t tid;
            for (int i = 0; i < _num; i++)
            {
                pthread_create(&tid, nullptr, Rountine, (void*)this);
            }
        }
        void PushTask(const T& in)
        {
            Lock();
            task_queue_.push(in);
            UnLock();
            WakeUp();
        }
        void PopTask(T* out)
        {
            *out = task_queue_.front();
            task_queue_.pop();
        }
    };

    template <class T>
    ThreadPool<T>* ThreadPool<T>::ins = nullptr;
}