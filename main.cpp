#include <iostream>
#include <string>
#include <queue>
#include "logging.h"
#include "helper.h"
#include "randomizer.h"

int main(int argc, char ** argv)
{
    if(argc < 2)
    {
        cout << "No configuration file provided" << endl;
        exit(1);
    }
    else if (argc == 2)
    {
        config cfg;
        string path = argv[1];
        string content = readFile(path);
        readConfig(content, cfg);
        string logPath = getDateAndTime() + ".log";
        
        priority_queue<event, vector<event>, compareEvents> events;
        queue<event> cpuQueue;
        queue<event> disk1Queue;
        queue<event> disk2Queue;
        queue<event> networkQueue;
        srand(cfg.SEED);
        
        event event1, event2, event3;

        event1.id = 1;
        event1.t = CPU_START;
        event1.time = cfg.INIT_TIME;
        
        events.push(event1);
        
        event2.id = 0; // null
        event2.t = SIMULATION_FINISH;
        event2.time = cfg.FIN_TIME;

        events.push(event2);

        event3.id = 2;
        event3.t = CPU_START;
        event3.time = 5;
        events.push(event3);
        while (!events.empty()) 
        {
            event e = events.top();
            events.pop();
            cout << "Time: " << e.time << "\n";
        }

    
    }
    else 
    {
        cout << "You can have only one configuration file." << endl;
        exit(1);
    }
    return 0;
}