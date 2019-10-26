#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

class Barrier
{
private:
    const uint32_t threadCounter;
    atomic<uint32_t> threadsWaiting;
    bool isNotWaiting;
    condition_variable waitVariable;
    mutex b_mutex;
public:
    Barrier(uint32_t n) : threadCounter(n), threadsWaiting(0), isNotWaiting(false) {}

    // явно запрещаем конструктор копирования
    Barrier(const Barrier &) = delete;

    void wait()
    {
        // fetch_add = RMW-operation (read-modify-write)
        // read atomic variable, add with argument and
        // write new value to atomic variable
        if( threadsWaiting.fetch_add(1) >= threadCounter - 1)
        {
            // if all thread at the barrier
            // tell everybody that they needn't to wait anymore
            isNotWaiting = true;
            waitVariable.notify_all();
            threadsWaiting.store(0);
        }
        else // wait all thread at the barrier
        {
            // if not all threads at the barrier
            // threads that at the barrier should sleep
            unique_lock<mutex> lock(b_mutex);
            // free mutex and stop thread until cond var will get the sygnal
            // after that thread will be waked up and then lock again
            // to avoid false waking ups - use predicate
            waitVariable.wait(lock, [&]{ return isNotWaiting; });
        }
    }
};

shared_ptr<Barrier> myBarrier;

class BarrierDemo
{
private:
    uint32_t id;
    shared_ptr<thread> myThread;
public:
    BarrierDemo( uint32_t i ) : id(i) {}

    void start()
    {
        cout << "Thread " << id << " start" << endl;
        myThread = shared_ptr<thread>(new thread(&BarrierDemo::run, this));
        cout << "Thread " << id << " created" << endl;
    }

    void wait()
    {
        myThread -> join();
    }

    void run()
    {
        cout << "Thread " << id << " runs before barrier" << endl;
        myBarrier -> wait();
        cout << "Thread " << id << " runs after barrier" << endl;
    }
};

int main()
{
    uint32_t threads;
    cin >> threads;
    myBarrier = shared_ptr<Barrier>(new Barrier(threads));
    shared_ptr<vector<BarrierDemo>> processing = make_shared<vector<BarrierDemo>>();

    for(uint32_t i = 0; i < threads; i++ )
    {
        processing -> push_back(BarrierDemo(i));
        processing -> at(i).start();
    }

    for(uint32_t i = 0; i < threads; i++ )
    {
        processing -> at(i).wait();
    }



//    shared_ptr<BarrierDemo> bar_demos = make_shared<BarrierDemo>(new (sizeof(BarrierDemo) * threads));
//    BarrierDemo* bar_demos = static_cast<BarrierDemo*>(::operator new(sizeof(BarrierDemo) * threads));



//    for( int32_t i = 0; i < threads; i++ )
//    {
//        new (&bar_demos[i])BarrierDemo(i);
//        bar_demos[i].start();
//    }
//    for( int32_t i = 0; i < threads; i++ )
//    {
//        bar_demos[i].wait();
//    }

//    ::operator delete(bar_demos);
//    delete myBarrier;

    return 0;
}
