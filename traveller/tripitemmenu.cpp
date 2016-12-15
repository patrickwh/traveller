#include "tripitemmenu.h"

TripItemMenu::TripItemMenu(QWidget *parent):QMenu(parent)
{
    QIcon editi = QIcon(StaticData::EDIT_ICON_PATH);
    this->editAct = new QAction(editi,"Edit Trip",parent);
    this->addAction(editAct);
    QIcon deletei = QIcon(StaticData::DELETE_ICON_PATH);
    this->deleteAct = new QAction(deletei,"Delete Trip",parent);
    this->addAction(deleteAct);
    this->style = StyleSheetCeator::setTextFont(this->style,StaticData::NORMAL_TEXT_SIZE,"bold");
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(this->style));
}
