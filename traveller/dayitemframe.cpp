#include "dayitemframe.h"

DayItemFrame::DayItemFrame(int tid,int did,QString color):QFrame(),tripid{tid},dayid{did}
{
    this->lay = new QVBoxLayout();
    this->lay->setAlignment(Qt::AlignTop);
    this->setLayout(this->lay);
    this->setFixedWidth(StaticData::DAY_ITEM_FRAME_WIDTH);
    this->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);

    title = new DayTitleFrame(tid,did);
    this->lay->addWidget(title);

    scroll = new QScrollArea();
    listf = new QWidget();
    scroll->setWidget(listf);
    scroll->horizontalScrollBar()->setEnabled(false);
    scroll->horizontalScrollBar()->setVisible(false);
    listLay = new QVBoxLayout();
    listf->setLayout(listLay);
    scroll->setWidgetResizable(true);
    listf->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lay->addWidget(scroll);

    style=StyleSheetCeator::setBackgroundColor(this->style,color);
    style=StyleSheetCeator::setPadding(style,0,0,0,0);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(this->style));
}

DayItemFrame::~DayItemFrame(){
    delete this->title;
    this->title = nullptr;
    delete this->lay;
    this->lay = nullptr;
}

void DayItemFrame::changeColor(QString color){
    this->style=StyleSheetCeator::setBackgroundColor(this->style,color);
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(this->style));
    int num = listLay->count();
    for(int i =0;i<num-1;i++){
        ((CityItemFrame*)this->listLay->itemAt(i)->widget())->changeColor(color);
    }
}
