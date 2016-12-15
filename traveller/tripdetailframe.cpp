#include "tripdetailframe.h"

TripDetailFrame::TripDetailFrame(QString color):QFrame()
{
    this->lay = new QVBoxLayout();
    this->setLayout(this->lay);
    this->setAutoFillBackground(true);

    this->titlef = new TripTitleFrame(color);
    this->lay->addWidget(this->titlef);

    this->listf = new DayListFrame();
    this->lay->addWidget(this->listf);
}

TripDetailFrame::~TripDetailFrame(){
    delete this->titlef;
    this->titlef = nullptr;
    delete this->listf;
    this->listf = nullptr;
    delete this->lay;
    this->lay = nullptr;
}
