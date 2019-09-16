#include "channel.h"
#include "unistd.h"
#include <thread>
#include <cassert>
#include <iostream>

using namespace std;

channel<int> chn;
void out()
{
    int value = 0;
    while (true)
    {
        int v;
        value++;
        chn >> v;
        cout << "out" << v << endl;
        cout.flush();
        if (v != value)
        {
            cerr << value << "!=" << v << endl;
            exit(1);
        }
    }
}
void in()
{
    int value = 0;
    while(true)
    {
        value++;
        //cout << "in" << value << endl;
        chn << value;
    }
}

int main()
{
    thread a(in);
    thread b(out);
    a.join();
    b.join();
    return 0;
}