#include "welcomeframe.h"

WelcomeFrame::WelcomeFrame(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout();
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,1);
    layout->setColumnStretch(3,1);
    setAutoFillBackground(true);
    m = 4;
    setLayout(layout);
}
