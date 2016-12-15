#include "travellercontroller.h"

TravellerController::TravellerController(TravellerModel* m,TravellerMainWindow* v):model{m},view(v)
{
}

void TravellerController::initialization()
{
    // get country list signal from main view, to model get
    connect(this->view,SIGNAL(getCountryListSig()),this->model,SLOT(getCountryListSlot()));
    // return country list from model, to controller set
    connect(this->model,SIGNAL(returnCountryList(QStringList)),this,SLOT(setCountryListSlot(QStringList)));
    // return newly added country list signal from model, to controller set
    connect(this->model,SIGNAL(returnNewlyAddedCountryList(QStringList)),this,SLOT(setNewlyAddedCountryListSlot(QStringList)));
    // get city list from main view, to model get
    connect(this->view,SIGNAL(getCityListSig(QString,int)),this->model,SLOT(getCityListSlot(QString,int)));
    // return city list from model, to controller set
    connect(this->model,SIGNAL(returnCityList(QStringList,int)),this,SLOT(setCityListSlot(QStringList,int)));
    // return newly added city list from model, to controller set
    connect(this->model,SIGNAL(returnNewlyAddedCityList(QStringList,int)),this,SLOT(setNewlyAddedCityListSlot(QStringList,int)));
    // get city list signal from controller, to model get
    connect(this,SIGNAL(getCityListSig(QString,int)),this->model,SLOT(getCityListSlot(QString,int)));
    // add country signal from controller, to model add
    connect(this,SIGNAL(addCountrySig(QString)),this->model,SLOT(addCountrySlot(QString)));
    // register combo group signal, to controller register
    connect(this->view,SIGNAL(registerComboGroupSig(TComboWithAddField*)),\
            this,SLOT(registerTComboWithAddSlot(TComboWithAddField*)));
    // get city signal from controller, to model get
    connect(this,SIGNAL(addCitySig(QString,QString,int)),this->model,SLOT(addCitySlot(QString,QString,int)));
    // get trip list signal from controller, to model get
    connect(this,SIGNAL(getTripByIdSig(int,int)),this->model,SLOT(getTripByIdSlot(int,int)));
    // return trip list signal from model, to controller set
    connect(this->model,SIGNAL(returnTripList(QList<TripItem*>)),this,SLOT(setTripList(QList<TripItem*>)));
    // return trip item siganel from model, to comtroller uodate view
    connect(this->model,SIGNAL(returnTrip(TripItem*)),this,SLOT(setTripSlot(TripItem*)));
    // error signal from model, to controller error popup
    connect(this->model,SIGNAL(dataErrorSig(QString)),this,SLOT(dataErrorPopupSlot(QString)));
    // database error signal from database, to controller popup
    connect(this->model->database,SIGNAL(databaseErrorSig(QString)),this,SLOT(databaseErrorPopupSlot(QString)));
    // return newly added signal from model, to controller add new trip frame slot
    connect(this->model,SIGNAL(returnNewlyAddedTrip(TripItem*)),this,SLOT(addNewTripFrameSlot(TripItem*)));
    // connect return trip info updated signal from model, to controller update
    connect(this->model,SIGNAL(returnUpdatedTrip(TripItem*)),this,SLOT(updateTripInfoSlot(TripItem*)));
    // connect return newly added event signal from model , to controller add event handller
    connect(this->model,SIGNAL(returnNewlyAddedEvent(EventItem*)),this,SLOT(addNewEventSlot(EventItem*)));
    // connect return updated event signal from model , to controller update event slot
    connect(this->model,SIGNAL(returnUpdatedEvent(EventItem*)),this,SLOT(updateEventInfoSlot(EventItem*)));
    // connect return newly added city item signal from model, to controller add
    connect(this->model,SIGNAL(returnNewlyAddedCityItem(CityItem*)),this,SLOT(addNewlyAddedCityItemSlot(CityItem*)));
    // connect return updated city item signal from model, to controller handeller
    connect(this->model,SIGNAL(returnUpdatedCityItemSig(CityItem*)),this,SLOT(updateCityItemInfoSlot(CityItem*)));
    // connect return newly added day signal from model, to controller handeller
    connect(this->model,SIGNAL(returnNewlyAddedDay(DayItem*)),this,SLOT(addNewlyAddedDaySlot(DayItem*)));
    // connect return deleted event signal from model, to controller handleller
    connect(this->model,SIGNAL(returnDeletedEvent()),this,SLOT(deleteEventUpdateSlot()));
    // connect return deleted city signal from model ,to controller handeller
    connect(this->model,SIGNAL(returnDeletedCity()),this,SLOT(deleteCityUpdateSlot()));
    // connect return deleted day signal from model ,to controller handeller
    connect(this->model,SIGNAL(returnDeletedDay()),this,SLOT(deleteDayUpdateSlot()));
    // connect return deleted day signal from model ,to controller handeller
    connect(this->model,SIGNAL(returnDeletedTrip()),this,SLOT(deleteTripUpdateSlot()));
    // get the trip list and update the view, -1 means get all the trips
    // type 0 means return to controller to add all trip
    emit this->getTripByIdSig(-1,0);
}

