#include "tcombowithaddfield.h"

TComboWithAddField::TComboWithAddField(QString text,QString hint,int i) : QWidget(),id{i}
{
    QGridLayout* layout= new QGridLayout();
    TTextLabel* label = new TTextLabel(text);
    layout->addWidget(label,0,0);
    layout->setColumnStretch(0,2);

    this->combo = new TComboBox();
    layout->addWidget(this->combo,0,1);
    layout->setColumnStretch(1,2);

    this->edit = new TLineEdit(hint);
    layout->addWidget(this->edit,0,2);
    layout->setColumnStretch(2,3);

    this->add = new TButton("Add",150);
    layout->addWidget(this->add,0,3);
    layout->setColumnStretch(3,1);

    this->setLayout(layout);
}

void TComboWithAddField::addButtonClicked(){    
    if(this->id%2 ==0)
    {
        QString country = this->edit->text();
        emit this->addCountrySigToController(country);
    }else{
        QString city = this->edit->text();
        emit this->addCitySigToCintroller(city,id);
    }
}

void TComboWithAddField::comboChangedSlot(QString str){
    if(this->id%2 == 0){
        // update the city combobox
        emit this->getCitySig(str,this->id+1);
    }
}
