#include "tdatabase.h"

QSqlDatabase TDataBase::database = QSqlDatabase::addDatabase("QSQLITE");

TDataBase::TDataBase()
{
}

void TDataBase::initDatabase()
{
    TDataBase::database.setDatabaseName("..\\database\\travellerData.db");
    if(!TDataBase::database.open()){
        emit this->databaseErrorSig("Cannot Open Database");
        return;
    }
}

bool TDataBase::openDatabase(){
    TDataBase::database.setDatabaseName("..\\database\\travellerData.db");
    if(!TDataBase::database.open()){
        emit this->databaseErrorSig("Cannot Open Database");
        return false;
    }
    return true;
}

QString TDataBase::getCountryList()
{
    QString list = NULL;
    openDatabase();
    QString selectAll = "SELECT * FROM countryList";
    QSqlQuery query;
    query.prepare(selectAll);
    if(!query.exec())
    {
        emit this->databaseErrorSig("Cannot Get All Country");
        return list;
    }
    list = "";
    while(query.next())
    {
        list += query.value(1).toString()+"\x03";
    }
    TDataBase::database.close();
    return list;
}

QString TDataBase::getCityList(QString country){
    QString list = NULL;
    openDatabase();
    QString select = "SELECT * FROM countryList WHERE name='"+country+"'";
    QSqlQuery query;
    query.prepare(select);
    if(!query.exec())
    {
        emit this->databaseErrorSig("Cannot Get City List");
        return list;
    }
    list = "";
    while(query.next())
    {
        list += query.value(2).toString();
    }
    TDataBase::database.close();
    return list;
}

QString TDataBase::addCountry(QString country, int id){
    openDatabase();
    QString add = "INSERT INTO countryList VALUES("+QString::number(id)+",'"+country+"','')";
    QSqlQuery query;
    query.prepare(add);
    if(!query.exec())
    {
        emit this->databaseErrorSig("Cannot Add Country");
        return StaticData::NULL_RESULT;
    }
    QString selectAll = "SELECT * FROM countryList";
    QString list = "";
    query.prepare(selectAll);
    if(!query.exec())
    {
        emit this->databaseErrorSig("Cannot Return Country List");
        return StaticData::NULL_RESULT;
    }
    list = "";
    while(query.next())
    {
        list += query.value(1).toString()+"\x03";
    }
    TDataBase::database.close();
    return list;
}

QString TDataBase::addCity(QString country, QString city){
    openDatabase();
    QString getCity = "SELECT * FROM countryList WHERE name='"+country+"'";
    QSqlQuery query;
    query.prepare(getCity);
    if(!query.exec())
    {
        emit this->databaseErrorSig("Cannot Get Country");;
        return StaticData::NULL_RESULT;
    }
    QString cityList="";
    if(query.next()){
        cityList = query.value(2).toString();
    }
    cityList += "\x03"+city;
    QString update = "UPDATE countryList SET cities='"+cityList+"' WHERE name='"+country+"'";
    query.prepare(update);
    if(!query.exec())
    {
        emit this->databaseErrorSig("Cannot Update City List");
        return StaticData::NULL_RESULT;
    }
    QString list = "";
    QString select = "SELECT * FROM countryList WHERE name='"+country+"'";
    query.prepare(select);
    if(!query.exec())
    {
        emit this->databaseErrorSig("Cannot Get Cities");
        return StaticData::NULL_RESULT;
    }
    if(query.next())
    {
        list = query.value(2).toString();
    }
    TDataBase::database.close();
    return list;
}

