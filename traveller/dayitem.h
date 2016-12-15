#ifndef DAYITEM_H
#define DAYITEM_H

#include <QString>
#include <QList>
#include "cityitem.h"


class DayItem
{
public:
    DayItem(int id,QList<CityItem*> list);
    int id;
    QList <CityItem*> cityList;
};

#endif // DAYITEM_H
