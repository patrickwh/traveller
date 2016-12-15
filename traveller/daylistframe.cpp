#include "daylistframe.h"

DayListFrame::DayListFrame():QFrame()
{
    mainLay = new QVBoxLayout();
    this->setLayout(mainLay);
    scroll = new QScrollArea(this);
    mainLay->addWidget(scroll);
    listf = new QWidget();
    scroll->setWidget(listf);
    lay = new QHBoxLayout();
    lay->setAlignment(Qt::AlignLeft);
    scroll->setWidgetResizable(true);
    scroll->verticalScrollBar()->setEnabled(false);
    scroll->verticalScrollBar()->setVisible(false);
    listf->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    listf->setLayout(lay);
}

DayListFrame::~DayListFrame(){
    delete lay;
    lay = nullptr;
    delete listf;
    listf = nullptr;
    delete scroll;
    scroll = nullptr;
    delete mainLay;
    mainLay = nullptr;
}
