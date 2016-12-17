#include "parseworker.h"
#include "util.h"
#include <QDebug>
void ParseWorker::run()
{
    QString value = Util::readFile(PrePath+fileName);
    Json::Reader reader;
    if (reader.parse(value.toStdString(), autostate.root, false))
    {
        qDebug()<<" Json::Value root "<<autostate.root.size();
    }

    autostate.stage.clear();

    int flag = 0;
    State *state = NULL;
    state = new State();
    state->startIndex = 0;

    for(int i=0;i<autostate.root.size();i++)
    {
        int action = autostate.root[i]["action"].asInt();
        int actionSta = autostate.root[i]["ac_sta"].asInt();
        if(action == NOAction){
            if(flag!= 0){
                if(actionSta == ActionState_DONE){
                    state->endIndex = i;
                    autostate.stage.append(*state);
                    state = new State();
                    state->startIndex = i;
                    flag = 0;
                }else {
                    flag = 0;
                }
            }
        }else{
            if(flag == 0){
                state->actionStartIndex = i;
                state->actionID = action;
                flag = 1;
            }
        }

    }

    autostate.printfInfo();
    emit(parsed());

}
