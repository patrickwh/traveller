#ifndef EVENTITEM_H
#define EVENTITEM_H

#include<QString>

class EventItem
{
public:
    EventItem(int id,QString dt,QString dn,QString cur, QString tcur,QString tt,QString tn,double ds=0.0,double ts=0.0);
    void updateValues(QString dt,QString dn,QString cur, QString tcur,QString tt,QString tn,double ds=0.0,double ts=0.0);
    int id;
    QString destType;
    QString destName;
    QString currency;
    QString tcurrency;
    double destCost;
    QString transportType;
    QString transportName;
    double transportCost;
};

#endif // EVENTITEM_H
