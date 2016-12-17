#include "autostate.h"
#include <QDebug>
AutoState::AutoState()
{
}

void AutoState::printfInfo()
{
    for(int i=0;i<stage.size();i++)
    {
        State state = stage.at(i);
        qDebug()<<state.startIndex<<" "<<state.endIndex<<" "<<state.actionStartIndex<<" "<<state.actionID;
    }
}
