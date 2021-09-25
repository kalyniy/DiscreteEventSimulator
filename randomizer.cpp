#include "randomizer.h"
#include <iostream>
using namespace std;
type t;
int rng(int min, int max)
{
    int number = rand()%(max-min + 1) + min;
    return number;
}
double rng()
{
    double chance = ((double) rand() / (RAND_MAX)) + 1;
    while(chance < 0)
    {
        chance = ((double) rand() / (RAND_MAX)) + 1;
    }
    return chance;
}
type randomType(config &cfg)
{
    double chance = rng();
    if(chance < cfg.QUIT_PROB)
    {
        return SIMULATION_FINISH;
    }
    else if(chance < cfg.NET_PROB)
    {
        return NETWORK_START;
    }
    else
    {
        return DISK1_START;
    }
    
}