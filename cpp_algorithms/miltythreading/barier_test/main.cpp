#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

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
        else
        {
            // if not all threads at the barrier
            // threads that at the barrier should sleep
            unique_lock<mutex> lock(b_mutex);
            // free mutex and stop thread until cond var will get the sygnal
            // after that thread will be waked up and then lock again
            // to avoid false waking ups - use predicate
            waitVariable.wait(lock, [&]{ return noWait; });
        }

    }






};

int main()ihr
{
    cout << "Hello World!" << endl;
    return 0;
}
