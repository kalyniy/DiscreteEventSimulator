#include "cpuHandler.h"
#include "logging.h"
#include "helper.h"
#include "main.h"
#include "randomizer.h"
#include <unistd.h>
int currentTime = 0;
int jobCounter = 1;

bool isCPUBusy = false;
bool isDISK1Busy = false;
bool isDISK2Busy = false;
bool isNETWORKBusy = false;

void printPriorityQueue(priority_queue<event, vector<event>, compareEvents> events)
{
    while (!events.empty()) 
        {
            event e = events.top();
            events.pop();
            string str = eventToString(e);
            cout << str << endl;
        }
}
void CPUHandler::run(config &cfg)
{
    settings = cfg;
    srand(cfg.SEED);
    //printConfig(cfg);
    string logPath = getDateAndTime() + ".log";
    cout << "Writing logs to: " << logPath << endl;
    event event1 = event(jobCounter, cfg.INIT_TIME, SIMULATION_START);
    event event2 = event(0, cfg.FIN_TIME, SIMULATION_FINISH);
    
    events.push(event1);
    events.push(event2);
    while(currentTime < cfg.FIN_TIME)
    {
        event current = events.top();
        events.pop();
        currentTime = current.time;
        string info = eventToString(current);
        cout << info << endl;
        
        switch (current.t)
        {
            case SIMULATION_START:
            {
                cout << info << " arrived" << endl;
                jobCounter += 1;
                int time = current.time + rng(cfg.ARRIVE_MIN, cfg.ARRIVE_MAX);
                event e = event(jobCounter, time, SIMULATION_START);
                events.push(e);

                current.time = current.time + rng(cfg.ARRIVE_MIN, cfg.ARRIVE_MAX);

                if (isCPUBusy)
                {
                    cpuQueue.push(current);
                }
                else
                {
                    current.t = CPU_START;
                    events.push(current);
                }
                break;
            }
            case CPU_START:
            {
                current.t = CPU_FINISH;
                isCPUBusy = true;
                current.time = current.time + rng(cfg.CPU_MIN, cfg.CPU_MAX);
                events.push(current);
                cout << info << " entered CPU" << endl;
                break;
            }  
            case CPU_FINISH:
            {
                isCPUBusy = false;
                type rt = randomType(settings);
                if(rt == SIMULATION_FINISH)
                {
                    current.t = SIMULATION_FINISH;
                    events.push(current);
                }   
                else if(rt == NETWORK_START) 
                {
                    if(isNETWORKBusy || networkQueue.size() != 0) 
                    {
                        networkQueue.push(current);
                    }
                    else 
                    {
                        current.time = current.time + rng(cfg.NETWORK_MIN, cfg.NETWORK_MAX);
                        current.t = NETWORK_START;
                        events.push(current);
                    }
                }
                else 
                {
                    if(isDISK1Busy)
                    {
                        if(disk1Queue.size() < disk2Queue.size()) 
                        {
                            disk1Queue.push(event(current.id, current.time, DISK1_START));
                        }
                        else 
                        {
                            disk2Queue.push(event(current.id, current.time, DISK2_START));
                        }
            
                    }
                    else if(isDISK2Busy)
                    {
                        if(disk2Queue.size() < disk1Queue.size())
                        {
                            disk2Queue.push(event(current.id, current.time, DISK2_START));
                        }
                        else
                        {
                            disk1Queue.push(event(current.id, current.time, DISK1_START));
                        }

                    }
                    else 
                    {
                        int chance = rng(0, 50);
                        if(chance < 50)
                        {
                            current.t = DISK1_START;
                            events.push(current);
                        }
                        else 
                        {
                            current.t = DISK2_START;
                            events.push(current);
                        }

                    }

                }
                if(cpuQueue.size() != 0) 
                {
                    events.push(event(cpuQueue.front().id, current.time, CPU_START));
                    cpuQueue.pop();
                }
                break;
            }
            case DISK1_START:
            {
                isDISK1Busy = true;
                current.time = current.time + rng(cfg.DISK1_MIN, cfg.DISK1_MAX);
                current.t = DISK1_FINISH;
                events.push(current);
                cout << info << " entered DISK1 queue" << endl;
                break;
            }
            case DISK1_FINISH:
            {
                isDISK1Busy = false;

                if (!isCPUBusy)
                {
                    current.t = CPU_START;
                    events.push(current);
                }
                else
                {
                    cpuQueue.push(current);
                }
                disk1Queue.front().t = DISK1_START;
                event update = disk1Queue.front();
                cout << info << " left DISK1 queue at " << currentTime << endl;
                cout << eventToString(update) << " entered the DISK1" << endl;
                break;
            }
            case DISK2_START:
            {
                isDISK2Busy = true;
                current.time = current.time + rng(cfg.DISK2_MIN, cfg.DISK2_MAX);
                current.t = DISK2_FINISH;
                events.push(current);
                cout << info << " entered DISK2" << endl;
                break;
            }
            case DISK2_FINISH:
            {
                isDISK2Busy = false;
                if (!isCPUBusy)
                {
                    current.t = CPU_START;
                    events.push(current);
                }
                else
                {
                    cpuQueue.push(current);
                }
                disk2Queue.front().t = DISK2_START;
                event update = disk2Queue.front();
                cout << info << " left DISK2 Queue at time " << currentTime << endl;
                cout << "Event " << eventToString(update) << " entered the DISK1 Queue" << endl;
                break;
            }
            case NETWORK_START:
            {
                isNETWORKBusy = true;
                current.time = current.time + rng(cfg.NETWORK_MIN, cfg.NETWORK_MAX);
                current.t = NETWORK_FINISH;
                events.push(current);
                cout << info <<  " entered NETWORK queue" << endl;
                break;
            }
            case NETWORK_FINISH:
            {
                isNETWORKBusy = false;
                if (!isCPUBusy)
                {
                    current.t = CPU_START;
                    events.push(current);
                }
                else
                {
                    cpuQueue.push(current);
                }
                networkQueue.front().t = NETWORK_START;
                event update = networkQueue.front();
                cout << info << " left network queue" << endl;
                cout << "at " << currentTime << " event" << info << " entered the disk1 queue" << endl;
                break;
            }
            default:
            {
                break;
            }
        }
        //sleep(1);
    }

}