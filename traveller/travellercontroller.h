#ifndef TRAVELLERCONTROLLER_H
#define TRAVELLERCONTROLLER_H

#include <QObject>
#include <QList>
#include <QMessageBox>
#include <QGridLayout>
#include <QListIterator>
#include <QPoint>
#include "travellermodel.h"
#include "travellermainwindow.h"
#include "tcombowithaddfield.h"
#include "tripitem.h"
#include "dayitem.h"
#include "cityitem.h"
#include "eventitem.h"
#include "welcomeframe.h"
#include "tripdetailframe.h"
#include "dayitemframe.h"
#include "cityitemframe.h"
#include "eventitemframe.h"
#include "addtripbuttonframe.h"
#include "addnewtripwindow.h"
#include "tripitemmenu.h"
#include "addeventorcitybutton.h"
#include "addneweventwindow.h"
#include "addnewcitywindow.h"

class TravellerController:public QObject
{
    Q_OBJECT

public:
    TravellerController(TravellerModel* m,TravellerMainWindow* v);
    ~TravellerController();
    void initialization();

private:
    TravellerModel* model;
    TravellerMainWindow* view;
    QList<TComboWithAddField*> comboGroupList;
    QList<TripFrame*> tripFrameList;
    WelcomeFrame* welcome = nullptr;
    TripDetailFrame* detail = nullptr;
    AddNewTripWindow* addNewWindow = nullptr;
    AddNewEventWindow* addEventWindow = nullptr;
    AddNewCityWindow* addCityWindow = nullptr;
    TripItemMenu* tiMenu = nullptr;

    void registerTripFrame(TripFrame* f);
    void removeTComboboxGroup(TComboWithAddField* combo);
    void setEventFrameValues(EventItemFrame* ef,EventItem* e);
    void setCityFrameValues(CityItemFrame* cf,CityItem* c);
    void refreshDayFrameDisplay();
    int getSpecifiedComboGroup(int id);
    int getAvaliableComboGroupId();
    bool isCountryOrCityNameValid(QString name);
    bool isTripInformationValid();
    TripFrame* getTripFrameById(int id);
    DayItemFrame* createDayItemFrameByData(DayItem* dtmp,QString tcolor,int tid);
    CityItemFrame* createCityFrameByData(CityItem* ctmp,int tid,int did);
    EventItemFrame* createEventFrameByData(EventItem* etmp,int tid,int did,int cid);

signals:
    void getCityListSig(QString,int);
    void addCountrySig(QString);
    void addCitySig(QString,QString,int);
    void getTripByIdSig(int id, int type);
    void addNewTripWindowClosePermittedSig();
    void addNewEventWindowClosePermittedSig();
    void addNewCityWindowClosePermittedSig();

public slots:
    void setCountryListSlot(QStringList list);
    void setCityListSlot(QStringList list,int id);
    void setNewlyAddedCountryListSlot(QStringList list);
    void setNewlyAddedCityListSlot(QStringList list,int id);
    void addCountrySlot(QString country);
    void addCitySlot(QString city,int id);
    void registerTComboWithAddSlot(TComboWithAddField* combo);
    void setTripList(QList<TripItem*> list);
    void tripFrameClickedSlot(int id);
    void returnBackToWelcomeSlot();
    void setTripSlot(TripItem* t);
    void addTripFrameClickedSlot();
    void addNewTripWindowClosedSlot(int type,int windowType);
    void dataErrorPopupSlot(QString errorMessage);
    void databaseErrorPopupSlot(QString errorMessage);
    void addNewTripFrameSlot(TripItem* trip);
    void tripTitleFrameDoubleClickedSlot();
    void updateTripInfoSlot(TripItem* trip);
    void tripRightClickedSlot(int id,QPoint pos);
    void tripMenuEditClickedSlot(bool state);
    void tripMenuDeleteClickedSlot(bool state);
    void addEventButtonClickedSlot(int tid,int did,int cid);
    void addCityButtonClickedSlot(int tid,int did);
    void addDayButtonClickedSlot(int tid);
    void addNewEventWindowClosedSlot(int type,int windowType);
    void addNewEventSlot(EventItem* event);
    void eventFrameDoubleClickedSlot(int did,int cid,int eid);
    void updateEventInfoSlot(EventItem* event);
    void addNewCityWindowClosedSlot(int type,int windowType);
    void addNewlyAddedCityItemSlot(CityItem* city);
    void cityItemFrameDoubleClickedSlot(int did,int cid);
    void updateCityItemInfoSlot(CityItem* city);
    void addNewlyAddedDaySlot(DayItem* day);
    void deleteEventButtonClicked(int did,int cid,int eid);
    void deleteEventUpdateSlot();
    void deleteCityButtonClicked(int did,int cid);
    void deleteCityUpdateSlot();
    void deleteDayButtonClicked(int did);
    void deleteDayUpdateSlot();
    void deleteTripButtonClicked();
    void deleteTripUpdateSlot();
};

#endif // TRAVELLERCONTROLLER_H