int TravellerController::getAvaliableComboGroupId(){
    int index = 0;
    QListIterator <TComboWithAddField*> itr(this->comboGroupList);
    while(itr.hasNext()){
        TComboWithAddField* t = itr.next();
        if(t->id == index){
            // index alredy used
            index ++;
        }else break;
    }
    return index;
}

TripFrame* TravellerController::getTripFrameById(int id){
    QGridLayout* lay = this->view->welconf->layout;
    int num = lay->count()-this->view->welconf->m-1;
    for(int i=0;i<num;i++){
        TripFrame* t = (TripFrame*) lay->itemAt(i)->widget();
        if(t->id == id){
            return t;
        }
    }
    return nullptr;
}

void TravellerController::setEventFrameValues(EventItemFrame *ef, EventItem *e){
    ef->event->setText(e->destType+":"+e->destName+" "+QString::number(e->destCost)+" "+e->currency);
    ef->transport->setText(e->transportType+":"+e->transportName+" "+QString::number(e->transportCost)+\
                           " "+e->tcurrency);
}

void TravellerController::setCityFrameValues(CityItemFrame *cf, CityItem *c){
    cf->title->cityName->setText(c->country+" "+c->city);
}

void TravellerController::registerTComboWithAddSlot(TComboWithAddField* combo){
    // add country signal from add button, to combo group to send add signal with
    // information in eidt field to controller
    // get avaliable index and date the ids in combobox group
    // QMessageBox::critical(0, QObject::tr("signal"),"id"+QString::number(combo->id));
    int id = this->getAvaliableComboGroupId();
    combo->id = id; // update the id
    this->comboGroupList<<combo;
    connect(combo->add,SIGNAL(clicked(bool)),combo,SLOT(addButtonClicked()));
    connect(combo,SIGNAL(addCountrySigToController(QString)),this,SLOT(addCountrySlot(QString)));
    connect(combo,SIGNAL(addCitySigToCintroller(QString,int)),this,SLOT(addCitySlot(QString,int)));
    // combobox changed signal, to controller send get signal to model
    connect(combo->combo,SIGNAL(currentIndexChanged(const QString&)),combo,SLOT(comboChangedSlot(QString)));
    connect(combo,SIGNAL(getCitySig(QString,int)),this->model,SLOT(getCityListSlot(QString,int)));
}

void TravellerController::removeTComboboxGroup(TComboWithAddField *combo){
    int index = this->getSpecifiedComboGroup(combo->id);
    this->comboGroupList.removeAt(index);
    disconnect(combo->add,SIGNAL(clicked(bool)),combo,SLOT(addButtonClicked()));
    disconnect(combo,SIGNAL(addCountrySigToController(QString)),this,SLOT(addCountrySlot(QString)));
    disconnect(combo,SIGNAL(addCitySigToCintroller(QString,int)),this,SLOT(addCitySlot(QString,int)));
    // combobox changed signal, to controller send get signal to model
    disconnect(combo->combo,SIGNAL(currentIndexChanged(const QString&)),combo,SLOT(comboChangedSlot(QString)));
    disconnect(combo,SIGNAL(getCitySig(QString,int)),this->model,SLOT(getCityListSlot(QString,int)));
}

void TravellerController::refreshDayFrameDisplay(){
    QHBoxLayout* laytmp = detail->listf->lay;
    int num = laytmp->count();
    for(int i=0;i<num-1;i++)
    {
        DayItemFrame* df = (DayItemFrame*) laytmp->itemAt(i)->widget();
        df->title->date->setText("DAY "+QString::number(i+1));
    }
}

int TravellerController::getSpecifiedComboGroup(int id){
    QListIterator<TComboWithAddField*> itr(this->comboGroupList);
    int r =-1;
    int index =0;
    while(itr.hasNext()){
        TComboWithAddField* tmp = itr.next();
        if(tmp->id == id){
            r = index;
            break;
        }
        index++;
    }
    return r;
}

bool TravellerController::isCountryOrCityNameValid(QString name){
    if(name == ""){
        this->dataErrorPopupSlot("Empty Not Acceptted");
        return false;
    }else if(name.startsWith(' ')){
        this->dataErrorPopupSlot("Cannot Start With Space");
        return false;
    }else{
        return true;
    }
}

bool TravellerController::isTripInformationValid(){
    QString name = this->addNewWindow->name->text();
    if(!this->isCountryOrCityNameValid(name)) return false;
    QString country = this->addNewWindow->hip->country->combo->currentText();
    if(!this->isCountryOrCityNameValid(country)) return false;
    QString city = this->addNewWindow->hip->city->combo->currentText();
    if(!this->isCountryOrCityNameValid(city)) return false;
    return true;
}

void TravellerController::addCountrySlot(QString country){
    if(!this->isCountryOrCityNameValid(country)) return;
    emit this->addCountrySig(country);
}

