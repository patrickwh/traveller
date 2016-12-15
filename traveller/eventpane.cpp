#include "eventpane.h"

EventPane::EventPane(int id) : QFrame()
{
    QVBoxLayout* layout = new QVBoxLayout();
    this->eid = id;

    QString eventTitle = "Event "+QString::number(id)+" :";
    TTextLabel* titleL = new TTextLabel(eventTitle);
    layout->addWidget(titleL);

    TComboWithCost* cwc = new TComboWithCost(0);
    layout->addWidget(cwc);

    TComboWithCost* t = new TComboWithCost(1);
    layout->addWidget(t);

    this->setLayout(layout);
}
