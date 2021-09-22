#include "cpuHandler.h"
#include "logging.h"
#include "main.h"

void CPUHandler::run(config &cfg)
{
    settings = cfg;
    //printConfig(cfg);
    event event1, event2;

    event1.id = 1;
    event1.t = CPU_START;
    event1.time = cfg.INIT_TIME;
    events.push(event1);

    event2.id = 0; 
    event2.t = SIMULATION_FINISH;
    event2.time = cfg.FIN_TIME;
    events.push(event2);

}