#include "travellermodel.h"

TravellerModel::TravellerModel()
{
    this->database = new TDataBase();
    QString etstr = "Airport,Train Station,Bus Station,Attrcation,Port,Restuarant,Bar,Other";
    eventTypeList = etstr.split(",");
    QString ttstr = "Plane,Train,Loacl Traffic,Boat,Taxi,Other";
    transportTypeList = ttstr.split(",");
}

void TravellerModel::getCountryListSlot()
{
    if(this->countryList.length()==0)
    {
        QString r = this->database->getCountryList();
        if(r!=StaticData::NULL_RESULT){
            this->countryList = r.split("\x03",QString::SkipEmptyParts);
        }
    }
    emit this->returnCountryList(this->countryList);
}

void TravellerModel::getCityListSlot(QString country,int id)
{
    QStringList list;
    if(this->cityList.contains(country))
        list = this->cityList[country];
    else
    {
        QString r = this->database->getCityList(country);
        if(r!=StaticData::NULL_RESULT){
            list = r.split("\x03",QString::SkipEmptyParts);
            this->cityList.insert(country,list);
            emit this->returnCityList(list,id);
        }else{
            emit this->dataErrorSig("Get City List Error");
        }
    }
    emit this->returnCityList(list,id);
}

void TravellerModel::addCountrySlot(QString country){
    // already in the country list
    if(this->countryList.contains(country)){
        emit this->dataErrorSig("Country Already Exists");
        return;
    }
    int id = this->countryList.length();
    QString r = this->database->addCountry(country,id);
    if(r != StaticData::NULL_RESULT){
        QStringList list = r.split("\x03",QString::SkipEmptyParts);
        emit this->returnNewlyAddedCountryList(list);
        this->countryList = list;
    }else{
        emit this->dataErrorSig("Add Country Error");
    }
}

void TravellerModel::addCitySlot(QString country, QString city, int id){
    // already in the country list
    if(this->cityList[country].contains(city)){
        emit this->dataErrorSig("City Already Exists");
        return;
    }
    QString r = this->database->addCity(country,city);
    if(r!=StaticData::NULL_RESULT){
        QStringList list = r.split("\x03",QString::SkipEmptyParts);
        emit this->returnNewlyAddedCityList(list,id);
        this->cityList[country] = list;
    }else{
        emit this->dataErrorSig("Add City Failed");
    }
}

void TravellerModel::getTripByIdSlot(int id,int type){
    if (this->tripList.length()==0)
    {
        this->tripList = this->database->getTheTripById(id);
    }
    if(type ==0){
        emit this->returnTripList(this->tripList);
    }else{
        this->selectedTripId = id;
        emit this->returnTrip(this->getTripById(id));
    }
}

void TravellerModel::addNewTrip(QString name,QString country, QString city, QDate date,QString themeColor){
    int id = this->getFirstAvialableTripId();
    if(id==-1) {
        emit this->dataErrorSig("Cannot Get Avaliable Id");
        return;
    }
    bool result = this->database->addNewTrip(id,name,country,city,date.toString(StaticData::DATE_STORATION_FORMAT),themeColor);
    if(result) {
        QList<DayItem*> list;
        TripItem* t = new TripItem(id,name,country,city,date,list,0,themeColor);
        this->tripList<<t;
        emit this->returnNewlyAddedTrip(t);
    }
    else emit this->dataErrorSig("Add Trip Error In Database");
}

void TravellerModel::updateTripInfo(int id, QString name, QString country, QString city, \
                                    QDate date, QString themeColor) {
    TripItem* t = this->getTripById(id);
    if(t == nullptr){
        emit this->dataErrorSig("No Such Trip ID");
        return;
    }
    if(this->database->updateTripInfo(id,name,country,city,\
                                      date.toString(StaticData::DATE_STORATION_FORMAT),themeColor)){
        t->name = name;
        t->homeCountry = country;
        t->homeCity = city;
        t->startDate = date;
        t->themeColor = themeColor;
        emit this->returnUpdatedTrip(t);
    }else{
        emit this->dataErrorSig("Update Database Failed");
        return;
    }
}

void TravellerModel::addNewEvent(QString et, QString en, QString ecur, double ecost, \
                                 QString tt, QString tn, QString tcur, double tcost){
    int tid = selectedTripId;
    int did = selectedDayId;
    int cid = selectedCityId;
    int eid = this->getFirstAvialableEventId();
    if(eid == -1){
        emit this->dataErrorSig("Cannot Find Proper Event Id");
        return;
    }
    if(!this->database->addNewEvent(tid,did,cid,eid,et,en,ecur,ecost,tt,tn,tcur,tcost)){
        emit this->dataErrorSig("Cannot Add Event - model");
    }else{
        EventItem* e = new EventItem(eid,et,en,ecur,tcur,tt,tn,ecost,tcost);
        emit this->returnNewlyAddedEvent(e);
        *(this->getEventList(selectedTripId,selectedDayId,selectedCityId))<<e;
    }
}

