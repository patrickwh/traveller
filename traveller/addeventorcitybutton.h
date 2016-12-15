#ifndef ADDEVENTBUTTON_H
#define ADDEVENTBUTTON_H

#include <QPushButton>
#include "staticdata.h"
#include "stylesheetceator.h"

class AddEventOrCityButton : public QPushButton
{
    Q_OBJECT

private:
    int tripid;
    int dayid;
    int cityid;
    int type;
    void init();
public:
    const static int TYPE_EVENT = 0;
    const static int TYPE_CITY = 1;
    const static int TYPE_DAY = 2;
    AddEventOrCityButton(int tid,QWidget* parent = nullptr);
    AddEventOrCityButton(int tid,int did,QWidget* parent = nullptr);
    AddEventOrCityButton(int tid,int did,int cid,QWidget* parent = nullptr);  
    QHash<QString,QString> style;

signals:
    void buttonClickedTypeEvent(int,int,int);
    void buttonClickedTypeCity(int,int);
    void buttonClickedTypeDay(int);
private slots:
    void clickedSlot(bool isClicked);
};

#endif // ADDEVENTBUTTON_H
