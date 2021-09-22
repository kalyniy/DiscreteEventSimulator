#include <iostream>
#include <string>
#include "logging.h"

struct event
{
    int id;
    int time;
    type t;
};
int main(int argc, char ** argv)
{
    if(argc < 2)
    {
        cout << "No configuration file provided" << endl;
        exit(1);
    }
    else if (argc == 2)
    {
        string path = argv[1];
        config cfg;
        cfg.ARRIVE_MAX = 0;
        cfg.ARRIVE_MIN = 0;
        cfg.CPU_MAX = 0;
        cfg.CPU_MIN = 0;
        cfg.DISK1_MAX = 0;
        cfg.DISK1_MIN = 0;
        cfg.DISK2_MIN = 0;
        cfg.DISK2_MIN = 0;
        cfg.FIN_TIME = 0;
        cfg.INIT_TIME = 0;
        cfg.NET_PROB = 0;
        cfg.NETWORK_MAX = 0;
        cfg.NETWORK_MIN = 0;
        cfg.QUIT_PROB = 0;
        cfg.SEED = 0;

        cout << path << endl;
        printConfig(cfg);
    }
    else 
    {
        cout << "You can have only one configuration file." << endl;
        exit(1);
    }
    return 0;
}