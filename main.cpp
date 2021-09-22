#include <iostream>
#include <string>
#include "logging.h"
#include "helper.h"

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
        readConfig(path, cfg);
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