void TravellerController::setCountryListSlot(QStringList list){
    // set all country comboboxes
    QListIterator<TComboWithAddField*> itr(this->comboGroupList);
    while(itr.hasNext()){
        TComboWithAddField* t = itr.next();
        if(t->id%2 == 0){
            t->combo->setList(list);
            t->combo->setCurrentIndex(0);
            t->edit->setText("");
            // detail tab is open and trip window is open
            if(detail != nullptr && addNewWindow != nullptr){
                int index = addNewWindow->hip->country->combo->findText(model->getTripById(model->selectedTripId)->homeCountry);
                addNewWindow->hip->country->combo->setCurrentIndex(index);
            }
            // detail tab is open and city window is open
            if(detail != nullptr && addCityWindow != nullptr && addCityWindow->getType() == AddNewCityWindow::TYPE_UPDATE){
                int index = addCityWindow->country->combo->findText(\
                            model->getCityItemByIds(model->selectedTripId,model->selectedDayId,model->selectedCityId)->country);
                addCityWindow->country->combo->setCurrentIndex(index);
            }
        }
    }
}

void TravellerController::setNewlyAddedCountryListSlot(QStringList list){
    QListIterator<TComboWithAddField*> itr(this->comboGroupList);
    while(itr.hasNext()){
        TComboWithAddField* t = itr.next();
        if(t->id%2 == 0){
            t->combo->setList(list);
            t->combo->setCurrentIndex(list.length()-1);
            t->edit->setText("");
        }
    }
}

void TravellerController::setCityListSlot(QStringList list,int id){
    // set the corresponding city combobox
    int index = this->getSpecifiedComboGroup(id);
    if(index != -1)
    {
        TComboWithAddField* r = this->comboGroupList[index];
        r->combo->setList(list);
        r->combo->setCurrentIndex(0);
        r->edit->setText("");
        if(detail != nullptr && addNewWindow != nullptr){
            int index = addNewWindow->hip->city->combo->findText(model->getTripById(model->selectedTripId)->homeCity);
            addNewWindow->hip->city->combo->setCurrentIndex(index);
        }
        // detail tab is open and city window is open
        if(detail != nullptr && addCityWindow != nullptr \
                && addCityWindow->getType() == AddNewCityWindow::TYPE_UPDATE){
            int index = addCityWindow->city->combo->findText(\
                        model->getCityItemByIds(model->selectedTripId,model->selectedDayId,model->selectedCityId)->city);
            addCityWindow->city->combo->setCurrentIndex(index);
        }
    }
}

void TravellerController::setNewlyAddedCityListSlot(QStringList list, int id){
    // set the corresponding city combobox
    int index = this->getSpecifiedComboGroup(id);
    if(index != -1)
    {
        TComboWithAddField* r = this->comboGroupList[index];
        r->combo->setList(list);
        r->combo->setCurrentIndex(list.length()-1);
        r->edit->setText("");
    }
}

void TravellerController::addCitySlot(QString city, int id){
    if(!this->isCountryOrCityNameValid(city)) return;
    // get the corresponding country combo group
    TComboWithAddField* r = this->comboGroupList[getSpecifiedComboGroup(id-1)];
    QString country = "";
    if(r!=0){
        country = r->combo->currentText();
        emit this->addCitySig(country,city,id);
    }
}

void TravellerController::setTripList(QList<TripItem *> list){
    int i = 0;
    int len = list.length();
    int m = this->view->welconf->m;
    QGridLayout* layout = this->view->welconf->layout;
    // add each trip item
    for(int k=0;k<len;k++)
    {
        TripItem* trip = list[k];
        QString colorv = StaticData::getColorByName(trip->themeColor);
        TripFrame* f = new TripFrame(trip->id,colorv,this->view->welconf);
        this->registerTripFrame(f);
        f->date->setText(trip->startDate.toString(StaticData::DATE_DISPLAY_FORMAT));
        f->name->setText(trip->name);
        layout->addWidget(f,i/m,i%m);
        i++;
    }
    // add new trip button frame
    AddTripButtonFrame* addf = new AddTripButtonFrame(this->view->welconf);
    layout->addWidget(addf,i/m,i%m);
    i++;
    // connect signals and slots
    // connect add trip signal from addtripButtonFrame, to controller add
    connect(addf,SIGNAL(addTripFrameClickedSig()),this,SLOT(addTripFrameClickedSlot()));
    // padding up the grid layout
    for(int j=0;j<m;j++){
        QWidget* padding = new QWidget(this->view->welconf);
        layout->addWidget(padding,i/m,i%m);
        layout->setColumnStretch(j,1);
        i++;
    }
}

void TravellerController::registerTripFrame(TripFrame *f){
    // add frame to the list
    this->tripFrameList<<f;
    // trip frame clicked signal from trip frame, to controller handel
    connect(f,SIGNAL(tripClickedSig(int)),this,SLOT(tripFrameClickedSlot(int)));
    // trip frame right clicked signal from trip frame, to ontroller handel
    connect(f,SIGNAL(tripRightClickedSig(int,QPoint)),this,SLOT(tripRightClickedSlot(int,QPoint)));
}

void TravellerController::tripFrameClickedSlot(int id){
    // release signal to model and update the view by data
    emit this->getTripByIdSig(id,1);
}

void TravellerController::returnBackToWelcomeSlot(){
    if(detail!=nullptr)
    {
        disconnect(this->detail->titlef->returnBack,SIGNAL(clicked(bool)),this,SLOT(returnBackToWelcomeSlot()));
        disconnect(this->detail->titlef,SIGNAL(tripTitleFrameDoubleClickedSig()),this,SLOT(tripTitleFrameDoubleClickedSlot()));
        delete this->detail;
        this->detail = nullptr;
    }
    this->view->tabPane->removeTab(0);
    this->view->tabPane->insertTab(0,this->welcome,"WELCOME");
    this->view->tabPane->setCurrentIndex(0);
}

