#include "eventitem.h"

EventItem::EventItem(int id,QString dt,QString dn,QString cur,QString tcur,QString tt,QString tn,double ds,double ts)\
    :id{id},destType{dt},destName{dn},currency{cur},tcurrency{tcur},transportType{tt},transportName{tn},destCost{ds},transportCost{ts}
{

}

void EventItem::updateValues(QString dt,QString dn,QString cur,QString tcur,QString tt,QString tn,double ds,double ts)
{
    destType = dt;
    destName = dn;
    destCost = ds;
    currency = cur;
    tcurrency = tcur;
    transportType = tt;
    transportName = tn;
    transportCost = ts;
}
