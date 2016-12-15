#include "tcombowithcost.h"

TComboWithCost::TComboWithCost(int type) : QWidget()
{
    QString label = "Transportation";
    QString hint = "Enter Name";
    costValildator = new QDoubleValidator(0,100000,2);
    if(type==TComboWithCost::TYPE_DEST) label = "Event Type";
    QGridLayout* layout = new QGridLayout();
    TTextLabel* eventTypeL = new TTextLabel(label);
    eventTypeL->setFixedWidth(400);
    layout->addWidget(eventTypeL,0,0);

    this->type = new TComboBox();
    layout->addWidget(this->type,0,1);

    this->name = new TLineEdit(hint);
    layout->addWidget(this->name,0,2);

    TTextLabel* costL = new TTextLabel("Cost");
    costL->setFixedWidth(150);
    layout->addWidget(costL,0,3);

    this->currency = new TComboBox();
    layout->addWidget(this->currency,0,4);

    this->amount = new TLineEdit("Amount",200);
    this->amount->setValidator(costValildator);
    this->amount->setText("0.00");
    layout->addWidget(this->amount,0,5);

    layout->setColumnStretch(1,2);
    layout->setColumnStretch(2,3);
    layout->setColumnStretch(4,1);

    this->setLayout(layout);
}
