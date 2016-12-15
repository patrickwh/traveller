#ifndef TDATABASE_H
#define TDATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QList>
#include <QDate>
#include "staticdata.h"
#include "tripitem.h"
#include "dayitem.h"
#include "cityitem.h"
#include "eventitem.h"

class TDataBase: public QObject
{
    Q_OBJECT
public:
    TDataBase();
    static QSqlDatabase database;
    void initDatabase();
    QString getCountryList();
    QString getCityList(QString country);
    bool openDatabase();
    QString addCountry(QString country,int id);
    QString addCity(QString country,QString city);
    QList<TripItem*> getTheTripById(int id);
    bool addNewTrip(int id,QString name,QString country,QString city,QString date,QString themeColor);
    bool updateTripInfo(int id,QString name,QString country,QString city,QString date,QString themeColor);
    bool addNewEvent(int tid,int did,int cid,int eid,QString et, QString en, QString ecur, double ecost, \
                     QString tt, QString tn, QString tcur, double tcost);
    bool updateEvent(int tid,int did,int cid,int eid,QString et, QString en, QString ecur, double ecost, \
                     QString tt, QString tn, QString tcur, double tcost);
    bool addNewCityItem(int tid,int did,int cid,QString country,QString city);
    bool updateCityItem(int tid,int did,int cid,QString country,QString city);
    bool addNewDay(int tid,int daynum);
    bool deleteEvent(int tid,int did,int cid,int eid);
    bool deleteCityItem(int tid,int did,int cid);
    bool deleteDay(int tid,int did,int oldDayNum);
    bool deleteTrip(int tid);
signals:
    void databaseErrorSig(QString);
};

#endif // TDATABASE_H
