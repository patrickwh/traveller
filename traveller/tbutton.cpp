#include "tbutton.h"

TButton::TButton(QString str,int width) : QPushButton(str)
{
    QFont* f = new QFont();
    f->setPointSize(StaticData::NORMAL_TEXT_SIZE);
    this->setFont(*f);
    this->setFixedHeight(StaticData::NORMAL_TEXT_HEIGHT);
    this->setFixedWidth(width);
}

TButton::TButton(QString str) : QPushButton(str)
{
    QFont* f = new QFont();
    f->setPointSize(StaticData::NORMAL_TEXT_SIZE);
    this->setFont(*f);
    this->setFixedHeight(StaticData::NORMAL_TEXT_HEIGHT);
}

TButton::TButton(int h,int w) : QPushButton()
{
    this->setFixedHeight(h);
    this->setFixedWidth(w);
    this->setBasicStyleSheet();
}

void TButton::setBasicStyleSheet(){
    style = StyleSheetCeator::setBorder(style,"none");
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(style));
}
