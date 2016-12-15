#include "triptitleframe.h"

TripTitleFrame::TripTitleFrame(QString color):QFrame()
{
    this->setFixedHeight(StaticData::TRIP_FRAME_HEIGHT);
    this->lay = new QGridLayout();
    this->setLayout(this->lay);

    this->returnBack = new TButton("BACK",150);
    this->lay->addWidget(this->returnBack,0,0);

    QGridLayout* layout = new QGridLayout();
    QWidget* temp = new QWidget();
    temp->setLayout(layout);
    this->lay->addWidget(temp,0,1);

    this->namel = new TTextLabel("Trip Name :");
    layout->addWidget(namel,0,0);
    this->name = new TTextLabel("");
    layout->addWidget(this->name,0,1);
    this->froml = new TTextLabel("From :");
    layout->addWidget(froml,1,0);
    this->from = new TTextLabel("");
    layout->addWidget(this->from,1,1);
    this->datel = new TTextLabel("Date :");
    layout->addWidget(datel,1,2);
    this->date = new TTextLabel("");
    layout->addWidget(this->date,1,3);

    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,2);
    layout->setColumnStretch(2,1);
    layout->setColumnStretch(3,2);

    // set style sheet for this widget
    this->style=StyleSheetCeator::setBackgroundColor(this->style,color);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(this->style));
}

TripTitleFrame::~TripTitleFrame(){
    delete this->name;
    this->name = nullptr;
    delete this->date;
    this->date = nullptr;
    delete this->from;
    this->from = nullptr;
    delete this->namel;
    this->namel = nullptr;
    delete this->froml;
    this->froml = nullptr;
    delete this->datel;
    this->datel = nullptr;
    delete this->returnBack;
    this->returnBack = nullptr;
    delete this->lay;
    this->lay = nullptr;
}

void TripTitleFrame::mouseDoubleClickEvent(QMouseEvent *event){
    emit this->tripTitleFrameDoubleClickedSig();
}

void TripTitleFrame::changeColor(QString color){
    this->style=StyleSheetCeator::setBackgroundColor(this->style,color);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(this->style));
}
