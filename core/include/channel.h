#include <mutex>

using namespace std;

template<typename T>
class channel
{
private:
    mutex outMutex;
    mutex inMutex;
    T value;

public:
    channel()
    {
        outMutex.lock();
    }
    channel& operator>>(T &rhs)
    {
        outMutex.lock();
        rhs = value;
        inMutex.unlock();
        return *this;
    }
    channel& operator<<(T &rhs)
    {
        inMutex.lock();
        value = rhs;
        outMutex.unlock();
        return *this;
    }
};