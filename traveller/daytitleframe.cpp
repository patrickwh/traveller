#include "daytitleframe.h"

DayTitleFrame::DayTitleFrame(int tid,int did,QWidget *parent) : QFrame(parent),tripid{tid},dayid{did}
{
    lay = new QHBoxLayout();
    this->setLayout(lay);
    date = new TTextLabel("test",StaticData::SMALL_TEXT_SIZE,StaticData::NORMAL_TEXT_HEIGHT);
    lay->addWidget(date);

    deleteb = new TButton(StaticData::DELETE_BUTTON_HEIGHT,StaticData::DELETE_BUTTON_HEIGHT);
    QIcon icon = QIcon("..\\icons\\red-cross.png");
    deleteb->setIcon(icon);
    deleteb->setEnabled(false);
    deleteb->setVisible(false);

    // this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    connect(deleteb,SIGNAL(clicked(bool)),this,SLOT(deleteClickedSlot(bool)));
}

void DayTitleFrame::enterEvent(QEvent *event){
     lay->insertWidget(1,deleteb);
     deleteb->setEnabled(true);
     deleteb->setVisible(true);
}

void DayTitleFrame::leaveEvent(QEvent *event){
    lay->removeWidget(deleteb);
    deleteb->setEnabled(false);
    deleteb->setVisible(false);
}

void DayTitleFrame::deleteClickedSlot(bool c){
    emit this->dayDeleteClickedSig(dayid);
}
