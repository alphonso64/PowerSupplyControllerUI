#ifndef DPUSTATUS_H
#define DPUSTATUS_H

class DpuStatus
{
public:
    DpuStatus();
    int temp_a;
    int temp_b;
    unsigned int ua;
    unsigned int ub;
    unsigned int uc;
    unsigned int ia;
    unsigned int ib;
    unsigned int ic;
    unsigned int power;
    int errorcode;
};

#endif // DPUSTATUS_H
