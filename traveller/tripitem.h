#ifndef TRIPITEM_H
#define TRIPITEM_H

#include <QString>
#include <QDate>
#include <QList>
#include "dayitem.h"

class TripItem
{
public:
    TripItem(int id,QString n,QString co,QString ci,QDate d,QList<DayItem*> list,int num,QString color,QString r="No Remark");
    int id;
    QString name;
    QString homeCountry;
    QString homeCity;
    QDate startDate;
    QList <DayItem*> dayList;
    QString remark;
    QString themeColor;
    int dayNum;
};

#endif // TRIPITEM_H
