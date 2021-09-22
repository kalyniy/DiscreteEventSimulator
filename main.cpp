#include <iostream>
#include <string>
#include <queue>
#include "logging.h"
#include "helper.h"
#include "randomizer.h"
#include "cpuHandler.h"
CPUHandler cpu;
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
        //string logPath = getDateAndTime() + ".log";
        cpu.run(cfg);
        
    
    }
    else 
    {
        cout << "You can have only one configuration file." << endl;
        exit(1);
    }
    return 0;
}