#ifndef DAYITEMFRAME_H
#define DAYITEMFRAME_H

#include <QFrame>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include "daytitleframe.h"
#include "staticdata.h"
#include "stylesheetceator.h"
#include "cityitemframe.h"

class DayItemFrame : public QFrame
{
    Q_OBJECT

public:
    int tripid;
    int dayid;
public:
    DayItemFrame(int tid,int did,QString color);
    ~DayItemFrame();
    QVBoxLayout* lay;
    DayTitleFrame* title;
    QScrollArea* scroll;
    QWidget* listf;
    QVBoxLayout* listLay;
    QHash<QString,QString> style;
    void changeColor(QString color);
};

#endif // DAYITEMFRAME_H
