#include "homeinfopane.h"

HomeInfoPane::HomeInfoPane(QWidget *parent) : QFrame(parent)
{
    QVBoxLayout* layout = new QVBoxLayout();

    this->setFrameStyle(QFrame::StyledPanel|QFrame::Plain);
    this->setLayout(layout);

    // type = 0 indicates that the combobox handels country information
    this->country = new TComboWithAddField("Home Country ","Other Country Not in the List",0);
    layout->addWidget(country);
    // type = 1 indicates that handels city information
    this->city = new TComboWithAddField("Home City ","Other City Not in the List",1);
    layout->addWidget(city);

    QWidget* date = new QWidget();
    QVBoxLayout* dl = new QVBoxLayout();
    TTextLabel* startDateL = new TTextLabel(tr("Start Date"));
    dl->addWidget(startDateL);
    this->startDatePicker = new QCalendarWidget();
    this->startDatePicker->setGridVisible(true);
    dl->addWidget(this->startDatePicker);
    date->setLayout(dl);
    layout->addWidget(date);
}
