#include "citytitleframe.h"

CityTitleFrame::CityTitleFrame(int tid,int did,int cid,QString tc, QWidget *parent) : \
    QFrame(parent),tripid{tid},dayid{did},cityid{cid},tcolor{tc}
{
    lay = new QHBoxLayout();
    this->setLayout(lay);
    cityName = new TTextLabel("test",StaticData::SMALL_TEXT_SIZE,StaticData::NORMAL_TEXT_HEIGHT);
    lay->addWidget(cityName);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    deleteb = new TButton(StaticData::DELETE_BUTTON_HEIGHT,StaticData::DELETE_BUTTON_HEIGHT);
    QIcon icon = QIcon("..\\icons\\red-cross.png");
    deleteb->setIcon(icon);
    deleteb->setEnabled(false);
    deleteb->setVisible(false);

    style = StyleSheetCeator::setValue(style,"border-color","#"+tc);
    style = StyleSheetCeator::setValue(style,"border-style","solid");
    style = StyleSheetCeator::setValue(style,"border-width","2px");
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(style));

    connect(deleteb,SIGNAL(clicked(bool)),this,SLOT(deleteClickedSlot(bool)));
}

void CityTitleFrame::enterEvent(QEvent *event){
     style = StyleSheetCeator::setValue(style,"border-color","white");
     this->setStyleSheet(StyleSheetCeator::getStyleSeetString(style));
     lay->insertWidget(1,deleteb);
     deleteb->setEnabled(true);
     deleteb->setVisible(true);
}

void CityTitleFrame::leaveEvent(QEvent *event){
    style = StyleSheetCeator::setValue(style,"border-color","#"+tcolor);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(style));
    lay->removeWidget(deleteb);
    deleteb->setEnabled(false);
    deleteb->setVisible(false);
}

void CityTitleFrame::deleteClickedSlot(bool c){
    emit this->cityItemDeleteClickedSig(dayid,cityid);
}

void CityTitleFrame::mouseDoubleClickEvent(QMouseEvent *e){
    emit this->cityItemFrameDoubleClickedSig(dayid,cityid);
}

void CityTitleFrame::changeColor(QString tc){
    tcolor = tc;
    style = StyleSheetCeator::setValue(style,"border-color","#"+tcolor);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(style));
}
