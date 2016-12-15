#include "travellermainwindow.h"
#include "ui_travellermainwindow.h"

TravellerMainWindow::TravellerMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TravellerMainWindow)
{
    ui->setupUi(this);

    QRect screct = QApplication::desktop()->screenGeometry();
    int sch = screct.height();
    int scw = screct.width();
    int windowh = int(sch*StaticData::MAIN_WINDOW_WIDTH_RATIO);
    int windoww = int(scw*StaticData::MAIN_WINDOW_HEIGHT_RATIO);
    this->setGeometry(int((scw-windoww)/2),int((sch-windowh)/2),windoww,windowh);
    this->setMinimumWidth(windoww);
    this->setMinimumHeight(windowh);

    this->tabPane = new QTabWidget;
    this->welconf = new WelcomeFrame();
    this->addnewf = new AddNewTripFrame();
    this->tabPane->addTab(this->welconf,tr("WELCOME"));
    // this->tabPane->addTab(this->addnewf,tr("AddANewTrip"));

    QWidget* mainWidget = new QWidget();

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(this->tabPane);
    mainWidget->setLayout(mainLayout);

    this->setCentralWidget(mainWidget);

    //***********************************
}

TravellerMainWindow::~TravellerMainWindow()
{
    delete ui;
    delete this->welconf;
    delete this->addnewf;
    delete this->tabPane;
}

void TravellerMainWindow::initialization(){
    emit this->registerComboGroupSig(this->addnewf->homeInfoPane->country);
    emit this->registerComboGroupSig(this->addnewf->homeInfoPane->city);
    emit this->getCountryListSig();
    QString hcl=this->addnewf->homeInfoPane->country->combo->currentText();
    emit this->addnewf->homeInfoPane->country->combo->currentIndexChanged(hcl);
}