EventItemFrame* TravellerController::createEventFrameByData(EventItem *etmp, int tid, int did, int cid){
    int eid = etmp->id;
    EventItemFrame* ef = new EventItemFrame(tid,did,cid,eid,\
                                            StaticData::getColorByName(model->getTripById(tid)->themeColor));
    // connect event frame double clicked signal from event frame, to controller pop up
    connect(ef,SIGNAL(eventFrameDoubleClickedSig(int,int,int)),this,SLOT(eventFrameDoubleClickedSlot(int,int,int)));
    connect(ef,SIGNAL(deleteEventClickedSig(int,int,int)),this,SLOT(deleteEventButtonClicked(int,int,int)));
    this->setEventFrameValues(ef,etmp);
    return ef;
}

CityItemFrame* TravellerController::createCityFrameByData(CityItem *ctmp, int tid, int did){
    int cid = ctmp->id;
    CityItemFrame* cf = new CityItemFrame(tid,did,cid,StaticData::getColorByName(model->getTripById(tid)->themeColor));
    // connect city item frame double cllicked signal from city item frame, to model handeller
    connect(cf->title,SIGNAL(cityItemFrameDoubleClickedSig(int,int)),this,SLOT(cityItemFrameDoubleClickedSlot(int,int)));
    connect(cf->title,SIGNAL(cityItemDeleteClickedSig(int,int)),this,SLOT(deleteCityButtonClicked(int,int)));
    setCityFrameValues(cf,ctmp);
    QListIterator<EventItem*> eitr(ctmp->eventList);
    while(eitr.hasNext()){
        EventItem* etmp = eitr.next();
        EventItemFrame* ef = createEventFrameByData(etmp,tid,did,cid);
        cf->eventsLay->addWidget(ef);
    }
    AddEventOrCityButton* addEventButton = new AddEventOrCityButton(tid,did,cid,cf);
    cf->eventsLay->addWidget(addEventButton);
    // connect add new event button clicked signal from add button, to controller add event handler
    connect(addEventButton,SIGNAL(buttonClickedTypeEvent(int,int,int)),this,SLOT(addEventButtonClickedSlot(int,int,int)));
    return cf;
}

DayItemFrame* TravellerController::createDayItemFrameByData(DayItem *dtmp,QString tcolor,int tid){
    int did = dtmp->id;
    DayItemFrame* df = new DayItemFrame(tid,did,tcolor);
    QListIterator<CityItem*> citr(dtmp->cityList);
    while(citr.hasNext()){
        CityItem* ctmp = citr.next();
        CityItemFrame* cf =  createCityFrameByData(ctmp,tid,did);
        df->listLay->addWidget(cf);
    }
    AddEventOrCityButton* addCityButton = new AddEventOrCityButton(tid,did,df);
    df->listLay->addWidget(addCityButton);
    // connect add new city button clicked signal from add button, to controller add city handler
    connect(addCityButton,SIGNAL(buttonClickedTypeCity(int,int)),this,SLOT(addCityButtonClickedSlot(int,int)));
    // caonnect delete day signal from day title frame, to controller handeller
    connect(df->title,SIGNAL(dayDeleteClickedSig(int)),this,SLOT(deleteDayButtonClicked(int)));
    return df;
}

void TravellerController::setTripSlot(TripItem *t){
    // if(this->detail == nullptr) return;
    // store the old frame
    this->model->selectedTripId = t->id;
    int tid = t->id;
    this->welcome = this->view->welconf;
    // remove the welcome frame
    this->view->tabPane->removeTab(0);
    // crate new detal frame
    QString tcolor = StaticData::getColorByName(t->themeColor);
    this->detail = new TripDetailFrame(tcolor);
    // add this to the first tab
    this->view->tabPane->insertTab(0,this->detail,"Edit Trip");
    // set this tab as selected
    this->view->tabPane->setCurrentIndex(0);
    // connect detail title frame return button to controller handeler
    connect(this->detail->titlef->returnBack,SIGNAL(clicked(bool)),this,SLOT(returnBackToWelcomeSlot()));
    // connect double click signal from trip title frame, to controller ouble click handeler
    connect(this->detail->titlef,SIGNAL(tripTitleFrameDoubleClickedSig()),this,SLOT(tripTitleFrameDoubleClickedSlot()));
    // update the view
    this->detail->titlef->name->setText(t->name);
    this->detail->titlef->from->setText(t->homeCountry+"  "+t->homeCity);
    this->detail->titlef->date->setText(t->startDate.toString(StaticData::DATE_DISPLAY_FORMAT)); 
    QList<DayItem*> dl = t->dayList;
    QListIterator<DayItem*> ditr(dl);
    while(ditr.hasNext()){
        DayItem* dtmp = ditr.next();
        DayItemFrame* df = createDayItemFrameByData(dtmp,tcolor,tid);
        this->detail->listf->lay->addWidget(df);
    }
    AddEventOrCityButton* addDay = new AddEventOrCityButton(model->selectedTripId);
    connect(addDay,SIGNAL(buttonClickedTypeDay(int)),this,SLOT(addDayButtonClickedSlot(int)));
    this->detail->listf->lay->addWidget(addDay);

    refreshDayFrameDisplay();
}

