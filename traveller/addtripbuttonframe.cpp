#include "addtripbuttonframe.h"

AddTripButtonFrame::AddTripButtonFrame(QWidget* parent):QFrame(parent)
{
    this->setFixedHeight(StaticData::TRIP_FRAME_HEIGHT);
    QVBoxLayout* layout = new QVBoxLayout();
    this->setLayout(layout);

    this->style=StyleSheetCeator::setBackgroundColor(this->style,StaticData::LIGHT_GRAY);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(this->style));


    TTextLabel* addl = new TTextLabel("+",20);
    layout->addWidget(addl);

}

AddTripButtonFrame::~AddTripButtonFrame(){
    foreach(QWidget* w,this->findChildren<QWidget*>()) delete w;
}

void AddTripButtonFrame::mouseReleaseEvent(QMouseEvent *event){
    emit this->addTripFrameClickedSig();
}
