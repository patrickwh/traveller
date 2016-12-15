#include "addeventorcitybutton.h"

void AddEventOrCityButton::init(){


    connect(this,SIGNAL(clicked(bool)),this,SLOT(clickedSlot(bool)));

    this->style = StyleSheetCeator::setBorder(style,"none");
    this->style = StyleSheetCeator::setBackgroundColor(style,StaticData::LIGHT_GRAY);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(style));
}

AddEventOrCityButton::AddEventOrCityButton(int tid,int did,int cid,QWidget* parent):QPushButton("Add A New Event",parent),\
    tripid{tid},dayid{did},cityid{cid},type{AddEventOrCityButton::TYPE_EVENT}
{
    this->setFixedHeight(StaticData::SMALL_BUTTON_HEIGHT);
    init();
}

AddEventOrCityButton::AddEventOrCityButton(int tid,int did,QWidget* parent):QPushButton("Add A New City",parent),\
    tripid{tid},dayid{did},type{AddEventOrCityButton::TYPE_CITY}
{
    this->setFixedHeight(StaticData::SMALL_BUTTON_HEIGHT);
    init();
}

AddEventOrCityButton::AddEventOrCityButton(int tid, QWidget *parent):QPushButton("+NEW",parent),tripid{tid}
{
    init();
    this->setFixedWidth(StaticData::ADD_NEW_DAY_BUTTON_WIDTH);
    this->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);
}

void AddEventOrCityButton::clickedSlot(bool isClicked){
    if(type == AddEventOrCityButton::TYPE_EVENT)
        emit this->buttonClickedTypeEvent(tripid,dayid,cityid);
    else if(type == AddEventOrCityButton::TYPE_CITY)
        emit this->buttonClickedTypeCity(tripid,dayid);
    else emit this->buttonClickedTypeDay(tripid);
}