void TravellerController::addTripFrameClickedSlot(){
    // add new window exists
    if(this->addNewWindow!=nullptr) return;
    // set main window as its parent and block it when opened in modal
    this->addNewWindow = new AddNewTripWindow(this->view);
    // register combobox in this window
    this->registerTComboWithAddSlot(this->addNewWindow->hip->country);
    this->registerTComboWithAddSlot(this->addNewWindow->hip->city);
    emit this->view->getCountryListSig();
    QString currentText=this->addNewWindow->hip->country->combo->currentText();
    emit this->addNewWindow->hip->country->combo->currentTextChanged(currentText);
    // connect add new window close signal to controller close slot
    connect(this->addNewWindow,SIGNAL(windowClosed(int,int)),this,SLOT(addNewTripWindowClosedSlot(int,int)));
    // connect controller add new window close permitted signal to add new window close event
    connect(this,SIGNAL(addNewTripWindowClosePermittedSig()),this->addNewWindow,SLOT(closePermittedSlot()));
    // in modal style
    this->addNewWindow->exec();
}

void TravellerController::dataErrorPopupSlot(QString errorMessage){
    QMessageBox::critical(0, QObject::tr("DATA ERROR"),errorMessage);
}

void TravellerController::databaseErrorPopupSlot(QString errorMessage){
    QMessageBox::critical(0, QObject::tr("DATABASE ERROR"),errorMessage);
}

void TravellerController::addNewTripWindowClosedSlot(int type,int windowType){
    HomeInfoPane* hip = this->addNewWindow->hip;
    if(type == StaticData::SAVE_AND_CLOSE){
        // no valid input not acceptable
        if(!this->isTripInformationValid()) return;
        QString name = this->addNewWindow->name->text();
        QString country = hip->country->combo->currentText();
        QString city = hip->city->combo->currentText();
        QDate date = hip->startDatePicker->selectedDate();
        QString color = this->addNewWindow->colorCombo->currentText();
        if(windowType == StaticData::ADD_NEW_WINDOW) this->model->addNewTrip(name,country,city,date,color);
        else this->model->updateTripInfo(model->selectedTripId,name,country,city,date,color);
    }
    this->removeTComboboxGroup(hip->country);
    this->removeTComboboxGroup(hip->city);
    emit this->addNewTripWindowClosePermittedSig();
    disconnect(this->addNewWindow,SIGNAL(windowClosed(int,int)),this,SLOT(addNewTripWindowClosedSlot(int,int)));
    disconnect(this,SIGNAL(addNewTripWindowClosePermittedSig()),this->addNewWindow,SLOT(closePermittedSlot()));
    delete this->addNewWindow;
    this->addNewWindow = nullptr;
}

void TravellerController::addNewTripFrameSlot(TripItem *trip){
    QGridLayout* lay = this->view->welconf->layout;
    // trip num + 1*addFrame + 4*padding
    int num = lay->count();
    int m = this->view->welconf->m;
    // index of the newly added trip frame
    int i = num-m-1;
    AddTripButtonFrame* add = (AddTripButtonFrame*)lay->itemAt(num-m-1)->widget();
    QList<QWidget*> padding;
    // get all padding items
    for(int k=0;k<m;k++)
    {
        padding << lay->itemAt(num-1-k)->widget();
    }
    // add new trip item fram
    QString colorv = StaticData::getColorByName(trip->themeColor);
    TripFrame* f = new TripFrame(trip->id,colorv);
    this->registerTripFrame(f);
    f->date->setText(trip->startDate.toString(StaticData::DATE_DISPLAY_FORMAT));
    f->name->setText(trip->name);
    lay->addWidget(f,i/m,i%m);
    i++;
    lay->addWidget(add,i/m,i%m);
    i++;
    for(int k=0;k<m;k++)
    {
        lay->addWidget(padding[k],i/m,i%m);
        i++;
    }
}

void TravellerController::tripTitleFrameDoubleClickedSlot(){
    if(this->addNewWindow != nullptr) return;
    TripItem* trip = this->model->getTripById(model->selectedTripId);
    // set main window as its parent and block it when opened in modal
    this->addNewWindow = new AddNewTripWindow(this->view,StaticData::UPDATE_INFO_WINDOW);
    // register combobox in this window
    this->registerTComboWithAddSlot(this->addNewWindow->hip->country);
    this->registerTComboWithAddSlot(this->addNewWindow->hip->city);
    emit this->view->getCountryListSig();
    int id = this->addNewWindow->colorCombo->findText(trip->themeColor);
    this->addNewWindow->colorCombo->setCurrentIndex(id);
    this->addNewWindow->name->setText(trip->name);
    // connect add new window close signal to controller close slot
    connect(this->addNewWindow,SIGNAL(windowClosed(int,int)),this,SLOT(addNewTripWindowClosedSlot(int,int)));
    // connect controller add new window close permitted signal to add new window close event
    connect(this,SIGNAL(addNewTripWindowClosePermittedSig()),this->addNewWindow,SLOT(closePermittedSlot()));
    // in modal style
    this->addNewWindow->exec();
}

