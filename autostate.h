#ifndef AUTOSTATE_H
#define AUTOSTATE_H
#include "json/json.h"
#include <QList>
#include <QTime>
class State
{
public :
    int startIndex;
    int endIndex;
    int actionStartIndex;
    int actionID;
};

class AutoState
{
public:
    AutoState();
    Json::Value root;
    QList<State> stage;

    void printfInfo();

    int cnt;
    int currenIndex;

};

#endif // AUTOSTATE_H
