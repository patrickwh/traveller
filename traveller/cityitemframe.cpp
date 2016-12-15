#include "cityitemframe.h"

CityItemFrame::CityItemFrame(int tid,int did,int cid,QString tc,QWidget *parent) : \
    QWidget(parent),dayid{did},cityid{cid},tripid{tid},tcolor{tc}
{
    this->lay = new QVBoxLayout();
    this->setLayout(this->lay);
    title = new CityTitleFrame(tid,did,cid,tcolor);
    lay->addWidget(title);

    this->events = new QWidget();
    this->lay->addWidget(this->events);
    this->eventsLay = new QVBoxLayout();
    this->events->setLayout(this->eventsLay);

    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
}

CityItemFrame::~CityItemFrame(){

    delete this->events;
    this->events = nullptr;

    int num = this->lay->count();
    for (int i=0;i<num;i++){
        QWidget* w = this->lay->itemAt(i)->widget();
        delete w;
        w = nullptr;
    }
    delete this->lay;
    this->lay = nullptr;
}

void CityItemFrame::changeColor(QString tc){
    title->changeColor(tc);
    int num = this->eventsLay->count();
    for(int i=0;i<num-1;i++){
        ((EventItemFrame*) eventsLay->itemAt(i)->widget())->changeColor(tc);
    }
}
