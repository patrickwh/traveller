#include "newdaypane.h"

NewDayPane::NewDayPane(int did,QDate* day) : QFrame()
{
    QVBoxLayout* layout = new QVBoxLayout();
    this->dayIndex = did;
    this->thisDate = day;
    QString titleLabel = "Day "+ QString::number(did)+": "+this->thisDate->toString("ddd yyyy.MM.dd");
    TTextLabel* titleL = new TTextLabel(titleLabel);
    layout->addWidget(titleL);

    int id = 2;
    TComboWithAddField* country = new TComboWithAddField("Destination Country","Other Country Not In The List",id);
    layout->addWidget(country);

    TComboWithAddField* city = new TComboWithAddField("Destination City","Other Country Not In The List",id+1);
    layout->addWidget(city);

    EventPane* svp = new EventPane();
    layout->addWidget(svp);

    this->addNew = new TButton("Add An Event",450);
    layout->addWidget(this->addNew);

    this->setLayout(layout);
}
