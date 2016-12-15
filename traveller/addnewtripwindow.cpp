#include "addnewtripwindow.h"

AddNewTripWindow::AddNewTripWindow(QWidget* parent,int type):QDialog(parent,Qt::CustomizeWindowHint|Qt::WindowTitleHint),type{type}
{
    QRect screct = QApplication::desktop()->screenGeometry();
    int sch = screct.height();
    int scw = screct.width();
    int windowh = int(sch*StaticData::ADD_TRIP_WIDONW_HEIGHT_RATIO);
    int windoww = int(scw*StaticData::ADD_TRIP_WIDONW_WIDTH_RATIO);
    this->setGeometry(int((scw-windoww)/2),int((sch-windowh)/2),windoww,windowh);
    this->setMinimumWidth(windoww);
    this->setMinimumHeight(windowh);
    // delet ethe window is closed
    this->setAttribute(Qt::WA_DeleteOnClose);

    this->lay = new QVBoxLayout();
    this->setLayout(lay);

    this->nameAndColor = new QWidget();
    this->nameAndColorLay = new QGridLayout();
    this->nameAndColor->setLayout(this->nameAndColorLay);
    this->lay->addWidget(nameAndColor);

    this->namel = new TTextLabel("Trip Name");
    this->nameAndColorLay->addWidget(namel,0,0);
    this->name = new TLineEdit("Trip Name Here");
    this->nameAndColorLay->addWidget(name,0,1);
    this->colorl = new TTextLabel("Theme Color");
    this->nameAndColorLay->addWidget(colorl,0,2);
    this->colorCombo = new TComboBox(StaticData::COLOR_SELECT_COMBOBOX);
    this->nameAndColorLay->addWidget(colorCombo,0,3);
    this->nameAndColorLay->setColumnStretch(1,1);
    this->nameAndColorLay->setColumnStretch(3,1);

    this->hip = new HomeInfoPane();
    lay->addWidget(hip);

    this->glay = new QGridLayout();
    this->buttonGroup = new QWidget();
    this->buttonGroup->setLayout(glay);
    this->lay->addWidget(this->buttonGroup);
    this->save = new TButton("Save");
    glay->addWidget(this->save,0,0);
    this->cancle = new TButton("Cancle");
    glay->addWidget(this->cancle,0,1);


    this->style=StyleSheetCeator::setBackgroundColor(this->style,StaticData::LIGHT_GRAY);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(this->style));

    // connect save and close signal from save button to this.save
    connect(this->save,SIGNAL(clicked(bool)),this,SLOT(saveClickedSlot()));
    // connect cancle and close signal from from cancle button to this.cancle
    connect(this->cancle,SIGNAL(clicked(bool)),this,SLOT(cancleClickedSlot()));
}

void AddNewTripWindow::saveClickedSlot(){
    emit this->windowClosed(StaticData::SAVE_AND_CLOSE,this->type);
}

void AddNewTripWindow::cancleClickedSlot(){
    emit this->windowClosed(StaticData::CANCEL_AND_CLOSE,this->type);
}

void AddNewTripWindow::closePermittedSlot(){
    QWidget::close();
}

AddNewTripWindow::~AddNewTripWindow(){
    delete hip;
    hip = nullptr;
    delete save;
    save = nullptr;
    delete cancle;
    cancle = nullptr;
    delete colorCombo;
    colorCombo = nullptr;
    delete name;
    name = nullptr;
    delete namel;
    namel = nullptr;
    delete colorl;
    colorl = nullptr;
    delete nameAndColorLay;
    nameAndColorLay = nullptr;
    delete nameAndColor;
    nameAndColor = nullptr;
    delete glay;
    glay = nullptr;
    delete buttonGroup;
    buttonGroup = nullptr;
    delete lay;
    lay = nullptr;
}
