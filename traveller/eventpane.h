#ifndef EVENTPANE_H
#define EVENTPANE_H

#include <QFrame>
#include "tcombowithcost.h"
#include <QVBoxLayout>
#include "ttextlabel.h"

class EventPane : public QFrame
{
public:
    EventPane(int id=1);
    int eid;
};

#endif // EVENTPANE_H