QList<TripItem*> TDataBase::getTheTripById(int id){
    openDatabase();
    QString select = "";
    // id==-1 means select all trips
    if(id==-1){
        select = "SELECT * FROM tripList";
    }else{
        select = "SELECT * FROM tripList WHERE id="+QString::number(id);
    }
    QSqlQuery q;
    q.prepare(select);
    QList<TripItem*> tripList;
    if(!q.exec()){
        emit this->databaseErrorSig("Cannot Get Trip List");
        return tripList;
    }
    while(q.next()){
        int id = q.value(0).toInt();
        QString name = q.value(1).toString();
        QString country = q.value(2).toString();
        QString city = q.value(3).toString();
        QDate date = QDate::fromString(q.value(4).toString(),StaticData::DATE_STORATION_FORMAT);
        QString remark = q.value(5).toString();
        int num = q.value(6).toInt();
        QString color = q.value(7).toString();
        QList<DayItem*> dayList;
        for(int did=0;did<num;did++)
        {
            QString selectDay = "SELECT * FROM dayCityList WHERE tripid="+QString::number(id)+\
                    " AND dayid="+QString::number(did);
            QSqlQuery q1;
            q1.prepare(selectDay);
            if(!q1.exec()){
                emit this->databaseErrorSig("Cannot Get Days");
                return tripList;
            }
            QList<CityItem*> cityList;
            while(q1.next()){
                int cid = q1.value(2).toInt();
                QString dco = q1.value(3).toString();
                QString dci = q1.value(4).toString();
                QSqlQuery q2;
                QString selectEvent = "SELECT * FROM eventList WHERE tripid="+QString::number(id)+\
                        " AND dayid="+QString::number(did)+" AND cityid = "+QString::number(cid);
                q2.prepare(selectEvent);
                if(!q2.exec()){
                    emit this->databaseErrorSig("Cannot Get Event");
                    return tripList;
                }
                QList<EventItem*> eventList;
                while(q2.next()){
                    int eid = q2.value(3).toInt();
                    QString dt = q2.value(4).toString();
                    QString dn = q2.value(5).toString();
                    QString cur = q2.value(6).toString();
                    double dc = q2.value(7).toDouble();
                    QString tt = q2.value(8).toString();
                    QString tn = q2.value(9).toString();
                    QString tcur = q2.value(10).toString();
                    double tc = q2.value(11).toDouble();
                    EventItem* event = new EventItem(eid,dt,dn,cur,tcur,tt,tn,dc,tc);
                    eventList<<event;
                }
                CityItem* city = new CityItem(cid,dco,dci,eventList);
                cityList<<city;
            }
            DayItem* day = new DayItem(did,cityList);
            dayList<<day;
        }
        TripItem* trip = new TripItem(id,name,country,city,date,dayList,num,color,remark);
        tripList<<trip;
    }
    TDataBase::database.close();
    return tripList;
}

bool TDataBase::addNewTrip(int id, QString name, QString country, QString city, QString date, QString themeColor){
    if(!openDatabase()) {
        TDataBase::database.close();
        return false;
    }
    QString insert = "INSERT INTO tripList VALUES("+QString::number(id)+",'"+name+\
            "','"+country+"','"+city+"','"+date+"','',0,'"+themeColor+"')";
    QSqlQuery query;
    query.prepare(insert);
    if(!query.exec()) {
        TDataBase::database.close();
        emit this->databaseErrorSig("Cannot Add Trip");
        return false;
    }
    TDataBase::database.close();
    return true;
}

bool TDataBase::updateTripInfo(int id, QString name, QString country, QString city, \
                               QString date, QString themeColor){
    if(!openDatabase()) {
        TDataBase::database.close();
        return false;
    }
    QString update = "UPDATE tripList SET name='"+name+"',country='"+country+"',city='"+city+"',date='"+
            date+"',themeColor='"+themeColor+"' WHERE tripid="+QString::number(id)+";";
    QSqlQuery query;
    query.prepare(update);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Update Trip Info");
        TDataBase::database.close();
        return false;
    }
    TDataBase::database.close();
    return true;
}

bool TDataBase::addNewEvent(int tid, int did, int cid, int eid, QString et, QString en, QString ecur, \
                            double ecost, QString tt, QString tn, QString tcur, double tcost){
    if(!openDatabase()) {
        TDataBase::database.close();
        return false;
    }
    QString add = "INSERT INTO eventList VALUES("+QString::number(tid)+","+QString::number(did)+","+\
            QString::number(cid)+","+QString::number(eid)+",'"+et+"','"+en+"','"+ecur+"',"+QString::number(ecost)+",'"+\
            tt+"','"+tn+"','"+tcur+"',"+QString::number(tcost)+");";
    QSqlQuery query;
    query.prepare(add);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Add Event - Database");
        TDataBase::database.close();
        return false;
    }
    TDataBase::database.close();
    return true;
}

bool TDataBase::updateEvent(int tid, int did, int cid, int eid, QString et, QString en, QString ecur, \
                            double ecost, QString tt, QString tn, QString tcur, double tcost){
    if(!openDatabase()) {
        TDataBase::database.close();
        return false;
    }
    QString update = "UPDATE eventList SET eventType='"+et+"',eventName='"+en+\
            "',currency='"+ecur+"',cost="+QString::number(ecost)+",transportType='"+tt+"',transportName='"+tn+\
            "',tcurrency='"+tcur+"',transportCost="+QString::number(tcost)+" WHERE tripid="+QString::number(tid)+\
            " AND dayid="+QString::number(did)+" AND cityid="+QString::number(cid)+" AND eventid="+QString::number(eid)+";";
    QSqlQuery query;
    query.prepare(update);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Update Event - Database");
        TDataBase::database.close();
        return false;
    }
    TDataBase::database.close();
    return true;
}

