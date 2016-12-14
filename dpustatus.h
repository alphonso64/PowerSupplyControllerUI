#ifndef DPUSTATUS_H
#define DPUSTATUS_H

class DpuStatus
{
public:
    DpuStatus();
    int temp_a;
    int temp_b;
    int ua;
    int ub;
    int uc;
    int ia;
    int ib;
    int ic;
    int power;
    int errorcode;
};

#endif // DPUSTATUS_H
