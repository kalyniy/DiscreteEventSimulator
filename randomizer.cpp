#include "randomizer.h"
type t;
int rng(int min, int max)
{
    int number = rand()%(max-min + 1) + min;
    return number;
}

type randomType(config &cfg)
{
    
    int chance = rng(0, 100);
    if(chance < cfg.QUIT_PROB)
    {
        
    }
    return CPU_START;
    
}