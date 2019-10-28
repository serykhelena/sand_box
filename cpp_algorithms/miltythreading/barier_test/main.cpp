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
        if( threadsWaiting.fetch_add(1) == threadCounter - 1)
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
    thread myThread;
    bool isProcessed;
public:
    BarrierDemo( uint32_t i ) : id(i), isProcessed(false) {}

    void start()
    {
        myThread = thread(&BarrierDemo::run, this);
        isProcessed = true;
    }

    void wait()
    {
        myThread.join();
    }

    void run()
    {
        if( isProcessed )
        {
            cout << "Thread " << id /*<< " : " << myThread.get_id()*/ << " runs before barrier" << endl;
            myBarrier -> wait();
            cout << "Thread " << id /*<< " : " << myThread.get_id()*/ << " runs after barrier" << endl;
        }
    }
};

int main()
{
    uint32_t threads;
    cout << "Enter number of threads: ";
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

    return 0;
}
