#include "addnewtripframe.h"

AddNewTripFrame::AddNewTripFrame(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout();

    QPalette* mainp = new QPalette();
    mainp->setColor(QPalette::Background,*CommonColor::LIGHT_BLACK_64);
    // to automatically fill the background
    this->setAutoFillBackground(true);
    this->setPalette(*mainp);

    QPalette* newDesP = new QPalette();
    newDesP->setColor(QPalette::Background,*CommonColor::LIGHT_BLACK_64);
    newDesP->setColor(QPalette::WindowText,*CommonColor::LIGHT_GREEN);
    QLabel* newDesL = new QLabel(tr("New Destination"));
    newDesL->setAutoFillBackground(true);
    newDesL->setPalette(*newDesP);
    newDesL->setFixedHeight(150);
    newDesL->setAlignment(Qt::AlignCenter);
    QFont* ftitle = new QFont();
    ftitle->setBold(true);
    ftitle->setPointSize(25);
    newDesL->setFont(*ftitle);
    mainLayout->addWidget(newDesL);

    QScrollArea* scroll=new QScrollArea();
    QWidget* list = new QWidget();
    scroll->setWidget(list);
    scroll->setWidgetResizable(true);
    list->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    mainLayout->addWidget(scroll);

    QVBoxLayout* listLayout = new QVBoxLayout();
    list->setLayout(listLayout);

    this->homeInfoPane = new HomeInfoPane();
    listLayout->addWidget(this->homeInfoPane);

    NewDayPane* ndp = new NewDayPane();
    listLayout->addWidget(ndp);

    QWidget* buttons = new QWidget();
    QGridLayout* buttonLayout = new QGridLayout();
    buttons->setLayout(buttonLayout);

    this->addNewDayB = new TButton("Add A Day");
    buttonLayout->addWidget(this->addNewDayB,0,0);

    this->saveAllB = new TButton("Save All and Close");
    buttonLayout->addWidget(this->saveAllB,0,1);

    this->cancel = new TButton("Cancel and Close");
    buttonLayout->addWidget(this->cancel,0,2);

    mainLayout->addWidget(buttons);

    // QLabel* margin = new QLabel();
    // mainLayout->addWidget(margin);
    this->setLayout(mainLayout);
}

AddNewTripFrame::~AddNewTripFrame(){

}
