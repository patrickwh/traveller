#include "tlineedit.h"

TLineEdit::TLineEdit(QString hint,int width) : QLineEdit()
{
    QFont* f=new QFont();
    f->setPointSize(15);

    this->setFixedHeight(75);
    this->setPlaceholderText(hint);
    this->setFont(*f);

    if(width>0) this->setFixedWidth(width);
}
