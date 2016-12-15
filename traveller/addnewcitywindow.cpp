#include "addnewcitywindow.h"

AddNewCityWindow::AddNewCityWindow(QWidget* parent,int type):\
    QDialog(parent,Qt::CustomizeWindowHint|Qt::WindowTitleHint),type{type}
{
    QRect screct = QApplication::desktop()->screenGeometry();
    int sch = screct.height();
    int scw = screct.width();
    int windowh = StaticData::NORMAL_TEXT_HEIGHT*5;
    int windoww = int(scw*StaticData::ADD_TRIP_WIDONW_WIDTH_RATIO);
    this->setGeometry(int((scw-windoww)/2),int((sch-windowh)/2),windoww,windowh);
    this->setMinimumWidth(windoww);
    this->setMinimumHeight(windowh);
    // delet ethe window is closed
    this->setAttribute(Qt::WA_DeleteOnClose);

    lay = new QVBoxLayout();
    this->setLayout(lay);

    country = new TComboWithAddField("Destination Country","Other Country",0);
    this->lay->addWidget(country);
    city = new TComboWithAddField("Destination City","Other City",1);
    this->lay->addWidget(city);

    glay = new QGridLayout();
    buttonGroup = new QWidget();
    buttonGroup->setLayout(glay);
    lay->addWidget(buttonGroup);
    save = new TButton("Save");
    glay->addWidget(this->save,0,0);
    cancle = new TButton("Cancle");
    glay->addWidget(cancle,0,1);

    // connect save and close signal from save button to this.save
    connect(save,SIGNAL(clicked(bool)),this,SLOT(saveAndExitSlot()));
    // connect cancle and close signal from from cancle button to this.cancle
    connect(cancle,SIGNAL(clicked(bool)),this,SLOT(cancleAndExitSlot()));

    style=StyleSheetCeator::setBackgroundColor(style,StaticData::LIGHT_GRAY);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(style));
}

void AddNewCityWindow::saveAndExitSlot(){
    emit this->closeAddCityWindowSig(AddNewCityWindow::SAVE_AND_EXIT,type);
}

void AddNewCityWindow::cancleAndExitSlot(){
    emit this->closeAddCityWindowSig(AddNewCityWindow::CANCLE_AND_EXIT,type);
}

void AddNewCityWindow::windowClosePermittedSlot(){
    QWidget::close();
}

int AddNewCityWindow::getType(){
    return this->type;
}
