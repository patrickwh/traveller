#include "eventitemframe.h"

EventItemFrame::EventItemFrame(int tid,int did,int cid,int eid,QString tc):\
    QFrame(),dayid{did},cityid{cid},eventid{eid},tripid{tid},tcolor{tc}
{
    this->infolay = new QVBoxLayout();
    lay = new QHBoxLayout;
    this->setLayout(lay);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    deleteb = new TButton(StaticData::DELETE_BUTTON_HEIGHT,StaticData::DELETE_BUTTON_HEIGHT);
    QIcon icon = QIcon("..\\icons\\red-cross.png");
    deleteb->setIcon(icon);
    deleteb->setEnabled(false);
    deleteb->setVisible(false);

    info = new QWidget();
    info->setLayout(infolay);
    event = new TTextLabel("test",StaticData::SMALL_TEXT_SIZE,StaticData::SMALL_TEXT_HEIGHT,false);
    infolay->addWidget(event);
    transport = new TTextLabel("test",StaticData::SMALL_TEXT_SIZE,StaticData::SMALL_TEXT_HEIGHT,false);
    infolay->addWidget(transport);
    QHash<QString,QString> s;
    s = StyleSheetCeator::setBorder(s,"none");
    info->setStyleSheet(StyleSheetCeator::getStyleSeetString(s));

    lay->addWidget(info);

    this->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
    this->setFixedWidth(StaticData::EVENT_FRAME_WIDTH);
    style = StyleSheetCeator::setValue(style,"border-color","#"+tc);
    style = StyleSheetCeator::setValue(style,"border-style","solid");
    style = StyleSheetCeator::setValue(style,"border-width","2px");
    style = StyleSheetCeator::setPadding(style,0,0,0,0);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(style));
    lay->setContentsMargins(0,0,0,0);
    lay->setSpacing(0);

    connect(deleteb,SIGNAL(clicked(bool)),this,SLOT(deleteClickedSlot(bool)));
}

EventItemFrame::~EventItemFrame(){
    delete this->event;
    this->event = nullptr;
    delete this->transport;
    this->transport = nullptr;
    delete this->infolay;
    this->infolay = nullptr;
}

void EventItemFrame::mouseDoubleClickEvent(QMouseEvent* e){
    emit this->eventFrameDoubleClickedSig(dayid,cityid,eventid);
}

void EventItemFrame::enterEvent(QEvent *event){
     style = StyleSheetCeator::setValue(style,"border-color","white");
     this->setStyleSheet(StyleSheetCeator::getStyleSeetString(style));
     lay->insertWidget(1,deleteb);
     deleteb->setEnabled(true);
     deleteb->setVisible(true);
}

void EventItemFrame::leaveEvent(QEvent *event){
    style = StyleSheetCeator::setValue(style,"border-color","#"+tcolor);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(style));
    lay->removeWidget(deleteb);
    deleteb->setEnabled(false);
    deleteb->setVisible(false);
}


void EventItemFrame::deleteClickedSlot(bool c){
    emit this->deleteEventClickedSig(dayid,cityid,eventid);
}

void EventItemFrame::changeColor(QString tc){
    tcolor = tc;
    style = StyleSheetCeator::setValue(style,"border-color","#"+tcolor);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(style));
}


