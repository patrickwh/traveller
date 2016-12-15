#include "addneweventwindow.h"

AddNewEventWindow::AddNewEventWindow(QWidget* parent,int type):\
    QDialog(parent,Qt::CustomizeWindowHint|Qt::WindowTitleHint),type{type}
{
    QRect screct = QApplication::desktop()->screenGeometry();
    int sch = screct.height();
    int scw = screct.width();
    int windowh = StaticData::NORMAL_TEXT_HEIGHT*6;
    int windoww = int(scw*StaticData::ADD_TRIP_WIDONW_WIDTH_RATIO);
    this->setGeometry(int((scw-windoww)/2),int((sch-windowh)/2),windoww,windowh);
    this->setMinimumWidth(windoww);
    this->setMinimumHeight(windowh);
    // delet ethe window is closed
    this->setAttribute(Qt::WA_DeleteOnClose);

    lay = new QVBoxLayout();
    this->setLayout(lay);

    event = new TComboWithCost(TComboWithCost::TYPE_DEST);
    lay->addWidget(event);
    transport = new TComboWithCost(TComboWithCost::TYPE_TRANS);
    lay->addWidget(transport);

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

void AddNewEventWindow::saveAndExitSlot(){
    emit this->windowClosedSig(AddNewEventWindow::SAVE_AND_EXIT,type);
}

void AddNewEventWindow::cancleAndExitSlot(){
    emit this->windowClosedSig(AddNewEventWindow::CANCLE_AND_EXIT,type);
}

void AddNewEventWindow::closePermittedSlot(){
    QWidget::close();
}

AddNewEventWindow::~AddNewEventWindow(){
    delete event;
    event = nullptr;
    delete transport;
    transport = nullptr;
    delete lay;
    lay = nullptr;
    delete save;
    save = nullptr;
    delete cancle;
    cancle = nullptr;
    delete glay;
    glay = nullptr;
    delete buttonGroup;
    buttonGroup = nullptr;
}