void TravellerController::updateTripInfoSlot(TripItem *trip){
    if(this->detail == nullptr) return;
    this->detail->titlef->name->setText(trip->name);
    this->detail->titlef->from->setText(trip->homeCountry+" "+trip->homeCity);
    this->detail->titlef->date->setText(trip->startDate.toString(StaticData::DATE_DISPLAY_FORMAT));
    TripFrame* t = this->getTripFrameById(trip->id);
    if(t==nullptr){
        this->dataErrorPopupSlot("No Such Trip");
        return;
    }
    QString tcolor = StaticData::getColorByName(trip->themeColor);
    t->changeColor(tcolor);
    t->date->setText(trip->startDate.toString(StaticData::DATE_DISPLAY_FORMAT));
    t->name->setText(trip->name);
    this->detail->titlef->changeColor(tcolor);
    int num = this->detail->listf->lay->count();
    for(int i=0;i<num-1;i++){
        DayItemFrame* d = (DayItemFrame*) this->detail->listf->lay->itemAt(i)->widget();
        d->changeColor(tcolor);
    }
}

void TravellerController::tripRightClickedSlot(int id,QPoint pos){
    TripFrame* t = this->getTripFrameById(id);
    if(t==nullptr){
        this->dataErrorPopupSlot("No Such Trip");
        return;
    }
    this->model->selectedTripId=id;
    if(this->tiMenu != nullptr){
        disconnect(this->tiMenu->editAct,SIGNAL(triggered(bool)),this,SLOT(tripMenuEditClickedSlot(bool)));
        delete this->tiMenu;
        this->tiMenu = nullptr;
    }
    this->tiMenu = new TripItemMenu(this->view);
    // connect edit signal from trip menu edit action, to controller trip frame double clicked slot
    connect(this->tiMenu->editAct,SIGNAL(triggered(bool)),this,SLOT(tripMenuEditClickedSlot(bool)));
    connect(this->tiMenu->deleteAct,SIGNAL(triggered(bool)),this,SLOT(tripMenuDeleteClickedSlot(bool)));
    this->tiMenu->popup(pos);
}

void TravellerController::tripMenuEditClickedSlot(bool state){
    this->tripFrameClickedSlot(this->model->selectedTripId);
}

void TravellerController::tripMenuDeleteClickedSlot(bool state){
    deleteTripButtonClicked();
}

void TravellerController::addEventButtonClickedSlot(int tid, int did, int cid){
    this->model->selectedTripId = tid;
    this->model->selectedDayId = did;
    this->model->selectedCityId = cid;
    if(this->addEventWindow != nullptr) return;
    this->addEventWindow = new AddNewEventWindow(this->view);
    connect(this->addEventWindow,SIGNAL(windowClosedSig(int,int)),this,SLOT(addNewEventWindowClosedSlot(int,int)));
    connect(this,SIGNAL(addNewEventWindowClosePermittedSig()),this->addEventWindow,SLOT(closePermittedSlot()));
    this->addEventWindow->exec();
}

void TravellerController::addCityButtonClickedSlot(int tid, int did){
    this->model->selectedTripId = tid;
    this->model->selectedDayId = did;
    if(this->addCityWindow != nullptr) return;
    this->addCityWindow = new AddNewCityWindow(this->view);

    this->registerTComboWithAddSlot(this->addCityWindow->country);
    this->registerTComboWithAddSlot(this->addCityWindow->city);
    emit this->view->getCountryListSig();

    connect(this->addCityWindow,SIGNAL(closeAddCityWindowSig(int,int)),this,SLOT(addNewCityWindowClosedSlot(int,int)));
    connect(this,SIGNAL(addNewCityWindowClosePermittedSig()),this->addCityWindow,SLOT(windowClosePermittedSlot()));
    this->addCityWindow->exec();
}

void TravellerController::addDayButtonClickedSlot(int tid){
    this->model->selectedTripId = tid;
    model->addNewDaySlot();
}

void TravellerController::addNewCityWindowClosedSlot(int type, int windowType){
    if(type == AddNewCityWindow::SAVE_AND_EXIT){
        QString country = addCityWindow->country->combo->currentText();
        QString city = addCityWindow->city->combo->currentText();
        if(windowType == AddNewCityWindow::TYPE_ADD)  model->addNewCityItemSlot(country,city);
        else model->updateCityItemInfoSlot(country,city);
    }
    this->removeTComboboxGroup(addCityWindow->country);
    this->removeTComboboxGroup(addCityWindow->city);
    emit this->addNewCityWindowClosePermittedSig();
    delete this->addCityWindow;
    this->addCityWindow = nullptr;
}

