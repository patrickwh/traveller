#include "tcombobox.h"

TComboBox::TComboBox(int type):QComboBox()
{
    this->setFixedHeight(StaticData::NORMAL_TEXT_HEIGHT);
    this->setFont(*(new TFont()));
    if(type == StaticData::COLOR_SELECT_COMBOBOX){
        QString* list=StaticData::COLOR_SET;
        int num = StaticData::COLOR_SET_SIZE;
        for(int i=0;i<num;i++){
            QString cname = list[i];
            QIcon icon = QIcon("..\\icons\\"+cname+".jpg");
            this->addItem(icon,cname);
        }
    }
}
 void TComboBox::setList(QStringList list)
 {
     this->clear();
     this->addItems(list);
 }