bool TDataBase::addNewCityItem(int tid, int did, int cid, QString country, QString city){
    if(!openDatabase()) {
        TDataBase::database.close();
        return false;
    }
    QString add = "INSERT INTO dayCityList VALUES("+QString::number(tid)+","+QString::number(did)+","+\
            QString::number(cid)+",'"+country+"','"+city+"');";
    QSqlQuery query;
    query.prepare(add);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Add City Item - Database");
        TDataBase::database.close();
        return false;
    }
    TDataBase::database.close();
    return true;
}

bool TDataBase::updateCityItem(int tid, int did, int cid, QString country, QString city){
    if(!openDatabase()) {
        TDataBase::database.close();
        return false;
    }
    QString update = "UPDATE dayCityList SET country='"+country+"',city='"+city+\
            "' WHERE tripid="+QString::number(tid)+" AND dayid="+QString::number(did)+" AND cityid="+\
            QString::number(cid)+";";
    QSqlQuery query;
    query.prepare(update);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Update City - Database");
        TDataBase::database.close();
        return false;
    }
    TDataBase::database.close();
    return true;
}

bool TDataBase::addNewDay(int tid, int daynum){
    if(!openDatabase()) {
        TDataBase::database.close();
        return false;
    }
    QString update = "UPDATE tripList SET daynum="+QString::number(daynum)+" WHERE tripid="+QString::number(tid)+";";
    QSqlQuery query;
    query.prepare(update);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Add Day - Database");
        TDataBase::database.close();
        return false;
    }
    TDataBase::database.close();
    return true;
}

bool TDataBase::deleteEvent(int tid, int did, int cid, int eid){
    if(!openDatabase()) {
        TDataBase::database.close();
        return false;
    }
    QString deletestr = "DELETE FROM eventList WHERE tripid="+QString::number(tid)+" AND dayid="+\
            QString::number(did)+" AND cityid="+QString::number(cid)+" AND eventid="+QString::number(eid)+";";
    QSqlQuery query;
    query.prepare(deletestr);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Delete Event - Database");
        TDataBase::database.close();
        return false;
    }
    TDataBase::database.close();
    return true;
}

bool TDataBase::deleteCityItem(int tid, int did, int cid){
    if(!openDatabase()) {
        TDataBase::database.close();
        return false;
    }
    QString deletestr = "DELETE FROM dayCityList WHERE tripid="+QString::number(tid)+" AND dayid="+\
            QString::number(did)+" AND cityid="+QString::number(cid)+";";
    QSqlQuery query;
    query.prepare(deletestr);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Delete City - Database");
        TDataBase::database.close();
        return false;
    }
    deletestr = "DELETE FROM eventList WHERE tripid="+QString::number(tid)+" AND dayid="+\
                QString::number(did)+" AND cityid="+QString::number(cid)+";";
    query.prepare(deletestr);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Delete Events - Database");
        TDataBase::database.close();
        return false;
    }
    TDataBase::database.close();
    return true;
}

bool TDataBase::deleteDay(int tid, int did, int oldDayNum){
    if(!openDatabase()) {
        TDataBase::database.close();
        return false;
    }
    QString update = "UPDATE tripList set daynum="+QString::number(oldDayNum-1)+\
            " WHERE tripid="+QString::number(tid)+";";
    QSqlQuery query;
    query.prepare(update);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Change Day Number - Database");
        TDataBase::database.close();
        return false;
    }
    QString deletestr = "DELETE FROM dayCityList WHERE tripid="+QString::number(tid)+" AND dayid="+\
            QString::number(did)+";";

    query.prepare(deletestr);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Delete City - Database");
        TDataBase::database.close();
        return false;
    }
    deletestr = "DELETE FROM eventList WHERE tripid="+QString::number(tid)+" AND dayid="+\
                QString::number(did)+";";
    query.prepare(deletestr);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Delete Events - Database");
        TDataBase::database.close();
        return false;
    }
    TDataBase::database.close();
    return true;
}


bool TDataBase::deleteTrip(int tid){
    if(!openDatabase()) {
        TDataBase::database.close();
        return false;
    }
    QString deletestr = "DELETE FROM tripList WHERE tripid="+QString::number(tid)+";";
    QSqlQuery query;
    query.prepare(deletestr);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Delete Trip - Database");
        TDataBase::database.close();
        return false;
    }
    deletestr = "DELETE FROM dayCityList WHERE tripid="+QString::number(tid)+";";
    query.prepare(deletestr);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Delete Cities - Database");
        TDataBase::database.close();
        return false;
    }
    deletestr = "DELETE FROM eventList WHERE tripid="+QString::number(tid)+";";
    query.prepare(deletestr);
    if(!query.exec()){
        emit this->databaseErrorSig("Cannot Delete Events - Database");
        TDataBase::database.close();
        return false;
    }
    TDataBase::database.close();
    return true;
}
