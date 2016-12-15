#include "tripframe.h"

TripFrame::TripFrame(int id,QString theme,QWidget* parent):QFrame(parent),id{id},tcolor{theme}
{
    this->setContentsMargins(QMargins(20,20,20,20));
    this->setFixedHeight(StaticData::TRIP_FRAME_HEIGHT);

    style = StyleSheetCeator::setBackgroundColor(style,theme);
    style = StyleSheetCeator::setValue(style,"border-style","solid");
    style = StyleSheetCeator::setValue(style,"border-width","5px");
    style = StyleSheetCeator::setValue(style,"border-color","#"+theme);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(this->style));

    this->layout = new QVBoxLayout();
    this->date = new TTextLabel("");
    this->name = new TTextLabel("");
    layout->addWidget(name);
    layout->addWidget(date);
    this->setLayout(layout);
}

void TripFrame::mouseDoubleClickEvent(QMouseEvent *event){
    emit this->tripClickedSig(this->id);
}

void TripFrame::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::RightButton){
        emit this->tripRightClickedSig(this->id,event->globalPos());
    }
}

void TripFrame::changeColor(QString color){
    this->style=StyleSheetCeator::setBackgroundColor(this->style,color);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(this->style));
}

TripFrame::~TripFrame(){
    delete this->date;
    this->date = nullptr;
    delete this->name;
    this->name = nullptr;
    delete this->layout;
    this->layout = nullptr;
}

void TripFrame::enterEvent(QEvent *event){
    style = StyleSheetCeator::setValue(style,"background-color","white");
    style = StyleSheetCeator::setValue(style,"color","#"+tcolor);
    setStyleSheet(StyleSheetCeator::getStyleSeetString(style));
}

void TripFrame::leaveEvent(QEvent *event){
    style = StyleSheetCeator::setValue(style,"background-color","#"+tcolor);
    style = StyleSheetCeator::setValue(style,"color","white");
    setStyleSheet(StyleSheetCeator::getStyleSeetString(style));
}