void TravellerController::eventFrameDoubleClickedSlot(int did, int cid, int eid){
    // update selected day city and event
    model->selectedDayId = did;
    model->selectedCityId = cid;
    model->selectedEventId = eid;
    if (this->addEventWindow!=nullptr) return;
    EventItem* e = this->model->getEventByIds(model->selectedTripId,did,cid,eid);
    if(e == nullptr){
        this->dataErrorPopupSlot("No Such Event");
        return;
    }
    addEventWindow = new AddNewEventWindow(this->view,AddNewEventWindow::TYPE_UPDATE);
    connect(this->addEventWindow,SIGNAL(windowClosedSig(int,int)),this,SLOT(addNewEventWindowClosedSlot(int,int)));
    connect(this,SIGNAL(addNewEventWindowClosePermittedSig()),this->addEventWindow,SLOT(closePermittedSlot()));

    int index = addEventWindow->event->type->findText(e->destType);
    addEventWindow->event->type->setCurrentIndex(index);
    addEventWindow->event->name->setText(e->destName);
    index = addEventWindow->event->currency->findText(e->currency);
    addEventWindow->event->currency->setCurrentIndex(index);
    addEventWindow->event->amount->setText(QString::number(e->destCost));

    index = addEventWindow->transport->type->findText(e->transportType);
    addEventWindow->transport->type->setCurrentIndex(index);
    addEventWindow->transport->name->setText(e->transportName);
    index = addEventWindow->transport->currency->findText(e->tcurrency);
    addEventWindow->transport->currency->setCurrentIndex(index);
    addEventWindow->transport->amount->setText(QString::number(e->transportCost));

    addEventWindow->exec();
}

void TravellerController::addNewEventWindowClosedSlot(int type, int windowType){
    if(type == AddNewEventWindow::SAVE_AND_EXIT){
        QString et = addEventWindow->event->type->currentText();
        QString en = addEventWindow->event->name->text();
        QString ecur = addEventWindow->event->currency->currentText();
        double ecost = addEventWindow->event->amount->text().toDouble();
        QString tt = addEventWindow->transport->type->currentText();
        QString tn = addEventWindow->transport->name->text();
        QString tcur = addEventWindow->transport->currency->currentText();
        double tcost = addEventWindow->transport->amount->text().toDouble();
        if(!isCountryOrCityNameValid(tn)||!isCountryOrCityNameValid(en)) return;
        if(windowType == AddNewEventWindow::TYPE_ADD)
            this->model->addNewEvent(et,en,ecur,ecost,tt,tn,tcur,tcost);
        else this->model->updateEventInfoSlot(et,en,ecur,ecost,tt,tn,tcur,tcost);
    }
    emit this->addNewEventWindowClosePermittedSig();
    delete this->addEventWindow;
    this->addEventWindow = nullptr;
}

void TravellerController::addNewEventSlot(EventItem* event){
    QList<int> list = this->model->getSelectedIndexInList();
    DayItemFrame* d = (DayItemFrame*) this->detail->listf->lay->itemAt(list[1])->widget();
    CityItemFrame* c = (CityItemFrame*) d->listLay->itemAt(list[2])->widget();
    QVBoxLayout* laytmp = c->eventsLay;
    int num = laytmp->count();
    EventItemFrame* ef = createEventFrameByData(event,model->selectedTripId,model->selectedDayId,model->selectedCityId);
    laytmp->insertWidget(num-1,ef);
    this->setEventFrameValues(ef,event);
}

void TravellerController::updateEventInfoSlot(EventItem *event){
    QList<int> list = this->model->getSelectedIndexInList();
    DayItemFrame* d = (DayItemFrame*) this->detail->listf->lay->itemAt(list[1])->widget();
    CityItemFrame* c = (CityItemFrame*) d->listLay->itemAt(list[2])->widget();
    EventItemFrame* e = (EventItemFrame*) c->eventsLay->itemAt(list[3])->widget();
    this->setEventFrameValues(e,event);
}

void TravellerController::addNewlyAddedCityItemSlot(CityItem *city){
    int tid = model->selectedTripId;
    int did = model->selectedDayId;
    QList<int> list = this->model->getSelectedIndexInList();
    DayItemFrame* d = (DayItemFrame*) this->detail->listf->lay->itemAt(list[1])->widget();
    QVBoxLayout* laytmp = d->listLay;
    CityItemFrame* cf = createCityFrameByData(city,tid,did);
    int num = laytmp->count();
    laytmp->insertWidget(num-1,cf);
}

void TravellerController::cityItemFrameDoubleClickedSlot(int did, int cid){
    if(this->addCityWindow != nullptr) return;
    model->selectedDayId = did;
    model->selectedCityId = cid;
    this->addCityWindow = new AddNewCityWindow(this->view,AddNewCityWindow::TYPE_UPDATE);

    this->registerTComboWithAddSlot(this->addCityWindow->country);
    this->registerTComboWithAddSlot(this->addCityWindow->city);
    emit this->view->getCountryListSig();

    connect(this->addCityWindow,SIGNAL(closeAddCityWindowSig(int,int)),this,SLOT(addNewCityWindowClosedSlot(int,int)));
    connect(this,SIGNAL(addNewCityWindowClosePermittedSig()),this->addCityWindow,SLOT(windowClosePermittedSlot()));
    this->addCityWindow->exec();
}

void TravellerController::updateCityItemInfoSlot(CityItem *city){
    QList<int> list = this->model->getSelectedIndexInList();
    DayItemFrame* d = (DayItemFrame*) this->detail->listf->lay->itemAt(list[1])->widget();
    CityItemFrame* c = (CityItemFrame*) d->listLay->itemAt(list[2])->widget();
    setCityFrameValues(c,city);
}

