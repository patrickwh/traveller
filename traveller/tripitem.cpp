#include "tripitem.h"

TripItem::TripItem(int id,QString n,QString co,QString ci,QDate d,QList<DayItem*> list,int num,QString color,QString r):\
    id{id},name{n},homeCountry{co},homeCity{ci},dayList{list},remark{r},startDate{d},dayNum{num},themeColor{color}
{

}
