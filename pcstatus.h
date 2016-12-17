#ifndef PCSTATUS_H
#define PCSTATUS_H
#include <QString>
#include "const_define.h"
class PcStatus
{
public:
    PcStatus();
    bool toppleControl;
    bool warningControl;
    int powerlevel;
    int action;
    int actionState;
    QString actionInfo;

};

#endif // PCSTATUS_H