void TravellerController::addNewlyAddedDaySlot(DayItem *day){
    QString tcolor = StaticData::getColorByName(model->getCurrentTripItem()->themeColor);
    DayItemFrame* df = createDayItemFrameByData(day,tcolor,model->selectedTripId);
    int num = detail->listf->lay->count();
    detail->listf->lay->insertWidget(num-1,df);
    refreshDayFrameDisplay();
}

void TravellerController::deleteEventButtonClicked(int did, int cid, int eid){
    QMessageBox deleteConfirm;
    deleteConfirm.setIcon(QMessageBox::Warning);
    deleteConfirm.setWindowTitle("Comfirmation");
    deleteConfirm.setText("DELETE BUTTON PRESSED");
    deleteConfirm.setInformativeText("Do you really want to delete the evnt");
    deleteConfirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    deleteConfirm.setDefaultButton(QMessageBox::No);
    int r = deleteConfirm.exec();
    if(r == QMessageBox::Yes){
        model->selectedDayId = did;
        model->selectedCityId = cid;
        model->selectedEventId = eid;
        model->deleteEventSlot();
    }
}

void TravellerController::deleteEventUpdateSlot(){
    QList<int> list = this->model->getSelectedIndexInList();
    DayItemFrame* d = (DayItemFrame*) this->detail->listf->lay->itemAt(list[1])->widget();
    CityItemFrame* c = (CityItemFrame*) d->listLay->itemAt(list[2])->widget();
    QVBoxLayout* laytmp = c->eventsLay;
    EventItemFrame* e = (EventItemFrame*)laytmp->itemAt(list[3])->widget();
    laytmp->removeWidget(e);
    delete e;
    e = nullptr;
    model->removeTheEventFromTheList();
}

void TravellerController::deleteCityButtonClicked(int did, int cid){
    QMessageBox deleteConfirm;
    deleteConfirm.setIcon(QMessageBox::Warning);
    deleteConfirm.setWindowTitle("Comfirmation");
    deleteConfirm.setText("DELETE BUTTON PRESSED");
    deleteConfirm.setInformativeText("Do you really want to delete the city");
    deleteConfirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    deleteConfirm.setDefaultButton(QMessageBox::No);
    int r = deleteConfirm.exec();
    if(r == QMessageBox::Yes){
        model->selectedDayId = did;
        model->selectedCityId = cid;
        model->deleteCitySlot();
    }
}

void TravellerController::deleteCityUpdateSlot(){
    QList<int> list = this->model->getSelectedIndexInList();
    DayItemFrame* d = (DayItemFrame*) this->detail->listf->lay->itemAt(list[1])->widget();
    QVBoxLayout* laytmp = d->listLay;
    CityItemFrame* c = (CityItemFrame*) laytmp->itemAt(list[2])->widget();
    laytmp->removeWidget(c);
    delete c;
    c = nullptr;
    model->removeTheCityFromTheList();
}

void TravellerController::deleteDayButtonClicked(int did){
    QMessageBox deleteConfirm;
    deleteConfirm.setIcon(QMessageBox::Warning);
    deleteConfirm.setWindowTitle("Comfirmation");
    deleteConfirm.setText("DELETE BUTTON PRESSED");
    deleteConfirm.setInformativeText("Do you really want to delete this day");
    deleteConfirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    deleteConfirm.setDefaultButton(QMessageBox::No);
    int r = deleteConfirm.exec();
    if(r == QMessageBox::Yes){
        model->selectedDayId = did;
        model->deleteDaySlot();
    }
}

void TravellerController::deleteDayUpdateSlot(){
    QList<int> list = this->model->getSelectedIndexInList();
    QHBoxLayout* laytmp = this->detail->listf->lay;
    DayItemFrame* d = (DayItemFrame*) this->detail->listf->lay->itemAt(list[1])->widget();
    laytmp->removeWidget(d);
    delete d;
    d = nullptr;
    model->removeTheDayFromTheList();
    refreshDayFrameDisplay();
}

void TravellerController::deleteTripButtonClicked(){
    QMessageBox deleteConfirm;
    deleteConfirm.setIcon(QMessageBox::Warning);
    deleteConfirm.setWindowTitle("Comfirmation");
    deleteConfirm.setText("DELETE BUTTON PRESSED");
    deleteConfirm.setInformativeText("Do you really want to delete this trip");
    deleteConfirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    deleteConfirm.setDefaultButton(QMessageBox::No);
    int r = deleteConfirm.exec();
    if(r == QMessageBox::Yes){
        model->deleteTripSlot();
    }
}

void TravellerController::deleteTripUpdateSlot(){
    model->removeTheTripFromTheList();
    delete welcome;
    view->welconf = new WelcomeFrame();
    welcome = view->welconf;
    returnBackToWelcomeSlot();
    QList<TripItem*> tl = model->getTripList();
    setTripList(tl);
}

TravellerController::~TravellerController(){
    if(this->model!=nullptr){
        delete this->model;
        this->model = nullptr;
    }
    if(this->view!=nullptr){
        delete this->view;
        this->view = nullptr;
    }
    if(this->welcome!=nullptr){
        delete this->welcome;
        this->welcome = nullptr;
    }
    if(this->detail!=nullptr){
        delete this->detail;
        this->detail = nullptr;
    }
    if(this->addNewWindow!=nullptr){
        delete this->addNewWindow;
        this->addNewWindow = nullptr;
    }
}
