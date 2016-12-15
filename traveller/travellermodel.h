#ifndef TRAVELLERMODEL_H
#define TRAVELLERMODEL_H

#include <QObject>
#include <QStringList>
#include <QList>
#include <QMessageBox>
#include <QHash>
#include <QListIterator>
#include <QDebug>
#include "tdatabase.h"
#include "staticdata.h"
#include "tripitem.h"

class TravellerModel:public QObject
{
    Q_OBJECT

public:
    TravellerModel();
    ~TravellerModel();
    TDataBase* database;
    int selectedTripId;
    int selectedDayId;
    int selectedCityId;
    int selectedEventId;
    QList<int> getSelectedIndexInList();
    TripItem* getTripById(int id);
    DayItem* getDayByIds(int tid,int did);
    CityItem* getCityItemByIds(int tid,int did,int cid);
    EventItem* getEventByIds(int tid,int did,int cid,int eid);
    TripItem* getCurrentTripItem();
    QList<TripItem*> getTripList();
private:
    QStringList eventTypeList;
    QStringList transportTypeList;
    QStringList countryList;
    QHash<QString,QStringList> cityList;
    QList<TripItem*> tripList;
    QList<EventItem*>* getEventList(int tid,int did,int cid);
    QList<CityItem*>* getCityList(int tid,int did);
    QList<DayItem*>* getDayList(int tid);
    int getFirstAvialableTripId();
    int getFirstAvialableDayId();
    int getFirstAvialableCityId();
    int getFirstAvialableEventId();

signals:
    void returnCountryList(QStringList list);
    void returnCityList(QStringList list,int id);
    void returnNewlyAddedCountryList(QStringList list);
    void returnNewlyAddedCityList(QStringList list,int id);
    void returnTripList(QList<TripItem*> list);
    void returnTrip(TripItem*);
    void dataErrorSig(QString);
    void returnNewlyAddedTrip(TripItem*);
    void returnUpdatedTrip(TripItem*);
    void returnNewlyAddedEvent(EventItem*);
    void returnUpdatedEvent(EventItem*);
    void returnNewlyAddedCityItem(CityItem*);
    void returnUpdatedCityItemSig(CityItem*);
    void returnNewlyAddedDay(DayItem*);
    void returnDeletedEvent();
    void returnDeletedCity();
    void returnDeletedDay();
    void returnDeletedTrip();

public slots:
    void getCountryListSlot();
    void getCityListSlot(QString country,int id);
    void addCountrySlot(QString country);
    void addCitySlot(QString country,QString city,int id);
    void getTripByIdSlot(int id,int type);
    void addNewTrip(QString name,QString country,QString city,QDate date,QString themeColor);
    void updateTripInfo(int id,QString name,QString country,QString city,QDate date,QString themeColor);
    void addNewEvent(QString et,QString en,QString ecur,double ecost,\
                     QString tt,QString tn,QString tcur,double tcost);
    void updateEventInfoSlot(QString et,QString en,QString ecur,double ecost,\
                             QString tt,QString tn,QString tcur,double tcost);
    void addNewCityItemSlot(QString country,QString city);
    void updateCityItemInfoSlot(QString country,QString city);
    void addNewDaySlot();
    void deleteEventSlot();
    void deleteCitySlot();
    void deleteDaySlot();
    void deleteTripSlot();
    void removeTheEventFromTheList();
    void removeTheCityFromTheList();
    void removeTheDayFromTheList();
    void removeTheTripFromTheList();
};

#endif // TRAVELLERMODEL_H
