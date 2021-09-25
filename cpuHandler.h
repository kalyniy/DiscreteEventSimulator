#include <iostream>
#include <string>
#include <queue>

#include "main.h"

using namespace std;

class CPUHandler
{
    public:
        priority_queue<event, vector<event>, compareEvents> events;
        queue<event> cpuQueue;
        queue<event> disk1Queue;
        queue<event> disk2Queue;
        queue<event> networkQueue;
        config settings;
        void run(config &cfg);
        
    private:
};