void TravellerModel::updateEventInfoSlot(QString et, QString en, QString ecur, double ecost, \
                                         QString tt, QString tn, QString tcur, double tcost){
    int tid = selectedTripId;
    int did = selectedDayId;
    int cid = selectedCityId;
    int eid = selectedEventId;
    if(!this->database->updateEvent(tid,did,cid,eid,et,en,ecur,ecost,tt,tn,tcur,tcost)){
        emit this->dataErrorSig("Cannot Update Event - model");
    }else{
        EventItem* e = this->getEventByIds(tid,did,cid,eid);
        e->updateValues(et,en,ecur,tcur,tt,tn,ecost,tcost);
        emit this->returnUpdatedEvent(e);
    }
}

void TravellerModel::addNewCityItemSlot(QString country, QString city){
    int tid = selectedTripId;
    int did = selectedDayId;
    int cid = getFirstAvialableCityId();
    if(!database->addNewCityItem(tid,did,cid,country,city))
        emit this->dataErrorSig("Cannot Add City Item - model");
    else{
        QList<EventItem*> elist;
        CityItem* c = new CityItem(cid,country,city,elist);
        *(this->getCityList(tid,did))<< c;
        emit this->returnNewlyAddedCityItem(c);
    }
}

void TravellerModel::updateCityItemInfoSlot(QString country, QString city){
    int tid = selectedTripId;
    int did = selectedDayId;
    int cid = selectedCityId;
    if(!database->updateCityItem(tid,did,cid,country,city))
        emit this->dataErrorSig("Cannot Update City Item - model");
    else{
        CityItem* c = this->getCityItemByIds(tid,did,cid);
        c->country = country;
        c->city = city;
        emit this->returnUpdatedCityItemSig(c);
    }
}

void TravellerModel::addNewDaySlot(){
    int tid = selectedTripId;
    int did = getFirstAvialableDayId();
    // add a new day increase the day number
    TripItem* t = getTripById(tid);
    int daynum = t->dayNum + 1;
    if(!database->addNewDay(tid,daynum))
        emit this->dataErrorSig("Cannot Add Day - model");
    else{
        t->dayNum ++;
        QList<CityItem*> cl;
        DayItem* d = new DayItem(did,cl);
        t->dayList << d;
        emit this->returnNewlyAddedDay(d);
    }
}

void TravellerModel::deleteEventSlot(){
    int tid = selectedTripId;
    int did = selectedDayId;
    int cid = selectedCityId;
    int eid = selectedEventId;
    if(!database->deleteEvent(tid,did,cid,eid))
        emit this->dataErrorSig("Cannot Delete Event - model");
    else{
        emit this->returnDeletedEvent();
    }
}

void TravellerModel::deleteCitySlot(){
    int tid = selectedTripId;
    int did = selectedDayId;
    int cid = selectedCityId;
    if(!database->deleteCityItem(tid,did,cid))
        emit this->dataErrorSig("Cannot Delete City - model");
    else{
        emit this->returnDeletedCity();
    }
}

void TravellerModel::deleteDaySlot(){
    int tid = selectedTripId;
    int did = selectedDayId;
    if(!database->deleteDay(tid,did,getTripById(tid)->dayNum))
        emit this->dataErrorSig("Cannot Delete Day - model");
    else{
        emit this->returnDeletedDay();
    }
}

void TravellerModel::deleteTripSlot(){
    int tid = selectedTripId;
    if(!database->deleteTrip(tid))
        emit this->dataErrorSig("Cannot Delte Trip - model");
    else emit this->returnDeletedTrip();
}

void TravellerModel::removeTheEventFromTheList(){
    int tid = selectedTripId;
    int did = selectedDayId;
    int cid = selectedCityId;
    int eid = selectedEventId;
    EventItem* e = getEventByIds(tid,did,cid,eid);
    getEventList(tid,did,cid)->removeOne(e);
    delete e;
    e = nullptr;
}

void TravellerModel::removeTheCityFromTheList(){
    int tid = selectedTripId;
    int did = selectedDayId;
    int cid = selectedCityId;
    CityItem* c = getCityItemByIds(tid,did,cid);
    getCityList(tid,did)->removeOne(c);
    delete c;
    c = nullptr;
}

void TravellerModel::removeTheDayFromTheList(){
    int tid = selectedTripId;
    int did = selectedDayId;
    DayItem* d = getDayByIds(tid,did);
    getDayList(tid)->removeOne(d);
    delete d;
    d = nullptr;
    getTripById(tid)->dayNum = getDayList(tid)->length();
}

void TravellerModel::removeTheTripFromTheList(){
    int tid = selectedTripId;
    TripItem* t = getTripById(tid);
    tripList.removeOne(t);
    delete t;
    t = nullptr;
}

QList<TripItem*> TravellerModel::getTripList(){
    return tripList;
}

