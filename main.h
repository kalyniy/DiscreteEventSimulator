enum type
{
    CPU_START,
    CPU_FINISH,
    SIMULATION_FINISH,
    DISK1_START,
    DISK1_FINISH,
    DISK2_START,
    DISK2_FINISH,
    NETWORK_START,
    NETWORK_FINISH
};
struct config
{
    int SEED;
    int INIT_TIME;
    int FIN_TIME;
    int ARRIVE_MIN;
    int ARRIVE_MAX;
    int QUIT_PROB;
    int NET_PROB;
    int CPU_MIN;
    int CPU_MAX;
    int DISK1_MIN;
    int DISK1_MAX;
    int DISK2_MIN;
    int DISK2_MAX;
    int NETWORK_MIN;
    int NETWORK_MAX;
};
struct event;