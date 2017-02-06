#include "pcstatus.h"

PcStatus::PcStatus()
{
    toppleControl = false;
    warningControl = false;
    powerlevel = 0;
    action = NOAction;
    actionState = ActionState_UNDO;
    actionInfo = "";
    state = false;
}