QList<int> TravellerModel::getSelectedIndexInList(){
    QList<int> list;
    QListIterator<TripItem*> titr(this->tripList);
    int ti = 0;
    while(titr.hasNext()){
        TripItem* t = titr.next();
        if(t->id == selectedTripId){
            list << ti;
            QListIterator<DayItem*> ditr(t->dayList);
            int di = 0;
            while(ditr.hasNext()){
                DayItem* d = ditr.next();
                if(d->id == selectedDayId){
                    list << di;
                    QListIterator<CityItem*> citr(d->cityList);
                    int ci = 0;
                    while(citr.hasNext()){
                        CityItem* c = citr.next();
                        if(c->id == selectedCityId){
                            list << ci;
                            QListIterator<EventItem*> eitr(c->eventList);
                            int ei = 0;
                            while(eitr.hasNext()){
                                EventItem* d = eitr.next();
                                if(d->id == selectedEventId){
                                    list << ei;
                                    return list;
                                }else ei++;
                            }
                        }else ci++;
                    }
                }else di++;
            }
        }else ti++;
    }
    return list;
}

TripItem* TravellerModel::getTripById(int id){
    TripItem* r;
    QListIterator<TripItem*> itr(this->tripList);
    while(itr.hasNext()){
        r = itr.next();
        if(r->id==id) return r;
    }
    return nullptr;
}

TripItem* TravellerModel::getCurrentTripItem(){
    return getTripById(selectedTripId);
}

DayItem* TravellerModel::getDayByIds(int tid, int did){
    TripItem* t = getTripById(tid);
    if(t == nullptr) return nullptr;
    QListIterator<DayItem*> itr(t->dayList);
    while(itr.hasNext()){
        DayItem* d = itr.next();
        if(d->id == did) return d;
    }
    return nullptr;
}

CityItem* TravellerModel::getCityItemByIds(int tid, int did, int cid){
    DayItem* d = getDayByIds(tid,did);
    if(d == nullptr) return nullptr;
    QListIterator<CityItem*> itr(d->cityList);
    while(itr.hasNext()){
        CityItem* c = itr.next();
        if(c->id == cid) return c;
    }
    return nullptr;
}

EventItem* TravellerModel::getEventByIds(int tid, int did, int cid, int eid){
    CityItem* c = getCityItemByIds(tid,did,cid);
    if(c == nullptr) return nullptr;
    QListIterator<EventItem*> itr(c->eventList);
    while(itr.hasNext()){
        EventItem* e = itr.next();
        if(e->id == eid) return e;
    }
    return nullptr;
}

int TravellerModel::getFirstAvialableTripId(){
    int id = 0;
    QListIterator<TripItem*> itr(this->tripList);
    while(itr.hasNext()){
        TripItem* t = itr.next();
        if(t->id != id){
            return id;
        }
        id++;
    }
    return id;
}

QList<DayItem*>* TravellerModel::getDayList(int tid){
    QList<DayItem*>* list = nullptr;
    TripItem* t = this->getTripById(tid);
    if(t == nullptr){
        emit this->dataErrorSig("No Such Trip");
        return list;
    }
    list = & t->dayList;
    return list;
}

QList<CityItem*>* TravellerModel::getCityList(int tid, int did){
    QList<DayItem*>* dl = getDayList(tid);
    if(dl == nullptr) return nullptr;
    QListIterator<DayItem*> itr(*dl);
    while(itr.hasNext()){
        DayItem* d = itr.next();
        if(d->id == did) return &d->cityList;
    }
    return nullptr;
}

QList<EventItem*>* TravellerModel::getEventList(int tid, int did, int cid){
    QList<CityItem*>* cl = getCityList(tid,did);
    if(cl == nullptr) return nullptr;
    QListIterator<CityItem*> itr(*cl);
    while(itr.hasNext()){
        CityItem* c = itr.next();
        if(c->id == cid) return &c->eventList;
    }
    return nullptr;
}

int TravellerModel::getFirstAvialableEventId(){
    QList<EventItem*> list = *(this->getEventList(selectedTripId,selectedDayId,selectedCityId));
    QListIterator<EventItem*> itr(list);
    int eid = 0;
    while(itr.hasNext()){
        EventItem* tmp = itr.next();
        if(tmp->id != eid) break;
        else eid++;
    }
    return eid;
}

int TravellerModel::getFirstAvialableCityId(){
    QList<CityItem*> list = *(this->getCityList(selectedTripId,selectedDayId));
    QListIterator<CityItem*> itr(list);
    int cid = 0;
    while(itr.hasNext()){
        CityItem* tmp = itr.next();
        if(tmp->id != cid) break;
        else cid++;
    }
    return cid;
}

int TravellerModel::getFirstAvialableDayId(){
    QList<DayItem*> list = *(this->getDayList(selectedTripId));
    QListIterator<DayItem*> itr(list);
    int did = 0;
    while(itr.hasNext()){
        DayItem* tmp = itr.next();
        if(tmp->id != did) break;
        else did++;
    }
    return did;
}

TravellerModel::~TravellerModel(){
    delete this->database;
    this->database = nullptr;
}
