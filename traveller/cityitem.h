#ifndef CITYITEM_H
#define CITYITEM_H

#include <QString>
#include <QList>
#include "eventitem.h"

class CityItem
{
public:
    CityItem(int id,QString co,QString ci,QList<EventItem*> list);
    int id;
    QString country;
    QString city;
    QList <EventItem*> eventList;
};

#endif // CITYITEM_H
