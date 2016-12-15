#ifndef NEWDAYPANE_H
#define NEWDAYPANE_H

#include <QFrame>
#include <QDate>
#include "ttextlabel.h"
#include <QVBoxLayout>
#include "tcombowithaddfield.h"
#include "tbutton.h"
#include "eventpane.h"

class NewDayPane : public QFrame
{
public:
    NewDayPane(int did=1,QDate *day=new QDate(2016,1,1));
    TButton* addNew;
private:
    int dayIndex;
    QDate* thisDate;
};

#endif // NEWDAYPANE_H
