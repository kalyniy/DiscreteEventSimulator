#include "logging.h"

void printConfig(config &cfg)
{
    cout << "SEED: " << cfg.SEED << endl;
    cout << "INIT_TIME: " << cfg.INIT_TIME << endl;
    cout << "FIN_TIME: " << cfg.FIN_TIME << endl;
    cout << "ARRIVE_MIN: " << cfg.ARRIVE_MIN << endl;
    cout << "ARRIVE_MAX: " << cfg.ARRIVE_MAX << endl;
    cout << "QUIT_PROB: " << cfg.NET_PROB << endl;
    cout << "CPU_MIN: " << cfg.CPU_MAX << endl;
    cout << "DISK1_MIN: " << cfg.DISK1_MIN << endl;
    cout << "DISK1_MAX: " << cfg.DISK1_MAX << endl;
    cout << "DISK2_MIN: " << cfg.DISK2_MIN << endl;
    cout << "DISK2_MAX: " << cfg.DISK2_MAX << endl;
    cout << "NETWORK_MIN: " << cfg.NETWORK_MIN << endl;
    cout << "NETWORK_MAX: " << cfg.NETWORK_MAX << endl;

}